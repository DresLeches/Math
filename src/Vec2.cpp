#include "Vec2.h"
#include "EngineMath.h"


Vec2::Vec2(const f32 x, const f32 y)
    : x(x), y(y)
{
}

Vec2::Vec2(const f32 xy)
    : x(xy), y(xy)
{
}

f32 Vec2::Dot(const Vec2& rhs)
{
    return x * rhs.x + y * rhs.y;
}

void Vec2::Normalize()
{
    const f32 len = Length();
    x /= len;
    y /= len;
}

Vec2 Vec2::Normalized()
{
    const f32 len = Length();
    return Vec2(x/len, y/len);
}

void Vec2::Inverse()
{
    x = 1.f / x;
    y = 1.f / y;
}

void Vec2::Clear()
{
    x = 0.f;
    y = 0.f;
}

/*static*/ f32 Vec2::Dot(const Vec2& lhs, const Vec2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

/*static*/ f32 Vec2::GetAngle(const Vec2& lhs, const Vec2& rhs)
{
    return Math::Acos(Dot(lhs, rhs) / (lhs.Length() * rhs.Length()));
}

/*static*/ bool Vec2::IsEqual(const Vec2& lhs, const Vec2& rhs)
{
    return Math::IsEqualF(lhs.x, rhs.x) && Math::IsEqualF(lhs.y, rhs.y);
}

f32 Vec2::Length() const
{
    return Math::SqrtF(LengthSq());
}

f32 Vec2::LengthSq() const
{
    return x*x + y*y;
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::operator*=(const f32 scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2& Vec2::operator/=(const f32 scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

f32 Vec2::operator[](u32 idx)
{
    return (&x)[idx];
}

const f32& Vec2::operator[](u32 idx) const
{
    return (&x)[idx];
}


