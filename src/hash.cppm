module;

#include <sstream> 

export module nhtypes:hash;

import :integers;
import :decimals;

namespace std {
    using namespace NH_NAMESPACE;
}

export namespace std {
    template <typename T>
    struct hash<BasicInt<T, UncheckedIntegerArithmetic>> {
        size_t operator()(const BasicInt<T, UncheckedIntegerArithmetic>& value) const noexcept {
            return +value;
        }
    };

    template <typename T>
    struct hash<BasicInt<T, CheckedIntegerArithmetic>> {
        size_t operator()(const BasicInt<T, CheckedIntegerArithmetic>& value) const noexcept {
            return +value;
        }
    };
}
