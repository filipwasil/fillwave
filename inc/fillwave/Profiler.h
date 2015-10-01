/*
 * Profiler.h
 *
 *  Created on: May 5, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_PROFILER_H_
#define SRC_PROFILER_H_

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

//#include <omp.h>
#include <chrono>
#include <thread>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FILLWAVE_AO_SAMPLE_RADIUS 1.6f
#define FILLWAVE_OQ_VERTICES 36

#endif /* SRC_PROFILER_H_ */
