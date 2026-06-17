#include "dta/telemetry.h"
#include "test_support.h"

TEST_CASE(parser, parses_status_frame) {
    const auto result = dta::parseTelemetryLine(
        "device=sensor-17;type=STATUS;ts=2026-06-16T08:15:00Z;payload=ok;checksum=AB12;battery=0.87");

    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.frame.deviceId, "sensor-17");
    EXPECT_EQ(dta::toString(result.frame.type), "STATUS");
    EXPECT_EQ(result.frame.battery, 0.87);
}

TEST_CASE(parser, rejects_unknown_type) {
    const auto result = dta::parseTelemetryLine(
        "device=sensor-17;type=BOOT;ts=2026-06-16T08:15:00Z;payload=ok;checksum=AB12");

    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.errorCode, "UNKNOWN_TYPE");
}

TEST_CASE(parser, keeps_legacy_checksum_before_payload_behavior) {
    const auto result = dta::parseTelemetryLine(
        "device=sensor-17;type=STATUS;ts=2026-06-16T08:15:00Z;payload=;checksum=0000;battery=0.87");

    EXPECT_FALSE(result.isValid());
    EXPECT_EQ(result.errorCode, "CHECKSUM_MISMATCH");
}

TEST_CASE(parser, allows_heartbeat_without_payload) {
    const auto result = dta::parseTelemetryLine(
        "device=sensor-17;type=HEARTBEAT;ts=2026-06-16T08:15:00Z;payload=;checksum=AB12");

    EXPECT_TRUE(result.isValid());
}
