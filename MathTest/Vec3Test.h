#pragma once
#include "gtest/gtest.h"

// vec3
#include "Defines.h"
#include "Vec3.h"


class Vec3Test : public ::testing::Test
{
protected:

    // vec
    Vec3 zero;
    Vec3 one;
    Vec3 basic;
    Vec3 norm;

    // set up
    void SetUp() override
    {
        zero = Vec3(0.f);
        one = Vec3(1.f);
        basic = Vec3(3.f, 4.f, 5.f);
        norm = Vec3(5.f, 0.f, 0.f);
    }

    // tear down
    void TearDown() override { }
};

TEST_F(Vec3Test, DotTest)
{
    EXPECT_EQ(one.Dot(basic), 12.f);
    EXPECT_EQ(Vec3::Dot(one, basic), 12.f);
}

TEST_F(Vec3Test, LengthTest)
{
    EXPECT_EQ(zero.Length(), 0.f);
    EXPECT_EQ(basic.Length(), 7.0710678f);
}

TEST_F(Vec3Test, LengthSqTest)
{
    EXPECT_EQ(basic.LengthSq(), 50.f);
}

TEST_F(Vec3Test, NormalizeTest)
{
    norm.Normalize();
    EXPECT_EQ(norm.x, 1.f);
    EXPECT_EQ(norm.y, 0.f);
    EXPECT_EQ(norm.z, 0.f);
}

TEST_F(Vec3Test, NormalizedTest)
{
    Vec3 res = norm.Normalized();
    EXPECT_EQ(res.x, 1.f);
    EXPECT_EQ(res.y, 0.f);
    EXPECT_EQ(res.z, 0.f);
}

TEST_F(Vec3Test, CrossTest)
{
    {
        Vec3 res = basic.Cross(one);
        EXPECT_EQ(res.x, -1.f);
        EXPECT_EQ(res.y, 2.f);
        EXPECT_EQ(res.z, -1.f);
    }
    {
        Vec3 res = Vec3::Cross(basic, one);
        EXPECT_EQ(res.x, -1.f);
        EXPECT_EQ(res.y, 2.f);
        EXPECT_EQ(res.z, -1.f);
    }
}

TEST_F(Vec3Test, InverseTest)
{
    basic.Inverse();
    EXPECT_EQ(basic.x, 1.f / 3.f);
    EXPECT_EQ(basic.y, 1.f / 4.f);
    EXPECT_EQ(basic.z, 1.f / 5.f);
}

