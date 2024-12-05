#pragma once
#include "AtominaTest.hpp"
#include "NetworkMessageFixture.hpp"

// All Attribute data types
using NetworkMessageTypes = ::testing::Types<
    char,
    unsigned char,
    short,
    unsigned short,
    int,
    unsigned int,
    float,
    long,
    unsigned long,
    double,
    long long,
    unsigned long long,
    std::string>;