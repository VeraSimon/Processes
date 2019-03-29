#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory
// and then calls `fork()` to create a new process.
// Can both the child and parent access the file descriptor returned by `fopen()`?
// Yes. Yes they can. Due to the nature of how CPU threads and forking work, it's never quite at the same time though.
// What happens when they are written to the file concurrently?
// Trick question. They're not. The two processes write in procession. Without telling the parent to wait first, we can't always guarentee write order from machine to machine though.

int main(void)
{
    // Your code here
    FILE *fp = fopen("text.txt", "a");

    int fark = fork();
    if (fark < 0)
    {
        fprintf(stderr, "Failed to fork child process\n");
        exit(1);
    }
    else if (fark == 0)
    {
        // Child
        fprintf(fp, "Hello mumther. This is your chilld %i.\n", (int)getpid());
    }
    else
    {
        // Parent
        fprintf(fp, "Hello chilld. This is your forthar %i.\n", (int)getpid());
    }

    fclose(fp);

    return 0;
}
