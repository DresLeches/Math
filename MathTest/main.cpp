#include <cstdio>
#include "gtest/gtest.h"
#include "Vec2Test.h"
#include "Vec3Test.h"
#include "Vec4Test.h"
#include "Mat3Test.h"
#include "Mat4Test.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}