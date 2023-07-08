[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/HdkhcjpH)

#A propos du développeur:

-Le nom du créateur du programme : RENAMY COLLARDEAU Christian Devis 
-Biographie : Etuadiant en L3 MIAGE / Devellopeur logicielle LINGUA CUSTODIA
-mail : christiancollardeau@gmail.com

#Programme creer sur Ubuntu

#Lancer le programme principale  : 

commande N1 : gcc -o dash dash.c src/CommandExecution.c src/PathManagement.c src/BuildCommands.c src/MessageError.c -Iinclude -Wall -Wextra -Werror -std=c17

commande N2 : ./dash 

#Lancer les tests : 

-Commande N0 : cd testUnitaires

1- Test BuildCommands

    
    Commande N1 : gcc -o  BuildCommandsTest  BuildCommandsTest.c   ../src/MessageError.c ../src/PathManagement.c ../src/BuildCommands.c minunit.h -Iinclude -Wall -Wextra -Werror -std=c17
    Commande N2 : ./BuildCommandsTest

2- Test Commande Execution 

    
    Commande N1 : gcc -o CommandExecutionTest CommandExecutionTest.c  ../src/MessageError.c ../src/PathManagement.c ../src/CommandExecution.c minunit.h  
    Commande N2 : ./CommandExecutionTest

3- Test Path Management 

    
    Commande N1 : gcc -o   PathManagementTest PathManagementTest.c   ../src/PathManagement.c  minunit.h  
    Commande N2 : ./PathManagementTest

