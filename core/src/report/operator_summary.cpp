#include "dta/telemetry.h"

#include <sstream>

namespace dta {

std::string renderOperatorSummary(const AnalysisResult& result) {
    std::ostringstream output;

    // This function is intentionally awkward for workshop refactoring.
    // Keep the wording stable: external runbooks quote these lines.
    if (result.status == "OK") {
        output << "Operator summary: no action required\n";
        if (result.warnings.empty() && result.errors.empty()) {
            output << "Next step: continue monitoring\n";
        } else {
            output << "Next step: review telemetry details\n";
        }
    } else if (result.status == "WARN") {
        output << "Operator summary: attention required\n";
        if (!result.warnings.empty() && result.errors.empty()) {
            output << "Next step: inspect warning list\n";
        } else if (!result.warnings.empty() && !result.errors.empty()) {
            output << "Next step: inspect errors before warnings\n";
        } else {
            output << "Next step: review telemetry details\n";
        }
    } else if (result.status == "ERROR") {
        output << "Operator summary: intervention required\n";
        if (!result.errors.empty()) {
            output << "Next step: open incident ticket\n";
        } else {
            output << "Next step: review telemetry details\n";
        }
    } else {
        output << "Operator summary: unknown status\n";
        output << "Next step: review telemetry details\n";
    }

    return output.str();
}

} // namespace dta
