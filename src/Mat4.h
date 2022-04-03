#pragma once
#include "Defines.h"
#include "Vec3.h"
#include "Vec4.h"


struct Mat4
{
    Mat4() = default;

    // ctor: vec4.x = m[0][j] vec4.y = m[1][j] vec4.z = m[2][j] vec4.z = m[3][j]
    explicit Mat4(const Vec4& xAxis, const Vec4& yAxis, const Vec4& zAxis, const Vec4& t);
    
    // ctor: arr[0] = m[0][0], arr[1] = m[0][1], arr[2] = m[0][2]...
    explicit Mat4(const f32* arr, const u32 len);

    // ctor: m[j][i] = m(i, j)
    explicit Mat4(const f32 m00, const f32 m01, const f32 m02, const f32 m03,
                  const f32 m10, const f32 m11, const f32 m12, const f32 m13,
                  const f32 m20, const f32 m21, const f32 m22, const f32 m23,
                  const f32 m30, const f32 m31, const f32 m32, const f32 m33);

    inline f32 operator()(const u32 i, const u32 j) const;
    inline f32 operator[](const u32 idx) const;

    enum class Axis
    {
        X_AXIS,
        Y_AXIS,
        Z_AXIS,
    };

    // projections
    void MakeOrtho(const Vec3& min, const Vec3& max);
    void MakeProj(const f32 fov, const f32 aspectRatio, const f32 near, const f32 epsilon = 1.f);
    void MakeLookAt(const Vec3& pos, const Vec3& dir);

    void Transpose();
    void SetIdentity();
    void SetZero();
    Vec3 GetAxis(const Axis axis);
    Vec3 GetTranslation() const;
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

    inline Mat4& operator+=(const Mat4& rhs);
    inline Mat4& operator-=(const Mat4& rhs);
    inline Mat4& operator*=(const Mat4& rhs);
    inline Mat4& operator*=(const f32 scalar);

    static Mat4 GetIdentity();
    static Mat4 GetZero();

    // TODO: add note about memory layout
    union
    {
        struct 
        {
            Vec4 xAxis;
            Vec4 yAxis;
            Vec4 zAxis;
            Vec4 translation;
        };
        // vec3 access
        struct
        {
            Vec3 xAxisVec3;         u32 p0;
            Vec3 yAxisVec3;         u32 p1;
            Vec3 zAxisVec3;         u32 p2;
            Vec3 translationVec3;   u32 p3;
        };
        f32 a[16];
        f32 m[4][4];
    };
};


f32 Mat4::operator()(const u32 i, const u32 j) const
{
    return m[j][i];
}

f32 Mat4::operator[](const u32 idx) const
{
    return a[idx];
}

inline Mat4 operator+(const Mat4& lhs, const Mat4& rhs)
{
    return Mat4(lhs.xAxis + rhs.xAxis, lhs.yAxis + rhs.yAxis, lhs.zAxis + rhs.zAxis, lhs.translation + rhs.translation);
}

inline Mat4 operator-(const Mat4& lhs, const Mat4& rhs)
{
    return Mat4(lhs.xAxis - rhs.xAxis, lhs.yAxis - rhs.yAxis, lhs.zAxis - rhs.zAxis, lhs.translation - rhs.translation);
}

inline Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
    Mat4 res;
    res.xAxis = Vec4(Vec4::Dot(Vec4(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x, lhs.translation.x), rhs.xAxis), 
                 Vec4::Dot(Vec4(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y, lhs.translation.y), rhs.xAxis), 
                 Vec4::Dot(Vec4(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z, lhs.translation.z), rhs.xAxis),
                 Vec4::Dot(Vec4(lhs.xAxis.w, lhs.yAxis.w, lhs.zAxis.w, lhs.translation.w), rhs.xAxis)
            );

    res.yAxis = Vec4(Vec4::Dot(Vec4(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x, lhs.translation.x), rhs.yAxis),
                 Vec4::Dot(Vec4(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y, lhs.translation.y), rhs.yAxis), 
                 Vec4::Dot(Vec4(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z, lhs.translation.z), rhs.yAxis),
                 Vec4::Dot(Vec4(lhs.xAxis.w, lhs.yAxis.w, lhs.zAxis.w, lhs.translation.w), rhs.yAxis)
                );

    res.zAxis = Vec4(Vec4::Dot(Vec4(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x, lhs.translation.x), rhs.zAxis),
                 Vec4::Dot(Vec4(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y, lhs.translation.y), rhs.zAxis), 
                 Vec4::Dot(Vec4(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z, lhs.translation.z), rhs.zAxis),
                 Vec4::Dot(Vec4(lhs.xAxis.w, lhs.yAxis.w, lhs.zAxis.w, lhs.translation.w), rhs.zAxis)
                );
    
    res.translation = Vec4(Vec4::Dot(Vec4(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x, lhs.translation.x), rhs.translation),
                       Vec4::Dot(Vec4(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y, lhs.translation.y), rhs.translation), 
                       Vec4::Dot(Vec4(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z, lhs.translation.z), rhs.translation),
                       Vec4::Dot(Vec4(lhs.xAxis.w, lhs.yAxis.w, lhs.zAxis.w, lhs.translation.w), rhs.translation)
                  );
    return res;

}

