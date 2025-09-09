#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_students_to_file(Student_list *studentPtr) {
    FILE *file = fopen("bin/database.txt","w");
    if(!file) {
        printf(RED"Error: Failed to open the file\n"RESET);
        return;
    }

    while(studentPtr != NULL) {
        fprintf(file,"%d|%s|%.2f\n"
                ,studentPtr->id
                ,studentPtr->name
                ,studentPtr->grade);
        studentPtr = studentPtr->next;
    }

    fclose(file);
}

void free_list_nodes(Student_list *studentPtr) {
    while(studentPtr != NULL) {
        Student_list *temp = studentPtr;
        studentPtr = studentPtr->next;
        free(temp);
    }
}

void load_students_from_file(Student_list **studentPtr) {
    FILE *file = fopen("bin/database.txt","r");
    if(!file) {
        printf("There is no data to load\n");
        return;
    }

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
                printf(RED"Error: Memory allocation failed\n"RESET);
                fclose(file);
                return;
            }

            new_student->id = id;
            new_student->grade = grade;
            strcpy(new_student->name,name);
            new_student->next = NULL;
            
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
    printf(BOLD YELLOW"Loading data...\n"RESET);
}

void sort_students_by_id(Student_list *studentPtr) {
    if(studentPtr == NULL) return;

    int swapped;
    Student_list *ptr1;
    Student_list *lptr = NULL;

    while(swapped) {
        swapped = 0;
        ptr1 = studentPtr;

        while(ptr1->next != lptr) {
            if(ptr1->id > ptr1->next->id) { 
                int tmp_id = ptr1->id;
                char tmp_name[STUDENT_NAME_SIZE];
                strcpy(tmp_name, ptr1->name);
                float tmp_grade = ptr1->grade;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->grade = ptr1->next->grade;

                ptr1->next->id = tmp_id;
                strcpy(ptr1->next->name, tmp_name);
                ptr1->next->grade = tmp_grade;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } 
}

void help_show_commands() {
    printf(BOLD YELLOW"\nCommands:\n"RESET);
    printf(BOLD YELLOW"  insert <id> <name> <grade>   | Adds a student to the database\n"RESET);
    printf(BOLD YELLOW"  update <id> <new_grade>      | Updates students grade by the ID\n"RESET);
    printf(BOLD YELLOW"  delete / delete <id>         | Deletes all students / deletes one student by the ID\n"RESET);
    printf(BOLD YELLOW"  select / select <name>       | Prints all the students / Prints one student by the name\n"RESET);
    printf(BOLD YELLOW"  average                      | Prints students average grade\n"RESET);
    printf(BOLD YELLOW"  count                        | Prints student count\n"RESET);
    printf(BOLD YELLOW"  cls                          | Clears the terminal\n"RESET);
    printf(BOLD YELLOW"  min                          | Finds the student with the minimum grade\n"RESET);
    printf(BOLD YELLOW"  max                          | Finds the student with the maximum grade\n"RESET);
    printf(BOLD YELLOW"  help                         | Shows this pannel\n"RESET);
    printf(BOLD YELLOW"  exit                         | Exits the program\n\n"RESET);
}
