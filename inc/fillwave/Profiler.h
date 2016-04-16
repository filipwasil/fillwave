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
#include <iostream>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FILLWAVE_AO_SAMPLE_RADIUS 1.6f
#define FILLWAVE_OQ_VERTICES 36

#define FILLWAVE_MEASURE(info, foo)  do {  \
    std::chrono::time_point<std::chrono::system_clock> start, end; \
    start = std::chrono::system_clock::now(); \
    foo; \
    end = std::chrono::system_clock::now();\
    std::chrono::duration<double> elapsed_seconds = end-start;\
    std::cout << info << elapsed_seconds.count() << std::endl;} while(0);\
 
#define FILLWAVE_MEASURE_START std::chrono::system_clock::now
#define FILLWAVE_MEASURE_STOP(info, start)  do {  \
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start;\
    std::cout << info << elapsed_seconds.count() << std::endl;} while(0);

/* Usage
 *  auto start = FILLWAVE_MEASURE_START();
 *  jobs ...
 *  FILLWAVE_MEASURE_STOP("The period passed:", start)
 * */


#endif /* SRC_PROFILER_H_ */
