#include "dta/telemetry.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace dta {
namespace {

std::unordered_map<std::string, std::string> parseFields(const std::string& line) {
    std::unordered_map<std::string, std::string> fields;
    std::stringstream stream(line);
    std::string part;

    while (std::getline(stream, part, ';')) {
        const auto separator = part.find('=');
        if (separator == std::string::npos) {
            continue;
        }
        fields[part.substr(0, separator)] = part.substr(separator + 1);
    }

    return fields;
}

FrameType parseType(const std::string& value) {
    if (value == "STATUS") return FrameType::Status;
    if (value == "ERROR") return FrameType::Error;
    if (value == "METRIC") return FrameType::Metric;
    if (value == "HEARTBEAT") return FrameType::Heartbeat;
    return FrameType::Unknown;
}

std::string fieldOrEmpty(const std::unordered_map<std::string, std::string>& fields, const std::string& key) {
    const auto it = fields.find(key);
    return it == fields.end() ? "" : it->second;
}

double numberOrDefault(const std::string& value, double fallback) {
    if (value.empty()) {
        return fallback;
    }

    try {
        return std::stod(value);
    } catch (const std::exception&) {
        return fallback;
    }
}

bool checksumLooksValid(const std::string& checksum) {
    return checksum.size() == 4 && checksum != "0000";
}

} // namespace

ParseResult parseTelemetryLine(const std::string& line) {
    const auto fields = parseFields(line);
    ParseResult result;

    result.frame.deviceId = fieldOrEmpty(fields, "device");
    result.frame.type = parseType(fieldOrEmpty(fields, "type"));
    result.frame.timestamp = fieldOrEmpty(fields, "ts");
    result.frame.payload = fieldOrEmpty(fields, "payload");
    result.frame.checksum = fieldOrEmpty(fields, "checksum");
    result.frame.battery = numberOrDefault(fieldOrEmpty(fields, "battery"), -1.0);
    result.frame.metricName = fieldOrEmpty(fields, "metric");
    result.frame.metricValue = numberOrDefault(fieldOrEmpty(fields, "value"), 0.0);
    result.frame.metricUnit = fieldOrEmpty(fields, "unit");
    result.frame.severity = fieldOrEmpty(fields, "severity");
    result.frame.errorCode = fieldOrEmpty(fields, "code");

    if (result.frame.deviceId.empty() || result.frame.timestamp.empty()) {
        result.status = ParseStatus::Malformed;
        result.errorCode = "MALFORMED_FRAME";
        result.message = "missing required device or timestamp";
        return result;
    }

    if (result.frame.type == FrameType::Unknown) {
        result.status = ParseStatus::UnknownType;
        result.errorCode = "UNKNOWN_TYPE";
        result.message = "unsupported telemetry frame type";
        return result;
    }

    // Legacy behavior: checksum is validated before payload presence.
    // This means an empty STATUS payload with checksum 0000 reports CHECKSUM_MISMATCH.
    if (!checksumLooksValid(result.frame.checksum)) {
        result.status = ParseStatus::InvalidChecksum;
        result.errorCode = "CHECKSUM_MISMATCH";
        result.message = "checksum did not match telemetry frame";
        return result;
    }

    if (result.frame.payload.empty() && result.frame.type != FrameType::Heartbeat) {
        result.status = ParseStatus::MissingPayload;
        result.errorCode = "EMPTY_PAYLOAD";
        result.message = "payload is required for this frame type";
        return result;
    }

    result.status = ParseStatus::Ok;
    result.errorCode = "";
    result.message = "ok";
    return result;
}

std::vector<ParseResult> parseTelemetryFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("cannot open telemetry input: " + path);
    }

    std::vector<ParseResult> results;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        results.push_back(parseTelemetryLine(line));
    }

    return results;
}

std::string toString(FrameType type) {
    switch (type) {
        case FrameType::Status: return "STATUS";
        case FrameType::Error: return "ERROR";
        case FrameType::Metric: return "METRIC";
        case FrameType::Heartbeat: return "HEARTBEAT";
        case FrameType::Unknown: return "UNKNOWN";
    }
    return "UNKNOWN";
}

std::string toString(ParseStatus status) {
    switch (status) {
        case ParseStatus::Ok: return "OK";
        case ParseStatus::InvalidChecksum: return "INVALID_CHECKSUM";
        case ParseStatus::MissingPayload: return "MISSING_PAYLOAD";
        case ParseStatus::UnknownType: return "UNKNOWN_TYPE";
        case ParseStatus::Malformed: return "MALFORMED";
    }
    return "MALFORMED";
}

} // namespace dta
