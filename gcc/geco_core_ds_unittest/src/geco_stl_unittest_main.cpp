#include <iostream>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <pthread.h>

TEST(testcase1, testHello)
{
    printf("hello\n");
}

#if GTEST_OS_WINDOWS_MOBILE
# include <tchar.h>  // NOLINT
GTEST_API_ int _tmain(int argc, TCHAR** argv)
{
#else
    GTEST_API_ int main(int argc, char** argv)
    {
#endif  // GTEST_OS_WINDOWS_MOBILE
        std::cout << "Running main() from gmock_main.cc\n";
        // Since Google Mock depends on Google Test, InitGoogleMock() is
        // also responsible for initializing Google Test.  Therefore there's
        // no need for calling testing::InitGoogleTest() separately.
        testing::InitGoogleMock(&argc, argv);
        return RUN_ALL_TESTS();
    }
