/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

#include <flw/OpenGL.h>
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