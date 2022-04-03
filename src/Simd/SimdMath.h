#pragma once
#include "PlatformConfig.h"
#include "Simd.h"

namespace SimdMath
{
    inline constexpr Simd_t SimdPi();
    inline constexpr Simd_t SimdTwoPi();
    inline constexpr Simd_t SimdPiOver2();

    // trig
    Simd_t Cos(const f32 inAng);
    Simd_t Sin(const f32 inAng);
    Simd_t Tan(const f32 inAng);
    Simd_t Acos(const f32 inVal);
    Simd_t Asin(const f32 inVal);
    Simd_t Atan(const f32 b, const f32 a);
    Simd_t ToRad(const Simd_t deg);
    Simd_t ToDeg(const Simd_t rad);

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

constexpr Simd_t SimdMath::SimdPi()
{
    return SimdSet32(3.1415926535f, 3.1415926535f, 3.1415926535f, 3.1415926535f);
}

constexpr Simd_t SimdMath::SimdTwoPi()
{
    return SimdSet32(3.1415926535f * 2.0f, 3.1415926535f * 2.0f, 3.1415926535f * 2.0f, 3.1415926535f * 2.0f);
}

constexpr Simd_t SimdMath::SimdPiOver2()
{
    return SimdSet32(3.1415926535f / 2.0f, 3.1415926535f / 2.0f, 3.1415926535f / 2.0f, 3.1415926535f / 2.0f);
}

