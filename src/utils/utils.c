#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
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
}

void sort_students_by_id(Student_list *studentPtr) {
    if(studentPtr == NULL) return;

    int swapped = 1;
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

void select_operations(Student_list **nodes,char *operation,float number) {
    if(strcmp(operation,">")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }
        
        int foundIdx = 0;
        Student_list *scan = *nodes;
        while(scan != NULL) {
            if(scan->grade > number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Students with grade > then %.2f, not found\n"RESET,number);
            return;
        }

        printf(BOLD YELLOW"\nStudents with grade > then %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BOLD BLUE"ID\t Name\t\t Grade"RESET);
        printf(" |\n");
        printf("+------------------------------+\n");

        while(temp != NULL) {
            if(temp->grade > number) {
                printf("| %d\t %-10s\t" ,temp->id ,temp->name);
                if(temp->grade < 10) {
                    printf("  %.2f |\n",temp->grade);
                } else if(temp->grade < 100) {
                    printf(" %.2f |\n",temp->grade);
                } else {
                    printf("%.2f |\n",temp->grade);
                }
            }
            temp = temp->next;
        }
        printf("+------------------------------+\n\n");
    } else if(strcmp(operation,"<")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }

        int foundIdx = 0;
        Student_list *scan = *nodes;
        while(scan != NULL) {
            if(scan->grade < number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Students with grade < then %.2f, not found\n"RESET,number);
            return;
        }

        printf(BOLD YELLOW"\nStudents with grade < then %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BOLD BLUE"ID\t Name\t\t Grade"RESET);
        printf(" |\n");
        printf("+------------------------------+\n");

        while(temp != NULL) {
            if(temp->grade < number) {
                printf("| %d\t %-10s\t" ,temp->id ,temp->name);
                if(temp->grade < 10) {
                    printf("  %.2f |\n",temp->grade);
                } else if(temp->grade < 100) {
                    printf(" %.2f |\n",temp->grade);
                } else {
                    printf("%.2f |\n",temp->grade);
                }
            }
            temp = temp->next;
        }

        printf("+------------------------------+\n\n");
    } else if(strcmp(operation,"=")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }

        int foundIdx = 0;
        Student_list *scan = *nodes;
        while(scan != NULL) {
            if(scan->grade == number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Students with grade = to %.2f, not found\n"RESET,number);
            return;
        }

        printf(BOLD YELLOW"\nStudents with grade = to %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BOLD BLUE"ID\t Name\t\t Grade"RESET);
        printf(" |\n");
        printf("+------------------------------+\n");

        while(temp != NULL) {
            if(temp->grade == number) {
                printf("| %d\t %-10s\t" ,temp->id ,temp->name);
                if(temp->grade < 10) {
                    printf("  %.2f |\n",temp->grade);
                } else if(temp->grade < 100) {
                    printf(" %.2f |\n",temp->grade);
                } else {
                    printf("%.2f |\n",temp->grade);
                }
            }
            temp = temp->next;
        }

        printf("+------------------------------+\n\n"); 
    } else {
        printf(RED"\nError: Invalid operation '%s'\n"RESET,operation);
        printf(RED"Type: 'SELECT HELP' for more details\n\n"RESET);
    }
}

void delete_operations(Student_list **nodes,char *operation,float number) {
    if(strcmp(operation,">")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }
                
        Student_list *scan = *nodes;
        int foundIdx = 0;
        while(scan != NULL) {
            if(scan->grade > number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Student with grade > then %.2f, not found\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade > number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next;
        }

        printf(GREEN"Students with grade > then %.2f, deleted successfully\n"RESET,number);
        return;
    } else if(strcmp(operation,"<")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }

        int foundIdx = 0;
        Student_list *scan = *nodes;
        while(scan != NULL) {
            if(scan->grade < number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Students with grade < then %.2f, not found\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade < number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next;
        }

        printf(GREEN"Students with grade < then %.2f, deleted successfully\n"RESET,number);
        return;
    } else if(strcmp(operation,"=")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty\n"RESET);
            return;
        }

        int foundIdx = 0;
        Student_list *scan = *nodes;
        while(scan != NULL) {
            if(scan->grade == number) {
                foundIdx = 1;
                break;
            }
            scan = scan->next;
        }

        if(!foundIdx) {
            printf(RED"Error: Students with grade = to %.2f, not found\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade == number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next; 
        }

        printf(GREEN"Students with grade = to %.2f, deleted successfully\n"RESET,number);
        return;
    } else {
        printf(RED"\nError: Invalid operation '%s'\n"RESET,operation);
        printf(RED"Type: 'DELETE HELP' for more details\n\n"RESET);
    }
}


void help_show_commands() {
    printf(BOLD YELLOW"\nCommands:\n"RESET);
    printf(BOLD YELLOW"  insert <id> <name> <grade>   | Adds a student to the database\n"RESET);
    printf(BOLD YELLOW"  update <id> <new_grade>      | Updates students grade by the ID\n"RESET);
    printf(BOLD YELLOW"  DELETE HELP                  | Shows you every usage of <delete> command\n"RESET);
    printf(BOLD YELLOW"  SELECT HELP                  | Shows you every usage of <select> command\n"RESET);
    printf(BOLD YELLOW"  average                      | Prints students average grade\n"RESET);
    printf(BOLD YELLOW"  count                        | Prints student count\n"RESET);
    printf(BOLD YELLOW"  cls                          | Clears the terminal\n"RESET);
    printf(BOLD YELLOW"  min                          | Finds the student with the minimum grade\n"RESET);
    printf(BOLD YELLOW"  max                          | Finds the student with the maximum grade\n"RESET);
    printf(BOLD YELLOW"  help                         | Shows this pannel\n"RESET);
    printf(BOLD YELLOW"  exit                         | Exits the program\n\n"RESET);
}

void help_show_select_command() {
    printf(BOLD YELLOW"\n3 usages:\n"RESET);
    printf(BOLD YELLOW"  select                | Prints all the students in the list\n"RESET);
    printf(BOLD YELLOW"  select <name>         | Prints the student with this name\n"RESET);
    printf(BOLD YELLOW"  select <op> <grade>   | Prints students with <op> <grade>\n"RESET);
    printf(BOLD YELLOW"\n\nAvailable OP: '>', '<', '='\n\n"RESET);
}

void help_show_delete_command() {
    printf(BOLD YELLOW"\n3 usages:\n"RESET);
    printf(BOLD YELLOW"  delete                | Deletes all the students in the list\n"RESET);
    printf(BOLD YELLOW"  delete <id>           | Deletes the student with this ID\n"RESET);
    printf(BOLD YELLOW"  delete <op> <grade>   | Deletes students with <op> <grade>\n"RESET);
    printf(BOLD YELLOW"\n\nAvailable OP: '>', '<', '='\n\n"RESET);
}
