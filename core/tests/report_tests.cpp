#include "dta/telemetry.h"
#include "test_support.h"

TEST_CASE(report, renders_stable_text_contract) {
    dta::AnalysisResult result;
    result.deviceId = "sensor-17";
    result.status = "WARN";
    result.warnings.push_back("LOW_BATTERY: battery below 20%");

    const auto report = dta::renderReport(result);

    EXPECT_TRUE(report.find("Device: sensor-17") != std::string::npos);
    EXPECT_TRUE(report.find("Status: WARN") != std::string::npos);
    EXPECT_TRUE(report.find("Warnings: 1") != std::string::npos);
    EXPECT_TRUE(report.find("Operator summary: attention required") != std::string::npos);
    EXPECT_TRUE(report.find("Next step: inspect warning list") != std::string::npos);
}

TEST_CASE(report, renders_error_operator_summary) {
    dta::AnalysisResult result;
    result.deviceId = "sensor-44";
    result.status = "ERROR";
    result.errors.push_back("E-017: device reported critical");

    const auto summary = dta::renderOperatorSummary(result);

    EXPECT_TRUE(summary.find("Operator summary: intervention required") != std::string::npos);
    EXPECT_TRUE(summary.find("Next step: open incident ticket") != std::string::npos);
}
