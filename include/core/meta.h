/*
 * meta.h
 *
 *  Created on: 2 Oct 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_META_H_
#define INCLUDE_CORE_META_H_


#include "core/meta_fwd.h"
#include "core/error/meta_type_error.h"

#include <string>
#include <sstream>
#include <memory>
#include <iostream>


namespace core {

  std::string json_dump(meta const& m);
  template <typename T> void operator<<(t_meta_array& array, T value);
//  bool operator==(meta const& left, meta const& right);

  struct meta {

    template <typename T> meta(T t);
    meta(meta const& m) : m_pvalue(m.m_pvalue->copy()) {}
    meta(meta &&) noexcept = default;

    meta& operator=(meta const& m) {
      meta tmp(m);
      *this = std::move(tmp);
      return *this;
    }
    meta& operator=(meta&&) noexcept = default;


    friend std::string json_dump(meta const& m) { return m.m_pvalue->json_dump(); }


    private:


    struct t_abstract {

      virtual ~t_abstract() = default;


      virtual t_abstract* copy() const = 0;
      virtual std::string json_dump() = 0;

    };


    template <typename T>
    struct t_specific : t_abstract {

      t_specific(T value) : m_value(std::move(value)) {}
      t_abstract* copy() const { return new t_specific<T>(*this); }

      std::string json_dump();

      T m_value;

    };


    std::unique_ptr<t_abstract> m_pvalue;
  };


}


#endif /* INCLUDE_CORE_META_H_ */

