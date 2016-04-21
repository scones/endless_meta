/*
 * attribute.h
 *
 *  Created on: 21 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_ATTRIBUTE_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_ATTRIBUTE_H_


#include <cinttypes>
#include <string>


namespace core {

  namespace support {

    namespace meta_detail {

      template <typename T>
      struct attribute {

        enum ACCESS_TYPE {
          PUBLIC = 0,
          PRIVATE,
          MAX
        };

        attribute(std::string name, T value, std::uint64_t access_level = ACCESS_TYPE::PUBLIC)
          :
            m_name(std::move(name)),
            m_access_level(access_level),
            m_value(std::move(value))
        {
        }
        attribute(attribute const& rhs)
          :
            m_name(rhs.m_name),
            m_access_level(rhs.m_access_level),
            m_value(rhs.m_value)
        {
        }
        attribute(attribute&&) = default;

        attribute& operator=(attribute rhs) {
          m_name = std::move(rhs.m_name);
          m_access_level = rhs.m_access_level;
          m_value = std::move(rhs.m_value);

          return *this;
        }

        attribute& operator=(attribute&& rhs) {
          m_name = std::move(rhs.m_name);
          m_access_level = rhs.m_access_level;
          m_value = std::move(rhs.m_value);

          return *this;
        }


        bool             can_access() const    noexcept { return ACCESS_TYPE::PUBLIC == m_access_level; }
        std::string const& get_name() const &  noexcept { return m_name; }
        std::string &&     get_name()       && noexcept { return std::move( m_name); }
        T const&          get_value() const &  noexcept { return m_value; }
        T &&              get_value()       && noexcept { return std::move(m_value); }


        private:


        std::string m_name;
        std::uint64_t m_access_level;
        T m_value;

      };

    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_ATTRIBUTE_H_ */

