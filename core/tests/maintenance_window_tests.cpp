#include "dta/telemetry.h"
#include "test_support.h"

TEST_CASE(maintenance, detects_regular_window) {
    EXPECT_TRUE(dta::isInsideMaintenanceWindow("2026-06-16T01:30:00Z", "01:00", "02:00"));
    EXPECT_FALSE(dta::isInsideMaintenanceWindow("2026-06-16T03:30:00Z", "01:00", "02:00"));
}

TEST_CASE(maintenance, detects_overnight_window) {
    EXPECT_TRUE(dta::isInsideMaintenanceWindow("2026-06-16T23:30:00Z", "23:00", "02:00"));
    EXPECT_TRUE(dta::isInsideMaintenanceWindow("2026-06-16T01:30:00Z", "23:00", "02:00"));
    EXPECT_FALSE(dta::isInsideMaintenanceWindow("2026-06-16T12:00:00Z", "23:00", "02:00"));
}
