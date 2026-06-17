#include "dta/telemetry.h"
#include "test_support.h"

TEST_CASE(analyzer, reports_low_battery_warning) {
    const auto parsed = std::vector<dta::ParseResult>{
        dta::parseTelemetryLine("device=sensor-17;type=STATUS;ts=2026-06-16T08:15:00Z;payload=ok;checksum=AB12;battery=0.10")
    };

    const auto analysis = dta::analyzeFrames(parsed);

    EXPECT_EQ(analysis.deviceId, "sensor-17");
    EXPECT_EQ(analysis.status, "WARN");
    EXPECT_EQ(analysis.warnings.size(), static_cast<std::size_t>(1));
}

TEST_CASE(analyzer, weak_test_only_checks_that_error_exists) {
    const auto parsed = std::vector<dta::ParseResult>{
        dta::parseTelemetryLine("device=sensor-17;type=ERROR;ts=2026-06-16T08:16:00Z;payload=fault;checksum=AB12;severity=critical;code=E-017")
    };

    const auto analysis = dta::analyzeFrames(parsed);

    // Deliberately weak: this is used during the workshop to discuss shallow AI-generated tests.
    EXPECT_TRUE(!analysis.errors.empty());
}
