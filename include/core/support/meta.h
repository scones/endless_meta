/*
 * meta.h
 *
 *  Created on: 14 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_H_
#define INCLUDE_CORE_SUPPORT_META_H_


#include "core/support/meta_detail/friend_signature.h"
#include "core/support/meta_detail/implementation.h"
#include "core/support/meta_detail/signature.h"
#include "core/support/meta_detail/callable.h"


#include <memory>
#include <iostream>
#include <string>
#include <type_traits>

#ifdef DEBUG
#include <cassert>
#endif


using namespace std;

namespace core {

  namespace support {

    /**
     * recursion end
     */
    template <typename... signature_types> struct meta;


    /**
     * forwarding class
     */
    template <
      typename result_type,
      typename function_type,
      typename... argument_types,
      typename... signature_types
    >
    struct meta<result_type(function_type, argument_types...), signature_types...>
      :
        meta<
          meta<
            result_type(function_type, argument_types...), signature_types...
          >,
          result_type(function_type, argument_types...), signature_types...
        >
    {

      typedef meta<
        meta<
          result_type(function_type, argument_types...), signature_types...
        >,
        result_type(function_type, argument_types...), signature_types...
      > base;

      template <typename... other_argument_types>
      meta(other_argument_types... arguments) : base(std::forward<other_argument_types>(arguments)...) {
      }

    };


    /**
     * main class
     */
    template <typename meta_type, typename... signature_types>
    struct meta<meta_type, signature_types...>
      :
        meta_detail::friend_signature<meta_type, meta_detail::signature<signature_types>...>
    {
      typedef meta base;


      /**
       * holder and value models
       */
      struct concept : meta_detail::signature<signature_types...>
      {
          virtual ~concept() = default;

          virtual concept* clone() const = 0;
          virtual void* data() noexcept = 0;
          virtual void const* data() const noexcept = 0;
          virtual std::type_info const& type() const noexcept = 0;
      };


      template <typename T>
      struct model
        :
          meta_detail::implementation<model<T>, concept, meta_detail::signature<signature_types>...>
      {
          model(T&& value) : m_value(move(value)) { }

          template <typename... argument_types>
          explicit model(argument_types... arguments) : m_value(std::forward<argument_types>(arguments)...) {}

          concept* clone() const { return new model(*this); }
          virtual void* data() noexcept override { return &m_value; }
          virtual void const* data() const noexcept override { return &m_value; }
          virtual std::type_info const& type() const noexcept override { return typeid(T); }
          T m_value;
      };


      /**
       * construct & assign
       */
      meta() noexcept = default;
      template <typename T>
      meta(T value) : m_data(new model<T>(move(value))) {

      }
      meta(meta const& rhs) : m_data(rhs.m_data->clone()) {

      }
      meta(meta&&) noexcept = default;

      meta& operator=(meta rhs) noexcept {
        m_data = std::move(rhs.m_data);
        return *this;
      }


      concept & get() & noexcept {
#ifdef DEBUG
        assert(m_data != nullptr);
#endif
        return *m_data;
      }

      concept const& get() const & noexcept {
#ifdef DEBUG
        assert(m_data != nullptr);
#endif
        return *m_data;
      }

      concept && get() const && noexcept {
#ifdef DEBUG
        assert(m_data != nullptr);
#endif
        return std::move(*m_data);
      }


      private:


      unique_ptr<const concept> m_data;

    };

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_H_ */

