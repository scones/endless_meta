/*
 * forward_like.h
 *
 *  Created on: 20 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_FORWARD_LIKE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_FORWARD_LIKE_H_


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename T, typename U> struct fwd { typedef U type; };
      template <typename T, typename U> struct fwd<T, U &>       : fwd<T, U> {};
      template <typename T, typename U> struct fwd<T, U const>   : fwd<T, U> {};
      template <typename T, typename U> struct fwd<T, U const &> : fwd<T, U> {};
      template <typename T, typename U> struct fwd<T &, U> { typedef U & type; };
      template <typename T, typename U> struct fwd<T &, U &> { typedef U & type; };
      template <typename T, typename U> struct fwd<T const &, U> {
          typedef U const & type;
      };
      template <typename T, typename U> struct fwd<T const &, U &> {
          typedef U const & type;
      };
      template <typename T, typename U> struct fwd<T const &, U const &> {
          typedef U const & type;
      };

      // --- forward_like<T>(u) ------------------------------------------------------

      template <typename T, typename U>
      typename fwd<T, U>::type && forward_like(U && u) noexcept {
          return static_cast<typename fwd<T, U>::type &&>(u);
      }

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_FORWARD_LIKE_H_ */

