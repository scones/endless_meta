/*
 * signature.h
 *
 *  Created on: 14 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_SIGNATURE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_SIGNATURE_H_


#include "core/support/meta_detail/self.h"


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename signature_type, typename self_type = typename self_from_signature<signature_type>::type>
      struct signature;


      template <typename result_type, typename function_type, typename... argument_types>
      struct signature<result_type(function_type, argument_types...), self>
      {

        virtual ~signature() = default;

        virtual result_type operator()(function_type, argument_types...) && = 0;
      };


      template <typename result_type, typename function_type, typename... argument_types>
      struct signature<result_type(function_type, argument_types...), self &&>
      {

        virtual ~signature() = default;

        virtual result_type operator()(function_type, argument_types...) && = 0;
      };


      template <typename result_type, typename function_type, typename... argument_types>
      struct signature<result_type(function_type, argument_types...), self&>
      {

        virtual ~signature() = default;

        virtual result_type operator()(function_type, argument_types...) & = 0;
      };


      template <typename result_type, typename function_type, typename... argument_types>
      struct signature<result_type(function_type, argument_types...), self const&>
      {

        virtual ~signature() = default;

        virtual result_type operator()(function_type, argument_types...) const& = 0;
      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_SIGNATURE_H_ */

