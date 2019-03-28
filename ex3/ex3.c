#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

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
        printf("hello\n");
    }
    else
    {
        // Parent
        int wc = waitpid(fark, NULL, 0);
        printf("goodbye\n");
    }

    return 0;
}
