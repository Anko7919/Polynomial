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

        /**
         * @brief 単項+演算子
         * coeffsの各要素に+演算子を適用した結果を返す
         * @return coeffsの各要素に+演算子を適用した結果
         */
        auto operator+() const noexcept(noexcept(+Coeff{})) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(this->coeffs.size()); 
            std::transform(std::execution::par, this->coeffs.cbegin(), this->coeffs.cend(), result.coeffs.begin(), [](const Coeff &v){ return +v; }); 
            return result; 
        }

        /**
         * @brief 単項-演算子
         * @return coeffsの各要素に-演算子を適用した結果
         */
        auto operator-() const noexcept(noexcept(-Coeff{})) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(this->coeffs.size()); 
            std::transform(std::execution::par, this->coeffs.cbegin(), this->coeffs.cend(), result.coeffs.begin(), [](const Coeff &v){ return -v; }); 
            return result; 
        }

        friend auto operator+(const Polynomial<Coeff> &lhs, const Polynomial<Coeff> &rhs) noexcept(noexcept(Coeff{} + Coeff{})) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(std::max(lhs.coeffs.size(), rhs.coeffs.size())); 
            const Polynomial<Coeff> &grater_poly{ (lhs.coeffs.size() < rhs.coeffs.size()) ? (rhs) : (lhs) }; 
            const Polynomial<Coeff> &less_poly{ (grater_poly == lhs) ? (rhs) : (lhs) }; 
            for (auto i{ 0uz }; i < grater_poly.coeffs.size(); ++i) {
                result.coeffs[i] = grater_poly.coeffs[i] + ((less_poly.coeffs.size() <= i) ? (Coeffs{ 0 }) : (less_poly.coeffs[i])); 
            }
            return result; 
        }
    }; 
} // ! namespace dorayaki

#endif // ! DORAYAKI_POLYNOMIAL_HPP_INCLUDED

