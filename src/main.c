#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <signal.h>
#include <string.h>

Student_list *nodes = NULL;
void sigint_handler(int sig) {
    printf("\nDont worry Freeing memory and exiting...\n");
    free_list_nodes(nodes); 
    exit(0);
}

int main(void) {
    char input[100];
    char command[20];
    char name[50];
    float grade;
    int id;

    signal(SIGINT, sigint_handler);
    load_students_from_file(&nodes);

    while(1) {
        printf(">> ");
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = 0;

        if(strlen(input)==0) continue;
        sscanf(input,"%s",command);

        if(strcmp(command,"insert")==0) {
            char *tokens[10];
            int i = 0;
            char *ptr = strtok(input, " "); 
            while(ptr && i < 10) {
                tokens[i++] = ptr;
                ptr = strtok(NULL, " ");
            }
        
            if(i >= 4) {
                char *endptr;
                id = strtol(tokens[1],&endptr,10);
                if(*endptr != '\0') {
                    printf("Error: Invalid id\n");
                    continue;
                }

                grade = strtof(tokens[i-1],&endptr);
                if(*endptr != '\0') {
                    printf("Error: Invalid grade\n");
                    continue;
                }
            
                name[0] = 0;
                for(int j=2; j<i-1; j++) {
                    strcat(name, tokens[j]);
                    if(j < i-2) strcat(name, " ");
                }
            
                add_student_to_list(&nodes, id, name, grade);
                continue;
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more details\n\n");
            }
        } else if(strcmp(command,"delete")==0) {
            if(sscanf(input,"delete %d",&id)==1) {
                delete_student_from_list(&nodes,id);
                continue;
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more details\n\n");
            } 
        } else if(strcmp(command,"select")==0) {
            char *arg = input + strlen("select");
            while(*arg == ' ' || *arg == '\t') arg++;

            if(*arg == '\0') {
                sort_students_by_id(nodes);
                print_student_list(nodes);
            } else if(sscanf(arg,"%d",&id)==1) {
                Student_list *tempPtr = nodes;
                while(tempPtr != NULL) {
                    if(tempPtr->id == id) {
                        printf("ID: %d | Name: %s | Grade: %.2f\n"
                                ,tempPtr->id
                                ,tempPtr->name
                                ,tempPtr->grade); 
                        break;
                    }
                    tempPtr = tempPtr->next;
                }
                if(tempPtr == NULL) {
                    printf("Error: Student not found\n");
                    continue;
                }
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more details\n\n");
            }
        } else if(strcmp(command,"update")==0) {
            float newGrade;
            if(sscanf(input,"update %d %f",&id,&newGrade)==2) {
                edit_student_grade(nodes,id,newGrade);
                continue;
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more details\n\n");
            } 
        } else if(strcmp(input,"help")==0) {
            help_show_commands();
        } else if(strcmp(input,"exit")==0) {
            printf("Exiting...\n");
            free_list_nodes(nodes);
            return 0;
        } else if(strcmp(input,"cls")==0) {
            system("clear");
        } else {
            printf("\nError: Invalid command '%s'\n",input);
            printf("Type: 'help' for more details\n\n");
        }
    }

    free_list_nodes(nodes);
    return 0;
}
