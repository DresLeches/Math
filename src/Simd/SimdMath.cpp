#include "SimdMath.h"
#include <cmath>

namespace SimdMath
{
    Simd_t Cos(const f32 inAng)
    {
        return SimdSet32(std::cosf(inAng));
    }

    Simd_t Sin(const f32 inAng)
    {
        return SimdSet32(std::sinf(inAng));
    }

    Simd_t Tan(const f32 inAng)
    {
        return SimdSet32(std::tanf(inAng));
    }

    Simd_t Acos(const f32 inVal)
    {
        return SimdSet32(std::acosf(inVal));
    }

    Simd_t Asin(const f32 inVal)
    {
        return SimdSet32(std::asinf(inVal));
    }

    Simd_t Atan(const f32 b, const f32 a)
    {
        return SimdSet32(std::atan2f(b, a));
    }

    Simd_t ToRad(const Simd_t deg)
    {
        return SimdMul32(deg, SimdDiv32(SimdPi(), SimdSet32(180.f)));
    }

    Simd_t ToDeg(const Simd_t rad)
    {
        return SimdMul32(rad, SimdDiv32(SimdSet32(180.f), SimdPi()));
    }
}