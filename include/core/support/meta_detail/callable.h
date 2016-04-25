/*
 * callable.h
 *
 *  Created on: 18 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_CALLABLE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_CALLABLE_H_


#include <utility>


#define META_CALLABLE(name) \
  constexpr struct name##_function : core::support::meta_detail::callable<name##_function> {} name = {}


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename function_type>
      struct callable {

        template <typename... argument_types>
        inline constexpr auto operator()(argument_types &&... arguments) const
        {
          call(
            static_cast<function_type const&>(*this),
            std::forward<argument_types>(arguments)...
          );
        }

      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_CALLABLE_H_ */

