#ifndef BUILDCOMMANDS_H
#define BUILDCOMMANDS_H

int executeBuiltInCommand(char** args);
void executePathCommand(char** args);
int executeCdCommand(char** args);
void executeExitCommand();
#endif /* BUILDCOMMANDS_H */
