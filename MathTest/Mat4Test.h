#pragma once
#include "Mat4.h"
#include "EngineMath.h"
#include "gtest/gtest.h"


class Mat4Test : public ::testing::Test
{
protected:

    // mat
    Mat4 zero;
    Mat4 identity;
    Mat4 basic;
    Mat4 basic1;

    // set up
    void SetUp() override
    {
        zero = Mat4::GetZero();
        identity = Mat4::GetIdentity();
        basic = Mat4(Vec4(1.f, 0.f, 0.f, 0.f), Vec4(0.f, 2.f, 0.f, 0.f), Vec4(0.f, 0.f, 3.f, 0.f), Vec4(0.f, 0.f, 0.f, 1.f));
        basic1 = Mat4(Vec4(1.f, 2.f, 3.f, 0.f), Vec4(4.f, 5.f, 6.f, 0.f), Vec4(7.f, 8.f, 9.f, 0.f), Vec4(0.f, 0.f, 0.f, 1.f));
    }

    // tear down
    void TearDown() override { }
};

TEST_F(Mat4Test, TranposeTest)
{
    Mat4 res = Mat4(1.f, 2.f, 3.f, 0.f,
                    4.f, 5.f, 6.f, 0.f,
                    7.f, 8.f, 9.f, 0.0f,
                    0.f, 0.f, 0.f, 1.f);
    basic1.Transpose();
    EXPECT_EQ(Vec4::IsEqual(res.xAxis, basic1.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.yAxis, basic1.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.zAxis, basic1.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.translation, basic1.translation), true);
}

TEST_F(Mat4Test, InvertTest)
{
    Mat4 res = Mat4(1.f,    0.f,   0.f,     0.f,
                    0.f,    0.5f,  0.f,     0.f,
                    0.f,    0.f,   0.3333f, 0.f,
                    0.f,    0.f,   0.f,     1.f);
    basic.Invert();
    EXPECT_EQ(Vec4::IsEqual(res.xAxis, basic.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.yAxis, basic.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.zAxis, basic.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.translation, basic.translation), true);
}

TEST_F(Mat4Test, RotateEulerTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat4 rot = Mat4(1.f,    0.f,                    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),     -Math::Sin(piOver4),    0.f,
                    0.f,    Math::Sin(piOver4),     Math::Cos(piOver4),     0.f,
                    0.f,    0.f,                    0.f,                    1.f);
    Mat4 res = Mat4(1.f,    0.f,                    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),     -Math::Sin(piOver4),    0.f,
                    0.f,    Math::Sin(piOver4),     Math::Cos(piOver4),     0.f,
                    0.f,    0.f,                    0.f,                    1.f);
    Mat4 rotatedMat = rot * identity;
    EXPECT_EQ(Vec4::IsEqual(res.xAxis, rotatedMat.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.yAxis, rotatedMat.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.zAxis, rotatedMat.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.translation, rotatedMat.translation), true);
}

TEST_F(Mat4Test, MatScaleTest)
{
    Mat4 res = Mat4(2.f, 0.f, 0.f, 0.f,
                    0.f, 2.f, 0.f, 0.f,
                    0.f, 0.f, 2.f, 0.f,
                    0.f, 0.f, 0.f, 1.f);
    identity.SetScale(2.f);
    EXPECT_EQ(Vec4::IsEqual(res.xAxis, identity.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.yAxis, identity.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.zAxis, identity.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.translation, identity.translation), true);
}


TEST_F(Mat4Test, MatAxisScaleTest)
{
    Mat4 res = Mat4(1.f, 0.f, 0.f, 0.f,
                    0.f, 2.f, 0.f, 0.f,
                    0.f, 0.f, 3.f, 0.f,
                    0.f, 0.f, 0.f, 1.f);
    identity.SetScalePerAxis(1.f, 2.f, 3.f);
    EXPECT_EQ(Vec4::IsEqual(res.xAxis, identity.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.yAxis, identity.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.zAxis, identity.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(res.translation, identity.translation), true);
}

TEST_F(Mat4Test, MatGetScale)
{
    Vec3 res(1.f, 2.f, 3.f);
    Vec3 vec = basic.GetScale();
    EXPECT_EQ(res.x, 1.f);
    EXPECT_EQ(res.y, 2.f);
    EXPECT_EQ(res.z, 3.f);
}

TEST_F(Mat4Test, GetEulerTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat4 rot = Mat4(1.f,    0.f,                    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),     -Math::Sin(piOver4),    0.f,
                    0.f,    Math::Sin(piOver4),     Math::Cos(piOver4),     0.f,
                    0.f,    0.f,                    0.f,                    1.f);
    Vec3 res(piOver4, 0.f, 0.f);
    Vec3 test = rot.GetEuler();
    EXPECT_EQ(Math::IsEqualF(res.x, test.x), true);
    EXPECT_EQ(Math::IsEqualF(res.y, test.y), true);
    EXPECT_EQ(Math::IsEqualF(res.z, test.z), true);
}

TEST_F(Mat4Test, EulerGimbalLockTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat4 rotX = Mat4(1.f,    0.f,                            0.f,                            0.f,
                    0.f,    Math::Cos(Math::PI_OVER_2),     -Math::Sin(Math::PI_OVER_2),    0.f,
                    0.f,    Math::Sin(Math::PI_OVER_2),     Math::Cos(Math::PI_OVER_2),     0.f,
                    0.f,    0.f,                            0.f,                            1.f);
    Mat4 rotY = Mat4(Math::Cos(piOver4),        0.f,        Math::Sin(piOver4),     0.f,
                     0.f,                       1.f,        0.f,                    0.f,
                     -Math::Sin(piOver4),       0.f,        Math::Cos(piOver4),     0.f,
                     0.f,                       0.f,        0.f,                    1.f);
    Mat4 rotZ = Mat4(Math::Cos(piOver4),    -Math::Sin(piOver4),       0.f,         0.f,
                     Math::Sin(piOver4),    Math::Cos(piOver4),        0.f,         0.f,
                     0.f,                   0.f,                       1.f,         0.f,
                     0.f,                   0.f,                       0.f,         1.f);
    Vec3 res(Math::PI_OVER_2, 0.f, 0.f);
    Vec3 test = rotX.GetEuler();
    EXPECT_EQ(Math::IsEqualF(res.x, test.x), true);
    EXPECT_EQ(Math::IsEqualF(res.y, test.y), true);
    EXPECT_EQ(Math::IsEqualF(res.z, test.z), true);
}

TEST_F(Mat4Test, MultiMatMatTest)
{
    Mat4 test = basic1;
    test = test * identity;
    EXPECT_EQ(Vec4::IsEqual(basic1.xAxis, test.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.yAxis, test.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.zAxis, test.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.translation, test.translation), true);
}

TEST_F(Mat4Test, MultiMatVecTest)
{
    Vec4 test(1.f, 2.f, 3.f, 1.f);
    Vec4 res = identity * test;
    EXPECT_EQ(Math::IsEqualF(1.f, res.x), true);
    EXPECT_EQ(Math::IsEqualF(2.f, res.y), true);
    EXPECT_EQ(Math::IsEqualF(3.f, res.z), true);
    EXPECT_EQ(Math::IsEqualF(1.f, res.w), true);
}

TEST_F(Mat4Test, UnaryMultiMatMatTest)
{
    Mat4 test = basic1;
    test *= identity;
    EXPECT_EQ(Vec4::IsEqual(basic1.xAxis, test.xAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.yAxis, test.yAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.zAxis, test.zAxis), true);
    EXPECT_EQ(Vec4::IsEqual(basic1.translation, test.translation), true);
}

