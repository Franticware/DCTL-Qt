#ifndef DCTL_PARTA_H
#define DCTL_PARTA_H

#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdarg>
#include <cassert>
#include <string>
#include <vector>
#include <cstdint>

#include "dctl_struct.h"

#define __DEVICE__ inline

struct float2
{
    float x, y;
};

inline float2 make_float2(float x, float y)
{
    float2 ret;
    ret.x = x;
    ret.y = y;
    return ret;
}

struct float3
{
    float x, y, z;
};

inline float3 make_float3(float x, float y, float z)
{
    float3 ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return ret;
}

struct Texture
{
    Texture(int prmW, int prmH, const unsigned char* prmP) : w(prmW), h(prmH), p(prmP) { }

    int w;
    int h;
    const unsigned char* p;
};

typedef const Texture& __TEXTURE__;

inline float _fabs(float x) // Returns the absolute value of x
{
    return std::abs(x);
}
inline float _powf(float x, float y) // Computes x raised to the power of y
{
    return std::pow(x, y);
}
inline float _logf(float x) // Computes the value of the natural logarithm of x
{
    return std::log(x);
}
inline float _log2f(float x) // Computes the value of the logarithm of x to base 2
{
    return std::log2(x)    ;
}
inline float _log10f(float x) // Computes the value of the logarithm of x to base 10
{
    return std::log10(x);
}
inline float _expf(float x) // Computes e**x, the base-e exponential of x
{
    return std::exp(x);
}
inline float _exp2f(float x) // Computes 2**x, the base-2 exponential of x
{
    return std::exp2(x);
}
inline float _exp10f(float x) // Computes 10**x, the base-10 exponential of x
{
    return std::pow(10.f, x);
}
inline float _copysignf(float x, float y) // Returns x with its sign changed to y’s
{
    return std::copysign(x, y);
}
inline float _fmaxf(float x, float y) // Returns x or y, whichever is larger
{
    return std::max(x, y);
}
inline float _fminf(float x, float y) // Returns x or y, whichever is smaller
{
    return std::min(x, y);
}
inline float _clampf(float x, float min, float max) // Clamps x to be within the interval [min, max]
{
    return std::clamp(x, min, max);
}
inline float _saturatef(float x) // Clamps x to be within the interval [0.0f, 1.0f]
{
    return std::clamp(x, 0.f, 1.f);
}
inline float _sqrtf(float x) // Computes the non-negative square root of x
{
    return std::sqrt(x);
}
inline float _ceilf(float x) // Returns the smallest integral value greater than or equal to x
{
    return std::ceil(x);
}
inline float _ceil(float x)
{
    return std::ceil(x);
}
inline float _floorf(float x) // Returns the largest integral value less than or equal to x
{
    return std::floor(x);
}
inline float _floor(float x)
{
    return std::floor(x);
}
inline float _truncf(float x) // Returns the integral value nearest to but no larger in magnitude than x
{
    return std::trunc(x);
}
inline float _round(float x) // Returns the integral value nearest to x rounding, with half-way cases rounded away from zero
{
    return std::round(x);
}
inline float _fmod(float x, float y) // Computes the floating-point remainder of x/y
{
    return std::fmod(x, y);
}
inline float _hypotf(float x, float y) // Computes the square root of the sum of squares of x and y
{
    return std::hypot(x, y);
}
inline float _cosf(float x) // Computes the cosine of x (measured in radians)
{
    return std::cos(x);
}
inline float _sinf(float x) // Computes the sine of x (measured in radians)
{
    return std::sin(x);
}
inline float _cospif(float x) // Computes the cosine of (x * pi) (measured in radians)
{
    return std::cos(x * M_PIf);
}
inline float _sinpif(float x) // Computes the sine of (x * pi) (measured in radians)
{
    return std::sin(x * M_PIf);
}
inline float _tanf(float x) // Computes the tangent of x (measured in radians)
{
    return std::tan(x);
}
inline float _acosf(float x) // Computes the principal value of the arc cosine of x
{
    return std::acos(x);
}
inline float _asinf(float x) // Computes the principal value of the arc sine of x
{
    return std::asin(x);
}
inline float _atan2f(float y, float x) // Computes the principal value of the arc tangent of y/x, using the signs of both arguments to determine the quadrant of the return value
{
    return std::atan2(y, x);
}
inline float _acoshf(float x) // Computes the principal value of the inverse hyperbolic cosine of x
{
    return std::acosh(x);
}
inline float _asinhf(float x) // Computes the principal value of the inverse hyperbolic sine of x
{
    return std::asinh(x);
}
inline float _atanhf(float x) // Computes the inverse hyperbolic tangent of x
{
    return std::atanh(x);
}
inline float _coshf(float x) // Computes the hyperbolic cosine of x
{
    return std::cosh(x);
}
inline float _sinhf(float x) // Computes the hyperbolic sine of x
{
    return std::sinh(x);
}
inline float _tanhf(float x) // Computes the hyperbolic tangent of x
{
    return std::tanh(x);
}
inline float _fdimf(float x, float y) // Returns the positive difference between x and y:x - y if x > y, +0 if x is less than or equal to y
{
    return std::fdim(x, y);
}
inline float _fmaf(float x, float y, float z) // Computes (x * y) + z as a single operation
{
    return (x * y) + z;
}
inline float _rsqrtf(float x) // Computes the reciprocal of square root of x
{
    return 1.f/std::sqrt(x);
}
inline float _fdivide(float x, float y) // Returns x/y
{
    return x/y;
}
inline float _frecip(float x) // Returns 1/x
{
    return 1.f/x;
}
inline int isinf(float x) // Returns a non-zero value if and only if x is an infinite value
{
    return std::isinf(x) ? 1 : 0;
}
inline int isnan(float x) // Returns a non-zero value if and only if x is a NaN value
{
    return std::isnan(x) ? 1 : 0;
}

