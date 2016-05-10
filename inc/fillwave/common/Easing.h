/*
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

//
//  easing.h
//
//  Copyright (c) 2011, Auerhaus Development, LLC
//
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What The Fuck You Want
//  To Public License, Version 2, as published by Sam Hocevar. See
//  http://sam.zoy.org/wtfpl/COPYING for more details.
//

#ifndef EASING_H_
#define EASING_H_

#include <fillwave/OpenGL.h>
#include <functional>

#if defined(__LP64__) && !defined(AH_EASING_USE_DBL_PRECIS)
#define AH_EASING_USE_DBL_PRECIS
#endif

/* We need the same float everywhere */
typedef GLfloat AHFloat;

/*
 #ifdef AH_EASING_USE_DBL_PRECIS
 #define AHFloat double
 #else
 #define AHFloat float
 #endif
 */

//typedef AHFloat (*AHEasingFunction)(AHFloat);
typedef std::function<AHFloat(AHFloat)> EasingFunction;

// Linear interpolation (no easing)
AHFloat LinearInterpolation(AHFloat p);

// Quadratic easing; p^2
AHFloat QuadraticEaseIn(AHFloat p);
AHFloat QuadraticEaseOut(AHFloat p);
AHFloat QuadraticEaseInOut(AHFloat p);

// Cubic easing; p^3
AHFloat CubicEaseIn(AHFloat p);
AHFloat CubicEaseOut(AHFloat p);
AHFloat CubicEaseInOut(AHFloat p);

// Quartic easing; p^4
AHFloat QuarticEaseIn(AHFloat p);
AHFloat QuarticEaseOut(AHFloat p);
AHFloat QuarticEaseInOut(AHFloat p);

// Quintic easing; p^5
AHFloat QuinticEaseIn(AHFloat p);
AHFloat QuinticEaseOut(AHFloat p);
AHFloat QuinticEaseInOut(AHFloat p);

// Sine wave easing; sin(p * PI/2)
AHFloat SineEaseIn(AHFloat p);
AHFloat SineEaseOut(AHFloat p);
AHFloat SineEaseInOut(AHFloat p);

// Circular easing; sqrt(1 - p^2)
AHFloat CircularEaseIn(AHFloat p);
AHFloat CircularEaseOut(AHFloat p);
AHFloat CircularEaseInOut(AHFloat p);

// Exponential easing, base 2
AHFloat ExponentialEaseIn(AHFloat p);
AHFloat ExponentialEaseOut(AHFloat p);
AHFloat ExponentialEaseInOut(AHFloat p);

// Exponentially-damped sine wave easing
AHFloat ElasticEaseIn(AHFloat p);
AHFloat ElasticEaseOut(AHFloat p);
AHFloat ElasticEaseInOut(AHFloat p);

// Overshooting cubic easing;
AHFloat BackEaseIn(AHFloat p);
AHFloat BackEaseOut(AHFloat p);
AHFloat BackEaseInOut(AHFloat p);

// Exponentially-decaying bounce easing
AHFloat BounceEaseIn(AHFloat p);
AHFloat BounceEaseOut(AHFloat p);
AHFloat BounceEaseInOut(AHFloat p);

#endif /* EASING_H_ */
