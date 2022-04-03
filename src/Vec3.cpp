#include "Vec3.h"
#include "EngineMath.h"


Vec3::Vec3(const f32 x, const f32 y, const f32 z)
    : x(x), y(y), z(z)
{
}

Vec3::Vec3(const f32 xyz)
    : x(xyz), y(xyz), z(xyz)
{
}

f32 Vec3::Dot(const Vec3& rhs)
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

/*static*/ f32 Vec3::Dot(const Vec3& lhs, const Vec3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

void Vec3::Normalize()
{
    const f32 len = Length();
    x /= len;
    y /= len;
    z /= len;
}

Vec3 Vec3::Normalized()
{
    const f32 len = Length();
    return Vec3(x/len, y/len, z/len);
}

Vec3 Vec3::Cross(const Vec3& rhs)
{
    f32 resX = y * rhs.z - z * rhs.y;
    f32 resY = z * rhs.x - x * rhs.z;
    f32 resZ = x * rhs.y - y * rhs.x;
    return Vec3(resX, resY, resZ);
}

/*static*/ Vec3 Vec3::Cross(const Vec3& lhs, const Vec3& rhs)
{
    f32 resX = lhs.y * rhs.z - lhs.z * rhs.y;
    f32 resY = lhs.z * rhs.x - lhs.x * rhs.z;
    f32 resZ = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vec3(resX, resY, resZ);
}

/*static*/ bool Vec3::IsEqual(const Vec3& lhs, const Vec3& rhs)
{
    return Math::IsEqualF(lhs.x, rhs.x) && Math::IsEqualF(lhs.y, rhs.y) && Math::IsEqualF(lhs.z, rhs.z);
}

f32 Vec3::operator[](u32 idx)
{
    return (&x)[idx];
}

const f32& Vec3::operator[](u32 idx) const
{
    return (&x)[idx];
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vec3& Vec3::operator*=(const f32 scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3& Vec3::operator/=(const f32 scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

void Vec3::Inverse()
{
    x = 1.f / x;
    y = 1.f / y;
    z = 1.f / z;
}

void Vec3::Clear()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

f32 Vec3::Length() const
{
    return Math::SqrtF(LengthSq());
}

f32 Vec3::LengthSq() const
{
    return x * x + y * y + z * z;
}

