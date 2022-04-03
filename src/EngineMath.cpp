#include "EngineMath.h"

// stdlib
#include <cmath>


namespace Math
{
    f32 Cos(const f32 inAng)
    {
        return std::cosf(inAng);
    }
    f32 Sin(const f32 inAng)
    {
        return std::sinf(inAng);
    }
    f32 Tan(const f32 inAng)
    {
        return std::tanf(inAng);
    }
    f32 Acos(const f32 inVal)
    {
        return std::acosf(inVal);
    }
    f32 Asin(const f32 inVal)
    {
        return std::asinf(inVal);
    }
    f32 Atan(const f32 b, const f32 a)
    {
        return std::atan2f(b, a);
    }
    f32 ToRad(const f32 deg)
    {
        return deg * (PI / 180.0f);
    }
    f32 ToDeg(const f32 rad)
    {
        return rad * (180.0f / PI);
    }

    f32 PowF(const f32 inVal, const f32 pow)
    {
        return std::powf(inVal, pow);
    }
    f32 SqrtF(const f32 inVal)
    {
        return std::sqrtf(inVal);
    }
    f32 RsqrtF(const f32 inVal)
    {
        return 1.0f / std::sqrtf(inVal);
    }
    f32 Log(const f32 inVal)
    {
        return std::logf(inVal);
    }
    f32 Log2(const f32 inVal)
    {
        return std::log2f(inVal);
    }

    bool IsZero(const f32 inVal, const f32 epsilon)
    {
        return Abs(inVal) <= epsilon;
    }
    
    bool IsEqualF(const f32 a, const f32 b, const f32 epsilon /* = 0.001f */)
    {
        return Abs(a - b) <= epsilon;
    }

    f32 Lerp(const f32 a, const f32 b, const f32 t)
    {
        return a + (b - a) * t;
    }

    s32 Abs(const s32 inVal)
    {
        return std::abs(inVal);
    }
    f32 Abs(const f32 inVal)
    {
        return std::fabsf(inVal);
    }

    f32 Ceil(const f32 inVal)
    {
        return std::ceilf(inVal);
    }
    f32 Floor(const f32 inVal)
    {
        return std::floorf(inVal);
    }

}