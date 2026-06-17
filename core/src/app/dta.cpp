#include "dta/telemetry.h"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: dta <input-file>\n";
        return 2;
    }

    try {
        const auto parsed = dta::parseTelemetryFile(argv[1]);
        const auto analysis = dta::analyzeFrames(parsed);
        std::cout << dta::renderReport(analysis);
        return analysis.errors.empty() ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "dta: " << error.what() << '\n';
        return 2;
    }
}
