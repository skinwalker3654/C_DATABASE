#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../colors/colors.h"
#include "../utils/utils.h"

#define DATABASE_FILE "bin/database.txt"

void save_students_to_file(Student_list *studentPtr) {
    FILE *file = fopen(DATABASE_FILE,"w");
    if(!file) {
        printf(RED"Error: Failed to open the file.\n"RESET);
        return;
    }

    /*This saves every student into a file*/
    while(studentPtr != NULL) {
        fprintf(file,"%d|%s|%.2f\n"
                ,studentPtr->id
                ,studentPtr->name
                ,studentPtr->grade);
        studentPtr = studentPtr->next;
    }

    fclose(file);
}

void load_students_from_file(Student_list **studentPtr) {
    FILE *file = fopen(DATABASE_FILE,"r");
    if(!file) { return; }

    free_list_nodes(*studentPtr);
    *studentPtr = NULL;

    int id;
    char name[STUDENT_NAME_SIZE];
    float grade;

    char line[100];
    while(fgets(line,sizeof(line),file)) {
        if(sscanf(line,"%d|%[^|]|%f",&id,name,&grade)==3) {
            Student_list *new_student = malloc(sizeof(Student_list));
            if(!new_student) {
                printf(RED"Error: Memory allocation failed.\n"RESET);
                fclose(file);
                return;
            }

            /*This initializes the stuedent node so we can add it to the linked list next*/
            new_student->id = id;
            new_student->grade = grade;
            strcpy(new_student->name,name);
            new_student->next = NULL;

            /*Adding the student node*/
            if(*studentPtr == NULL) {
                *studentPtr = new_student;
                continue;
            }

            Student_list *temp = *studentPtr;
            while(temp->next != NULL) temp = temp->next;
            temp->next = new_student;
        }
    }

    fclose(file);
}
