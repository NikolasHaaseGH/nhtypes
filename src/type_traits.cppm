module;

#include <type_traits>

export module nhtypes.type_traits;

import nhtypes;

export namespace NH_NAMESPACE {

    template<typename T>
    struct is_nh_type : std::false_type {};

    template<typename T, typename S>
    struct is_nh_type<BasicInt<T, S>> : std::true_type {};

    template<typename T, typename S>
    struct is_nh_type<BasicDecimal<T, S>> : std::true_type {};

    template<>
    struct is_nh_type<Bool> : std::true_type {};

    template<typename T>
    inline constexpr bool is_nh_type_v = is_nh_type<T>::value;
}

export namespace NH_NAMESPACE {

    template<typename T>
    struct is_nh_integral : std::false_type {};

    template<typename T, typename S>
    struct is_nh_integral<BasicInt<T, S>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_nh_integral_v = is_nh_integral<T>::value;
}

export namespace NH_NAMESPACE {

    template<typename T>
    struct is_nh_floating_point : std::false_type {};

    template<typename T, typename S>
    struct is_nh_floating_point<BasicDecimal<T, S>> : std::true_type {};

    template<typename T>
    inline constexpr bool is_nh_floating_point_v = is_nh_floating_point<T>::value;
}
