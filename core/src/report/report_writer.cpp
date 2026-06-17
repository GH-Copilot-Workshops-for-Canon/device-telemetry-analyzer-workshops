#include "dta/telemetry.h"

#include <sstream>

namespace dta {

std::string renderReport(const AnalysisResult& result) {
    std::ostringstream output;

    output << "Device: " << result.deviceId << '\n';
    output << "Status: " << result.status << '\n';
    output << "Warnings: " << result.warnings.size() << '\n';
    for (const auto& warning : result.warnings) {
        output << "- " << warning << '\n';
    }
    output << "Errors: " << result.errors.size() << '\n';
    for (const auto& error : result.errors) {
        output << "- " << error << '\n';
    }
    output << dta::renderOperatorSummary(result);

    return output.str();
}

} // namespace dta
