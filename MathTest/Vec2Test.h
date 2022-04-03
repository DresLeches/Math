#pragma once

// gtest
#include "gtest/gtest.h"

// vec3
#include "Defines.h"
#include "Vec2.h"
#include "EngineMath.h"



class Vec2Test : public ::testing::Test 
{
protected:

    // vec
    Vec2 zero;
    Vec2 basic;
    Vec2 norm;
    Vec2 angTest1;
    Vec2 angTest2;

    // set up
    void SetUp() override
    {
        zero = Vec2(0.f);
        basic = Vec2(3.f, 4.f);
        norm = Vec2(5.f, 0.f);
        angTest1 = Vec2(1.f, 0.f);
        angTest2 = Vec2(0.7071067811865f, 0.7071067811865f);
    }

    // tear down
    void TearDown() override { }
};

TEST_F(Vec2Test, DotTest)
{
    EXPECT_EQ(zero.Dot(zero), 0.f);
    EXPECT_EQ(basic.Dot(basic), 25.f);
    EXPECT_EQ(Vec2::Dot(basic, basic), 25.f);
}

TEST_F(Vec2Test, LengthTest)
{
    EXPECT_EQ(zero.Length(), 0.f);
    EXPECT_EQ(basic.Length(), 5.f);
}

TEST_F(Vec2Test, LengthSqTest)
{
    EXPECT_EQ(basic.LengthSq(), 25.f);
}

TEST_F(Vec2Test, NormalizeTest)
{
    norm.Normalize();
    EXPECT_EQ(norm.x, 1.f);
    EXPECT_EQ(norm.y, 0.f);
}

TEST_F(Vec2Test, NormalizedTest)
{
    Vec2 val = norm.Normalized();
    EXPECT_EQ(val.x, 1.f);
    EXPECT_EQ(val.y, 0.f);
}

TEST_F(Vec2Test, InverseTest)
{
    basic.Inverse();
    EXPECT_EQ(basic.x, 1.f / 3.f);
    EXPECT_EQ(basic.y, 1.f / 4.f);
}

TEST_F(Vec2Test, AngleTest)
{
    const f32 ang = Math::ToDeg(Vec2::GetAngle(angTest1, angTest2));
    EXPECT_EQ(Math::IsEqualF(ang, 45.f), true);
}

