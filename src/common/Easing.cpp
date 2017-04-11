/*
 * Easing.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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
//  easing.c
//
//  Copyright (c) 2011, Auerhaus Development, LLC
//
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What The Fuck You Want
//  To Public License, Version 2, as published by Sam Hocevar. See
//  http://sam.zoy.org/wtfpl/COPYING for more details.
//

#include <math.h>
#include <fillwave/common/Easing.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2         3.14159265358979323846 * 0.5
#endif

// Modeled after the line y = x
AHFloat LinearInterpolation(AHFloat p) {
  return p;
}

// Modeled after the parabola y = x^2
AHFloat QuadraticEaseIn(AHFloat p) {
  return p * p;
}

// Modeled after the parabola y = -x^2 + 2x
AHFloat QuadraticEaseOut(AHFloat p) {
  return -(p * (p - 2.0f));
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
AHFloat QuadraticEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 2.0f * p * p;
  } else {
    return (-2.0f * p * p) + (4.0f * p) - 1.0f;
  }
}

// Modeled after the cubic y = x^3
AHFloat CubicEaseIn(AHFloat p) {
  return p * p * p;
}

// Modeled after the cubic y = (x - 1)^3 + 1
AHFloat CubicEaseOut(AHFloat p) {
  AHFloat f = (p - 1.0f);
  return f * f * f + 1.0f;
}

// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
AHFloat CubicEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 4.0f * p * p * p;
  } else {
    AHFloat f = ((2.0f * p) - 2.0f);
    return 0.5f * f * f * f + 1.0f;
  }
}

// Modeled after the quartic x^4
AHFloat QuarticEaseIn(AHFloat p) {
  return p * p * p * p;
}

// Modeled after the quartic y = 1 - (x - 1)^4
AHFloat QuarticEaseOut(AHFloat p) {
  AHFloat f = (p - 1.0f);
  return f * f * f * (1.0f - p) + 1.0f;
}

// Modeled after the piecewise quartic
// y = (1/2)((2x)^4)        ; [0, 0.5)
// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
AHFloat QuarticEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 8.0f * p * p * p * p;
  } else {
    AHFloat f = (p - 1);
    return -8.0f * f * f * f * f + 1.0f;
  }
}

// Modeled after the quintic y = x^5
AHFloat QuinticEaseIn(AHFloat p) {
  return p * p * p * p * p;
}

// Modeled after the quintic y = (x - 1)^5 + 1
AHFloat QuinticEaseOut(AHFloat p) {
  AHFloat f = (p - 1.0f);
  return f * f * f * f * f + 1.0f;
}

// Modeled after the piecewise quintic
// y = (1/2)((2x)^5)       ; [0, 0.5)
// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
AHFloat QuinticEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 16 * p * p * p * p * p;
  } else {
    AHFloat f = ((2.0f * p) - 2.0f);
    return 0.5f * f * f * f * f * f + 1;
  }
}

// Modeled after quarter-cycle of sine wave
AHFloat SineEaseIn(AHFloat p) {
  return static_cast<AHFloat>(sinf((p - 1.0f) * static_cast<AHFloat>(M_PI_2))) + 1.0f;
}

// Modeled after quarter-cycle of sine wave (different phase)
AHFloat SineEaseOut(AHFloat p) {
  return sinf(p * static_cast<AHFloat>(M_PI_2));
}

// Modeled after half sine wave
AHFloat SineEaseInOut(AHFloat p) {
  return 0.5f * (1.0f - (cosf(p * static_cast<AHFloat>(M_PI))));
}

// Modeled after shifted quadrant IV of unit circle
AHFloat CircularEaseIn(AHFloat p) {
  return 1.0f - sqrtf(1.0f - (p * p));
}

// Modeled after shifted quadrant II of unit circle
AHFloat CircularEaseOut(AHFloat p) {
  return sqrtf((2.0f - p) * p);
}

// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
AHFloat CircularEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 0.5f * (1 - sqrtf(1.0f - 4.0f * (p * p)));
  } else {
    return 0.5f * (sqrtf(-((2.0f * p) - 3.0f) * ((2.0f * p) - 1.0f)) + 1.0f);
  }
}

// Modeled after the exponential function y = 2^(10(x - 1))
AHFloat ExponentialEaseIn(AHFloat p) {
  return (p == 0.0f) ? p : powf(2.0f, 10.0f * (p - 1));
}

// Modeled after the exponential function y = -2^(-10x) + 1
AHFloat ExponentialEaseOut(AHFloat p) {
  return (p == 1.0f) ? p : 1.0f - powf(2.0f, -10.0f * p);
}

// Modeled after the piecewise exponential
// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
AHFloat ExponentialEaseInOut(AHFloat p) {
  if (p == 0.0f || p == 1.0f) {
    return p;
  }

  if (p < 0.5f) {
    return 0.5f * powf(2.0f, (20.0f * p) - 10.0f);
  } else {
    return -0.5f * powf(2.0f, (-20.0f * p) + 10.0f) + 1.0f;
  }
}

// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
AHFloat ElasticEaseIn(AHFloat p) {
  return sinf(13.0f * static_cast<AHFloat>(M_PI_2) * p) * powf(2.0f, 10.0f * (p - 1.0f));
}

// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
AHFloat ElasticEaseOut(AHFloat p) {
  return sinf(-13.0f * static_cast<AHFloat>(M_PI_2) * (p + 1)) * powf(2.0f, -10.0f * p) + 1.0f;
}

// Modeled after the piecewise exponentially-damped sine wave:
// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
AHFloat ElasticEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 0.5f * sinf(13.0f * static_cast<AHFloat>(M_PI_2) * (2.0f * p)) * powf(2.0f, 10.0f * ((2.0f * p) - 1.0f));
  } else {
    return 0.5f * (
        sinf(-13.0f * static_cast<AHFloat>(M_PI_2) * ((2.0f * p - 1.0f) + 1.0f)) *
        powf(2.0f, -10.0f * (2.0f * p - 1.0f)) + 2.0f
    );
  }
}

// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
AHFloat BackEaseIn(AHFloat p) {
  return p * p * p - p * sinf(p * static_cast<AHFloat>(M_PI));
}

// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
AHFloat BackEaseOut(AHFloat p) {
  AHFloat f = (1.0f - p);
  return 1.0f - (f * f * f - f * sinf(f * static_cast<AHFloat>(M_PI)));
}

// Modeled after the piecewise overshooting cubic function:
// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
AHFloat BackEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    AHFloat f = 2.0f * p;
    return 0.5f * (f * f * f - f * sinf(f * static_cast<AHFloat>(M_PI)));
  } else {
    AHFloat f = (1.0f - (2.0f * p - 1.0f));
    return 0.5f * (1.0f - (f * f * f - f * sinf(f * static_cast<AHFloat>(M_PI)))) + 0.5f;
  }
}

AHFloat BounceEaseIn(AHFloat p) {
  return 1.0f - BounceEaseOut(1 - p);
}

AHFloat BounceEaseOut(AHFloat p) {
  if (p < 4.0f / 11.0f) {
    return (121.0f * p * p) / 16.0f;
  } else if (p < 8.0f / 11.0f) {
    return (363.0f / 40.0f * p * p) - (99.0f / 10.0f * p) + 17 / 5.0f;
  } else if (p < 9.0f / 10.0f) {
    return (4356.0f / 361.0f * p * p) - (35442.0f / 1805.0f * p) + 16061.0f / 1805.0f;
  } else {
    return (54.0f / 5.0f * p * p) - (513.0f / 25.0f * p) + 268.0f / 25.0f;
  }
}

AHFloat BounceEaseInOut(AHFloat p) {
  if (p < 0.5f) {
    return 0.5f * BounceEaseIn(p * 2.0f);
  } else {
    return 0.5f * BounceEaseOut(p * 2.0f - 1.0f) + 0.5f;
  }
}

#ifndef M_PI
#undef M_PI           3.14159265358979323846
#endif

#ifndef M_PI_2
#undef M_PI_2         3.14159265358979323846 * 0.5
#endif
