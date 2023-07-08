#ifndef PATHMANAGEMENT_H
#define PATHMANAGEMENT_H

#define MAX_PATH_LENGTH 1024
#define MAX_ARGS 10
#define MAX_ARG_LENGTH 16
#define MAX_INPUT_LENGTH 100

extern char* path[MAX_ARGS];
extern int pathLength;

void readPath(char* input);

#endif /* PATHMANAGEMENT_H */
