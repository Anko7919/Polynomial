#ifndef DORAYAKI_IDENTITIES_HPP_INCLUDED
#define DORAYAKI_IDENTITIES_HPP_INCLUDED

#include <type_traits>
#include "axioms.hpp"

namespace dorayaki {
    namespace utils {
        template <typename T, template <typename> class Container>
        struct is_instance_of : public std::false_type {}; 

        template <typename T, template <typename> class Container>
        struct is_instance_of<Container<T>, Container> : public std::true_type {}; 
    }

    template <zeroable T>
    constexpr auto zero() noexcept -> T {
        constexpr auto b{ std::is_arithmetic_v<T> || utils::is_instance_of<T, std::complex>::value }; 
        if constexpr (b) {
            return static_cast<T>(0); 
        }
        else {
            static_assert(b, "zero() is not defined for this type"); 
        }
    }

    template <zeroable T>
    constexpr auto one() noexcept -> T {
        constexpr auto b{ std::is_arithmetic_v<T> || utils::is_instance_of<T, std::complex>::value }; 
        if constexpr (b) {
            return static_cast<T>(1); 
        }
        else {
            static_assert(b, "one() is not defined for this type"); 
        }
    }
}

#endif // ! DORAYAKI_IDENTITIES_HPP_INCLUDED
       
