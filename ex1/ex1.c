// Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable
// (e.g., x) and set its value to something (e.g., 100).
// What value is the variable in the child process?
//  Starts at the value set pre-fork, then updates to the child set value for the remainder of the lifetime of the child process.
// What happens to the variable when both the child and parent change the value of x?
//  The child-set value remains that way for the lifetime of the child, and the parent-set value remains that way for the lifetime of the parent. They're mutually exclusive that way.

// ~~ Output ~~
// $ ./ex1
// Pre-fork x: 0, from PID: 2870
// Parent PID: 2870
// Parent before setting x: 0
// Parent after setting x: 100
// Post-fork x: 100, from PID: 2870
// Child PID: 2871
// Child before setting x: 0
// Child after setting x: 50
// Post-fork x: 50, from PID: 2871

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    // Your code here
    int x = 0;
    printf("Pre-fork x: %i, from PID: %i\n", x, (int)getpid());

    int fark = fork();
    if (fark < 0)
    {
        fprintf(stderr, "Failed to fork child process\n");
        exit(1);
    }
    else if (fark == 0)
    {
        printf("Child PID: %i\n", (int)getpid());
        printf("Child before setting x: %i\n", x);
        x = 50;
        printf("Child after setting x: %i\n", x);
    }
    else
    {
        printf("Parent PID: %i\n", (int)getpid());
        printf("Parent before setting x: %i\n", x);
        x = 100;
        printf("Parent after setting x: %i\n", x);
    }

    printf("Post-fork x: %i, from PID: %i\n", x, (int)getpid());

    return 0;
}
