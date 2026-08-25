module;


export module nhtypes:common;

import std;
import :boolean;

namespace NH_NAMESPACE {

    void DebugBreak()
    {
#if (__has_builtin(__builtin_debugtrap))
        __builtin_debugtrap();
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
        __debugbreak()
#elif (defined(__linux__) || defined(__gnu_linux__) || defined(__APPLE__))
        raise(SIGTRAP);
#else
        throw "Invalid Platform";
#endif
    }

    export inline void Assert(Bool condition) { 
        if(!condition) [[unlikely]]{
#if ENABLE_TESTABLE_ASSERTIONS
            throw 1;
#elif( defined(_DEBUG))
            DebugBreak();
else
            std::exit(); 
#endif
        }
    }

    export inline void Assert(bool condition) { 
        if(!condition) [[unlikely]]{
#if ENABLE_TESTABLE_ASSERTIONS
            throw 1;
#elif( defined(_DEBUG))
            DebugBreak();
else
            std::exit(); 
#endif
        }
    }
}
