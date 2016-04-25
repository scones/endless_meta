/*
 * implementation.h
 *
 *  Created on: 14 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_IMPLEMENTATION_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_IMPLEMENTATION_H_


//#include <type_traits>

#include "../meta_detail/signature.h"


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename model_type, typename concept_type, typename... signature_types> struct implementation;


      template <typename model_type, typename concept_type>
      struct implementation<model_type, concept_type> : concept_type
      {
      };


      template <
        typename model_type,
        typename concept_type,
        typename result_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<result_type(function_type, argument_types...), self>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual result_type operator()(function_type ft, argument_types... arguments) && override {
          return call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &&>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename result_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<result_type(function_type, argument_types...), self &&>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual result_type operator()(function_type ft, argument_types... arguments) && override {
          return call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &&>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename result_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<result_type(function_type, argument_types...), self &>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual result_type operator()(function_type ft, argument_types... arguments) & override {
          return call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename result_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<result_type(function_type, argument_types...), self const&>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual result_type operator()(function_type ft, argument_types... arguments) const& override {
          return call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type const&>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<void(function_type, argument_types...), self>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual void operator()(function_type ft, argument_types... arguments) && override {
          call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &&>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<void(function_type, argument_types...), self &&>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual void operator()(function_type ft, argument_types... arguments) && override {
          call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &&>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<void(function_type, argument_types...), self &>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual void operator()(function_type ft, argument_types... arguments) & override {
          call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type &>(*this).m_value
            )...
          );
        }

      };


      template <
        typename model_type,
        typename concept_type,
        typename function_type,
        typename... argument_types,
        typename... signature_types
      >
      struct implementation<
        model_type,
        concept_type,
        signature<void(function_type, argument_types...), self const&>,
        signature_types...
      >
        : implementation<model_type, concept_type, signature_types...>
      {

        virtual ~implementation() = default;

        virtual void operator()(function_type ft, argument_types... arguments) const& override {
          call(
            ft,
            self_to_this(
              std::forward<argument_types>(arguments),
              static_cast<model_type const&>(*this).m_value
            )...
          );
        }

      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_IMPLEMENTATION_H_ */

