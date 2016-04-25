/*
 * json.h
 *
 *  Created on: 24 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_JSON_H_
#define INCLUDE_CORE_SUPPORT_JSON_H_


#include "core/support/meta.h"
#include "core/support/duktape.h"
#include "core/support/meta_detail/attribute.h"
#include "core/error/json_error.h"


#include <vector>
#include <cinttypes>
#include <string>
#include <sstream>

#include <iostream>
#include "null_type.h"


namespace core {

  namespace support {

    struct json {

      json() = delete;
      ~json() = delete;


      template <typename... signature_types>
      static meta<signature_types...> parse(std::string const& root_name, duktape* pduk, bool has_prefix = false)  {
        using meta_type = meta<signature_types...>;
        using meta_vector = std::vector<meta_type>;

        bool array_type = false;
        if (pduk->is_array()) {
          array_type = true;
        } else if (!pduk->is_object()) {
          std::ostringstream oss;
          oss << "type (";
          switch (pduk->get_type()) {
            case DUK_TYPE_NONE: oss << "none"; break;
            case DUK_TYPE_UNDEFINED: oss << "undefined"; break;
            case DUK_TYPE_NULL: oss << "null"; break;
            case DUK_TYPE_BOOLEAN: oss << "boolean"; break;
            case DUK_TYPE_NUMBER: oss << "number"; break;
            case DUK_TYPE_STRING: oss << "string "; break;
            case DUK_TYPE_OBJECT: oss << "object"; break;
            case DUK_TYPE_BUFFER: oss << "buffer"; break;
            case DUK_TYPE_POINTER: oss << "pointer"; break;
            case DUK_TYPE_LIGHTFUNC: oss << "lightfunc"; break;
            default: oss << "unknown";
          }
          oss << ")[" << pduk->to_string() << "] is not an object or array type";
          throw core::error::json_error(oss.str());
        }
        bool children_have_prefix = !array_type;

        pduk->enumerate(0);

        meta_vector result;

        while (pduk->next(-1)) {

          std::int32_t type = pduk->get_type(-1);
          std::string key = pduk->to_string(-2);

          switch (type) {
            case DUK_TYPE_NULL:
              result.push_back(meta_detail::attribute<null>(key, null(), type, children_have_prefix));
              break;
            case DUK_TYPE_BOOLEAN: {
              bool value = 1 == pduk->get_boolean();
              result.push_back(meta_detail::attribute<bool>(key, value, type, children_have_prefix));
              break;
            }
            case DUK_TYPE_NUMBER: {
              result.push_back(meta_detail::attribute<std::int64_t>(key, pduk->get_int(), type, children_have_prefix));
              break;
            }
            case DUK_TYPE_STRING:
              result.push_back(meta_detail::attribute<std::string>(key, std::move(pduk->get_string()), type, children_have_prefix));
              break;
            case DUK_TYPE_OBJECT: {
              result.push_back(json::parse<signature_types...>(key, pduk, children_have_prefix));
              break;
            }
            case DUK_TYPE_UNDEFINED:
            default:
              std::ostringstream oss;
              oss << "unsupported type-id: " << type;
              throw core::error::json_error(oss.str());
              break;
          } // switch
          pduk->pop_2(); // next

        } // next
        pduk->pop(); // enumerate

        return meta_type(meta_detail::attribute<meta_vector>(root_name, result, (array_type ? meta_detail::type::ARRAY : DUK_TYPE_OBJECT), has_prefix));
      }

    };

  }

}


#endif /* INCLUDE_CORE_SUPPORT_JSON_H_ */

