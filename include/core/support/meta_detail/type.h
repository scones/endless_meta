/*
 * type.h
 *
 *  Created on: 24 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_TYPE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_TYPE_H_


#include "core/error/json_error.h"
#include "core/support/utils/range.h"
#include "core/support/null_type.h"


#include <vector>
#include <string>


namespace core {

  namespace support {

    namespace meta_detail {



      struct type {

        enum JSON_TYPE {
          NONE = 0,
          UNDEFINED,
          NULL_TYPE,
          BOOLEAN,
          NUMBER,
          STRING,
          OBJECT,
          BUFFER,
          POINTER,
          LIGHTFUNC,
          ARRAY,
          ROOT_OBJECT
        };

        struct square_bracket_type;
        struct curly_bracket_type;
        struct quote_type;
        struct empty_type;
        struct none_type;

        type(std::uint64_t id = UNDEFINED) : m_id(id) {};
        ~type() = default;
        type(type const&) = default;
        type(type&&) = default;

        type& operator=(type& rhs) { return *this; }
        type& operator=(type&& rhs) { return *this; }

        inline std::string front_enclosure() const {
          static std::vector<std::string> s_front_enclosures({
            "", "", "", "", "", "\"", "{", "", "", "", "[", "{"
          });
          return s_front_enclosures[m_id];
        }

        inline std::string back_enclosure() const {
          static std::vector<std::string> s_front_enclosures({
            "", "", "", "", "", "\"", "}", "", "", "", "]", "}"
          });
          return s_front_enclosures[m_id];
        }

        std::uint64_t get_id() const { return m_id; }


        private:


        std::uint64_t m_id;

      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_TYPE_H_ */

