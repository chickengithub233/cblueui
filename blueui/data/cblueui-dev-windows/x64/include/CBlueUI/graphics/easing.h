
//  easing.h
//  Copyright (c) 2011, Auerhaus Development, LLC
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What The Fuck You Want
//  To Public License, Version 2, as published by Sam Hocevar. See
//  http://sam.zoy.org/wtfpl/COPYINGformore details.


#ifndef CBLUEUI_EASING_WWWDD_INC
#define CBLUEUI_EASING_WWWDD_INC

#pragma once

#include "core/CCoreBasePro.h"

#ifndef EASING_USE_DBL_PRECIS
#define XFloat double
#else
#define XFloat float
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef XFloat (*lpEasingFuc)(XFloat);

// Linear interpolation (no easing)
UI_EXP XFloat LinearInterpolation(XFloat p);

// Quadratic easing; p^2
UI_EXP XFloat QuadraticEaseIn(XFloat p);
UI_EXP XFloat QuadraticEaseOut(XFloat p);
UI_EXP XFloat QuadraticEaseInOut(XFloat p);

// Cubic easing; p^3
UI_EXP XFloat CubicEaseIn(XFloat p);
UI_EXP XFloat CubicEaseOut(XFloat p);
UI_EXP XFloat CubicEaseInOut(XFloat p);

// Quartic easing; p^4
UI_EXP XFloat QuarticEaseIn(XFloat p);
UI_EXP XFloat QuarticEaseOut(XFloat p);
UI_EXP XFloat QuarticEaseInOut(XFloat p);

// Quintic easing; p^5
UI_EXP XFloat QuinticEaseIn(XFloat p);
UI_EXP XFloat QuinticEaseOut(XFloat p);
UI_EXP XFloat QuinticEaseInOut(XFloat p);

// Sine wave easing; sin(p * PI/2)
UI_EXP XFloat SineEaseIn(XFloat p);
UI_EXP XFloat SineEaseOut(XFloat p);
UI_EXP XFloat SineEaseInOut(XFloat p);

// Circular easing; sqrt(1 - p^2)
UI_EXP XFloat CircularEaseIn(XFloat p);
UI_EXP XFloat CircularEaseOut(XFloat p);
UI_EXP XFloat CircularEaseInOut(XFloat p);

// Exponential easing, base 2
UI_EXP XFloat ExponentialEaseIn(XFloat p);
UI_EXP XFloat ExponentialEaseOut(XFloat p);
UI_EXP XFloat ExponentialEaseInOut(XFloat p);

// Exponentially-damped sine wave easing
UI_EXP XFloat ElasticEaseIn(XFloat p);
UI_EXP XFloat ElasticEaseOut(XFloat p);
UI_EXP XFloat ElasticEaseInOut(XFloat p);

// Overshooting cubic easing;
UI_EXP XFloat BackEaseIn(XFloat p);
UI_EXP XFloat BackEaseOut(XFloat p);
UI_EXP XFloat BackEaseInOut(XFloat p);

// Exponentially-decaying bounce easing
UI_EXP XFloat BounceEaseIn(XFloat p);
UI_EXP XFloat BounceEaseOut(XFloat p);
UI_EXP XFloat BounceEaseInOut(XFloat p);


typedef XFloat (*Animation_Fun)(XFloat p);

#ifdef __cplusplus
}
#endif

#endif