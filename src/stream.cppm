module;

#include <sstream> 

export module nhtypes.stream;

import nhtypes;

export namespace NH_NAMESPACE {

    #define FRIEND_STREAM_OPERATOR(Type)                               \
        std::ostream& operator<<(std::ostream& os, const Type& i) {    \
            os << +i;                                                   \
            return os;                                                 \
        }                                                                              

    FRIEND_STREAM_OPERATOR(Int8)
    FRIEND_STREAM_OPERATOR(Int16)
    FRIEND_STREAM_OPERATOR(Int32)
    FRIEND_STREAM_OPERATOR(Int64)
    FRIEND_STREAM_OPERATOR(UInt8)
    FRIEND_STREAM_OPERATOR(UInt16)
    FRIEND_STREAM_OPERATOR(UInt32)
    FRIEND_STREAM_OPERATOR(UInt64)

    FRIEND_STREAM_OPERATOR(SafeInt8)
    FRIEND_STREAM_OPERATOR(SafeInt16)
    FRIEND_STREAM_OPERATOR(SafeInt32)
    FRIEND_STREAM_OPERATOR(SafeInt64)
    FRIEND_STREAM_OPERATOR(SafeUInt8)
    FRIEND_STREAM_OPERATOR(SafeUInt16)
    FRIEND_STREAM_OPERATOR(SafeUInt32)
    FRIEND_STREAM_OPERATOR(SafeUInt64)

    FRIEND_STREAM_OPERATOR(Float)
    FRIEND_STREAM_OPERATOR(Double)

    FRIEND_STREAM_OPERATOR(SafeFloat)
    FRIEND_STREAM_OPERATOR(SafeDouble)
}
