#include "Mat3.h"
#include "EngineMath.h"
#include <cstring>
#include <cassert>


Mat3::Mat3(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis)
    : xAxis(xAxis)
    , yAxis(yAxis)
    , zAxis(zAxis)
{
}

Mat3::Mat3(const f32* arr, const u32 len)
{
    memcpy(a, arr, sizeof(f32) * len);
}

Mat3::Mat3(const f32 m00, const f32 m01, const f32 m02, 
           const f32 m10, const f32 m11, const f32 m12, 
           const f32 m20, const f32 m21, const f32 m22)
{
    m[0][0] = m00;  m[0][1] = m10;  m[0][2] = m20;
    m[1][0] = m01;  m[1][1] = m11;  m[1][2] = m21;
    m[2][0] = m02;  m[2][1] = m12;  m[2][2] = m22;
}

void Mat3::Transpose()
{
    for (u32 i = 0; i < 2; i++)
    {
        for (u32 j = i+1; j < 3; j++)
        {
            Math::Swap(m[i][j], m[j][i]);
        }
    }
}

void Mat3::SetIdentity()
{
    m[0][0] = 1.f;
    m[1][1] = 1.f;
    m[2][2] = 1.f;
}

void Mat3::SetZero()
{
    memset(a, 0, sizeof(f32) * 9);
}

Vec3 Mat3::GetAxis(const Axis axis)
{
    Vec3 res(0.f);
    switch(axis)
    {
    case Axis::X_AXIS:  res = xAxis;    break;
    case Axis::Y_AXIS:  res = yAxis;    break;
    case Axis::Z_AXIS:  res = zAxis;    break;
    }
    return res;
}

f32 Mat3::Determinant()
{
    f32 det  = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
    det     -= m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
    det     += m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
    return det;
}

// TODO: credit eric lengyel FGED math
void Mat3::Invert()
{
    // get the determinant of all three axes'
    f32 det  = xAxis.x * (yAxis.y * zAxis.z - yAxis.z * zAxis.y);
    det     -= xAxis.y * (yAxis.x * zAxis.z - yAxis.z * zAxis.x);
    det     += xAxis.z * (yAxis.x * zAxis.y - yAxis.y * zAxis.x);

    // get the cross product
    Vec3 r0 = Vec3::Cross(yAxis, zAxis);
    Vec3 r1 = Vec3::Cross(zAxis, xAxis);
    Vec3 r2 = Vec3::Cross(xAxis, yAxis);
    
    // set the matrices
    xAxis.SetXYZ(r0.x, r1.x, r2.x);
    yAxis.SetXYZ(r0.y, r1.y, r2.y);
    zAxis.SetXYZ(r0.z, r1.z, r2.z);
    
    // don't forget the determinant 
    *this *= 1.0f/det;
}

void Mat3::RotateEuler(const f32 angX, const f32 angY, const f32 angZ)
{
    // rotation order
    // yaw(y) <- pitch(x) <- roll(z) <- v

    // roll
    f32 cosRoll = Math::Cos(angZ);
    f32 sinRoll = Math::Sin(angZ);

    // pitch
    f32 cosPitch = Math::Cos(angX);
    f32 sinPitch = Math::Sin(angX);

    // yaw
    f32 cosYaw = Math::Cos(angY);
    f32 sinYaw = Math::Sin(angY);

    // x-axis
    xAxis.x = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
    xAxis.y = cosPitch * sinRoll;
    xAxis.z = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;

    // y-axis
    yAxis.x = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
    yAxis.y = cosPitch * cosRoll;
    yAxis.z = sinYaw * sinRoll + cosYaw * sinPitch * cosRoll;

    // z-axis
    zAxis.x = sinYaw * cosPitch;
    zAxis.y = -sinPitch;
    zAxis.z = cosYaw * cosPitch;
}

