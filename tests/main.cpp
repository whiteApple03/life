#define CTEST_MAIN

#include "../thirdparty/ctest.h"

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}

CTEST(cirlce1, check_area)
{
    ASSERT_DBL_NEAR_TOL(3.14, 3.14, 0.01);
}