#include "../includes/PathManagement.h"
#include <stdio.h>
#include <string.h>

char* path[MAX_ARGS];
int pathLength = 0;


void readPath(char* input) {
    // Utilisation de strtok pour extraire les chemins séparés par des espaces et des retours à la ligne
    char* token = strtok(input, " \n");
    pathLength = 0;

    // Parcours des tokens extraits
    while (token != NULL) {
        // Stockage du chemin dans le tableau path
        path[pathLength] = token;
        pathLength++;

        // Extraction du prochain token
        token = strtok(NULL, " \n");
    }
}

