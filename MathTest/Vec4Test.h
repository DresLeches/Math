#pragma once
#include "gtest/gtest.h"

// vec3
#include "Defines.h"
#include "Vec4.h"


class Vec4Test : public ::testing::Test
{
protected:

    // vec
    Vec4 zero;
    Vec4 one;
    Vec4 basic;
    Vec4 norm;

    // set up
    void SetUp() override
    {
        zero = Vec4(0.f);
        one = Vec4(1.f);
        basic = Vec4(1.f, 2.f, 3.f, 4.f);
        norm = Vec4(5.f, 0.f, 0.f, 0.f);
    }

    // tear down
    void TearDown() override { }
};

TEST_F(Vec4Test, DotTest)
{
    EXPECT_EQ(one.Dot(basic), 10.f);
    EXPECT_EQ(Vec4::Dot(one, basic), 10.f);
}

TEST_F(Vec4Test, LengthTest)
{
    EXPECT_EQ(zero.Length(), 0.f);
    EXPECT_EQ(Math::IsEqualF(basic.Length(), 5.47722f), true);
}

TEST_F(Vec4Test, LengthSqTest)
{
    EXPECT_EQ(basic.LengthSq(), 30.f);
}

TEST_F(Vec4Test, NormalizeTest)
{
    norm.Normalize();
    EXPECT_EQ(norm.x, 1.f);
    EXPECT_EQ(norm.y, 0.f);
    EXPECT_EQ(norm.z, 0.f);
    EXPECT_EQ(norm.w, 0.f);
}

TEST_F(Vec4Test, NormalizedTest)
{
    Vec4 res = norm.Normalized();
    EXPECT_EQ(res.x, 1.f);
    EXPECT_EQ(res.y, 0.f);
    EXPECT_EQ(res.z, 0.f);
    EXPECT_EQ(res.w, 0.f);
}

TEST_F(Vec4Test, InverseTest)
{
    basic.Inverse();
    EXPECT_EQ(basic.x, 1.f / 1.f);
    EXPECT_EQ(basic.y, 1.f / 2.f);
    EXPECT_EQ(basic.z, 1.f / 3.f);
    EXPECT_EQ(basic.w, 1.f / 4.f);
}

