module;

#include "catch2/catch_test_macros.hpp"
#include <limits>
#include <iostream>

export module test.decimal;

import nhtypes;

using namespace nh;

#define Make_Safe_Decimal_Tests(Type, CType)                             \
    TEST_CASE("Test " #Type) {                                           \
        constexpr CType Min = std::numeric_limits<CType>::min();         \
        constexpr CType Max = std::numeric_limits<CType>::max();         \
        constexpr CType Inf = std::numeric_limits<CType>::infinity();    \
        constexpr auto  NaN = NAN;                                       \
                                                                         \
                                                                         \
        REQUIRE_NOTHROW(Type(Max));                                      \
        REQUIRE_NOTHROW(Type(Min));                                      \
    }

Make_Safe_Decimal_Tests(nh::SafeFloat, float);

TEST_CASE("Test conversions") {
    Int16 i = 5;
    Float f = 2;
    Double d = 2;
    //double d = 2;
    auto a = i * f;
    std::cout << "Type: " << typeid(a.value).name() << std::endl;

}

