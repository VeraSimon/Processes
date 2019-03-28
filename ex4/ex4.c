#include <stdio.h>
#include <unistd.h>
// ^-- exec() lives here
#include <stdlib.h>
#include <sys/wait.h>

// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as
// `execl()`, `execle()`, `execv()`, and others.
// Why do you think there are so many variants of the same basic call?
// exec_()
//    l: comma separated argument input
//    v: vector (array) argument input
//    p: includes systems search path(s)
//    e: passes in environment config

int main(void)
{
    // Your code here
    int fark = fork();
    if (fark < 0)
    {
        fprintf(stderr, "Failed to fork child process\n");
        exit(1);
    }
    else if (fark == 0)
    {
        // Child
        // -l: changes output to list format
        // -a: shows all files, including hidden ones
        // -h: human-readable file sizes
        // (note: we could also bundle them all as a single arg `-lah`, but I separated them as a demo of passing more args)
        char *farkingArgs[] = {"ls", "-l", "-a", "-h", NULL};
        printf("The args: %s\n", farkingArgs);
        // ~~ execvp() ~~
        // v: vector formatted arguments
        // p: includes system path, so the app can actually find `ls`
        execvp(farkingArgs[0], farkingArgs);
    }
    else
    {
        // Parent
        int wc = waitpid(fark, NULL, 0);
        printf("This is your parent speaking. Please exit the child process in an orderly manner and proceed to the nearest fork.\n");
    }

    return 0;
}
