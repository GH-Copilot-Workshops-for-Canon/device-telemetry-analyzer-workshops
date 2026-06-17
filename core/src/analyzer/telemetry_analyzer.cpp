#include "dta/telemetry.h"

#include <algorithm>

namespace dta {

AnalysisResult analyzeFrames(const std::vector<ParseResult>& parsedFrames) {
    AnalysisResult result;
    result.status = "OK";

    bool hasStatusFrame = false;
    bool hasMetricFrame = false;
    bool hasLowBattery = false;

    for (const auto& parsed : parsedFrames) {
        if (result.deviceId.empty() && !parsed.frame.deviceId.empty()) {
            result.deviceId = parsed.frame.deviceId;
        }

        if (!parsed.isValid()) {
            result.errors.push_back(parsed.errorCode + ": " + parsed.message);
            result.status = "ERROR";
            continue;
        }

        if (parsed.frame.type == FrameType::Status) {
            hasStatusFrame = true;
            if (parsed.frame.battery >= 0.0 && parsed.frame.battery < 0.20) {
                hasLowBattery = true;
            }
        }

        if (parsed.frame.type == FrameType::Metric) {
            hasMetricFrame = true;
            if (parsed.frame.metricName == "temperature" && parsed.frame.metricValue > 70.0) {
                result.warnings.push_back("HIGH_TEMPERATURE: temperature over threshold");
            }
        }

        if (parsed.frame.type == FrameType::Error) {
            result.status = "ERROR";
            result.errors.push_back(parsed.frame.errorCode + ": device reported " + parsed.frame.severity);
        }
    }

    if (result.deviceId.empty()) {
        result.deviceId = "unknown";
    }

    if (hasLowBattery) {
        result.warnings.push_back("LOW_BATTERY: battery below 20%");
        if (result.status != "ERROR") {
            result.status = "WARN";
        }
    }

    // Historical coupling: this warning exists only when status and metric frames
    // are both present in one input file. It is intentionally easy to break.
    if (hasStatusFrame && hasMetricFrame && result.status != "ERROR") {
        result.warnings.push_back("COMBINED_SIGNAL: status and metrics observed together");
        result.status = "WARN";
    }

    if (!result.errors.empty()) {
        result.status = "ERROR";
    }

    std::sort(result.warnings.begin(), result.warnings.end());
    return result;
}

} // namespace dta
