#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "includes/MessageError.h"
#include "includes/BuildCommands.h"
#include "includes/PathManagement.h"
#include "includes/CommandExecution.h"


int main() {
    char* input = malloc(MAX_INPUT_LENGTH);  // Allocation de mémoire pour stocker l'entrée utilisateur

    while (1) {
        printf("dash> ");  // Affichage du prompt
        fgets(input, MAX_INPUT_LENGTH, stdin);  // Lecture de la ligne de commande

        if (feof(stdin)) {
            printf("\n");  // L'utilisateur a appuyé sur Ctrl+D, fin de l'exécution
            break;
        }

        if (input[strlen(input)-1] == '\n') {
            input[strlen(input)-1] = '\0';  // Suppression du caractère de nouvelle ligne
        }

        char* args[MAX_ARGS];  // Tableau pour stocker les arguments
        int argsLength = 0;  // Nombre d'arguments

        char* token = strtok(input, " ");  // Découpage de la ligne de commande en arguments
        while (token != NULL) {
            args[argsLength] = malloc(strlen(token) + 1);  // Allocation de mémoire pour chaque argument
            strcpy(args[argsLength], token);  // Copie de l'argument dans le tableau
            argsLength++;
            token = strtok(NULL, " ");
        }
        args[argsLength] = NULL;  // Dernier élément du tableau doit être NULL pour execvp()

        pid_t pid = fork();  // Création d'un nouveau processus

        if (pid == -1) {
            afficherErreur();// Erreur lors de la création du processus
        } else if (pid == 0) {  // Processus enfant
            execvp(args[0], args);  // Exécution de la commande avec les arguments
            exit(EXIT_FAILURE);  // Si execvp() échoue, on termine le processus enfant avec un code d'erreur
        } else {  // Processus parent
            int status;
            waitpid(pid, &status, 0);  // Attente de la fin de l'exécution du processus enfant
        }

        if (executeBuiltInCommand(args) == 0) {
            int inFd = STDIN_FILENO;  // Descripteur de fichier pour la redirection de l'entrée standard

            for (int i = 0; i < argsLength; i++) {
                if (strcmp(args[i], "<") == 0) {  // Détection de la redirection d'entrée
                    if (args[i+1] == NULL) {
                        break;
                    }
                    int fileFd = open(args[i+1], O_RDONLY);  // Ouverture du fichier en lecture seule
                    if (fileFd == -1) {
                        afficherErreur();  // Erreur d'ouverture du fichier
                        break;
                    }
                    inFd = fileFd;
                    i++;
                } else {
                    executeCommand(args+i, inFd);  // Exécution d'une commande externe avec la redirection de l'entrée
                    break;
                }
            }
        }
        for (int i = 0; i < argsLength; i++) {
            free(args[i]);  // Libération de la mémoire allouée pour chaque argument
        }
    }

    free(input);  // Libération de la mémoire allouée pour l'entrée utilisateur

    return 0;  // Fin du programme avec un code de retour 0
}


