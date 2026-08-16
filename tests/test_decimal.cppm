module;

#include "catch2/catch_test_macros.hpp"
#include <limits>

export module test.decimal;

import nhtypes;

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


