#pragma once

#include <iostream>

#define RUN_TEST(test_func) \
    if (test_func()) \
    { \
        std::cerr << "[FAILED] " << #test_func << std::endl; \
        return 1; \
    } \
    std::cerr << "[  OK  ] " << #test_func << std::endl;
