module;

export module nhtypes;

import std;

export import :common;
export import :boolean;
export import :integers;
export import :decimals;
export import :hash;

export namespace nh {

    /************* Integers **************/
    using Int8 = BasicInt<std::int8_t, UncheckedIntegerArithmetic>;
    using Int16 = BasicInt<std::int16_t, UncheckedIntegerArithmetic>;
    using Int32 = BasicInt<std::int32_t, UncheckedIntegerArithmetic>;
    using Int64 = BasicInt<std::int64_t, UncheckedIntegerArithmetic>;
    using UInt8 = BasicInt<std::uint8_t, UncheckedIntegerArithmetic>;
    using UInt16 = BasicInt<std::uint16_t, UncheckedIntegerArithmetic>;
    using UInt32 = BasicInt<std::uint32_t, UncheckedIntegerArithmetic>;
    using UInt64 = BasicInt<std::uint64_t, UncheckedIntegerArithmetic>;

    using SafeInt8 = BasicInt<std::int8_t, CheckedIntegerArithmetic>;
    using SafeInt16 = BasicInt<std::int16_t, CheckedIntegerArithmetic>;
    using SafeInt32 = BasicInt<std::int32_t, CheckedIntegerArithmetic>;
    using SafeInt64 = BasicInt<std::int64_t, CheckedIntegerArithmetic>;
    using SafeUInt8 = BasicInt<std::uint8_t, CheckedIntegerArithmetic>;
    using SafeUInt16 = BasicInt<std::uint16_t, CheckedIntegerArithmetic>;
    using SafeUInt32 = BasicInt<std::uint32_t, CheckedIntegerArithmetic>;
    using SafeUInt64 = BasicInt<std::uint64_t, CheckedIntegerArithmetic>;

    /************* Decimals **************/
    using Float = BasicDecimal<float, UncheckedDecimalArithmetic>;
    using Double = BasicDecimal<double, UncheckedDecimalArithmetic>;
    using SafeFloat = BasicDecimal<float, CheckedDecimalArithmetic>;
    using SafeDouble = BasicDecimal<double, CheckedDecimalArithmetic>;
}
