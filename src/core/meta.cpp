/*
 * meta.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: scones
 */


#include "core/meta.h"


namespace core {

  template <typename T> meta::meta(T t) : m_pvalue(new t_specific<T>(std::move(t))) {}
  template <> meta::meta(char const* t) : m_pvalue(new t_specific<std::string>(std::move(std::string(t)))) {} // implicitly convert to string object)
  template <> meta::meta(std::string t) : m_pvalue(new t_specific<std::string>(std::move(t))) {}
  template <> meta::meta(int t) : m_pvalue(new t_specific<int>(std::move(t))) {}
  template <> meta::meta(bool t) : m_pvalue(new t_specific<bool>(std::move(t))) {}
  template <> meta::meta(double t) : m_pvalue(new t_specific<double>(std::move(t))) {}
  template <> meta::meta(t_meta_object t) : m_pvalue(new t_specific<t_meta_object>(std::move(t))) {}
  template <> meta::meta(t_meta_array t) : m_pvalue(new t_specific<t_meta_array>(std::move(t))) {}


  template <>
  std::string meta::t_specific<int>::json_dump() {
    std::ostringstream oss;
    oss << m_value;
    return oss.str();
  }


  template <>
  std::string meta::t_specific<std::string>::json_dump() {
    return '"' + m_value + '"';
  }


  template <>
  std::string meta::t_specific<double>::json_dump() {
    std::ostringstream oss;
    oss << m_value;
    return oss.str();
  }


  template <>
  std::string meta::t_specific<bool>::json_dump() {
    if (m_value)
      return "true";
    return "false";
  }


  template <>
  std::string meta::t_specific<t_meta_object>::json_dump() {
    std::string output("{");

    for (auto const& element : m_value)
      output += "\"" + element.first + "\":" + ::core::json_dump(element.second) + ',';

    output[output.size() - 1] = '}';
    return output;
  }


  template <>
  std::string meta::t_specific<t_meta_array>::json_dump() {
    std::string output("[");

    for (auto const& element : m_value)
      output += ::core::json_dump(element) + ',';

    output[output.size() - 1] = ']';
    return output;
  }

}

