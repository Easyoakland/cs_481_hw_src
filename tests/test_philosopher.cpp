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
    int n = 5;
    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    diners_t* diners = (diners_t*)malloc(n*sizeof(diners_t));
    sem_t** forks = (sem_t**)malloc(n*sizeof(sem_t*));
    bool* eat = (bool*)malloc(n*sizeof(bool));
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    char buf[10];
    
    for (int i = 0; i < n; i++)
    {
        eat[i] = false;
        snprintf(buf, 10, "forks_%d", i);
        forks[i] = sem_open(buf, O_CREAT, S_IRUSR | S_IWUSR, 1);
    }

    for (int i = 0; i < n; i++)
    {
        diners[i].forks = forks;
        diners[i].size = n;
        diners[i].mutex = mutex;
        diners[i].eat = eat;
        diners[i].philosopher = i;

        pthread_create(&(threads[i]), NULL, philosopher, &(diners[i]));
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
        ASSERT_EQ(eat[i], true);
    }

    for (int i = 0; i < n; i++)
    {
        sem_close(forks[i]);
        snprintf(buf, 10, "forks_%d", i);
        sem_unlink(buf);
    }

    pthread_mutex_destroy(&mutex);

    free(forks);
    free(diners);
    free(threads);
}
