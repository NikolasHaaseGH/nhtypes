module;

export module nhtypes:integers;

import std;
import :common;
import :boolean;

namespace NH_NAMESPACE {

    template <typename T>
    concept Integer =
        std::is_integral_v<T> &&
        !std::is_same_v<T, bool>;

    template <typename T>
    concept IS_UNSIGNED = std::is_unsigned_v<T>;

    template <typename T>
    concept IS_SIGNED = std::is_signed_v<T>;

    template <typename T>
    concept PolicySuitable = std::is_empty_v<T>;

}

export namespace NH_NAMESPACE {

    template <Integer T, PolicySuitable ArithmeticPolicy>
    struct BasicInt {
        T value;

        constexpr BasicInt(T value = 0) : value(value) {}

        explicit constexpr operator T() const noexcept { return value; }
        constexpr T operator+() const noexcept { return value; }

        /*
        constexpr inline BasicInt(int64_t value = 0) ENABLE_IF_SIGNED(IntType) : Base(value) {
            Assert(value >= min && value <= max);
        }

        constexpr inline SafeInt(uint64_t value = 0) ENABLE_IF_UNSIGNED(IntType) : Base(value) {
            Assert(value <= max);
        }
        */

        template <typename Other>
        requires(sizeof(Other) >= sizeof(T) && IS_SIGNED<T> == IS_SIGNED<Other>)
        constexpr operator BasicInt<Other, ArithmeticPolicy>() const { return static_cast<Other>(value); }

        template <typename Other>
        requires(sizeof(Other) > sizeof(T) && IS_UNSIGNED<T> && IS_SIGNED<Other>)
        constexpr operator BasicInt<Other, ArithmeticPolicy>() const { return static_cast<Other>(value); }

