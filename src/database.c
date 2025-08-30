#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <string.h>

void save_students_to_file(Student_list *studentPtr) {
    FILE *file = fopen("bin/database.txt","w");
    if(!file) {
        printf("Error: Failed to open the file\n");
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
        printf("No data to load\n");
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
                printf("Error: Memory allocation failed\n");
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
    printf("Loading data...\n");
}

void add_student_to_list(Student_list **studentPtr,int id,char *name,float grade) {
     if(grade < MIN_STUDENT_GRADE || grade > MAX_STUDENT_GRADE) {
        printf("Error: Invalid grade. Must be 0-100\n");
        return;
    }
    
    Student_list *new_student = malloc(sizeof(Student_list));
    if(!new_student) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    Student_list *temp1 = *studentPtr;
    while(temp1 != NULL) {
        if(temp1->id == id) {
            printf("Error: This id already exists\n");
            free(new_student);
            return;
        }
        temp1 = temp1->next;
    }

    strcpy(new_student->name,name);
    new_student->grade = grade;
    new_student->id = id;
    new_student->next = NULL;

    if(*studentPtr == NULL) {
        *studentPtr = new_student;
        save_students_to_file(*studentPtr);
        printf("Student added successfully\n");
        return;
    }

    Student_list *temp2 = *studentPtr;
    while(temp2->next != NULL) temp2 = temp2->next;
    temp2->next = new_student;

    save_students_to_file(*studentPtr);
    printf("Student added successfully\n");
}

void delete_student_from_list(Student_list **studentPtr,int id) {
    if(*studentPtr == NULL) {
        printf("Error: Student list is empty\n");
        return;
    }

    Student_list *temp = *studentPtr, *prev = NULL;
    if(temp != NULL && temp->id == id) {
        *studentPtr = temp->next;
        free(temp);
        save_students_to_file(*studentPtr);
        printf("Student deleted successfully\n");
        return;
    }

    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf("Student not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    save_students_to_file(*studentPtr);
    printf("Student deleted successfully\n");
}

void print_student_list(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf("Error: Student list is empty\n");
        return;
    }

    printf("\nID\tName\t\tGrade\n");
    while(studentPtr != NULL) {
        printf("%d\t%-10s\t%.2f\n"
                ,studentPtr->id
                ,studentPtr->name
                ,studentPtr->grade);
        studentPtr = studentPtr->next;
    }

    printf("\n");
}

void edit_student_grade(Student_list *studentPtr,int id,float newGrade) {
    if(studentPtr == NULL) {
        printf("Error: Student list is empty\n");
        return;
    }

    if(newGrade < MIN_STUDENT_GRADE || newGrade > MAX_STUDENT_GRADE) {
        printf("Error: Invalid grade\n");
        return;
    }

    Student_list *head = studentPtr;
    while(studentPtr != NULL) {
        if(studentPtr->id == id) {
            studentPtr->grade = newGrade;
            printf("Student grade updated successfully\n");
            save_students_to_file(head);
            return;
        }
        studentPtr = studentPtr->next;
    }

    printf("Student not found\n");
}

void help_show_commands() {
    printf("\nCommands:\n");
    printf("  insert <id> <name> <grade>   | Adds a student to the database\n");
    printf("  delete <id>                  | Deletes a student from the database\n");
    printf("  select                       | Prints all the students\n");
    printf("  update <id> <new_grade>      | Updates students grade by the ID\n");
    printf("  cls                          | clears the terminal\n\n");
}
