#ifndef DORAYAKI_IDENTITIES_HPP_INCLUDED
#define DORAYAKI_IDENTITIES_HPP_INCLUDED

#include <type_traits>
#include "axioms.hpp"

namespace dorayaki {
    namespace utils {
        template <typename T, typename <typename> Container>
        struct is_instance_of : public std::false_type {}; 

        template <typename T, typename <typename> Container>
        struct is_instance_of<Container<T>, Container> : public std::true_type {}; 
    }

    template <zeroable T>
    auto zero() noexcept -> T; 

    template <zeroable T> requires (std::is_arithmetic_v<T> || utils::is_instance_of<T, std::complex>)
    auto zero() noexcept -> T {
        return static_cast<T>(0); 
    }
}

#endif // ! DORAYAKI_IDENTITIES_HPP_INCLUDED
       
