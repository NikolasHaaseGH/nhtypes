module;

#include "catch2/catch_test_macros.hpp"
#include <limits>
#include <iostream>

export module test.integer;

import nhtypes;
import nhtypes.overflow;

using namespace nh;

TEST_CASE("Convert between integer types") {
  SECTION("Signed to signed") {
    Int8 fi8 = Int8();
    Int16 fi16 = Int8();
    Int32 fi32 = Int16();
    Int64 fi64 = Int32();
    Int64 fi64_ = Int64();

    SafeInt8 si8 = Int8();
    SafeInt16 si16 = Int8();
    SafeInt32 si32 = Int16();
    SafeInt64 si64 = Int32();
    SafeInt64 si64_ = Int64();

    SafeInt8 si8_ = SafeInt8();
    SafeInt16 si16_ = SafeInt8();
    SafeInt32 si32_ = SafeInt16();
    SafeInt64 si64__ = SafeInt32();
    SafeInt64 si64___ = SafeInt64();

    Int32 a = 2'147'483'64;
    UInt32 b = 1;
    OverflowAddition(a, b);
    //UInt32 maxi2 = maxi;
    std::cout << "HUNNY: "<< +maxi << std::endl;
  }

  SECTION("Unsigned to unsigned") {
    // Same classes as signed counterparts(only internal type is different)
    // and therefore identical behaviour as above.
  }

  SECTION("Unsigned to signed") {
    Int16 fi16 = UInt8();
    Int32 fi32 = UInt8();
    Int64 fi64 = UInt32();

    SafeInt16 si16 = UInt8();
    SafeInt32 si32 = UInt16();
    SafeInt64 si64 = UInt32();

    SafeInt16 si16_ = SafeUInt8();
    SafeInt32 si32_ = SafeUInt16();
    SafeInt64 si64_ = SafeUInt32();
  }
}

#define Integer_Arithmetic_Tests(Type, CType)                                  \
                                                                               \
  REQUIRE_NOTHROW(Type(Min));                                                  \
  REQUIRE_NOTHROW(Type(Max));                                                  \
                                                                               \
  REQUIRE_THROWS(Type(Min) -= 1);                                              \
  REQUIRE_THROWS(Type(Max) += 1);                                              \
  REQUIRE_THROWS(Type(Max) *= 2);                                              \
  REQUIRE_THROWS(Type(Max) /= 0);                                              \
                                                                               \
  REQUIRE_NOTHROW(Type(Min) += 1);                                             \
  REQUIRE_NOTHROW(Type(Max) -= 1);                                             \
  REQUIRE_NOTHROW(Type(1) *= 2);                                               \
  REQUIRE_NOTHROW(Type(Max) /= 1);                                             \
                                                                               \
  REQUIRE_NOTHROW(Type(Min)++);                                                \
  REQUIRE_NOTHROW(++Type(Min));                                                \
  REQUIRE_NOTHROW(Type(Max)--);                                                \
  REQUIRE_NOTHROW(--Type(Max));                                                \
                                                                               \
  REQUIRE_THROWS(Type(Max)++);                                                 \
  REQUIRE_THROWS(++Type(Max));                                                 \
  REQUIRE_THROWS(Type(Min)--);                                                 \
  REQUIRE_THROWS(--Type(Min));                                                 \
                                                                               \
  REQUIRE(+Type(1));                                                           \
  REQUIRE_FALSE(+Type(0));

#define Integer_Bitwise_Tests(Type, CType)                                     \
  REQUIRE_THROWS(Type(0) <<= (sizeof(CType) * 8));                             \
  REQUIRE_THROWS(Type(0) >>= (sizeof(CType) * 8));                             \
                                                                               \
  REQUIRE_NOTHROW(Type(0) <<= (sizeof(CType) * 8) - 1);                        \
  REQUIRE_NOTHROW(Type(0) <<= 0);                                              \
  REQUIRE_NOTHROW(Type(0) >>= (sizeof(CType) * 8) - 1);                        \
  REQUIRE_NOTHROW(Type(0) >>= 0);

#define Make_Signed_Integer_Tests(Type, CType)                                 \
  TEST_CASE("Test " #Type) {                                                   \
    constexpr CType Min = std::numeric_limits<CType>::min();                   \
    constexpr CType Max = std::numeric_limits<CType>::max();                   \
                                                                               \
    Integer_Arithmetic_Tests(Type, CType);                                     \
                                                                               \
    REQUIRE_THROWS(Type(Min) *= 2);                                            \
    REQUIRE_THROWS(Type(Max) -= (-1));                                         \
    REQUIRE_THROWS(-Type(Min));                                                \
  }

#define Make_Unsigned_Integer_Tests(Type, CType)                               \
  TEST_CASE("Test " #Type) {                                                   \
    constexpr CType Min = std::numeric_limits<CType>::min();                   \
    constexpr CType Max = std::numeric_limits<CType>::max();                   \
                                                                               \
    Integer_Arithmetic_Tests(Type, CType);                                     \
                                                                               \
    REQUIRE_NOTHROW(Type(Min) *= 2);                                           \
  }

#define Make_Index_Integer_Tests(Type, CType)                                  \
  TEST_CASE("Test " #Type) {                                                   \
    constexpr CType Min = std::numeric_limits<CType>::min();                   \
    constexpr CType Max = std::numeric_limits<CType>::max();                   \
                                                                               \
    Integer_Arithmetic_Tests(Type, CType);                                     \
    Integer_Bitwise_Tests(Type, CType);                                        \
                                                                               \
    REQUIRE_NOTHROW(Type(Min) *= 2);                                           \
    REQUIRE(Type(1));                                                          \
    REQUIRE_FALSE(Type(0));                                                    \
  }

Make_Unsigned_Integer_Tests(SafeUInt8, uint8_t);
Make_Unsigned_Integer_Tests(SafeUInt16, uint16_t);
Make_Unsigned_Integer_Tests(SafeUInt32, uint32_t);
Make_Unsigned_Integer_Tests(SafeUInt64, uint64_t);

Make_Signed_Integer_Tests(SafeInt8, int8_t);
Make_Signed_Integer_Tests(SafeInt16, int16_t);
Make_Signed_Integer_Tests(SafeInt32, int32_t);
Make_Signed_Integer_Tests(SafeInt64, int64_t);
