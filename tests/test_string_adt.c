#include "framework/unity.h"
#include "../adts/string_adt.h"
#include <string.h>
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
                fn;                                     \
                _exit(0);                               \
        }                                               \
        int status;                                     \
        waitpid(pid, &status, 0);                       \
        TEST_ASSERT(WIFSIGNALED(status));               \
        TEST_ASSERT(WTERMSIG(status) == SIGABRT);       \
    } while (0)

string_t s1 = NULL;
string_t s2 = NULL;

void setUp(void) {}

void tearDown(void) {
    string_delete(s1);
    s1 = NULL;

    if (s2 != NULL) {
        string_delete(s2);
        s2 = NULL;
    }
}

void test_string_new(void) {
    s1 = string_new();

    TEST_ASSERT(string_len(s1) == 0);
    TEST_ASSERT(string_cap(s1) != 0);
    TEST_ASSERT(string_cstr(s1)[0] == '\0');
}

void test_string_init(void) {
    const char *cstr = "Example sentence.";
    const size_t len = strlen(cstr);

    s1 = string_init(cstr);

    TEST_ASSERT_EQUAL_STRING(cstr, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(len, string_len(s1));
}

void test_string_insert(void) {
    s1 = string_init("to be question");

    const char *cstr = "the ";
    string_insert(s1, 6, cstr);

    const char *expected = "to be the question";
    size_t expected_len = strlen(expected);

    TEST_ASSERT_EQUAL_STRING(expected, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(expected_len, string_len(s1));
}

void test_string_erase_1(void) {
    s1 = string_init("This is an example sentence.");
    string_erase(s1, 10, 8);

    const char *expected = "This is an sentence.";
    const size_t expected_len = strlen(expected);

    TEST_ASSERT_EQUAL_STRING(expected, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(expected_len, string_len(s1));
}

void test_string_erase_2(void) {
    s1 = string_init("This is an example sentence.");
    string_erase(s1, 18, 9);

    const char *expected = "This is an example.";
    const size_t expected_len = strlen(expected);

    TEST_ASSERT_EQUAL_STRING(expected, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(expected_len, string_len(s1));
}

void test_string_erase_3(void) {
    s1 = string_init("This is an example sentence.");
    string_erase(s1, 20, 0);

    const char *expected = "This is an example sentence.";
    const size_t expected_len = strlen(expected);

    TEST_ASSERT_EQUAL_STRING(expected, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(expected_len, string_len(s1));
}

void test_string_erase_assert(void) {
    s1 = string_init("This");
    s2 = string_new();
    TEST_ASSERT_ABORT(string_erase(s1, 20, 0));
    TEST_ASSERT_ABORT(string_erase(s1, 2, 3));
    TEST_ASSERT_ABORT(string_erase(s2, 0, 1));
    TEST_ASSERT_ABORT(string_erase(s2, 0, 0));
}

void test_string_find(void) {
    s1 = string_init("There are two needles in this haystack with needles.");
    const ssize_t idx = string_find(s1, "needle");

    const ssize_t expected = 14;

    TEST_ASSERT_EQUAL(expected, idx);
}

void test_string_swap(void) {
    const char *cstr1 = "an example sentence.";
    const char *cstr2 = "an example phrase.";
    const size_t len1 = strlen(cstr1);
    const size_t len2 = strlen(cstr2);

    s1 = string_init(cstr1);
    s2 = string_init(cstr2);

    const size_t cap1 = string_cap(s1);
    const size_t cap2 = string_cap(s2);

    string_swap(s1, s2);

    TEST_ASSERT_EQUAL_STRING(cstr1, string_cstr(s2));
    TEST_ASSERT_EQUAL_STRING(cstr2, string_cstr(s1));
    TEST_ASSERT_EQUAL_size_t(len1, string_len(s2));
    TEST_ASSERT_EQUAL_size_t(len2, string_len(s1));
    TEST_ASSERT_EQUAL_size_t(cap1, string_cap(s2));
    TEST_ASSERT_EQUAL_size_t(cap2, string_cap(s1));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_string_new);
    RUN_TEST(test_string_init);
    RUN_TEST(test_string_insert);
    RUN_TEST(test_string_find);
    RUN_TEST(test_string_erase_1);
    RUN_TEST(test_string_erase_2);
    RUN_TEST(test_string_erase_3);
    RUN_TEST(test_string_erase_assert);
    RUN_TEST(test_string_swap);
    return UNITY_END();
}
