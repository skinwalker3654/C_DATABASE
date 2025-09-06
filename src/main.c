#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <signal.h>
#include <string.h>

Student_list *nodes = NULL;
void sigint_handler(int sig) {
    printf(GREEN"\nDont worry Freeing memory and exiting...\n"RESET);
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
        printf(CYAN">> "RESET);
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = 0;

        if(strlen(input)==0) continue;
        sscanf(input,"%s",command);

        if(strcmp(command,"insert")==0) {
            const int tokensCount = 4;
            char *tokens[tokensCount];
            int count = 0;
            char *ptr = strtok(input, " "); 
            while(ptr && count < 4) {
                tokens[count++] = ptr;
                ptr = strtok(NULL, " ");
            }

            if(count == tokensCount) {
                char *endptr;
                id = strtol(tokens[1], &endptr, 10);
                if(*endptr != '\0') {
                    printf(RED"\nError: Invalid arguments passed\n"RESET);
                    printf(RED"Type: 'help' for more details\n\n"RESET);
                    continue;
                }

                grade = strtof(tokens[3], &endptr);
                if(*endptr != '\0') {
                    printf(RED"\nError: Invalid arguments passed\n"RESET);
                    printf(RED"Type: 'help' for more details\n\n"RESET);
                    continue;
                }

                strncpy(name, tokens[2], sizeof(name));
                name[sizeof(name)-1] = '\0';

                add_student_to_list(&nodes, id, name, grade);
                continue;
            } else {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
            }
        } else if(strcmp(command,"delete")==0) {
            char *arg = input + strlen("delete");
            while(*arg == ' ' || *arg == '\t') arg++;

            if(*arg == '\0') {
                if(nodes == NULL) { 
                    printf(RED"Error: Student list is empty\n"RESET); 
                    continue; 
                }
                free_list_nodes(nodes);
                nodes = NULL;
                save_students_to_file(nodes);
                printf(GREEN"Students deleted successfully\n"RESET);
                continue;
            } else if(sscanf(arg,"%d",&id)==1) {
                if(delete_student_from_list(&nodes,id)!=0) {continue;}
                printf(GREEN"Student deleted successfully\n"RESET);
                continue;
            } else {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
                continue;
            }
        } else if(strcmp(command,"select")==0) {
            char *arg = input + strlen("select");
            while(*arg == ' ' || *arg == '\t') arg++;

            if(*arg == '\0') {
                sort_students_by_id(nodes);
                print_student_list(nodes);
            } else if(sscanf(arg,"%s",name)==1) {
                Student_list *tempPtr = nodes;
                while(tempPtr != NULL) {
                    if(strcmp(tempPtr->name,name)==0) {
                        printf(BOLD YELLOW"ID: %d"RESET,tempPtr->id);
                        printf(" | ");
                        printf(BOLD YELLOW "Name: %s"RESET,tempPtr->name);
                        printf(" | ");
                        printf(BOLD YELLOW "Grade: %.2f\n"RESET,tempPtr->grade); 
                        break;
                    }
                    tempPtr = tempPtr->next;
                }
                if(tempPtr == NULL) {
                    printf(RED"Error: Student not found\n"RESET);
                    continue;
                }
            } else {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
            }
        } else if(strcmp(command,"update")==0) {
            float newGrade;
            if(sscanf(input,"update %d %f",&id,&newGrade)==2) {
                edit_student_grade(nodes,id,newGrade);
                continue;
            } else {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
            } 
        } else if(strcmp(input,"count")==0) {
            int studentCount = find_students_count(nodes);
            if(studentCount == -1) {continue;}
            else if(studentCount == 1) {
                printf(BOLD YELLOW"There is %d student in the list\n"RESET,studentCount);
                continue;
            } else if(studentCount > 1) {
                printf(BOLD YELLOW"There are %d students in the list\n"RESET,studentCount);
                continue;
            }
        } else if(strcmp(input,"help")==0) {
            help_show_commands();
        } else if(strcmp(input,"exit")==0) {
            printf(BOLD BLUE"Exiting...\n"RESET);
            free_list_nodes(nodes);
            return 0;
        } else if(strcmp(input,"cls")==0) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        } else {
            printf(RED"\nError: Invalid command '%s'\n"RESET,input);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }

    free_list_nodes(nodes);
    return 0;
}
