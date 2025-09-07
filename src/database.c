#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include <string.h>

/*UTIL FUNCTIONS*/
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
 
void help_show_commands() {
    printf(BOLD YELLOW"\nCommands:\n"RESET);
    printf(BOLD YELLOW"  insert <id> <name> <grade>   | Adds a student to the database\n"RESET);
    printf(BOLD YELLOW"  update <id> <new_grade>      | Updates students grade by the ID\n"RESET);
    printf(BOLD YELLOW"  delete / delete <id>         | Deletes all students / deletes one student by the ID\n"RESET);
    printf(BOLD YELLOW"  select / select <name>       | Prints all the students / Prints one student by the name\n"RESET);
    printf(BOLD YELLOW"  average                      | Prints students average grade\n"RESET);
    printf(BOLD YELLOW"  count                        | Prints student count\n"RESET);
    printf(BOLD YELLOW"  cls                          | Clears the terminal\n"RESET);
    printf(BOLD YELLOW"  help                         | Shows this pannel\n"RESET);
    printf(BOLD YELLOW"  exit                         | Exits the program\n\n"RESET);
}
