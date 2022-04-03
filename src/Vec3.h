#pragma once
#include "Defines.h"

struct Vec3
{
    Vec3() = default;
    explicit Vec3(const f32 x, const f32 y, const f32 z);
    explicit Vec3(const f32 xyz);

    f32 Dot(const Vec3& rhs);
    f32 Length() const;
    f32 LengthSq() const;
    void Normalize();
    Vec3 Normalized();
    Vec3 Cross(const Vec3& rhs);
    void Inverse();
    void Clear();

    // static
    static f32 Dot(const Vec3& lhs, const Vec3& rhs);
    static Vec3 Cross(const Vec3& lhs, const Vec3& rhs);
    static bool IsEqual(const Vec3& lhs, const Vec3& rhs);      // a more precise check

    // operator
    Vec3& operator+=(const Vec3& rhs);
    Vec3& operator-=(const Vec3& rhs);
    Vec3& operator*=(const f32 scalar);
    Vec3& operator/=(const f32 scalar);
    f32 operator[](u32 idx);
    const f32& operator[](u32 idx) const;

    // setter
    inline void SetX(const f32 x);
    inline void SetY(const f32 y);
    inline void SetZ(const f32 z);
    inline void SetXYZ(const f32 x, const f32 y, const f32 z);

    f32 x, y, z;
};

inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(const Vec3& v, const f32 scalar)
{
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

inline Vec3 operator*(const f32 scalar, const Vec3& v)
{
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

inline Vec3 operator/(const Vec3& v, const f32 scalar)
{
    return Vec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

inline Vec3 operator/(const f32 scalar, const Vec3& v)
{
    return Vec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

inline bool operator==(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
}

inline bool operator!=(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z);
}

inline bool operator>(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z);
}

inline bool operator>=(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z);
}

inline bool operator<(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);
}

inline bool operator<=(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z);
}

void Vec3::SetX(const f32 x)
{
    this->x = x;
}

void Vec3::SetY(const f32 y)
{
    this->y = y;
}

void Vec3::SetZ(const f32 z)
{
    this->z = z;
}

void Vec3::SetXYZ(const f32 x, const f32 y, const f32 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}



