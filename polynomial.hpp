#ifndef DORAYAKI_POLYNOMIAL_HPP_INCLUDED
#define DORAYAKI_POLYNOMIAL_HPP_INCLUDED

#include <type_traits>
#include <vector>

namespace dorayaki {
    template <typename T>
    concept field_like = requires(T &a, T &b) {
        { a + b } -> std::same_as<T>; 
        { a - b } -> std::same_as<T>; 
        { a * b } -> std::same_as<T>; 
        { a / b } -> std::same_as<T>; 
        { +a } -> std::same_as<T>; 
        { -a } -> std::same_as<T>; 
        { T{ 0 } } -> std::same_as<T>; 
        { T{ 1 } } -> std::same_as<T>; 
    }; 

    template <field_like Coeff>
    class Polynomial {
    private: 
        std::vector<Coeff> coeffs; ///< 多項式の係数を次数が小さいほうから並べたもの
                                    
    public: 
        Polynomial() const noexcept : coeffs{ Coeff{ 0 } } {}
        Polynomial(const Coeff &c) const : coeffs{ c } {}
        Polynomial(const std::initializer_list<Coeff> &cs) const : coeffs{ cs } {}
        Polynomial(const Polynomial<Coeff> &) = default; 
        Polynomial(Polynomial<Coeff> &&) = default; 
    }; 
} // ! namespace dorayaki

#endif // ! DORAYAKI_POLYNOMIAL_HPP_INCLUDED

