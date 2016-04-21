/*
 * is_plain.h
 *
 *  Created on: 14 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_UTILS_IS_PLAIN_H_
#define INCLUDE_CORE_SUPPORT_UTILS_IS_PLAIN_H_


#include <type_traits>


namespace core {

  namespace support {

    template <typename T> struct is_plain            : std::true_type {};
    template <typename T> struct is_plain<T &>       : std::false_type {};
    template <typename T> struct is_plain<T const>   : std::false_type {};
    template <typename T> struct is_plain<T const &> : std::false_type {};

  }

}


#endif /* INCLUDE_CORE_SUPPORT_UTILS_IS_PLAIN_H_ */

