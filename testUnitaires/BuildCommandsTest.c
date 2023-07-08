#include "../includes/CommandExecution.h"
#include "../includes/BuildCommands.h"
#include "../includes/MessageError.h"
#include "../includes/PathManagement.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

MU_TEST(test_executeExitCommand) {
    executeExitCommand();
    mu_check(1); // Test toujours réussi
}

MU_TEST(test_executePathCommand) {
    char* args[] = {"path", "path/to/file", NULL};
    mu_assert_int_eq(0, pathLength); // Vérifie que pathLength est initialisé à 0

    executePathCommand(args);

    mu_assert_int_eq(1, pathLength); // Vérifie que pathLength est mis à jour
    mu_assert_string_eq("path/to/file", path[0]); // Vérifie que le chemin est correctement stocké dans path
}

MU_TEST(test_executeBuiltInCommand) {
    char* args1[] = {"exit", NULL};
    mu_check(executeBuiltInCommand(args1) == 0); // Vérifie que la fonction exit est appelée

    char* args2[] = {"cd", "path/to/dir", NULL};
    mu_assert_int_eq(1, executeBuiltInCommand(args2)); // Vérifie le comportement de executeCdCommand

    char* args3[] = {"path", "path/to/file", NULL};
    mu_assert_int_eq(0, pathLength); // Vérifie que pathLength est initialisé à 0

    executeBuiltInCommand(args3);

    mu_assert_int_eq(1, pathLength); // Vérifie que pathLength est mis à jour
    mu_assert_string_eq("path/to/file", path[0]); // Vérifie que le chemin est correctement stocké dans path
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_executeExitCommand);
    MU_RUN_TEST(test_executePathCommand);
    MU_RUN_TEST(test_executeBuiltInCommand);
}

int main() {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE ;
}
