/*
 * macros.h
 *
 *  Created on: 22 May 2015
 *      Author: Filip Wasil
 */

#ifndef MACROS_H_
#define MACROS_H_

#define FILLWAVE_ARRAY_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))

#define FILLWAVE_ARRAY_FILL_ZEROS(x) memset(x, 0, sizeof(x))

#endif /* MACROS_H_ */