void Mat3::RotateAxis(const Axis axis, const f32 ang)
{
    switch (axis)
    {
    case Axis::X_AXIS:
    {
        RotateEuler(ang, 0.f, 0.f);
        break;
    }
    case Axis::Y_AXIS:
    {
        RotateEuler(0.f, ang, 0.f);
        break;
    }
    case Axis::Z_AXIS:
    {
        RotateEuler(0.f, 0.f, ang);
        break;
    }
    default:
        assert(false);
        break;
    }
}

f32 Mat3::GetAxisEuler(const Axis axis)
{
    // do some arctan magic to get the angle
    // TODO: check if my arctan magic works
    f32 res = 0.f;
    switch (axis)
    {
    case Axis::X_AXIS:
    {
        Vec3 zAxisNorm = zAxis.Normalized();
        res = Math::Atan(-zAxisNorm.y, zAxisNorm.x);
        break;
    }
    case Axis::Y_AXIS:
    {
        Vec3 zAxisNorm = zAxis.Normalized();
        res = Math::Atan(zAxisNorm.x, zAxisNorm.z);
        break;
    }
    case Axis::Z_AXIS:
    {
        Vec3 xAxisNorm = xAxis.Normalized();
        res = Math::Atan(xAxisNorm.y, xAxisNorm.x);
        break;
    }
    default:
        assert(false);
        break;
    }
    return res;
}

Vec3 Mat3::GetEuler()
{
    using namespace Math;

    // do some arctan magic to get the angle
    // TODO: check if my arctan magic works
    // noramlize the axes
    Vec3 xAxisNorm = xAxis.Normalized();
    Vec3 yAxisNorm = yAxis.Normalized();
    Vec3 zAxisNorm = zAxis.Normalized();

    Vec3 euler;
    euler.x = Asin(-zAxisNorm.y);
    
    // handle gimbal lock
    if (Abs(Cos(euler.x)) < 0.0001f)
    {
        euler.y = 0.f;
        euler.z = Atan(-yAxisNorm.x, xAxisNorm.x);
    }
    else
    {
        euler.y = Atan(zAxisNorm.x, zAxisNorm.z);
        euler.z = Atan(xAxisNorm.y, xAxisNorm.x);
    }
    return euler;
}

void Mat3::SetScale(const f32 scale)
{
    xAxis *= scale;
    yAxis *= scale;
    zAxis *= scale;
}

void Mat3::SetAxisScale(const Axis axis, const f32 scale)
{
    switch (axis)
    {
    case Axis::X_AXIS:
    {
        xAxis *= scale;
        break;
    }
    case Axis::Y_AXIS:
    {
        yAxis *= scale;
        break;
    }
    case Axis::Z_AXIS:
    {
        zAxis *= scale;
        break;
    }
    default:
        assert(false);
        break;
    }
}

void Mat3::SetScalePerAxis(const f32 scaleX, const f32 scaleY, const f32 scaleZ)
{
    xAxis *= scaleX;
    yAxis *= scaleY;
    zAxis *= scaleZ;
}

f32 Mat3::GetAxisScale(const Axis axis)
{
    f32 len = 0.f;
    switch (axis)
    {
    case Axis::X_AXIS:
    {
        len = xAxis.Length();
        break;
    }
    case Axis::Y_AXIS:
    {
        len = yAxis.Length();
        break;
    }
    case Axis::Z_AXIS:
    {
        len = zAxis.Length();
        break;
    }
    default:
        assert(false);
        break;
    }
    return len;
}

Vec3 Mat3::GetScale()
{
    return Vec3(xAxis.Length(), yAxis.Length(), zAxis.Length());
}

/*static*/ Mat3 Mat3::GetIdentity()
{
    return Mat3(1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.f, 0.f, 1.f);
}

/*static*/ Mat3 Mat3::GetZero()
{
    return Mat3(0.f, 0.f, 0.f,
                0.f, 0.f, 0.f,
                0.f, 0.f, 0.f);
}

