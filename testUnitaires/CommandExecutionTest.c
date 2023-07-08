#include "../includes/CommandExecution.h"
#include "../includes/MessageError.h"
#include "../includes/PathManagement.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Variable globale pour les tests
char* commandResult = NULL;

// Cas de test pour findCommandPath
MU_TEST(test_findCommandPath) {
    // Configuration
    char command[1024];
    char* args[] = {"command", NULL};
    strcpy(path[0], "/usr/bin");

    // Test
    int result = findCommandPath(command, args);

    // Assertion
    mu_assert_int_eq(1, result);
    mu_assert_string_eq("/usr/bin/command", command);
}

// Cas de test pour executeCommand
MU_TEST(test_executeCommand) {
    // Configuration
    char* args[] = {"mock_command", NULL};
    int inFd = STDIN_FILENO;

    // Test
    executeCommand(args, inFd);

    // Assertion
    mu_assert_string_eq("Mock command executed successfully", commandResult);

    // Libération de la mémoire allouée avec malloc
    free(commandResult);
    commandResult = NULL; // Réinitialisation du pointeur
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_findCommandPath);
    MU_RUN_TEST(test_executeCommand);
}

int main(int argc, char *argv[]) {
    // Initialisation du chemin pour les tests
    strcpy(path[0], "/usr/bin");

    // Allocation de mémoire pour commandResult
    commandResult = (char*) malloc(sizeof(char) * 1024);
    if (commandResult == NULL) {
        printf("Failed to allocate memory for commandResult\n");
        return -1;
    }

    MU_RUN_SUITE(test_suite);
    MU_REPORT();

    // Libération de la mémoire allouée avec malloc
    free(commandResult);

    return MU_EXIT_CODE;
}
