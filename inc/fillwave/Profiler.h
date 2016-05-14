/*
 * Profiler.h
 *
 *  Created on: May 5, 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

#define FILLWAVE_MEASURE(info, foo)  do {  \
    std::chrono::time_point<std::chrono::system_clock> start, end; \
    start = std::chrono::system_clock::now(); \
    foo; \
    end = std::chrono::system_clock::now();\
    std::chrono::duration<double> elapsed_seconds = end-start;\
    std::cout << info << elapsed_seconds.count() << std::endl;} while(0);\

#define FILLWAVE_MEASURE_START std::chrono::system_clock::now
#define FILLWAVE_MEASURE_STOP_PRINT(info, start)  do {  \
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start;\
    std::cout << info << elapsed_seconds.count() << std::endl;} while(0);

#define FILLWAVE_MEASURE_STOP_GET(start) (std::chrono::system_clock::now() - start).count()

/* Usage
 *  auto start = FILLWAVE_MEASURE_START();
 *  jobs ...
 *  FILLWAVE_MEASURE_STOP_PRINT("The period passed:", start)
 *  FILLWAVE_MEASURE_STOP_GET(start)
 * */


#endif /* SRC_PROFILER_H_ */
