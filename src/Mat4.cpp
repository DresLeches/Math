#include "Mat4.h"
#include "EngineMath.h"
#include <cstring>
#include <cassert>


Mat4::Mat4(const Vec4& xAxis, const Vec4& yAxis, const Vec4& zAxis, const Vec4& t)
    : xAxis(xAxis)
    , yAxis(yAxis)
    , zAxis(zAxis)
    , translation(t)
{
}

Mat4::Mat4(const f32* arr, const u32 len)
{
    memcpy(a, arr, sizeof(f32) * len);
}

Mat4::Mat4(const f32 m00, const f32 m01, const f32 m02, const f32 m03, 
           const f32 m10, const f32 m11, const f32 m12, const f32 m13, 
           const f32 m20, const f32 m21, const f32 m22, const f32 m23, 
           const f32 m30, const f32 m31, const f32 m32, const f32 m33)
{
    m[0][0] = m00;  m[0][1] = m10;  m[0][2] = m20;  m[0][3] = m30;
    m[1][0] = m01;  m[1][1] = m11;  m[1][2] = m21;  m[1][3] = m31;
    m[2][0] = m02;  m[2][1] = m12;  m[2][2] = m22;  m[2][3] = m32;
    m[3][0] = m03;  m[3][1] = m13;  m[3][2] = m23;  m[3][3] = m33;
}

void Mat4::MakeOrtho(const Vec3& min, const Vec3& max)
{
    // inverse
    f32 invWidth = 1.f / (max.x - min.x);
    f32 invHeight = 1.f / (max.y - min.y);
    f32 invDepth = 1.f / (max.z - min.z);

    // axes
    xAxis.SetXYZW(  2.f * invWidth,  0.f,                0.f,                0.f  );
    yAxis.SetXYZW(  0.f,             2.f * invHeight,    0.f,                0.f  );
    zAxis.SetXYZW(  0.f,             0.f,                1.f * invDepth,     0.f  );
    translation.SetXYZW(-(min.x + max.x) * invWidth, -(min.y + max.y) * invHeight, min.z * invDepth, 0.f);
}

// TODO: credit Eric Lengyel for this brilliant for mathematical formula
void Mat4::MakeProj(const f32 fov, const f32 aspectRatio, const f32 near, const f32 epsilon /* = 1.f */)
{
    const f32 g = 1.f / Math::Tan(fov * 0.5f);
    const f32 invEpsilon = epsilon;
    
    // axes
    xAxis.SetXYZW(  g / aspectRatio,    0.f,    0.f,            0.f);
    yAxis.SetXYZW(  0.f,                g,      0.f,            0.f);
    zAxis.SetXYZW(  0.f,                0.f,    invEpsilon,     -near * invEpsilon);
    translation.SetXYZW(0.f, 0.f, 1.f, 0.f);
}

void Mat4::MakeLookAt(const Vec3& pos, const Vec3& dir)
{
    const Vec3 side = Vec3::Cross(dir, Vec3(0.f, 1.f, 0.f)).Normalized();
    const Vec3 up = Vec3::Cross(dir, side).Normalized();
    xAxis.SetXYZW(dir.x, dir.y, dir.z, 0.f);
    yAxis.SetXYZW(side.x, side.y, side.z, 0.f);
    zAxis.SetXYZW(up.x, up.y, up.z, 0.f);
    translation.SetXYZW(pos.x, pos.y, pos.z, 1.f);
}

void Mat4::Transpose()
{
    for (u32 i = 0; i < 3; i++)
    {
        for (u32 j = i + 1; j < 4; j++)
        {
            Math::Swap(m[i][j], m[j][i]);
        }
    }
}

void Mat4::SetIdentity()
{
    m[0][0] = 1.f;
    m[1][1] = 1.f;
    m[2][2] = 1.f;
    m[3][3] = 1.f;
}

void Mat4::SetZero()
{
    memset(a, 0, sizeof(f32) * 16);
}

Vec3 Mat4::GetAxis(const Axis axis)
{
    Vec3 res;
    switch (axis)
    {
    case Axis::X_AXIS:  res = xAxisVec3;    break;
    case Axis::Y_AXIS:  res = yAxisVec3;    break;
    case Axis::Z_AXIS:  res = zAxisVec3;    break;
    }
    return res;
}