        friend constexpr Bool operator==(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs == +rhs); }
        friend constexpr Bool operator!=(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs != +rhs); }
        friend constexpr Bool operator<(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs < +rhs); }
        friend constexpr Bool operator>(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs > +rhs); }
        friend constexpr Bool operator>=(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs >= +rhs);}
        friend constexpr Bool operator<=(BasicInt lhs, BasicInt rhs) { return static_cast<Bool>(+lhs <= +rhs); }

        constexpr BasicInt & operator++() { return ArithmeticPolicy::PreIncrement(*this); }
        constexpr BasicInt & operator--() { return ArithmeticPolicy::PreDecrement(*this); }
        constexpr BasicInt operator++(auto) { return ArithmeticPolicy::PostIncrement(value); }
        constexpr BasicInt operator--(auto) { return ArithmeticPolicy::PostDecrement(value); }
        constexpr BasicInt operator-() const requires(IS_SIGNED<T>) { return ArithmeticPolicy::UnaryMinus(value); }

        friend constexpr BasicInt operator+(BasicInt lhs, BasicInt rhs) { return ArithmeticPolicy::Add(lhs.value, rhs.value); }
        friend constexpr BasicInt operator-(BasicInt lhs, BasicInt rhs) { return ArithmeticPolicy::Subtract(lhs.value, rhs.value); }
        friend constexpr BasicInt operator/(BasicInt lhs, BasicInt rhs) { return ArithmeticPolicy::Divide(lhs.value, rhs.value); }
        friend constexpr BasicInt operator*(BasicInt lhs, BasicInt rhs) { return ArithmeticPolicy::Multiply(lhs.value, rhs.value); }
        friend constexpr BasicInt operator%(BasicInt lhs, BasicInt rhs) { return ArithmeticPolicy::Modulo(lhs.value, rhs.value); }

        constexpr BasicInt operator~() const requires(IS_UNSIGNED<T>) { return ~value; }
        constexpr BasicInt & operator<<=(BasicInt rhs) requires(IS_UNSIGNED<T>) { return ArithmeticPolicy::ShiftLeft(*this, rhs); }
        constexpr BasicInt & operator>>=(BasicInt rhs) requires(IS_UNSIGNED<T>) { return ArithmeticPolicy::ShiftRight(*this, rhs); }
        constexpr BasicInt & operator&=(BasicInt rhs) requires(IS_UNSIGNED<T>) { value &= rhs.value; return *this; }
        constexpr BasicInt & operator|=(BasicInt rhs) requires(IS_UNSIGNED<T>) { value |= rhs.value; return *this; }
        constexpr BasicInt & operator^=(BasicInt rhs) requires(IS_UNSIGNED<T>) { value ^= rhs.value; return *this; }

        friend constexpr BasicInt operator&(BasicInt lhs, BasicInt rhs) requires(IS_UNSIGNED<T>) { return lhs &= rhs; }
        friend constexpr BasicInt operator|(BasicInt lhs, BasicInt rhs) requires(IS_UNSIGNED<T>) { return lhs |= rhs; }
        friend constexpr BasicInt operator^(BasicInt lhs, BasicInt rhs) requires(IS_UNSIGNED<T>) { return lhs ^= rhs; }
        friend constexpr BasicInt operator<<(BasicInt lhs, BasicInt rhs) requires(IS_UNSIGNED<T>) { return lhs <<= rhs; }
        friend constexpr BasicInt operator>>(BasicInt lhs, BasicInt rhs) requires(IS_UNSIGNED<T>) { return lhs >>= rhs; }

        constexpr BasicInt & operator+=(BasicInt other) { return *this = *this + other; }
        constexpr BasicInt & operator-=(BasicInt other) { return *this = *this - other; }
        constexpr BasicInt & operator/=(BasicInt other) { return *this = *this / other; }
        constexpr BasicInt & operator*=(BasicInt other) { return *this = *this * other; }
        constexpr BasicInt & operator%=(BasicInt other) { return *this = *this % other; }

    private:
        friend struct UncheckedIntegerArithmetic;
        friend struct CheckedIntegerArithmetic;

        static constexpr auto max = std::numeric_limits<T>::max();
        static constexpr auto min = std::numeric_limits<T>::min();
        static constexpr auto bit_width = std::numeric_limits<T>::digits;
    };

    struct UncheckedIntegerArithmetic
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

        template<typename T>
        static constexpr T & PreIncrement(T & var){ ++(var.value); return var; }

        template<typename T>
        static constexpr T & PreDecrement(T & var){ --(var.value); return var; }

        template<typename ValueType>
        static constexpr ValueType PostIncrement(ValueType & var){ return var++; }

        template<typename ValueType>
        static constexpr ValueType PostDecrement(ValueType & var){ return var--; }

        template<typename ValueType>
        static constexpr ValueType UnaryMinus(ValueType var){ return -var; }

        template<typename T>
        static constexpr T & ShiftLeft(T & lhs, T rhs){ lhs.value <<= rhs.value; return lhs; }

        template<typename T>
        static constexpr T & ShiftRight(T & lhs, T rhs){ lhs.value >>= rhs.value; return lhs; }
    };

    struct CheckedIntegerArithmetic
    {
        template<IS_UNSIGNED ValueType>
        static constexpr ValueType Add(ValueType lhs, ValueType rhs)
        {
            const ValueType result = lhs + rhs;
            Assert(result >= lhs);        
            return result;  
        }

        template<IS_SIGNED ValueType>
        static constexpr ValueType Add(ValueType lhs, ValueType rhs)
        {
            const bool didOverflow = (rhs > 0 && lhs > std::numeric_limits<ValueType>::max() - rhs) || (rhs < 0 && lhs < std::numeric_limits<ValueType>::min() - rhs);
            Assert(!didOverflow);
            return lhs + rhs;  
        }

        template<IS_UNSIGNED ValueType>
        static constexpr ValueType Subtract(ValueType lhs, ValueType rhs)
        { 
            Assert(lhs >= rhs);
            return lhs - rhs; 
        }

        template<IS_SIGNED ValueType>
        static constexpr ValueType Subtract(ValueType lhs, ValueType rhs)
        {
            const bool didOverflow = (rhs < 0 && lhs > std::numeric_limits<ValueType>::max() + rhs) || (rhs > 0 && lhs < std::numeric_limits<ValueType>::min() + rhs);
            Assert(!didOverflow);
            return lhs - rhs;  
        }

        template<IS_SIGNED ValueType>
        static constexpr ValueType Multiply(ValueType lhs, ValueType rhs)
        { 
            constexpr auto min = std::numeric_limits<ValueType>::min();
            constexpr auto max = std::numeric_limits<ValueType>::max();

            Assert(!(lhs == min && rhs == -1));
            Assert(!(rhs == min && lhs == -1));

            if (lhs > 0)
            {
                if (rhs > 0) Assert(lhs <= max / rhs);
                else Assert(lhs <= min / rhs);
            }
            else if (lhs < 0)
            {
                if (rhs > 0) Assert(lhs >= min / rhs);
                else Assert(lhs >= max / rhs);
            }

            return lhs * rhs;
        }

        template<IS_UNSIGNED ValueType>
        static constexpr ValueType Multiply(ValueType lhs, ValueType rhs)
        {         
            if (rhs != 0) Assert(lhs <= (std::numeric_limits<ValueType>::max() / rhs));
            return lhs * rhs; 
        }

        template<IS_UNSIGNED ValueType>
        static constexpr ValueType Divide(ValueType lhs, ValueType rhs)
        { 
            Assert(rhs != 0);
            return lhs / rhs;
        }

        template<IS_SIGNED ValueType>
        static constexpr ValueType Divide(ValueType lhs, ValueType rhs)
        { 
            const bool didOverflow = (rhs == 0 || (rhs == -1 && lhs == std::numeric_limits<ValueType>::min()));
            Assert(!didOverflow);
            return lhs / rhs;
        }

        template<IS_UNSIGNED ValueType>
        static constexpr ValueType Modulo(ValueType lhs, ValueType rhs)
        { 
            Assert(rhs != 0);
            return lhs % rhs;
        }

        template<IS_SIGNED ValueType>
        static constexpr ValueType Modulo(ValueType lhs, ValueType rhs)
        { 
            Assert(rhs != 0);
            Assert(!(lhs == std::numeric_limits<ValueType>::min() && rhs == -1));
            return lhs % rhs;
        }

        template<typename T>
        static constexpr T & PreIncrement(T & var)
        {      
            Assert(var.value != T::max);
            ++(var.value);
            return var;
        }

        template<typename T>
        static constexpr T & PreDecrement(T & var)
        {
            Assert(var.value != T::min);
            --(var.value);
            return var; 
        }

        template<typename ValueType>
        static constexpr ValueType PostIncrement(ValueType & var)
        { 
            Assert(var != std::numeric_limits<ValueType>::max());
            return var++;
        }

        template<typename ValueType>
        static constexpr ValueType PostDecrement(ValueType & var)
        {
            Assert(var != std::numeric_limits<ValueType>::min());
            return var--;
        }

        template<typename ValueType>
        static constexpr ValueType UnaryMinus(ValueType var)
        {
            Assert(var != std::numeric_limits<ValueType>::min());
            return -var; 
        }

        template<typename T>
        static constexpr T & ShiftLeft(T & lhs, T rhs)
        {
            Assert(rhs.value < T::bit_width);
            Assert(lhs.value <= T::max >> rhs.value);
            lhs.value <<= rhs.value;
            return lhs;
        }

        template<typename T>
        static constexpr T & ShiftRight(T & lhs, T rhs)
        {
            Assert(rhs.value < T::bit_width);
            lhs.value >>= rhs.value;
            return lhs;
        }
    };
}

