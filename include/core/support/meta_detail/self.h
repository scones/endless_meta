/*
 * self.h
 *
 *  Created on: 20 Apr 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_SUPPORT_META_DETAIL_SELF_H_
#define INCLUDE_CORE_SUPPORT_META_DETAIL_SELF_H_


namespace core {

  namespace support {

    struct self {};

    namespace meta_detail {

      // --- self_to_this(a, t) ------------------------------------------------------

      template <typename argument_type, typename this_type>
      argument_type && self_to_this(argument_type && a, this_type &&) noexcept {
        return std::forward<argument_type>(a);
      }

      template <typename this_type>
      this_type && self_to_this(self, this_type && tt) noexcept {
        return std::forward<this_type>(tt);
      }

      // --- self_to_this_<argument_type, this_type> ------------------------------------------------

      template <typename argument_type, typename this_type>
      struct self_to_this_                  { typedef argument_type type; };
      template <typename T>
      struct self_to_this_<self, T>         { typedef T type; };
      template <typename T>
      struct self_to_this_<self &&, T>      { typedef T && type; };
      template <typename T>
      struct self_to_this_<self &, T>       { typedef T & type; };
      template <typename T>
      struct self_to_this_<self const &, T> { typedef T const & type; };

      // --- forward_self<argument_type>()(arg) ------------------------------------------------

      template <typename argument_type> struct forward_self {
        template <typename T>
        argument_type && operator()(T && a) const noexcept { return std::forward<argument_type>(a); }
      };
      template <> struct forward_self<self> {
        template <typename T>
        self operator()(T &&) const noexcept { return self(); }
      };
      template <> struct forward_self<self &&> : forward_self<self> {};
      template <> struct forward_self<self &> {
        self s;
        template <typename T>
        self & operator()(T &) noexcept { return s; }
      };
      template <> struct forward_self<self const &> {
        self s;
        template <typename T>
        self const & operator()(T const &) const noexcept { return s; }
      };

      // --- self_from<argument_types...> ------------------------------------------------------

      template <typename... argument_types> struct self_from;
      template <typename argument_type, typename... more_types>
      struct self_from<argument_type, more_types...> : self_from<more_types...> {
        template <typename first_type, typename... even_more_types>
        static auto apply(first_type &&, even_more_types &&... even_more) {
          return self_from<more_types...>::apply(std::forward<even_more_types>(even_more)...);
        }
      };
      template <typename... more_types> struct self_from<self, more_types...> {
        typedef self type;
        template <typename first_type, typename... even_more_types>
        static auto apply(first_type && first, even_more_types &&...) {
          return std::forward<first_type>(first);
        }
      };
      template <typename... more_types> struct self_from<self &&, more_types...> {
        typedef self && type;
        template <typename function_type, typename... even_more_types>
        static typename std::decay<function_type>::type &&
        apply(function_type && first, even_more_types &&...) noexcept {
            return std::move(first);
        }
      };
      template <typename... more_types> struct self_from<self &, more_types...> {
        typedef self & type;
        template <typename first_type, typename... even_more_types>
        static first_type & apply(first_type & first, even_more_types &&...) noexcept {
          return first;
        }
      };
      template <typename... more_types> struct self_from<self const &, more_types...> {
        typedef self const & type;
        template <typename first_type, typename... even_more_types>
        static first_type const & apply(first_type const & first, even_more_types &&...) noexcept {
          return first;
        }
      };
      template <> struct self_from<> {
        template <typename... even_more_types>
        static void apply(even_more_types &&...) {}
      };

      // --- self_from_signature<R(F, argument_types0..., self [[const] &], argument_types1...)> ---------

      template <typename signature_type> struct self_from_signature {
        typedef void type;
      };
      template <typename result_type, typename function_type, typename... argument_types>
      struct self_from_signature<result_type(function_type, argument_types...)>
        :
          self_from<argument_types...>
      {
      };


    }

  }

}


#endif /* INCLUDE_CORE_SUPPORT_META_DETAIL_SELF_H_ */

