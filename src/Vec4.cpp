#include "Vec4.h"
#include "EngineMath.h"


Vec4::Vec4(const f32 x, const f32 y, const f32 z, const f32 w)
    : x(x), y(y), z(z), w(w)
{
}

Vec4::Vec4(const f32 xyzw)
    : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
{
}

Vec4::Vec4(const f32 xyz, const f32 w)
    : x(xyz), y(xyz), z(xyz), w(w)
{
}

f32 Vec4::Dot(const Vec4& rhs)
{
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

f32 Vec4::Length() const
{
    return Math::SqrtF(LengthSq());
}

f32 Vec4::LengthSq() const
{
    return x * x + y * y + z * z + w * w;
}

void Vec4::Normalize()
{
    const f32 len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}

Vec4 Vec4::Normalized()
{
    const f32 len = Length();
    return Vec4(x/len, y/len, z/len, w/len);
}

void Vec4::Inverse()
{
    x = 1.f / x;
    y = 1.f / y;
    z = 1.f / z;
    w = 1.f / w;
}

void Vec4::Clear()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 0.f;
}

/*static*/ f32 Vec4::Dot(const Vec4& lhs, const Vec4& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

/*static*/ bool Vec4::IsEqual(const Vec4& lhs, const Vec4& rhs)
{
    return  Math::IsEqualF(lhs.x, rhs.x) && 
            Math::IsEqualF(lhs.y, rhs.y) && 
            Math::IsEqualF(lhs.z, rhs.z) &&
            Math::IsEqualF(lhs.w, rhs.w);
}

Vec4& Vec4::operator+=(const Vec4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

Vec4& Vec4::operator*=(const f32 scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vec4& Vec4::operator/=(const f32 scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

f32 Vec4::operator[](u32 idx)
{
    return (&x)[idx];
}

const f32& Vec4::operator[](u32 idx) const
{
    return (&x)[idx];
}

