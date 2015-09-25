/*
 * string.h
 *
 *  Created on: 14 Apr 2014
 *      Author: Filip Wasil
 */

#ifndef STRING_H_
#define STRING_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <string>
#include <vector>
#include <sstream>

namespace fillwave {
namespace strings {

   std::vector<std::string> split(const std::string &s, char delim);
   std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
   std::string getStructField(std::string structName, std::string fieldName, int index);
   std::string getStructField(std::string structName, int index);
   std::string getNotIndexableName(std::string structName, int index);

   template <typename T>
   std::string to_string(T value) {
      std::ostringstream os ;
      os << value ;
      return os.str() ;
   }
}
}
#endif /* STRING_H_ */
