module;

#include <sstream> 

export module nhtypes.stream;

import nhtypes;

export namespace NH_NAMESPACE {

    template <typename T, typename S>
    std::ostream& operator<<(std::ostream & os, const BasicInt<T, S>& i) {
        os << +i;
        return os;
    }

    template <typename T, typename S>
    std::ostream& operator<<(std::ostream & os, const BasicDecimal<T, S>& d) {
        os << +d;
        return os;
    }
}
