#pragma once
#include "EngineMath.h"
#include "gtest/gtest.h"


TEST(MathTest, ToRadTest)
{
    using namespace Math;

    const f32 piOver4 = PI_OVER_2 / 2.f;
    EXPECT_EQ(ToRad(45.f), piOver4);
    EXPECT_EQ(ToRad(90.f), PI_OVER_2);
    EXPECT_EQ(ToRad(180.f), PI);
    EXPECT_EQ(ToRad(270.f), PI * 3.f / 2.f);
}

TEST(MathTest, ToDegTest)
{
    using namespace Math;

    const f32 piOver4 = PI_OVER_2 / 2.f;
    EXPECT_EQ(ToDeg(piOver4), 45.f);
    EXPECT_EQ(ToDeg(PI_OVER_2), 90.f);
    EXPECT_EQ(ToDeg(PI), 180.f);
    EXPECT_EQ(ToDeg(PI * 3.f / 2.f), 270.f);
}

TEST(Math, ClampTest)
{
    using namespace Math;
    EXPECT_EQ(Clamp(5.f, 10.f, 20.f), 10.f);
    EXPECT_EQ(Clamp(15.f, 0.f, 10.f), 10.f);
}

TEST(Math, IsZeroTest)
{
    using namespace Math;
    EXPECT_NE(IsZero(0.1f), true);
    EXPECT_EQ(IsZero(0.0000000001f), true);
}