Vec3 Mat4::GetTranslation() const
{
    return translationVec3;
}

void Mat4::Invert()
{
    // TODO: credit eric lengyel's FGED vol 1 lol
    const Vec3 a = xAxisVec3;
    const Vec3 b = yAxisVec3;
    const Vec3 c = zAxisVec3;
    const Vec3 d = translationVec3;

    const f32 x = m[0][3];
    const f32 y = m[1][3];
    const f32 z = m[2][3];
    const f32 w = m[3][3];
    
    Vec3 s = Vec3::Cross(a, b);
    Vec3 t = Vec3::Cross(c, d);
    Vec3 u = y * a - x * b;
    Vec3 v = w * c - z * d;

    f32 invDet = 1.f / (Vec3::Dot(s, v) + Vec3::Dot(t, u));
    s *= invDet;
    t *= invDet;
    u *= invDet;
    v *= invDet;
    
    Vec3 r0 = Vec3::Cross(b, v) + y * t;
    Vec3 r1 = Vec3::Cross(v, a) - x * t;
    Vec3 r2 = Vec3::Cross(d, u) + w * s;
    Vec3 r3 = Vec3::Cross(u, c) - z * s;

    // manually insert the result into the matrix
    m[0][0] = r0.x;             m[0][1] = r1.x;             m[0][2] = r2.x;             m[0][3] = r3.x;
    m[1][0] = r0.y;             m[1][1] = r1.y;             m[1][2] = r2.y;             m[1][3] = r3.y;
    m[2][0] = r0.z;             m[2][1] = r1.z;             m[2][2] = r2.z;             m[2][3] = r3.z;
    m[3][0] = -Vec3::Dot(b,t);  m[3][1] = Vec3::Dot(a,t);   m[3][2] = -Vec3::Dot(d,s);  m[3][3] = Vec3::Dot(c,s);
   
}

void Mat4::RotateEuler(const f32 angX, const f32 angY, const f32 angZ)
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

void Mat4::RotateAxis(const Axis axis, const f32 ang)
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

f32 Mat4::GetAxisEuler(const Axis axis)
{
    // do some arctan magic to get the angle
    // TODO: check if my arctan magic works
    f32 res = 0.f;
    switch (axis)
    {
    case Axis::X_AXIS:
    {
        Vec4 zAxisNorm = zAxis.Normalized();
        res = Math::Atan(-zAxisNorm.y, zAxisNorm.x);
        break;
    }
    case Axis::Y_AXIS:
    {
        Vec4 zAxisNorm = zAxis.Normalized();
        res = Math::Atan(zAxisNorm.x, zAxisNorm.z);
        break;
    }
    case Axis::Z_AXIS:
    {
        Vec4 xAxisNorm = xAxis.Normalized();
        res = Math::Atan(xAxisNorm.y, xAxisNorm.x);
        break;
    }
    default:
        assert(false);
        break;
    }
    return res;
}

Vec3 Mat4::GetEuler()
{
    using namespace Math;

    // do some arctan magic to get the angle
    // TODO: check if my arctan magic works
    // noramlize the axes
    Vec3 xAxisNorm = xAxisVec3.Normalized();
    Vec3 yAxisNorm = yAxisVec3.Normalized();
    Vec3 zAxisNorm = zAxisVec3.Normalized();

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

void Mat4::SetScale(const f32 scale)
{
    xAxis *= scale;
    yAxis *= scale;
    zAxis *= scale;
}

void Mat4::SetAxisScale(const Axis axis, const f32 scale)
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

void Mat4::SetScalePerAxis(const f32 scaleX, const f32 scaleY, const f32 scaleZ)
{
    xAxis *= scaleX;
    yAxis *= scaleY;
    zAxis *= scaleZ;
}

f32 Mat4::GetAxisScale(const Axis axis)
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

Vec3 Mat4::GetScale()
{
    return Vec3(xAxis.Length(), yAxis.Length(), zAxis.Length());
}

/*static*/ Mat4 Mat4::GetIdentity()
{
    return Mat4(1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f);
}

/*static*/ Mat4 Mat4::GetZero()
{
    return Mat4(0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f);
}

