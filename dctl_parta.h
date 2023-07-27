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

inline float _acosf(float f)
{
    return std::acos(f);
}

inline float _clampf(float f, float l, float h)
{
    return std::clamp(f, l, h);
}

inline float _copysignf(float x, float y)
{
    return std::copysign(x, y);
}

inline float _cosf(float f)
{
    return std::cos(f);
}

inline float _exp2f(float f)
{
    return std::exp2(f);
}

inline float _fabs(float f)
{
    return std::fabs(f);
}

inline float _fdivide(float x, float y)
{
    return x/y;
}

inline float _floor(float f)
{
    return std::floor(f);
}

inline float _fmaf(float x, float y, float z)
{
    return std::fma(x, y, z);
}

inline float _fmaxf(float x, float y)
{
    return std::fmax(x, y);
}

inline float _fminf(float x, float y)
{
    return std::fmin(x, y);
}

inline float _hypotf(float x, float y)
{
    return std::hypot(x, y);
}

inline float _round(float f)
{
    return std::round(f);
}

inline float _saturatef(float f)
{
    if (f != f) return 0;
    return _clampf(f, 0, 1);
}

inline float _sinf(float f)
{
    return std::sin(f);
}

inline float _tanf(float f)
{
    return std::tan(f);
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
