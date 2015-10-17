/*
 * Profiler.h
 *
 *  Created on: May 5, 2015
 *      Author: Filip Wasil
 */

#ifndef SRC_PROFILER_H_
#define SRC_PROFILER_H_

#ifdef __APPLE__
#else
#include <omp.h>
#endif

#include <chrono>
#include <thread>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FILLWAVE_AO_SAMPLE_RADIUS 1.6f
#define FILLWAVE_OQ_VERTICES 36

#endif /* SRC_PROFILER_H_ */
