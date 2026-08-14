module;

#include <sstream> 

export module nhtypes.overflow;

import nhtypes;

export namespace NH_NAMESPACE {

    template <typename T, typename S>
    concept PossibleIntOverflow = std::is_signed_v<T> && std::is_unsigned_v<S> || std::is_unsigned_v<T> && std::is_signed_v<S>;

    template <typename T, typename S>
    concept FirstTypeIsLarger = sizeof(T) > sizeof(S);

    template <typename T, typename S>
    concept SecondTypeIsLarger = sizeof(T) < sizeof(S);

    template <typename T, typename S>
    concept TypesAreSameSize = sizeof(T) == sizeof(S);

    template <typename LHS, typename RHS>
    requires(PossibleIntOverflow<LHS, RHS> && TypesAreSameSize<LHS, RHS>)
    constexpr  OverflowAddition(Int<LHS> lhs, Int<RHS> rhs){ return (+lhs) + (+rhs); }

}
