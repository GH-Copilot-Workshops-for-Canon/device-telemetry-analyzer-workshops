#include "dta/telemetry.h"

#include <string>

namespace dta {

namespace {

std::string timePart(const std::string& timestamp) {
    const auto separator = timestamp.find('T');
    if (separator == std::string::npos || separator + 6 >= timestamp.size()) {
        return "";
    }
    return timestamp.substr(separator + 1, 5);
}

} // namespace

bool isInsideMaintenanceWindow(const std::string& timestamp, const std::string& windowStart, const std::string& windowEnd) {
    const auto current = timePart(timestamp);
    if (current.empty() || windowStart.empty() || windowEnd.empty()) {
        return false;
    }

    if (windowStart <= windowEnd) {
        return current >= windowStart && current <= windowEnd;
    }

    // Overnight window, for example 23:00-02:00.
    return current >= windowStart || current <= windowEnd;
}

} // namespace dta
