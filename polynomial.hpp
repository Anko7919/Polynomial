#ifndef DORAYAKI_POLYNOMIAL_HPP_INCLUDED
#define DORAYAKI_POLYNOMIAL_HPP_INCLUDED

#include <algorithm>
#include <type_traits>
#include <utility>
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

        auto trimmed() const noexcept -> Polynomial<Coeff>{
            auto result{ *this }; 
            for (auto it{ result.coeffs.rbegin() }, end{ result.coeffs.rend() }; it != end - 1; ++it) {
                if (*it == Coeffs{ 0 }) {
                    result.coeffs.erase(it); 
                }
            }
            return result; 
        }

        auto trim() noexcept -> void {
            for (auto it{ this->coeffs.rbegin() }, end{ this->coeffs.rend() }; it != end - 1; ++it) {
                if (*it == Coeffs{ 0 }){
                    this->coeffs.erase(it); 
                }
            }
        } 

        auto operator=(const Polynomial &) -> Polynomial<Coeff> & = default; 
        auto operator=(Polynomial &&) -> Polynomial<Coeff> & = default; 

        auto operator==(const Polynomial<Coeff> &, const Polynomial<Coeff> &) noexcept -> bool = default; 

        /**
         * @brief 単項+演算子
         * coeffsの各要素に+演算子を適用した結果を返す
         * @return coeffsの各要素に+演算子を適用した結果
         */
        auto operator+() const noexcept(noexcept(+std::declval<Coeff>())) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(this->coeffs.size()); 
            std::transform(std::execution::par, this->coeffs.cbegin(), this->coeffs.cend(), result.coeffs.begin(), [](const Coeff &v){ return +v; }); 
            return result; 
        }

        /**
         * @brief 単項-演算子
         * @return coeffsの各要素に-演算子を適用した結果
         */
        auto operator-() const noexcept(noexcept(-std::declval<Coeff>())) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(this->coeffs.size()); 
            std::transform(std::execution::par, this->coeffs.cbegin(), this->coeffs.cend(), result.coeffs.begin(), [](const Coeff &v){ return -v; }); 
            return result; 
        }

        friend auto operator+(const Polynomial<Coeff> &lhs, const Polynomial<Coeff> &rhs) noexcept(noexcept(std::declval<Coeff>() + std::declval<Coeff>())) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(std::max(lhs.coeffs.size(), rhs.coeffs.size())); 
            const Polynomial<Coeff> &greater_poly{ (lhs.coeffs.size() < rhs.coeffs.size()) ? (rhs) : (lhs) }; 
            const Polynomial<Coeff> &less_poly{ (greater_poly == lhs) ? (rhs) : (lhs) }; 
            for (auto i{ 0uz }; i < greater_poly.coeffs.size(); ++i) {
                result.coeffs[i] = greater_poly.coeffs[i] + ((less_poly.coeffs.size() <= i) ? (Coeff{ 0 }) : (less_poly.coeffs[i])); 
            }
            return result; 
        }

        friend auto operator-(const Polynomial<Coeff> &lhs, const Polynomial<Coeff> &rhs) noexcept(noexcept(std::declval<Coeff>() - std::declval<Coeff>())) -> Polynomial<Coeff> {
            Polynomial<Coeff> result; 
            result.coeffs.resize(std::max(lhs.coeffs.size(), rhs.coeffs.size())); 
            const Polynomial<Coeff> &greater_poly{ (lhs.coeffs.size() < rhs.coeffs.size()) ? (rhs) : (lhs) }; 
            const Polynomial<Coeff> &less_poly{ (greater_poly == lhs) ? (rhs) : (lhs) }; 
            for (auto i{ 0uz }; i < greater_poly.coeffs.size(); ++i) {
                result.coeffs[i] = greater_poly.coeffs[i] - ((less_poly.coeffs.size() <= i) ? (Coeff{ 0 }) : (less_poly.coeffs[i])); 
            }
            return result; 
        }

        friend auto operator*(const Polynomial<Coeff> &lhs, const Polynomial<Coeff> &rhs) noexcept(noexcept(Coeff{} * Coeff{})) -> Polynomial<Coeff>{
            Polynomial<Coeff> result; 
            result.coeffs.resize(lhs.size() * rhs.size()); 
            return result; 
        }

        friend auto operator<<(std::ostream &os, const Polynomial<Coeff> &poly) noexcept(noexcept(std::declval<std::ostream &>() << std::declval<Coeff>())) -> std::ostream & {
            return os; 
        }
    }; 
} // ! namespace dorayaki

#endif // ! DORAYAKI_POLYNOMIAL_HPP_INCLUDED

