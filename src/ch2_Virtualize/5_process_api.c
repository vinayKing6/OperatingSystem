#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void p1(int rc)
{
    if (rc < 0)
    {
        fprintf(stderr, "fork failed!!\n");
    }
    else if (rc == 0)
    {
        printf("hello i am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        printf("hello i am parent (pid:%d)\n", (int)getpid());
    }
}

void p2(int rc)
{
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("hello i am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        int rc_wait = wait(NULL);
        printf("hello i am parent of (pid:%d) waiting for (pid:%d) (pid:%d)", rc, rc_wait, (int)getpid());
    }
}

void p3(int rc)
{
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (rc == 0)
    {
        printf("hello i am child (pid:%d)", (int)getpid());
        char *myargs[3];
        // just run wc p3.c on linux
        myargs[0] = strdup("wc");
        myargs[1] = strdup("5_process_api.c");
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs);
        printf("this should not print out because execvp never returns");
    }
    else
    {
        int rc_wait = wait(NULL);
        printf("hello i am parent of (pid:%d) waiting for (pid:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
    }
}

void p4(int rc)
{
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("hello i am child (pid:%d)", (int)getpid());
        char *myargs[3];

        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        // just run wc p3.c > p4.output on linux
        myargs[0] = strdup("wc");
        myargs[1] = strdup("5_process_api.c");
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs);
        printf("this should not print out because execvp never returns");
    }
    else
    {
        int rc_wait = wait(NULL);
        printf("hello i am parent of (pid:%d) waiting for (pid:%d) (pid:%d)\n", rc, rc_wait, (int)getpid());
    }
}

int main()
{
    printf("hello os (pid:%d) \n", (int)getpid());
    int rc = fork(); // get pid of new process if new process is created
    // p1(rc);
    // p2(rc);
    // p3(rc);
    p4(rc);
    return 0;
}
