#include "../includes/CommandExecution.h"
#include "../includes/PathManagement.h"
#include "../includes/MessageError.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h> // Pour strcpy et strcat
#include <stdlib.h> // Pour exit


/** 
 * Trouve le chemin complet d'une commande à partir des chemins de recherche
 * spécifiés dans la variable path.
 * 
 * @param command Le nom de la commande à rechercher.
 * @param args    Les arguments de la commande.
 * @return        1 si la commande est trouvée et le chemin est valide, 0 sinon.
 */
int findCommandPath(char* command, char** args) {
    int pathLength = 256;
    for (int i = 0; i < pathLength; i++) {
        strcpy(command, path[i]);
        strcat(command, "/");
        strcat(command, args[0]);

        // Vérifie si le chemin est exécutable
        if (access(command, X_OK) == 0) {
            return 1; // Commande trouvée et chemin valide
        }
    }
    return 0; // Aucune commande trouvée ou chemin invalide
}

/**
 * Redirige l'entrée standard vers un descripteur de fichier donné.
 * 
 * @param inFd Le descripteur de fichier vers lequel rediriger l'entrée standard.
 */
void handleInputRedirection(int inFd) {
    if (inFd != STDIN_FILENO) {
        if (dup2(inFd, STDIN_FILENO) == -1) {
            afficherErreur();
            exit(0);
        }
        close(inFd);
    }
}

/**
 * Exécute une commande avec ses arguments en utilisant la fonction execv().
 * Si execv() échoue, le processus enfant se termine.
 * 
 * @param args    Les arguments de la commande.
 * @param command Le chemin complet de la commande.
 */
void executeCommandWithArgs(char** args, char* command) {
    execv(command, args);

    // Si execv() échoue, le processus enfant se termine
    afficherErreur();
    exit(0);
}

/**
 * Exécute une commande avec ses arguments en créant un nouveau processus enfant.
 * Le processus parent attend la fin de l'exécution du processus enfant.
 * 
 * @param args Les arguments de la commande.
 * @param inFd Le descripteur de fichier d'entrée à rediriger vers l'entrée standard.
 */
void executeCommand(char** args, int inFd) {
    pid_t pid = fork();  // Crée un nouveau processus en utilisant fork()

    if (pid == -1) {
        afficherErreur();
        return;
    } else if (pid == 0) {
        // Processus enfant

        char command[MAX_PATH_LENGTH];

        // Recherche du chemin complet de la commande
        int found = findCommandPath(command, args);

        if (found == 0) {
            exit(0);  // Aucune commande trouvée, le processus enfant se termine
        }

        handleInputRedirection(inFd);  // Gestion de la redirection de l'entrée standard

        executeCommandWithArgs(args, command);  // Exécution de la commande avec les arguments donnés
    } else {
        // Processus parent
        int status;
        waitpid(pid, &status, 0);  // Attend la fin de l'exécution du processus enfant
    }
}
