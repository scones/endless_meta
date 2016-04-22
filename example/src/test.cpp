#include "core/support/meta_detail/callable.h"
#include "core/support/meta_detail/attribute.h"
#include "core/support/meta.h"


#include <iostream>
#include <type_traits>
#include <vector>


META_CALLABLE(print);


using printable = core::support::meta<int(print_function, core::support::self const&, std::ostream&, std::size_t)>;

template <typename T>
int call(print_function, T const& value, std::ostream& out, std::size_t position) {
  out << value;

  return 0;
}


template <>
int call(print_function, std::string const& value, std::ostream& out, std::size_t position) {
  out << '"' << value << '"';

  return 0;
}


template <>
int call(print_function, char* const& value, std::ostream& out, std::size_t position) {
  out << '"' << value << '"';

  return 0;
}


template <typename T>
int call(print_function, core::support::meta_detail::attribute<T> const& value, std::ostream& out, std::size_t position) {
  out << std::string(position, ' ') << '"' << value.get_name() << "\": ";
  print(value.get_value(), out, position);

  return 0;
}


template <typename T>
int call(print_function, std::vector<T> const& some_vector, std::ostream& out, std::size_t position) {
  out << std::string(position, ' ') << "{" << std::endl;
  for (std::uint64_t i(0); i < some_vector.size(); ++i) {
    print(some_vector[i], out, position + 2);
    if (i != some_vector.size() -1)
      out << ',';
    out << std::endl;
  }
  out << std::string(position, ' ') << "}" << std::flush;

  return 0;
}


using object_type = std::vector<printable>;

int main(int argc, char** argv) {

  object_type object;

  object.reserve(4);
  object.push_back(core::support::meta_detail::attribute<int>("foo", 1));
  object.push_back(core::support::meta_detail::attribute<std::string>("bar", "foo"));
  object.push_back(core::support::meta_detail::attribute<object_type>("meh", object));
  object.push_back(core::support::meta_detail::attribute<std::uint64_t>("bla", std::uint64_t(123)));

  print(object, std::cout, 0);

  return 0;
}


