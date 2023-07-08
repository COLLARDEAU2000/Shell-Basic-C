#ifndef COMMANDEXECUTION_H
#define COMMANDEXECUTION_H

int findCommandPath(char* command, char** args);
void handleInputRedirection(int inFd);
void executeCommandWithArgs(char** args, char* command);
void executeCommand(char** args, int inFd);

#endif /* COMMANDEXECUTION_H */
