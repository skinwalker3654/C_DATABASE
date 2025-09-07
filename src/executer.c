#include "executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_commands(char *input, Student_list **nodes) {
    char command[20];
    char name[50];
    float grade;
    int id;

    if(strlen(input) == 0) return;
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
                return;
            }

            grade = strtof(tokens[3], &endptr);
            if(*endptr != '\0') {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
                return;
            }

            strncpy(name, tokens[2], sizeof(name));
            name[sizeof(name)-1] = '\0';

            add_student_to_list(nodes, id, name, grade);
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"delete")==0) {
        char *arg = input + strlen("delete");
        while(*arg == ' ' || *arg == '\t') arg++;

        if(*arg == '\0') {
            if(*nodes == NULL) {
                printf(RED"Error: Student list is empty\n"RESET);
                return;
            }
            free_list_nodes(*nodes);
            *nodes = NULL;
            save_students_to_file(*nodes);
            printf(GREEN"Students deleted successfully\n"RESET);
        }
        else if(sscanf(arg,"%d",&id)==1) {
            if(delete_student_from_list(nodes,id)!=0) return;
            printf(GREEN"Student deleted successfully\n"RESET);
        }
        else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"select")==0) {
        char *arg = input + strlen("select");
        while(*arg == ' ' || *arg == '\t') arg++;

        if(*arg == '\0') {
            sort_students_by_id(*nodes);
            print_student_list(*nodes);
        }
        else if(sscanf(arg,"%s",name)==1) {
            Student_list *tempPtr = *nodes;
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
                return;
            }
        }
        else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"update")==0) {
        float newGrade;
        if(sscanf(input,"update %d %f",&id,&newGrade)==2) {
            edit_student_grade(*nodes,id,newGrade);
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(input,"count")==0) {
        int studentCount = find_students_count(*nodes);
        if(studentCount == -1) return;
        else if(studentCount == 1) printf(BOLD YELLOW"There is %d student in the list\n"RESET,studentCount);
        else if(studentCount > 1) printf(BOLD YELLOW"There are %d students in the list\n"RESET,studentCount);
    }
    else if(strcmp(input,"average")==0) {
        print_average_grade(*nodes);
    }
    else if(strcmp(input,"help")==0) {
        help_show_commands();
    }
    else if(strcmp(input,"exit")==0) {
        printf(BOLD BLUE"Exiting...\n"RESET);
        free_list_nodes(*nodes);
        exit(0);
    }
    else if(strcmp(input,"cls")==0) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    else {
        printf(RED"\nError: Invalid command '%s'\n"RESET,input);
        printf(RED"Type: 'help' for more details\n\n"RESET);
    }
}


