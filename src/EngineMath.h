#pragma once
#include "Defines.h"

namespace Math
{
    constexpr f32 PI            = 3.1415926535f;
    constexpr f32 TWO_PI        = PI * 2.0f;
    constexpr f32 PI_OVER_2     = PI / 2.0f;
    
    // trig
    f32 Cos(const f32 inAng);
    f32 Sin(const f32 inAng);
    f32 Tan(const f32 inAng);
    f32 Acos(const f32 inVal);
    f32 Asin(const f32 inVal);
    f32 Atan(const f32 b, const f32 a);
    f32 ToRad(const f32 deg);
    f32 ToDeg(const f32 rad);

    // exponential
    f32 PowF(const f32 inVal, const f32 pow);
    f32 SqrtF(const f32 inVal);
    f32 RsqrtF(const f32 inVal);
    f32 Log(const f32 inVal);           // natural log
    f32 Log2(const f32 inVal);
    
    // comp
    template<typename T>
    inline T Min(const T a, const T b);

    template<typename T>
    inline T Max(const T a, const T b);

    template<typename T>
    inline T Clamp(const T inVal, const T minVal, const T maxVal);
    bool IsZero(const f32 inVal, const f32 epsilon = 0.001f);
    bool IsEqualF(const f32 a, const f32 b, const f32 epsilon = 0.001f);

    // interp
    f32 Lerp(const f32 a, const f32 b, const f32 t);
    
    // abs
    s32 Abs(const s32 inVal);
    f32 Abs(const f32 inVal);

    // floor/ceil
    f32 Ceil(const f32 inVal);
    f32 Floor(const f32 inVal);

    // swap
    template<typename T>
    inline void Swap(T& l, T& r);
}

template<typename T>
T Math::Min(const T a, const T b)
{
    return (a < b ? a : b);
}

template<typename T>
T Math::Max(const T a, const T b)
{
    return (a > b ? a : b);
}

template<typename T>
T Math::Clamp(const T inVal, const T minVal, const T maxVal)
{
    return Math::Min(maxVal, Math::Max(minVal, inVal));
}

template<typename T>
void Math::Swap(T& l, T& r)
{
    auto temp = l;
    l = r;
    r = temp;
}

