module;

#include "catch2/catch_test_macros.hpp"
#include <sstream>

export module test.stream;

import nhtypes;
import nhtypes.stream;

using namespace nh;

TEST_CASE("stream types") {

    Int8 i32 = 42;

    std::stringstream ss;
    ss << i32;
}
