#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace test {

struct Case {
    std::string group;
    std::string name;
    std::function<void()> run;
};

inline std::vector<Case>& registry() {
    static std::vector<Case> cases;
    return cases;
}

struct Registrar {
    Registrar(std::string group, std::string name, std::function<void()> run) {
        registry().push_back({std::move(group), std::move(name), std::move(run)});
    }
};

inline void fail(const std::string& message) {
    throw std::runtime_error(message);
}

template <typename T, typename U>
void expectEq(const T& actual, const U& expected, const std::string& expression) {
    if (!(actual == expected)) {
        throw std::runtime_error(expression);
    }
}

inline void expectTrue(bool value, const std::string& expression) {
    if (!value) {
        throw std::runtime_error(expression);
    }
}

inline void expectFalse(bool value, const std::string& expression) {
    if (value) {
        throw std::runtime_error(expression);
    }
}

} // namespace test

#define TEST_CASE(group, name) \
    static void group##_##name(); \
    static test::Registrar group##_##name##_registrar(#group, #name, group##_##name); \
    static void group##_##name()

#define EXPECT_EQ(actual, expected) test::expectEq((actual), (expected), "EXPECT_EQ failed: " #actual " != " #expected)
#define EXPECT_TRUE(value) test::expectTrue((value), "EXPECT_TRUE failed: " #value)
#define EXPECT_FALSE(value) test::expectFalse((value), "EXPECT_FALSE failed: " #value)
