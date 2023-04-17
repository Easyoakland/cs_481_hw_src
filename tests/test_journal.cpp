// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "cs_481_hw_src/src.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

TEST(TLBTest, TestsIntests)
{
    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "txe21";
    write_to_journal(5, txb, 2, ib, 2, bb, 11, str, 5, txe);

    char journal_name[] = "journal.txt";
    char sol[] = "txe12ibbbhello worldtxe21";

    int fd = open(journal_name, O_RDONLY);

    struct stat st;
    stat(journal_name, &st);
    int size = st.st_size;
    char* file_bytes = (char*)malloc(size*sizeof(char));
    read(fd, file_bytes, size);

    ASSERT_STREQ(file_bytes, sol);
    
}
