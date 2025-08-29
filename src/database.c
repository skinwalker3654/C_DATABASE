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

    for(int i=0; i<studentPtr->count_students; i++) {
        fprintf(file,"%d|%s|%.2f\n"
                ,studentPtr->students[i].id
                ,studentPtr->students[i].name
                ,studentPtr->students[i].grade);
    }

    fclose(file);
}

void load_students_from_file(Student_list *studentPtr) {
    if(studentPtr->count_students >= MAX_STUDENTS_COUNT) return;

    FILE *file = fopen("bin/database.txt","r");
    if(!file) {
        printf("No data to load\n");
        return;
    }

    int id;
    char name[STUDENT_NAME_SIZE];
    float grade;

    char line[100];
    while(fgets(line,sizeof(line),file)) {
        if(sscanf(line,"%d|%49[^|]|%f",&id,name,&grade)==3) {
            studentPtr->students[studentPtr->count_students].id = id;
            strcpy(studentPtr->students[studentPtr->count_students].name,name);
            studentPtr->students[studentPtr->count_students].grade = grade;
            studentPtr->count_students++;
        }
    }

    fclose(file);
    printf("Loading data...\n");
}

void initialize_list(Student_list *studentPtr) {
    studentPtr->count_students = 0;
}

Student_list students;

void add_student_to_list(Student_list *studentPtr,int id,char *name,float grade) {
    if(studentPtr->count_students >= MAX_STUDENTS_COUNT) {
        printf("Error: Student list is full\n");
        return;
    }

    if(grade < MIN_STUDENT_GRADE || grade > MAX_STUDENT_GRADE) {
        printf("Error: Invalid grade. Must be 0-100\n");
        return;
    }

    studentPtr->students[studentPtr->count_students].id = id;
    strcpy(studentPtr->students[studentPtr->count_students].name,name);
    studentPtr->students[studentPtr->count_students].grade = grade;

    studentPtr->count_students++;
    printf("Student added successfully\n");
    save_students_to_file(studentPtr);
}

void delete_student_from_list(Student_list *studentPtr,int id) {
    if(studentPtr->count_students == 0) {
        printf("Error: Student list is empty\n");
        return;
    }

    for(int i=0; i<studentPtr->count_students; i++) {
        if(studentPtr->students[i].id == id) {
            for(int j=i; j<studentPtr->count_students-1; j++)
                studentPtr->students[j] = studentPtr->students[j+1];
            studentPtr->count_students--;
            printf("Student deleted successfully\n");
            save_students_to_file(studentPtr);
            return;
        }
    }

    printf("Student not found\n");
}

void print_student_list(Student_list *studentPtr) {
    if(studentPtr->count_students == 0) {
        printf("Error: Student list is empty\n");
        return;
    }

    printf("\n");
    printf("ID\tName\t\tGrade\n");
    for(int i=0; i<studentPtr->count_students; i++) {
        printf("%d\t%-10s\t%.2f\n"
                ,studentPtr->students[i].id
                ,studentPtr->students[i].name
                ,studentPtr->students[i].grade);
    }

    printf("\n");
}

void edit_student_grade(Student_list *studentPtr,int id,float newGrade) {
    if(studentPtr->count_students == 0) {
        printf("Error: Student list is empty\n");
        return;
    }

    if(newGrade < MIN_STUDENT_GRADE || newGrade > MAX_STUDENT_GRADE) {
        printf("Error: Invalid grade\n");
        return;
    }

    for(int i=0; i<studentPtr->count_students; i++) {
        if(studentPtr->students[i].id == id) {
            studentPtr->students[i].grade = newGrade;
            printf("Students grade updated successfully\n");
            save_students_to_file(studentPtr);
            return;
        }
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
