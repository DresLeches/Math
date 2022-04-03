#pragma once
#include "Defines.h"
#include "Vec3.h"

struct Mat3
{
    Mat3() = default;

    // ctor: vec3.x = m[0][j] vec3.y = m[1][j] vec3.z = m[2][j]
    explicit Mat3(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);

    // ctor: arr[0] = m[0][0], arr[1] = m[0][1], arr[2] = m[0][2]...
    explicit Mat3(const f32* arr, const u32 len);

    // ctor: m[j][i] = m(i, j)
    explicit Mat3(const f32 m00, const f32 m01, const f32 m02,
                  const f32 m10, const f32 m11, const f32 m12,
                  const f32 m20, const f32 m21, const f32 m22);

    inline f32 operator()(const u32 i, const u32 j) const;
    inline f32 operator[](const u32 idx) const;

    enum class Axis
    {
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
    };

    void Transpose();
    void SetIdentity();
    void SetZero();
    Vec3 GetAxis(const Axis axis);

    f32 Determinant();
    void Invert();

    void RotateEuler(const f32 angX, const f32 angY, const f32 angZ);
    void RotateAxis(const Axis axis, const f32 ang);                     // rotate along some axis
    f32 GetAxisEuler(const Axis axis);
    Vec3 GetEuler();

    void SetScale(const f32 scale);
    void SetAxisScale(const Axis axis, const f32 scale);
    void SetScalePerAxis(const f32 scaleX, const f32 scaleY, const f32 scaleZ);     // allows for non-uniform scaling
    f32 GetAxisScale(const Axis axis);
    Vec3 GetScale();

    inline Mat3& operator+=(const Mat3& rhs);
    inline Mat3& operator-=(const Mat3& rhs);
    inline Mat3& operator*=(const Mat3& rhs);
    inline Mat3& operator*=(const f32 scalar);

    static Mat3 GetIdentity();
    static Mat3 GetZero();

    // TODO: add note about memory layout
    union
    {
        struct 
        {
            Vec3 xAxis;
            Vec3 yAxis;
            Vec3 zAxis;
        };
        f32 a[9];
        f32 m[3][3];
    };
};

f32 Mat3::operator()(const u32 i, const u32 j) const
{
    return m[j][i];
}

f32 Mat3::operator[](const u32 idx) const
{
    return a[idx];
}

inline Mat3 operator+(const Mat3& lhs, const Mat3& rhs)
{
    return Mat3(lhs.xAxis + rhs.xAxis, lhs.yAxis + rhs.yAxis, lhs.zAxis + rhs.zAxis);
}

inline Mat3 operator-(const Mat3& lhs, const Mat3& rhs)
{
    return Mat3(lhs.xAxis - rhs.xAxis, lhs.yAxis - rhs.yAxis, lhs.zAxis - rhs.zAxis);
}

inline Mat3 operator*(const Mat3& lhs, const Mat3& rhs)
{
    Mat3 res;
    res.xAxis = Vec3(Vec3::Dot(Vec3(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x), rhs.xAxis), 
                 Vec3::Dot(Vec3(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y), rhs.xAxis), 
                 Vec3::Dot(Vec3(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z), rhs.xAxis) 
                );

    res.yAxis = Vec3(Vec3::Dot(Vec3(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x), rhs.yAxis),
                 Vec3::Dot(Vec3(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y), rhs.yAxis), 
                 Vec3::Dot(Vec3(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z), rhs.yAxis) 
                );

    res.zAxis = Vec3(Vec3::Dot(Vec3(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x), rhs.zAxis),
                 Vec3::Dot(Vec3(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y), rhs.zAxis), 
                 Vec3::Dot(Vec3(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z), rhs.zAxis) 
                );
    return res;
}

inline Mat3 operator*(const Mat3& lhs, const f32 scalar)
{
    return Mat3(lhs.xAxis * scalar, lhs.yAxis * scalar, lhs.zAxis * scalar);
}

inline Mat3 operator*(const f32 scalar, const Mat3& rhs)
{
    return Mat3(rhs.xAxis * scalar, rhs.yAxis * scalar, rhs.zAxis * scalar);
}

inline Vec3 operator*(const Mat3& lhs, const Vec3& rhs)
{
    Vec3 res;
    res.x = Vec3::Dot(rhs, Vec3(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x));
    res.y = Vec3::Dot(rhs, Vec3(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y));
    res.z = Vec3::Dot(rhs, Vec3(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z));
    return res;
}

Mat3& Mat3::operator+=(const Mat3& rhs)
{
    xAxis += rhs.xAxis;
    yAxis += rhs.yAxis;
    zAxis += rhs.zAxis;
    return *this;
}

Mat3& Mat3::operator-=(const Mat3& rhs)
{
    xAxis -= rhs.xAxis;
    yAxis -= rhs.yAxis;
    zAxis -= rhs.zAxis;
    return *this;
}

// TODO: add note to explain this mathematical gymnastics
Mat3& Mat3::operator*=(const Mat3& rhs)
{
    xAxis = Vec3(Vec3::Dot(Vec3(xAxis.x, yAxis.x, zAxis.x), rhs.xAxis), 
                 Vec3::Dot(Vec3(xAxis.y, yAxis.y, zAxis.y), rhs.xAxis), 
                 Vec3::Dot(Vec3(xAxis.z, yAxis.z, zAxis.z), rhs.xAxis) 
                );

    yAxis = Vec3(Vec3::Dot(Vec3(xAxis.x, yAxis.x, zAxis.x), rhs.yAxis),
                 Vec3::Dot(Vec3(xAxis.y, yAxis.y, zAxis.y), rhs.yAxis), 
                 Vec3::Dot(Vec3(xAxis.z, yAxis.z, zAxis.z), rhs.yAxis) 
                );

    zAxis = Vec3(Vec3::Dot(Vec3(xAxis.x, yAxis.x, zAxis.x), rhs.zAxis),
                 Vec3::Dot(Vec3(xAxis.y, yAxis.y, zAxis.y), rhs.zAxis), 
                 Vec3::Dot(Vec3(xAxis.z, yAxis.z, zAxis.z), rhs.zAxis) 
                );
    
    return *this;
}

Mat3& Mat3::operator*=(const f32 scalar)
{
    xAxis *= scalar;
    yAxis *= scalar;
    zAxis *= scalar;
    return *this;
}

