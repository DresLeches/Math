#pragma once
#include "Mat3.h"
#include "EngineMath.h"
#include "gtest/gtest.h"


class Mat3Test : public ::testing::Test
{
protected:

    // mat
    Mat3 zero;
    Mat3 identity;
    Mat3 basic;
    Mat3 basic1;

    // set up
    void SetUp() override
    {
        zero = Mat3::GetZero();
        identity = Mat3::GetIdentity();
        basic = Mat3(Vec3(1.f, 0.f, 0.f), Vec3(0.f, 2.f, 0.f), Vec3(0.f, 0.f, 3.f));
        basic1 = Mat3(Vec3(1.f, 2.f, 3.f), Vec3(4.f, 5.f, 6.f), Vec3(7.f, 8.f, 9.f));
    }

    // tear down
    void TearDown() override { }
};

TEST_F(Mat3Test, TranposeTest)
{
    Mat3 res = Mat3(1.f, 2.f, 3.f,
                    4.f, 5.f, 6.f,
                    7.f, 8.f, 9.f);
    basic1.Transpose();
    EXPECT_EQ(Vec3::IsEqual(res.xAxis, basic1.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.yAxis, basic1.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.zAxis, basic1.zAxis), true);
}

TEST_F(Mat3Test, DeterminantTest)
{
    f32 res = basic1.Determinant();
    EXPECT_EQ(res, 0.f);
}

TEST_F(Mat3Test, InvertTest)
{
    Mat3 res = Mat3(1.f, 0.f, 0.f,
                    0.f, 0.5f, 0.f,
                    0.f, 0.f, 0.3333f);
    basic.Invert();
    EXPECT_EQ(Vec3::IsEqual(res.xAxis, basic.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.yAxis, basic.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.zAxis, basic.zAxis), true);
}

TEST_F(Mat3Test, RotateEulerTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat3 rot = Mat3(1.f,    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),    -Math::Sin(piOver4),
                    0.f,    Math::Sin(piOver4),    Math::Cos(piOver4));
    Mat3 res = Mat3(1.f,    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),    -Math::Sin(piOver4),
                    0.f,    Math::Sin(piOver4),    Math::Cos(piOver4));
    Mat3 rotatedMat = rot * identity;
    EXPECT_EQ(Vec3::IsEqual(res.xAxis, rotatedMat.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.yAxis, rotatedMat.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.zAxis, rotatedMat.zAxis), true);
}

TEST_F(Mat3Test, MatScaleTest)
{
    Mat3 res = Mat3(2.f, 0.f, 0.f,
                    0.f, 2.f, 0.f,
                    0.f, 0.f, 2.f);
    identity.SetScale(2.f);
    EXPECT_EQ(Vec3::IsEqual(res.xAxis, identity.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.yAxis, identity.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.zAxis, identity.zAxis), true);
}


TEST_F(Mat3Test, MatAxisScaleTest)
{
    Mat3 res = Mat3(1.f, 0.f, 0.f,
                    0.f, 2.f, 0.f,
                    0.f, 0.f, 3.f);
    identity.SetScalePerAxis(1.f, 2.f, 3.f);
    EXPECT_EQ(Vec3::IsEqual(res.xAxis, identity.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.yAxis, identity.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(res.zAxis, identity.zAxis), true);
}

TEST_F(Mat3Test, MatGetScale)
{
    Vec3 res(1.f, 2.f, 3.f);
    Vec3 vec = basic.GetScale();
    EXPECT_EQ(res.x, 1.f);
    EXPECT_EQ(res.y, 2.f);
    EXPECT_EQ(res.z, 3.f);
}

TEST_F(Mat3Test, GetEulerTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat3 rot = Mat3(1.f,    0.f,                    0.f,
                    0.f,    Math::Cos(piOver4),    -Math::Sin(piOver4),
                    0.f,    Math::Sin(piOver4),     Math::Cos(piOver4));
    Vec3 res(piOver4, 0.f, 0.f);
    Vec3 test = rot.GetEuler();
    EXPECT_EQ(Math::IsEqualF(res.x, test.x), true);
    EXPECT_EQ(Math::IsEqualF(res.y, test.y), true);
    EXPECT_EQ(Math::IsEqualF(res.z, test.z), true);
}

TEST_F(Mat3Test, EulerGimbalLockTest)
{
    constexpr f32 piOver4 = Math::PI / 4.f;
    Mat3 rotX = Mat3(1.f,    0.f,                            0.f,
                     0.f,    Math::Cos(Math::PI_OVER_2),     -Math::Sin(Math::PI_OVER_2),
                     0.f,    Math::Sin(Math::PI_OVER_2),      Math::Cos(Math::PI_OVER_2));
    Mat3 rotY = Mat3(Math::Cos(piOver4),    0.f,        Math::Sin(piOver4),
                     0.f,                       1.f,        0.f,
                     -Math::Sin(piOver4),        0.f,        Math::Cos(piOver4));
    Mat3 rotZ = Mat3(Math::Cos(piOver4),    -Math::Sin(piOver4),       0.f,
                     Math::Sin(piOver4),    Math::Cos(piOver4),        0.f,
                     0.f,                   0.f,                       1.f);
    Vec3 res(Math::PI_OVER_2, 0.f, 0.f);
    Vec3 test = (rotY * (rotX * rotZ)).GetEuler();
    EXPECT_EQ(Math::IsEqualF(res.x, test.x), true);
    EXPECT_EQ(Math::IsEqualF(res.y, test.y), true);
    EXPECT_EQ(Math::IsEqualF(res.z, test.z), true);
}

TEST_F(Mat3Test, MultiMatMatTest)
{
    Mat3 test = basic1;
    test = test * identity;
    EXPECT_EQ(Vec3::IsEqual(basic1.xAxis, test.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(basic1.yAxis, test.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(basic1.zAxis, test.zAxis), true);
}

TEST_F(Mat3Test, MultiMatVecTest)
{
    Vec3 test(1.f, 2.f, 3.f);
    Vec3 res = identity * test;
    EXPECT_EQ(Math::IsEqualF(res.x, 1.f), true);
    EXPECT_EQ(Math::IsEqualF(res.y, 2.f), true);
    EXPECT_EQ(Math::IsEqualF(res.z, 3.f), true);
}

TEST_F(Mat3Test, UnaryMultiMatMatTest)
{
    Mat3 test = basic1;
    test *= identity;
    EXPECT_EQ(Vec3::IsEqual(basic1.xAxis, test.xAxis), true);
    EXPECT_EQ(Vec3::IsEqual(basic1.yAxis, test.yAxis), true);
    EXPECT_EQ(Vec3::IsEqual(basic1.zAxis, test.zAxis), true);
}

