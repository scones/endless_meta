/*
 * forward_like.h
 *
 *  Created on: 12 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_UTILS_FORWARD_LIKE_H_
#define INCLUDE_CORE_SUPPORT_UTILS_FORWARD_LIKE_H_


namespace core {

  namespace support {

    namespace utils {

      #define FORWARD_LIKE_RESULT \
        typename std::conditional< \
          std::is_lvalue_reference<result_type>::value, \
          input_type&, \
          typename std::remove_reference<input_type>::type&& \
        >::type

      /**
      .. function:: auto utils::forward_like<Like, T>(T&& t) noexcept
          Forward the reference *t* like the type of *Like*. That means, if *Like* is
          an lvalue (reference), this function will return an lvalue reference of *t*.
          Otherwise, if *Like* is an rvalue, this function will return an rvalue
          reference of *t*.
          This is mainly used to propagate the expression category (lvalue/rvalue) of
          a member of *Like*, generalizing ``std::forward``.
      */
      template <typename result_type, typename input_type>
      FORWARD_LIKE_RESULT forward_like(input_type&& input) noexcept
      {
          return static_cast<FORWARD_LIKE_RESULT>(input);
      }

      #undef FORWARD_LIKE_RESULT

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_UTILS_FORWARD_LIKE_H_ */

