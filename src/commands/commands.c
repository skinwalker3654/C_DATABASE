#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include <string.h>

/*MAIN FUNCTIONS*/
void add_student_to_list(Student_list **studentPtr,int id,char *name,float grade) {
     if(grade < MIN_STUDENT_GRADE || grade > MAX_STUDENT_GRADE) {
        printf(RED"Error: Invalid grade. Must be a number between 0-100\n"RESET);
        return;
    }
    
    Student_list *new_student = malloc(sizeof(Student_list));
    if(!new_student) {
        printf(RED"Error: Memory allocation failed\n"RESET);
        return;
    }

    if(id < MIN_STUDENT_IDNUM) {
        printf(RED"Error: Invalid ID. It must be a positive number\n"RESET);
        free(new_student);
        return;
    }

    Student_list *temp1 = *studentPtr;
    while(temp1 != NULL) {
        if(temp1->id == id) {
            printf(RED"Error: Student with this ID already exists\n"RESET);
            free(new_student);
            return;
        }
        temp1 = temp1->next;
    }

    Student_list *temp2 = *studentPtr;
    while(temp2 != NULL) {
        if(strcmp(temp2->name,name)==0) {
            printf(RED"Error: Student with this name already exists\n"RESET);
            free(new_student);
            return;
        }
        temp2 = temp2->next;
    }

    strcpy(new_student->name,name);
    new_student->grade = grade;
    new_student->id = id;
    new_student->next = NULL;

    if(*studentPtr == NULL) {
        *studentPtr = new_student;
        save_students_to_file(*studentPtr);
        printf(GREEN"Student added successfully\n"RESET);
        return;
    }

    Student_list *temp3 = *studentPtr;
    while(temp3->next != NULL) temp3 = temp3->next;
    temp3->next = new_student;

    save_students_to_file(*studentPtr);
    printf(GREEN"Student added successfully\n"RESET);
}

int delete_student_from_list(Student_list **studentPtr,int id) {
    if(*studentPtr == NULL) {
        printf(RED"Error: Student list is empty\n"RESET);
        return -1;
    }

    Student_list *temp = *studentPtr, *prev = NULL;
    if(temp != NULL && temp->id == id) {
        *studentPtr = temp->next;
        free(temp);
        save_students_to_file(*studentPtr);
        return 0;
    }

    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf(RED"Error: Student not found in the list\n"RESET);
        return -1;
    }

    prev->next = temp->next;
    free(temp);
    save_students_to_file(*studentPtr);
    return 0;
}

void print_student_list(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty\n"RESET);
        return;
    }

    printf(BOLD BLUE"\nID\tName\t\tGrade\n"RESET);
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
        printf(RED"Error: Student list is empty\n"RESET);
        return;
    }

    if(newGrade < MIN_STUDENT_GRADE || newGrade > MAX_STUDENT_GRADE) {
        printf(RED"Error: Invalid grade. Must be a number between 0-100\n"RESET);
        return;
    }

    Student_list *head = studentPtr;
    while(studentPtr != NULL) {
        if(studentPtr->id == id) {
            studentPtr->grade = newGrade;
            printf(GREEN"Student grade updated successfully\n"RESET);
            save_students_to_file(head);
            return;
        }
        studentPtr = studentPtr->next;
    }

    printf(RED"Error: Student not found in the list\n"RESET);
}

int find_students_count(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty\n"RESET);
        return -1;
    }
    
    int countStudents = 0;
    while(studentPtr != NULL) {
        countStudents++;
        studentPtr = studentPtr->next;
    }

    return countStudents;
}

void print_average_grade(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty\n"RESET);
        return;
    }

    float sumGrade = 0;
    Student_list *temp = studentPtr;
    while(temp != NULL) {
        sumGrade += temp->grade;
        temp = temp->next;
    }

    float average_grade = sumGrade / find_students_count(studentPtr);
    printf(BOLD YELLOW"Students average grade is: %.2f\n"RESET,average_grade);
}
 
