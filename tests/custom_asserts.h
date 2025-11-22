#ifndef CUSTOM_ASSERTS_H
#define CUSTOM_ASSERTS_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TEST_ASSERT_ABORT(fn)                           \
    do {                                                \
        pid_t pid = fork();                             \
        TEST_ASSERT_MESSAGE(pid >= 0, "fork() failed"); \
        if (pid == 0) {                                 \
            int devnull = open("/dev/null", O_WRONLY);  \
            if (devnull >= 0) {                         \
                dup2(devnull, STDERR_FILENO);           \
                close(devnull);                         \
            }                                           \
            fn;                                         \
            _exit(0);                                   \
        }                                               \
        int status;                                     \
        waitpid(pid, &status, 0);                       \
        TEST_ASSERT(WIFSIGNALED(status));               \
        TEST_ASSERT(WTERMSIG(status) == SIGABRT);       \
    } while (0)

#endif
