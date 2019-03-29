/*
Write a program that will find the average time it takes for your computer
to make a system call an empty write to stdout. Your program should use the
`clock_gettime` procedure to time how long a single system call takes. It'll
do this for one million iterations, and then find the average of all of those
iterations in nanoseconds.
For some helpful documentation and examples of using time-related system calls,
visit this site: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
While the linked site does say that `clock_gettime()` does not work on OSX, this
turns out to only be the case for OSX versions < 10.12. Anything later than that
and `clock_gettime()` should work just fine.
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define number_iter 1000000
#define BILLION 1000000000L

int main()
{
    // Your code here

    uint64_t diff;
    struct timespec start, end;
    const void *buf;
    uint64_t runtimes = 0;

    for (int i = 0; i < number_iter; i++)
    {
        // Monotonic clock used mainly because it can't be set by a user with
        // enough permissions on their system, unlike CLOCK_REALTIME. Only gets
        // adjusted by adjtime and NTP.
        /* mark start time */
        clock_gettime(CLOCK_MONOTONIC, &start);

        // http://codewiki.wikidot.com/c:system-calls:write
        // Does a zero-byte output (arg 3) to stdout (arg 1) based on a const void buffer (arg 2) that's still defaulting to NULL
        write(1, buf, 0);

        /* mark the end time */
        clock_gettime(CLOCK_MONOTONIC, &end);

        // calculate the time difference and add the runtime to runtimes
        //     |--convert seconds to nanoseconds---| + trailing nanoseconds
        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        runtimes = runtimes + diff;
    }

    printf("average runtime: %llu nanoseconds\n", (long long unsigned int)runtimes / number_iter);

    return 0;
}
