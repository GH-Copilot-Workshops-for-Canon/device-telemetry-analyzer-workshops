#pragma once

#include <string>
#include <vector>

namespace dta {

enum class FrameType {
    Status,
    Error,
    Metric,
    Heartbeat,
    Unknown
};

enum class ParseStatus {
    Ok,
    InvalidChecksum,
    MissingPayload,
    UnknownType,
    Malformed
};

struct TelemetryFrame {
    std::string deviceId;
    FrameType type = FrameType::Unknown;
    std::string timestamp;
    std::string payload;
    std::string checksum;
    double battery = -1.0;
    std::string metricName;
    double metricValue = 0.0;
    std::string metricUnit;
    std::string severity;
    std::string errorCode;
};

struct ParseResult {
    ParseStatus status = ParseStatus::Malformed;
    std::string errorCode;
    std::string message;
    TelemetryFrame frame;

    bool isValid() const {
        return status == ParseStatus::Ok;
    }
};

struct AnalysisResult {
    std::string deviceId;
    std::string status;
    std::vector<std::string> warnings;
    std::vector<std::string> errors;
};

ParseResult parseTelemetryLine(const std::string& line);
std::vector<ParseResult> parseTelemetryFile(const std::string& path);
AnalysisResult analyzeFrames(const std::vector<ParseResult>& parsedFrames);
std::string renderReport(const AnalysisResult& result);
std::string renderOperatorSummary(const AnalysisResult& result);
bool isInsideMaintenanceWindow(const std::string& timestamp, const std::string& windowStart, const std::string& windowEnd);

std::string toString(FrameType type);
std::string toString(ParseStatus status);

} // namespace dta
