#include "../includes/PathManagement.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
MU_TEST(test_readPath) {
    char input[MAX_INPUT_LENGTH] = "path1 path2 path3";
    readPath(input);

    mu_check(pathLength == 3);
    mu_check(strcmp(path[0], "path1") == 0);
    mu_check(strcmp(path[1], "path2") == 0);
    mu_check(strcmp(path[2], "path3") == 0);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_readPath);
}

int main(int argc, char* argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}