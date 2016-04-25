/*
 * with_duktape.cpp
 *
 *  Created on: 22 Apr 2016
 *      Author: scones
 */


#include "core/support/json.h"
#include "core/support/meta_detail/callable.h"


#ifdef WITH_DUKTAPE
#include "core/support/duktape.h"
#endif


#include <iostream>


META_CALLABLE(print);


using printable_functionality = void(print_function, core::support::self const&, std::ostream&, std::size_t);
using printable = core::support::meta<printable_functionality>;
using meta_vector = std::vector<printable>;


template <typename T>
void call(print_function, T const& value, std::ostream& out, std::size_t position) {
  out << value;
}


template <>
void call(print_function, core::support::null const&, std::ostream& out, std::size_t position) {
  out << "null";
}


template <typename T>
void call(print_function, core::support::meta_detail::attribute<T> const& value, std::ostream& out, std::size_t position) {
  out << std::string(position, ' ') << value.attribute_print_name() << value.get_type().front_enclosure();
  print(value.get_value(), out, position);
  out << value.get_type().back_enclosure();
}


template <typename T>
void call(print_function, std::vector<T> const& some_vector, std::ostream& out, std::size_t position) {
  std::cout << std::endl;
  for (std::uint64_t i(0); i < some_vector.size(); ++i) {
    print(some_vector[i], out, position + 2);
    if (i != some_vector.size() -1)
      out << ',';
    out << std::endl;
  }
  out << std::string(position, ' ') << std::flush;
}


int main(int argc, char** argv) {
  printable result;

#ifdef WITH_DUKTAPE

  std::string json = R"(
  {
    "foo": "bar",
    "meh": 1,
    "bla": true,
    "x": {
      "some_var": null,
      "some_array": [1,2,3]
    },
    "last_key": false
  }
  )";
  auto duk = core::support::duktape::create_from_json(json);
  result = core::support::json::parse<printable_functionality>("root_object", &duk);

#endif

  std::cout << std::boolalpha;
  print(result, std::cout, 0);
  std::cout << std::noboolalpha << std::endl;;

  return 0;
}

