/*
 * environment.h
 *
 *  Created on: 11 Sep 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_ENVIRONMENT_H_
#define INCLUDE_CORE_ENVIRONMENT_H_


#include "core/support/duktape.h"
#include "core/meta.h"


namespace core {

  class environment {

    public:


    environment() : m_duk(nullptr) {
    }


    void reset_environment() {
      delete m_duk;

      // create duktape object
      m_duk = new core::support::duktape;

      // setup basics
      m_duk->peval_string(
        "({"
        "  print: this.print,"
        "  alert: this.alert,"
        "  eval: this.eval,"
        "  parseInt: this.parseInt,"
        "  parseFloat: this.parseFloat,"
        "  isNaN: this.isNaN,"
        "  isFinite: this.isFinite,"
        "  decodeURI: this.decodeURI,"
        "  encodeURI: this.encodeURI,"
        "  encodeURIComponent: this.encodeURIComponent,"
        "  NaN: this.NaN,"
        "  undefined: this.undefined,"
        "  Infinity: this.Infinity,"
        "  Object: this.Object,"
        "  Function: this.Function,"
        "  Array: this.Array,"
        "  String: this.String,"
        "  Boolean: this.Boolean,"
        "  Number: this.Number,"
        "  Date: this.Date,"
        "  RegExp: this.RegExp,"
        "  Error: this.Error,"
        "  EvalError: this.EvalError,"
        "  RangeError: this.RangeError,"
        "  ReferenceError: this.ReferenceError,"
        "  SyntaxError: this.SyntaxError,"
        "  TypeError: this.TypeError,"
        "  URIError: this.URIError,"
        "  Math: this.Math,"
        "  JSON: this.JSON,"
        "  Logger: this.Duktape.Logger,"
        "  endless: {"
        "    events: [],"
        "    addons: []"
        "  }"
        "})"
      );
      m_duk->set_global_object();

      // setup niceties
      m_duk->peval_string(
        "console = { log: function() { print(Array.prototype.join.call(arguments, ' ')); } };"
      );

      m_duk->peval_string(
        "  print([\"1\", 2, false, 3.3]);"
        "("
        "  function () {"
        "    for (var k in this) {"
        "      print('key 2:', k);"
        "    }"
        "  }"
        ")"
        "();"
      );
    }


    private:


    core::support::duktape m_duk;

  };

}


#endif /* INCLUDE_CORE_ENVIRONMENT_H_ */

