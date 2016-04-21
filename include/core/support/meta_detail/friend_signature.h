/*
 * friend.h
 *
 *  Created on: 14 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_FRIEND_SIGNATURE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_FRIEND_SIGNATURE_H_


#include "core/support/meta_detail/signature.h"
#include "core/support/meta_detail/self.h"
#include "core/support/meta_detail/forward_like.h"


#pragma GCC diagnostic ignored "-Wnon-template-friend"


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename meta_type, typename... signature_types> struct friend_signature;


      template <typename meta_type> struct friend_signature<meta_type> {};


      template <
        typename meta_type,
        typename result_type,
        typename function_type,
        typename... argument_types,
        typename self_type,
        typename... signature_types
      >
      struct friend_signature<
        meta_type,
        signature<
          result_type(function_type, argument_types...),
          self_type
        >,
        signature_types...
      >
        : friend_signature<meta_type, signature_types...>
      {

        friend result_type call(
          function_type ft,
          typename self_to_this_<
            argument_types,
            meta_type
          >::type... arguments
        ) {
          return forward_like<self_type>(
            self_from<argument_types...>::apply(
              std::forward<
                typename self_to_this_<argument_types, meta_type >::type
              >(arguments)...
            ).get()
          )
          (ft, forward_self<argument_types>()(arguments)...);
        }
      };


      template <
        typename meta_type,
        typename function_type,
        typename... argument_types,
        typename self_type,
        typename... signature_types
      >
      struct friend_signature<meta_type, signature<void(function_type, argument_types...), self_type>, signature_types...>
        : friend_signature<meta_type, signature_types...>
      {

        friend void call(
          function_type ft,
          typename self_to_this_<
            argument_types,
            meta_type
          >::type... arguments
        ) {
          forward_like<self_type>(
            self_from<argument_types...>::apply(
              std::forward<
                typename self_to_this_<argument_types, meta_type >::type
              >(arguments)...
            ).get()
          )
          (ft, forward_self<argument_types>()(arguments)...);
        }
      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_FRIEND_SIGNATURE_H_ */

