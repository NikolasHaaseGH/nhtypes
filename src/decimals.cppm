module;

#include <functional>
#include <limits>
#include <cmath>

export module nhtypes:decimals;

import :common;
import :integers;
import :boolean;

template <typename T>
concept Decimal = std::is_floating_point_v<T>;

template <typename T>
concept PolicySuitable = std::is_empty_v<T>;


export namespace NH_NAMESPACE {

    template <typename T, PolicySuitable ArithmeticPolicy>
    struct BasicDecimal {

        constexpr BasicDecimal(T value = 0) : value(value) {}

        explicit constexpr operator T() const noexcept { return value; }
        constexpr T operator+() const noexcept { return value; }

        template <typename Other>
        requires (sizeof(Other) >= sizeof(T))
        constexpr inline operator BasicDecimal<Other, ArithmeticPolicy>() { return value; }

        /*
        template <typename IntType>
        requires(sizeof(IntType) * 8 <= std::numeric_limits<T>::digits)
        constexpr BasicDecimal(BasicInt<IntType> value) : Base(+value) {}

        template <typename IntType>
        requires(sizeof(IntType) * 8 >= std::numeric_limits<T>::digits)
        constexpr operator BasicInt<IntType>() { return m_value; }
        */

        constexpr T operator-() const noexcept { return ArithmeticPolicy::ChangeSign(value); }

        friend constexpr Bool operator<(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs < +rhs); }
        friend constexpr Bool operator>(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs > +rhs); }
        friend constexpr Bool operator>=(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs >= +rhs); }
        friend constexpr Bool operator<=(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs <= +rhs); }

        // Dangerous if not tested against some epsilon
        // We are still providing these so we dont restrict implementations/templates and users are expected to do their own approximation tests.
        friend constexpr Bool operator==(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs == +rhs); }
        friend constexpr Bool operator!=(BasicDecimal lhs, BasicDecimal rhs) { return static_cast<Bool>(+lhs != +rhs); }

        friend constexpr BasicDecimal operator+(BasicDecimal lhs, BasicDecimal rhs) { return ArithmeticPolicy::Add(lhs.value, rhs.value); }
        friend constexpr BasicDecimal operator-(BasicDecimal lhs, BasicDecimal rhs) { return ArithmeticPolicy::Subtract(lhs.value, rhs.value); }
        friend constexpr BasicDecimal operator/(BasicDecimal lhs, BasicDecimal rhs) { return ArithmeticPolicy::Divide(lhs.value, rhs.value); }
        friend constexpr BasicDecimal operator*(BasicDecimal lhs, BasicDecimal rhs) { return ArithmeticPolicy::Multiply(lhs.value, rhs.value); }
        friend constexpr BasicDecimal operator%(BasicDecimal lhs, BasicDecimal rhs) { return ArithmeticPolicy::Modulo(lhs.value, rhs.value); }

        constexpr BasicDecimal & operator+=(BasicDecimal other) { return *this = *this + other; }
        constexpr BasicDecimal & operator-=(BasicDecimal other) { return *this = *this - other; }
        constexpr BasicDecimal & operator/=(BasicDecimal other) { return *this = *this / other; }
        constexpr BasicDecimal & operator*=(BasicDecimal other) { return *this = *this * other; }
        constexpr BasicDecimal & operator%=(BasicDecimal other) { return *this = *this % other; }

    private:
        T value;

        friend struct UncheckedDecimalArithmetic;
        friend struct CheckedDecimalArithmetic;
    };


    struct UncheckedDecimalArithmetic
    {
        template<typename ValueType>
        static constexpr ValueType Add(ValueType lhs, ValueType rhs){ return lhs + rhs; }

        template<typename ValueType>
        static constexpr ValueType Subtract(ValueType lhs, ValueType rhs){ return lhs - rhs; }

        template<typename ValueType>
        static constexpr ValueType Multiply(ValueType lhs, ValueType rhs){ return lhs * rhs; }

        template<typename ValueType>
        static constexpr ValueType Divide(ValueType lhs, ValueType rhs){ return lhs / rhs; }

        template<typename ValueType>
        static constexpr ValueType Modulo(ValueType lhs, ValueType rhs){ return lhs % rhs; }

        template<typename ValueType>
        static constexpr ValueType ChangeSign(ValueType var){ return -var; }
    };

    struct CheckedDecimalArithmetic
    {
    private:
        template<Decimal T>
        static constexpr T Check(T result)
        {
            Assert(std::isfinite(result));
            return result;
        }

    public:
        template<Decimal T>
        static constexpr T Add(T lhs, T rhs)
        {
            return Check(lhs + rhs);
        }

        template<Decimal T>
        static constexpr T Subtract(T lhs, T rhs)
        {
            return Check(lhs - rhs);
        }

        template<Decimal T>
        static constexpr T Multiply(T lhs, T rhs)
        {
            return Check(lhs * rhs);
        }

        template<Decimal T>
        static constexpr T Divide(T lhs, T rhs)
        {
            Assert(rhs != 0);
            return Check(lhs / rhs);
        }

        template<Decimal T>
        static constexpr T Modulo(T lhs, T rhs)
        {
            Assert(rhs != 0);
            return Check(std::fmod(lhs, rhs));
        }

        template<Decimal T>
        static constexpr T ChangeSign(T value)
        {
            return Check(-value);
        }
    };

    using Float = BasicDecimal<float, UncheckedDecimalArithmetic>;
    using Double = BasicDecimal<double, UncheckedDecimalArithmetic>;
    using SafeFloat = BasicDecimal<float, CheckedDecimalArithmetic>;
    using SafeDouble = BasicDecimal<double, CheckedDecimalArithmetic>;
}
