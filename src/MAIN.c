#include <stdio.h>
#include <stdlib.h>
#include "executer/executer.h"
#include <signal.h>
#include <string.h>

/*Database of students*/
Student_list *nodes = NULL;

void sigint_handler(int signal) {
    if(signal == SIGINT) {
        printf(GREEN"\nDont worry memory is getting freed and closing the program...\n"RESET);
        free_list_nodes(nodes);
        exit(EXIT_SUCCESS);
    } else {
        printf(RED"Error: Ctr + C signal failed to catch."RESET);
    }
}

int main(void) {
    char input[100];

    signal(SIGINT, sigint_handler);
    load_students_from_file(&nodes);

    printf(LBLUE"Type 'help' to see available commands.\n\n"RESET);
    
    while(1) {
        printf(CYAN">> "RESET);
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = 0;

        if(strlen(input)==0) continue;
        execute_commands(input,&nodes);
    }

    free_list_nodes(nodes);
    return 0;
}