inline float _tex2D(__TEXTURE__ t, float xf, float yf)
{
    int x = std::floor(xf);
    int y = std::floor(yf);

    x = std::clamp(x, 0, t.w - 1);
    y = std::clamp(y, 0, t.h - 1);

    return t.p[(x + y * t.w) << 2] / 255.f;
}

float3 transform(int p_Width, int p_Height, int p_X, int p_Y, __TEXTURE__ p_TexR, __TEXTURE__ p_TexG, __TEXTURE__ p_TexB);

static std::vector<void*> dctlUiVect;

inline int addToUiVect(void* p) { dctlUiVect.push_back(p); return 0; }

struct DCTLUI_SLIDER_FLOAT_t
{
    int type;
    const char* name;
    const char* label;
    float val, def, lo, hi, step;
    operator float() { return val; }
};

struct DCTLUI_CHECK_BOX_t
{
    int type;
    const char* name;
    const char* label;
    int val, def;
    operator int() { return val; }
};

DCTLUI_SLIDER_FLOAT_t DCTLUI_SLIDER_FLOAT_init(const char* name, const char* label, ...)
{
    DCTLUI_SLIDER_FLOAT_t ret;
    ret.type = DCTL_SLIDER;
    ret.name = name;
    ret.label = label;

    va_list ptr;
    va_start(ptr, label);
    double value0 = va_arg(ptr, double);
    double value1 = va_arg(ptr, double);
    double value2 = va_arg(ptr, double);
    double value3 = va_arg(ptr, double);
    va_end(ptr);

    ret.val = 0;
    ret.def = value0;
    ret.lo = value1;
    ret.hi = value2;
    ret.step = value3;

    return ret;
}

DCTLUI_CHECK_BOX_t DCTLUI_CHECK_BOX_init(const char* name, const char* label, ...)
{
    DCTLUI_CHECK_BOX_t ret;
    ret.type = DCTL_CHECKBOX;
    ret.name = name;
    ret.label = label;

    va_list ptr;
    va_start(ptr, label);
    int value = va_arg(ptr, int);
    va_end(ptr);

    ret.val = 0;
    ret.def = value != 0;

    return ret;
}

#define DEFINE_UI_PARAMS(v, label, type, ...) static type##_t v = type##_init(#v, #label, __VA_ARGS__); static const int v##_dummy = addToUiVect((void*)&v);

#endif // DCTL_PARTA_H
