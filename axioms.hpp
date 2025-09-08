#ifndef DORAYAKI_AXIOMS_HPP_INCLUDED
#define DORAYAKI_AXIOMS_HPP_INCLUDED

#include <complex>
#include <type_traits>

namespace dorayaki {
    /* 四則演算を持っているか */
    // Addition
    template <typename T>
    concept addable = requires (T &a, T &b) {
        { a + b } -> std::same_as<T>; 
    }; 

    // Subtraction
    template <typename T>
    concept subtractable = requires (T &a, T &b) {
        { a - b } -> std::same_as<T>; 
    }; 

    // Multiplication
    template <typename T>
    concept multipliable = requires (T &a, T &b) {
        { a * b } -> std::same_as<T>; 
    }; 

    // Division
    template <typename T>
    concept divisible = requires (T &a, T &b) {
        { a / b } -> std::same_as<T>; 
    }; 

    /* 単項演算子 */
    // Negative
    template <typename T>
    concept negatable = requires (T &a) {
        { -a } -> std::same_as<T>; 
    }; 

    /* 単位元の存在 */
    // zero element
    template <typename T>
    struct has_zero : public std::false_type {}

    template <typename T> requires std::is_arithmetic<T>
    struct has_zero<T> : public std::true_type {}

    template <typename T>
    struct has_zero<std::complex<T>> : public std::true_type {}

    // one element
    template <typename T>
    struct has_one : public std::false_type {}

    template <typename T> requires std::is_arithmetic<T>
    struct has_one<T> : public std::true_type {}

    template <typename T>
    struct has_one<std::complex<T>> : public std::true_type{}
}

#endif // ! DORAYAKI_AXIOMS_HPP_INCLUDED
       
