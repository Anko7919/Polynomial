#ifndef DORAYAKI_POLYNOMIAL_HPP_INCLUDED
#define DORAYAKI_POLYNOMIAL_HPP_INCLUDED

#include <algorithm>
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
        Polynomial() noexcept : coeffs{ Coeff{ 0 } } {}
        Polynomial(const Coeff &c) : coeffs{ c } {}
        Polynomial(const std::initializer_list<Coeff> &cs) : coeffs{ cs } {}
        Polynomial(const Polynomial<Coeff> &) = default; 
        Polynomial(Polynomial<Coeff> &&) = default; 

        auto operator=(const Polynomial &) -> Polynomial<Coeff> & = default; 
        auto operator=(Polynomial &&) -> Polynomial<Coeff> & = default; 

        auto operator==(const Polynomial<Coeff> &, const Polynomial<Coeff> &) noexcept -> bool = default; 

        auto operator+() const noexcept -> Polynomial<Coeff> {
            auto ret{ this->coeffs.size() }; 
            std::transform(std::execution::par, this->coeffs.cbegin(), this->coeffs.cend(), ret.begin(), [](const Coeff &v){ return +v; }); 
            return ret; 
        }
    }; 
} // ! namespace dorayaki

#endif // ! DORAYAKI_POLYNOMIAL_HPP_INCLUDED