inline Mat4 operator*(const Mat4& lhs, const f32 scalar)
{
    return Mat4(lhs.xAxis * scalar, lhs.yAxis * scalar, lhs.zAxis * scalar, lhs.translation * scalar);
}

inline Mat4 operator*(const f32 scalar, const Mat4& rhs)
{
    return Mat4(rhs.xAxis * scalar, rhs.yAxis * scalar, rhs.zAxis * scalar, rhs.translation * scalar);
}

inline Vec4 operator*(const Mat4& lhs, const Vec4& rhs)
{
    Vec4 res;
    res.x = Vec4::Dot(rhs, Vec4(lhs.xAxis.x, lhs.yAxis.x, lhs.zAxis.x, lhs.translation.x));
    res.y = Vec4::Dot(rhs, Vec4(lhs.xAxis.y, lhs.yAxis.y, lhs.zAxis.y, lhs.translation.y));
    res.z = Vec4::Dot(rhs, Vec4(lhs.xAxis.z, lhs.yAxis.z, lhs.zAxis.z, lhs.translation.z));
    res.w = Vec4::Dot(rhs, Vec4(lhs.xAxis.w, lhs.yAxis.w, lhs.zAxis.w, lhs.translation.w));
    return res;
}

Mat4& Mat4::operator+=(const Mat4& rhs)
{
    xAxis       += rhs.xAxis;
    yAxis       += rhs.yAxis;
    zAxis       += rhs.zAxis;
    translation += rhs.translation;
    return *this;
}

Mat4& Mat4::operator-=(const Mat4& rhs)
{
    xAxis       -= rhs.xAxis;
    yAxis       -= rhs.yAxis;
    zAxis       -= rhs.zAxis;
    translation -= rhs.translation;
    return *this;
}

Mat4& Mat4::operator*=(const Mat4& rhs)
{
    xAxis = Vec4(Vec4::Dot(Vec4(xAxis.x, yAxis.x, zAxis.x, translation.x), rhs.xAxis), 
                 Vec4::Dot(Vec4(xAxis.y, yAxis.y, zAxis.y, translation.y), rhs.xAxis), 
                 Vec4::Dot(Vec4(xAxis.z, yAxis.z, zAxis.z, translation.z), rhs.xAxis),
                 Vec4::Dot(Vec4(xAxis.w, yAxis.w, zAxis.w, translation.w), rhs.xAxis)
            );

    yAxis = Vec4(Vec4::Dot(Vec4(xAxis.x, yAxis.x, zAxis.x, translation.x), rhs.yAxis),
                 Vec4::Dot(Vec4(xAxis.y, yAxis.y, zAxis.y, translation.y), rhs.yAxis), 
                 Vec4::Dot(Vec4(xAxis.z, yAxis.z, zAxis.z, translation.z), rhs.yAxis),
                 Vec4::Dot(Vec4(xAxis.w, yAxis.w, zAxis.w, translation.w), rhs.yAxis)
                );

    zAxis = Vec4(Vec4::Dot(Vec4(xAxis.x, yAxis.x, zAxis.x, translation.x), rhs.zAxis),
                 Vec4::Dot(Vec4(xAxis.y, yAxis.y, zAxis.y, translation.y), rhs.zAxis), 
                 Vec4::Dot(Vec4(xAxis.z, yAxis.z, zAxis.z, translation.z), rhs.zAxis),
                 Vec4::Dot(Vec4(xAxis.w, yAxis.w, zAxis.w, translation.w), rhs.zAxis)
                );
    
    translation = Vec4(Vec4::Dot(Vec4(xAxis.x, yAxis.x, zAxis.x, translation.x), rhs.translation),
                       Vec4::Dot(Vec4(xAxis.y, yAxis.y, zAxis.y, translation.y), rhs.translation), 
                       Vec4::Dot(Vec4(xAxis.z, yAxis.z, zAxis.z, translation.z), rhs.translation),
                       Vec4::Dot(Vec4(xAxis.w, yAxis.w, zAxis.w, translation.w), rhs.translation)
                  );

    return *this;
}

Mat4& Mat4::operator*=(const f32 scalar)
{
    xAxis       *= scalar;
    yAxis       *= scalar;
    zAxis       *= scalar;
    translation *= scalar;
}



