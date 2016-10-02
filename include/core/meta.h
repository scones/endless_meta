

#include "core/error/meta_type_error.h"

#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>
#include <iostream>


namespace core {


  class meta;
  typedef std::unordered_map<std::string, meta> t_meta_object;
  typedef std::vector<meta> t_meta_array;


  std::string json_dump(meta const& m);
  template <typename T> void operator<<(t_meta_array& array, T value);

  class meta {

    public:


    template <typename T>
    meta(T t) : m_pvalue(new t_specific<T>(std::move(t))) {}
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
  template <> meta::meta<>(char const* t) : m_pvalue(new t_specific<std::string>(std::move(std::string(t)))) {} // implicitly convert to string object


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

