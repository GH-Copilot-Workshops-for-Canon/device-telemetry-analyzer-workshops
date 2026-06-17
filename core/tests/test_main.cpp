#include "test_support.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string filter;
    if (argc == 3 && std::string(argv[1]) == "--filter") {
        filter = argv[2];
    }

    int failed = 0;
    int executed = 0;

    for (const auto& testCase : test::registry()) {
        if (!filter.empty() && testCase.group != filter) {
            continue;
        }

        ++executed;
        try {
            testCase.run();
            std::cout << "PASS " << testCase.group << "." << testCase.name << '\n';
        } catch (const std::exception& error) {
            ++failed;
            std::cerr << "FAIL " << testCase.group << "." << testCase.name << ": " << error.what() << '\n';
        }
    }

    std::cout << executed << " test(s), " << failed << " failure(s)\n";
    return failed == 0 ? 0 : 1;
}
