#include <stdio.h>
#include <stdlib.h>
#include "commands.h"
#include "../colors/colors.h"
#include <string.h>

/*MAIN FUNCTIONS*/
void add_student_to_list(Student_list **studentPtr,int id,char *name,float grade) {
     if(grade < MIN_STUDENT_GRADE || grade > MAX_STUDENT_GRADE) {
        printf(RED"Error: Invalid grade, it must be a number between 0-100.\n"RESET);
        return;
    }

    if(id < MIN_STUDENT_IDNUM) {
        printf(RED"Error: Invalid ID number, it must be a positive number bigger than 0.\n"RESET);
        return;
    }

    Student_list *new_student = malloc(sizeof(Student_list));
    if(!new_student) {
        printf(RED"Error: Memory allocation failed.\n"RESET);
        return;
    }

    Student_list *temp1 = *studentPtr;
    while(temp1 != NULL) {
        if(temp1->id == id) {
            printf(RED"Error: Student with this ID already exists.\n"RESET);
            free(new_student);
            return;
        }
        temp1 = temp1->next;
    }

    Student_list *temp2 = *studentPtr;
    while(temp2 != NULL) {
        if(strcmp(temp2->name,name)==0) {
            printf(RED"Error: Student with this name already exists.\n"RESET);
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
        printf(GREEN"Student added succesfully.\n"RESET);
        return;
    }

    Student_list *temp3 = *studentPtr;
    while(temp3->next != NULL) temp3 = temp3->next;
    temp3->next = new_student;

    printf(GREEN"Student added succesfully.\n"RESET);
}

void delete_student_from_list(Student_list **studentPtr,int id) {
    if(*studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }

    Student_list *temp = *studentPtr, *prev = NULL;
    if(temp != NULL && temp->id == id) {
        *studentPtr = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) {
        printf(RED"Error: Student not found in the list.\n"RESET);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

void print_student_list(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }

    printf("\n+------------------------------+\n");
    printf("| ");
    printf(BLUE"ID\t Name\t\t Grade"RESET);
    printf(" |\n");
    printf("+------------------------------+\n");
    while(studentPtr != NULL) {
        printf("| %d\t %-10s\t",studentPtr->id ,studentPtr->name);
        if(studentPtr->grade < 10) { 
            printf("  %.2f |\n",studentPtr->grade); 
        } else if(studentPtr->grade < 100) {
            printf(" %.2f |\n",studentPtr->grade);
        } else {
            printf("%.2f |\n",studentPtr->grade);
        }

        studentPtr = studentPtr->next;
    }

    printf("+------------------------------+\n\n");
}

void edit_student_grade(Student_list *studentPtr,int id,float newGrade) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }

    if(newGrade < MIN_STUDENT_GRADE || newGrade > MAX_STUDENT_GRADE) {
        printf(RED"Error: Invalid grade. Must be a number between 0-100.\n"RESET);
        return;
    }

    while(studentPtr != NULL) {
        if(studentPtr->id == id) {
            studentPtr->grade = newGrade;
            printf(GREEN"Students grade updated succesfully.\n"RESET);
            return;
        }
        studentPtr = studentPtr->next;
    }

    printf(RED"Error: Student not found in the list.\n"RESET);
}

void edit_student_name(Student_list *studentPtr,int id,char *newName) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty\n"RESET);
        return;
    }
    
    while(studentPtr != NULL) {
        if(studentPtr->id == id) {
            strcpy(studentPtr->name,newName);
            printf(GREEN"Students name updated succesfully.\n"RESET);
            return;
        }
        studentPtr = studentPtr->next;
    }

    printf(RED"Error: Student not found in the list.\n"RESET);
}

int find_students_count(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
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
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }

    float sumGrade = 0;
    Student_list *temp = studentPtr;
    while(temp != NULL) {
        sumGrade += temp->grade;
        temp = temp->next;
    }

    float average_grade = sumGrade / find_students_count(studentPtr);
    printf(LBLUE"Total students average grade is:"RESET); 
    printf(GREEN" %.2f\n"RESET,average_grade);
}

void find_max_student_grade(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }
    
    Student_list *temp = studentPtr;
    Student_list *student = studentPtr;
    float max_grade = temp->grade;
    while(temp != NULL) {
        if(temp->grade > max_grade) {
            max_grade = temp->grade;
            student = temp;
        }
        temp = temp->next;
    }

    printf("\nStudent with the maximum grade:\n");
    printf(LBLUE"Name: %s"RESET,student->name);
    printf(" | ");
    printf(LBLUE"Grade: %.2f"RESET,max_grade);
    printf(" | ");
    printf(LBLUE"ID: %d\n\n"RESET,student->id);
}

void find_min_student_grade(Student_list *studentPtr) {
    if(studentPtr == NULL) {
        printf(RED"Error: Student list is empty.\n"RESET);
        return;
    }

    Student_list *temp = studentPtr;
    Student_list *student = studentPtr;
    float min_grade = temp->grade;
    while(temp != NULL) {
        if(temp->grade < min_grade) {
            min_grade = temp->grade;
            student = temp;
        }
        temp = temp->next;
    }

    printf("\nStudent with the minimum grade:\n");
    printf(LBLUE"Name: %s"RESET,student->name);
    printf(" | ");
    printf(LBLUE"Grade: %.2f"RESET,min_grade);
    printf(" | ");
    printf(LBLUE"ID: %d\n\n"RESET,student->id);
}
