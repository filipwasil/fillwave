//
// Created by filip on 08.05.16.
//

#ifndef EXCEPTIONFILLWAVE_H
#define EXCEPTIONFILLWAVE_H

#include <exception>
#include <string>

namespace fillwave {
class ExceptionFillwave : public std::exception {
 public:
	ExceptionFillwave(const std::string &why) : mWhy(why) {

	};

	virtual const char *what() const throw() {
		return mWhy.c_str();
	}

 private:
	std::string mWhy;
};

} /* fillwave */

#endif /* EXCEPTIONFILLWAVE_H */
