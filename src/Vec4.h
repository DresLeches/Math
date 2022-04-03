#pragma once
#include "Defines.h"

struct Vec4
{
    Vec4() = default;
    explicit Vec4(const f32 x, const f32 y, const f32 z, const f32 w);
    explicit Vec4(const f32 xyzw);
    explicit Vec4(const f32 xyz, const f32 w);

    f32 Dot(const Vec4& rhs);
    f32 Length() const;
    f32 LengthSq() const;
    void Normalize();
    Vec4 Normalized();
    void Inverse();
    void Clear();

    // static
    static f32 Dot(const Vec4& lhs, const Vec4& rhs);
    static bool IsEqual(const Vec4& lhs, const Vec4& rhs);

    // operator
    Vec4& operator+=(const Vec4& rhs);
    Vec4& operator-=(const Vec4& rhs);
    Vec4& operator*=(const f32 scalar);
    Vec4& operator/=(const f32 scalar);
    f32 operator[](u32 idx);
    const f32& operator[](u32 idx) const;

    // setter
    inline void SetX(const f32 x);
    inline void SetY(const f32 y);
    inline void SetZ(const f32 z);
    inline void SetW(const f32 w);
    inline void SetXYZW(const f32 x, const f32 y, const f32 z, const f32 w);
    inline void SetXYZW(const f32 xyz, const f32 w);

    f32 x, y, z, w;
};

inline Vec4 operator+(const Vec4& a, const Vec4& b)
{
    return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline Vec4 operator-(const Vec4& a, const Vec4& b)
{
    return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline Vec4 operator*(const Vec4& v, const f32 scalar)
{
    return Vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

inline Vec4 operator*(const f32 scalar, const Vec4& v)
{
    return Vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

inline Vec4 operator/(const Vec4& v, const f32 scalar)
{
    return Vec4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

inline Vec4 operator/(const f32 scalar, const Vec4& v)
{
    return Vec4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

inline bool operator==(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w);
}

inline bool operator!=(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z && lhs.w != rhs.w);
}

inline bool operator>(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w);
}

inline bool operator>=(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z && lhs.w >= rhs.w);
}

inline bool operator<(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w);
}

inline bool operator<=(const Vec4& lhs, const Vec4& rhs)
{
    return (lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z && lhs.w <= rhs.w);
}

void Vec4::SetX(const f32 x)
{
    this->x = x;
}

void Vec4::SetY(const f32 y)
{
    this->y = y;
}

void Vec4::SetZ(const f32 z)
{
    this->z = z;
}

void Vec4::SetW(const f32 w)
{
    this->w = w;
}

void Vec4::SetXYZW(const f32 x, const f32 y, const f32 z, const f32 w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vec4::SetXYZW(const f32 xyz, const f32 w)
{
    this->x = xyz;
    this->y = xyz;
    this->z = xyz;
    this->w = w;
}



