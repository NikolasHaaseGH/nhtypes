module;

#include <type_traits>

export module nhtypes;

export import :common;
export import :boolean;
export import :integers;
export import :decimals;
//export import :type_traits;

export namespace NH_NAMESPACE {

template <typename T>
concept isHeliumInteger =
    std::is_same_v<T, SafeI8> || std::is_same_v<T, SafeI16> ||
    std::is_same_v<T, SafeI32> || std::is_same_v<T, SafeI64> ||
    std::is_same_v<T, SafeU8> || std::is_same_v<T, SafeU16> ||
    std::is_same_v<T, SafeU32> || std::is_same_v<T, SafeU64> ||
    std::is_same_v<T, Int8> || std::is_same_v<T, Int16> ||
    std::is_same_v<T, Int32> || std::is_same_v<T, Int64> ||
    std::is_same_v<T, UInt8> || std::is_same_v<T, UInt16> ||
    std::is_same_v<T, UInt32> || std::is_same_v<T, UInt64>;

template <typename T>
concept isHeliumDecimal =
    std::is_same_v<T, Float> || std::is_same_v<T, Double> ||
    std::is_same_v<T, SafeFloat> || std::is_same_v<T, SafeDouble>;

template <typename T>
concept isHeliumNumber = isHeliumInteger<T> || isHeliumDecimal<T>;
} // namespace nh
