/*
 * meta_type_error.h
 *
 *  Created on: 25 Sep 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_ERROR_META_TYPE_ERROR_H_
#define INCLUDE_CORE_ERROR_META_TYPE_ERROR_H_


#include "core/error/error.h"


namespace core {

  namespace error {

    struct meta_type_error : public core::error::error {

      meta_type_error(std::string const& what) : core::error::error(what) {}

    };

  }

}


#endif /* INCLUDE_CORE_ERROR_META_TYPE_ERROR_H_ */

