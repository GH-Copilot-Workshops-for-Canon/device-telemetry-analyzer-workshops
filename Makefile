CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Icore/include
BUILD_DIR := build
BUILD_STAMP := $(BUILD_DIR)/.dir
CORE_SRCS := \
	core/src/parser/telemetry_parser.cpp \
	core/src/analyzer/telemetry_analyzer.cpp \
	core/src/analyzer/maintenance_window.cpp \
	core/src/report/report_writer.cpp \
	core/src/report/operator_summary.cpp
APP_SRCS := $(CORE_SRCS) core/src/app/dta.cpp
TEST_SRCS := $(CORE_SRCS) core/tests/parser_tests.cpp core/tests/analyzer_tests.cpp core/tests/report_tests.cpp core/tests/maintenance_window_tests.cpp core/tests/test_main.cpp

.PHONY: build test test-parser golden scenario-empty-payload check-env clean cli

build: $(BUILD_DIR)/dta

$(BUILD_STAMP):
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_STAMP)

$(BUILD_DIR)/dta: $(APP_SRCS) | $(BUILD_STAMP)
	$(CXX) $(CXXFLAGS) $(APP_SRCS) -o $@

$(BUILD_DIR)/tests: $(TEST_SRCS) | $(BUILD_STAMP)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $@

test: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests

test-parser: $(BUILD_DIR)/tests
	./$(BUILD_DIR)/tests --filter parser

golden: build
	python3 tools/golden.py

scenario-empty-payload: build
	python3 tools/scenario_runner.py empty-payload

check-env:
	python3 tools/check-env.py

cli:
	dotnet build cli/DeviceTelemetry.Cli/DeviceTelemetry.Cli.csproj

clean:
	rm -rf $(BUILD_DIR)
	rm -f fixtures/actual/*.report.txt
