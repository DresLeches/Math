#pragma once
#include "Defines.h"

struct Vec2
{
    Vec2() = default;
    explicit Vec2(const f32 x, const f32 y);
    explicit Vec2(const f32 xy);

    f32 Dot(const Vec2& rhs);
    f32 Length() const;
    f32 LengthSq() const;
    void Normalize();
    Vec2 Normalized();
    void Inverse();
    void Clear();

    // static
    static f32 Dot(const Vec2& lhs, const Vec2& rhs);
    static f32 GetAngle(const Vec2& lhs, const Vec2& rhs);
    static bool IsEqual(const Vec2& lhs, const Vec2& rhs);    // a more precise check

    // operator
    Vec2& operator+=(const Vec2& rhs);
    Vec2& operator-=(const Vec2& rhs);
    Vec2& operator*=(const f32 scalar);
    Vec2& operator/=(const f32 scalar);
    f32 operator[](u32 idx);
    const f32& operator[](u32 idx) const;

    // setter
    inline void SetX(const f32 x);
    inline void SetY(const f32 y);
    inline void SetXY(const f32 x, const f32 y);

    f32 x, y;
};


inline Vec2 operator+(const Vec2& a, const Vec2& b)
{
    return Vec2(a.x + b.x, a.y + b.y);
}

inline Vec2 operator-(const Vec2& a, const Vec2& b)
{
    return Vec2(a.x - b.x, a.y - b.y);
}

inline Vec2 operator*(const Vec2& v, const f32 scalar)
{
    return Vec2(v.x * scalar, v.y * scalar);
}

inline Vec2 operator*(const f32 scalar, const Vec2& v)
{
    return Vec2(v.x * scalar, v.y * scalar);
}

inline Vec2 operator/(const Vec2& v, const f32 scalar)
{
    return Vec2(v.x / scalar, v.y / scalar);
}

inline Vec2 operator/(const f32 scalar, const Vec2& v)
{
    return Vec2(v.x / scalar, v.y / scalar);
}

inline bool operator==(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

inline bool operator!=(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x != rhs.x && lhs.y != rhs.y);
}

inline bool operator>(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x > rhs.x && lhs.y > rhs.y);
}

inline bool operator>=(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x >= rhs.x && lhs.y >= rhs.y);
}

inline bool operator<(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x < rhs.x && lhs.y < rhs.y);
}

inline bool operator<=(const Vec2& lhs, const Vec2& rhs)
{
    return (lhs.x <= rhs.x && lhs.y <= rhs.y);
}

void Vec2::SetX(const f32 x)
{
    this->x = x;
}

void Vec2::SetY(const f32 y)
{
    this->y = y;
}

void Vec2::SetXY(const f32 x, const f32 y)
{
    this->x = x;
    this->y = y;
}

