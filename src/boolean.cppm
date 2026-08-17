module;

#include <functional>

export module nhtypes:boolean;


export namespace NH_NAMESPACE {

enum class BooleanValue : uint8_t {
    False = 0,
    True = 1
};

constexpr BooleanValue True = BooleanValue::True;
constexpr BooleanValue False = BooleanValue::False;

struct Bool {
        BooleanValue value;

        explicit inline constexpr Bool(bool value) noexcept : value(static_cast<BooleanValue>(value)) {}

        inline constexpr operator bool() const noexcept { return static_cast<bool>(value); }

        inline constexpr Bool(const BooleanValue value = False) noexcept : value(value) {}

        inline constexpr Bool & operator &=(Bool rhs) noexcept { value = static_cast<BooleanValue>(static_cast<bool>(value) & static_cast<bool>(rhs.value)); return *this; }
        inline constexpr Bool & operator |=(Bool rhs) noexcept { value = static_cast<BooleanValue>(static_cast<bool>(value) | static_cast<bool>(rhs.value)); return *this; }
        inline constexpr Bool & operator ^=(Bool rhs) noexcept { value = static_cast<BooleanValue>(static_cast<bool>(value) ^ static_cast<bool>(rhs.value)); return *this; }
        
        friend inline constexpr Bool operator==(Bool lhs, Bool rhs)  noexcept { return static_cast<BooleanValue>(+lhs == +rhs); }
        friend inline constexpr Bool operator!=(Bool lhs, Bool rhs) noexcept { return static_cast<BooleanValue>(+lhs != +rhs); }

        inline constexpr Bool operator!() const noexcept { return static_cast<BooleanValue>(!static_cast<bool>(value)); }

        inline constexpr bool operator+() const noexcept { return static_cast<bool>(value); }
        
        Bool & operator +=(Bool rhs) = delete;
        Bool & operator -=(Bool rhs) = delete;
        Bool & operator *=(Bool rhs) = delete;
        Bool & operator /=(Bool rhs) = delete;
        Bool & operator %=(Bool rhs) = delete;
        
        Bool & operator +(Bool rhs) = delete;
        Bool & operator -(Bool rhs) = delete;
        Bool & operator *(Bool rhs) = delete;
        Bool & operator /(Bool rhs) = delete;
        Bool & operator %(Bool rhs) = delete;
        
        Bool & operator <<=(Bool rhs) = delete;
        Bool & operator >>=(Bool rhs) = delete;
        Bool & operator <<(Bool rhs) = delete;
        Bool & operator >>(Bool rhs) = delete;

        Bool operator >(Bool rhs) = delete;
        Bool operator <(Bool rhs) = delete;
        Bool operator >=(Bool rhs) = delete;
        Bool operator <=(Bool rhs) = delete;
        auto operator <=>(Bool rhs) = delete;        
    };
}

export namespace std {
    template <>
    struct hash<NH_NAMESPACE::Bool> {
        size_t operator()(const NH_NAMESPACE::Bool & value) const {
            return +value;
        }
    };
}
