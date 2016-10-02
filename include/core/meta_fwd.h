/*
 * meta_fwd.h
 *
 *  Created on: 2 Oct 2016
 *      Author: scones
 */

#ifndef INCLUDE_CORE_META_FWD_H_
#define INCLUDE_CORE_META_FWD_H_


#include <vector>
#include <unordered_map>


namespace core {

  struct meta;
  typedef std::unordered_map<std::string, meta> t_meta_object;
  typedef std::vector<meta> t_meta_array;

}


#endif /* INCLUDE_CORE_META_FWD_H_ */

