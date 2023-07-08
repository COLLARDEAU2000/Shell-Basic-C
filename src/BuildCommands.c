#include "../includes/BuildCommands.h"
#include "../includes/MessageError.h"
#include "../includes/PathManagement.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void executeExitCommand() {
    exit(0);
}

/**
 * Exécute la commande 'cd' (Changer de répertoire).
 * @param args Les arguments de la commande.
 * @return 0 si la commande s'est exécutée avec succès, 1 sinon.
 */
int executeCdCommand(char** args) {
    if (args[1] == NULL || args[2] != NULL) {
        afficherErreur(); // Fonction pour afficher une erreur (non définie ici).
        return 1;
    }
    if (chdir(args[1]) == -1) {
        afficherErreur();
        return 1;
    }
    return 1;
}

/**
 * Exécute la commande 'path' (Afficher le chemin).
 * @param args Les arguments de la commande.
 */
void executePathCommand(char** args) {
    readPath(args[1]); // Fonction pour lire et traiter le chemin (non définie ici).
}

/**
 * Exécute les commandes intégrées au programme.
 * @param args Les arguments de la commande.
 * @return 0 si la commande n'est pas intégrée, 1 sinon.
 */
int executeBuiltInCommand(char** args) {
    if (strcmp(args[0], "exit") == 0) {
        executeExitCommand();
    } else if (strcmp(args[0], "cd") == 0) {
        return executeCdCommand(args);
    } else if (strcmp(args[0], "path") == 0) {
        executePathCommand(args);
    }

    return 0;
}
