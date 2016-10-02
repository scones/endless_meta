/*
 * json_dump_test.cpp
 *
 *  Created on: 25 Sep 2016
 *      Author: scones
 */


#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>


#include "core/meta.h"


BOOST_AUTO_TEST_SUITE(json_dump_test)


BOOST_AUTO_TEST_CASE(json_dump_string) {
  core::meta f(std::string("foo"));

  BOOST_CHECK("\"foo\"" == json_dump(f));
}


BOOST_AUTO_TEST_CASE(json_dump_int) {
  core::meta i(1);
  BOOST_CHECK("1" == json_dump(i));
}


BOOST_AUTO_TEST_CASE(json_dump_boolean) {
  core::meta b(false);
  BOOST_CHECK("false" == json_dump(b));

  b = true;
  BOOST_CHECK("true" == json_dump(b));
}


BOOST_AUTO_TEST_CASE(json_dump_double) {
  core::meta d(3.42);
  BOOST_CHECK("3.42" == json_dump(d));
}


BOOST_AUTO_TEST_CASE(json_dump_array) {
  core::t_meta_array arr = {
    1,
    "one"
  };
  BOOST_CHECK("[1,\"one\"]" == json_dump(arr));
}


BOOST_AUTO_TEST_CASE(json_dump_object) {
  core::t_meta_object o = {
    {"foo", "bar"},
    {"a", 2}
  };
  BOOST_CHECK("{\"a\":2,\"foo\":\"bar\"}" == json_dump(o));
}


BOOST_AUTO_TEST_SUITE_END()

