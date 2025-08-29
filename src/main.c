#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <string.h>

int main(void) {
    char input[100];
    char command[20];
    char name[50];
    float grade;
    int id;

    initialize_list(&students);
    load_students_from_file(&students);

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
                id = atoi(tokens[1]);
                grade = atof(tokens[i-1]);
            
                name[0] = 0;
                for(int j=2; j<i-1; j++) {
                    strcat(name, tokens[j]);
                    if(j < i-2) strcat(name, " ");
                }
            
                add_student_to_list(&students, id, name, grade);
                continue;
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more details\n\n");
            }
        } else if(strcmp(command,"delete")==0) {
            if(sscanf(input,"delete %d",&id)==1) {
                delete_student_from_list(&students,id);
                continue;
            } else {
                printf("Error: Invalid arguments passed\n");
                printf("Type: 'help' for more detailes\n\n");
            } 
        } else if(strcmp(command,"select")==0) {
            print_student_list(&students);
        } else if(strcmp(command,"update")==0) {
            float newGrade;
            if(sscanf(input,"update %d %f",&id,&newGrade)==2) {
                edit_student_grade(&students,id,newGrade);
                continue;
            } else {
                printf("\nError: Invalid arguments passed\n");
                printf("Type: 'help' for more detailes\n\n");
            } 
        } else if(strcmp(input,"help")==0) {
            help_show_commands();
        } else if(strcmp(input,"exit")==0) {
            printf("Exiting...\n");
            return 0;
        } else if(strcmp(input,"cls")==0) {
            system("clear");
        } else {
            printf("\nError: Invalid command '%s'\n",command);
            printf("Type: 'help' for more detailes\n\n");
        }
    }

    return 0;
}
