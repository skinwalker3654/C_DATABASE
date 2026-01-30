#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../colors/colors.h"

/*UTIL FUNCTIONS*/
void free_list_nodes(Student_list *studentPtr) {
    while(studentPtr != NULL) {
        Student_list *temp = studentPtr;
        studentPtr = studentPtr->next;
        free(temp);
    }
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
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }
        
        /*This finds stuednts with grade > than the given number*/
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
            printf(RED"Error: Students with grade > than %.2f not found.\n"RESET,number);
            return;
        }

        printf(LBLUE"\nStudents with grade > than %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BLUE"ID\t Name\t\t Grade"RESET);
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
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }

        /*This finds students with grade < than the given number*/
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
            printf(RED"Error: Students with grade < than %.2f not found.\n"RESET,number);
            return;
        }

        printf(LBLUE"\nStudents with grade < than %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BLUE"ID\t Name\t\t Grade"RESET);
        printf(" |\n");
        printf("+------------------------------+\n");

        /*We print those students*/
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
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }

        /*This finds students with grade = to the given number*/
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
            printf(RED"Error: Students with grade = to %.2f not found.\n"RESET,number);
            return;
        }

        printf(LBLUE"\nStudents with grade = to %.2f:\n"RESET,number);
        printf("\n+------------------------------+\n");
        printf("| ");
        printf(BLUE"ID\t Name\t\t Grade"RESET);
        printf(" |\n");
        printf("+------------------------------+\n");

        /*We print those students*/
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
        printf(RED"\nError: Invalid operation '%s'.\n"RESET,operation);
        printf(RED"Type: 'SELECT HELP' for more details.\n\n"RESET);
    }
}

void delete_operations(Student_list **nodes,char *operation,float number) {
    if(strcmp(operation,">")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }

        /*This finds stuednts with grade > than the given number*/
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
            printf(RED"Error: Students with grade > than %.2f not found.\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade > number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next;
        }

        printf(GREEN"Students with grade > than %.2f have been deleted successfully.\n"RESET,number);
    } else if(strcmp(operation,"<")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }

        /*This finds students with grade < than the given number*/
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
            printf(RED"Error: Students with grade < than %.2f not found.\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade < number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next;
        }

        printf(GREEN"Students with grade < than %.2f have been deleted successfully.\n"RESET,number);
    } else if(strcmp(operation,"=")==0) {
        Student_list *temp = *nodes;
        if(temp == NULL) {
            printf(RED"Error: Student list is empty.\n"RESET);
            return;
        }

        /*This finds students with grade = to the given number*/
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
            printf(RED"Error: Students with grade = to %.2f not found.\n"RESET,number);
            return;
        }

        while(temp != NULL) {
            if(temp->grade == number) 
                delete_student_from_list(nodes,temp->id);
            temp = temp->next;
        }

        printf(GREEN"Students with grade = to %.2f have been deleted successfully.\n"RESET,number);
    } else {
        printf(RED"\nError: Invalid operation '%s'.\n"RESET,operation);
        printf(RED"Type: 'DELETE HELP' for more details.\n\n"RESET);
    }
}
void help_show_commands() {
    printf(LBLUE"\nCommands:\n"RESET);
    printf(LBLUE"  insert <id> <name> <grade>   | Adds students to the database\n"RESET);
    printf(LBLUE"  update <id> <new_grade>      | Updates students grade by the ID\n"RESET);
    printf(LBLUE"  rename <id> <new_name>       | Updates the name of the student\n"RESET);
    printf(LBLUE"  DELETE HELP                  | Shows you every usage of <delete> command\n"RESET);
    printf(LBLUE"  SELECT HELP                  | Shows you every usage of <select> command\n"RESET);
    printf(LBLUE"  version                      | Shows the current version of the program\n"RESET);
    printf(LBLUE"  average                      | Prints students average grade\n"RESET);
    printf(LBLUE"  count                        | Prints student count\n"RESET);
    printf(LBLUE"  cls                          | Clears the terminal\n"RESET);
    printf(LBLUE"  min                          | Finds the student with the minimum grade\n"RESET);
    printf(LBLUE"  max                          | Finds the student with the maximum grade\n"RESET);
    printf(LBLUE"  help                         | Shows this panel\n"RESET);
    printf(LBLUE"  exit                         | Exits the program\n\n"RESET);
}

void help_show_select_command() {
    printf(LBLUE"\n3 usages:\n"RESET);
    printf(LBLUE"  select                | Prints all the students in the list\n"RESET);
    printf(LBLUE"  select <name>         | Prints the student with this name\n"RESET);
    printf(LBLUE"  select <op> <grade>   | Prints students with grade [<|>|=] than <grade>\n"RESET);
    printf(LBLUE"\n\nAvailable OP: '>', '<', '='\n\n"RESET);
}

void help_show_delete_command() {
    printf(LBLUE"\n3 usages:\n"RESET);
    printf(LBLUE"  delete                | Deletes all the students in the list\n"RESET);
    printf(LBLUE"  delete <id>           | Deletes the student with this ID\n"RESET);
    printf(LBLUE"  delete <op> <grade>   | Deletes students with grade [<|>|=] than <grade>\n"RESET);
    printf(LBLUE"\n\nAvailable OP: '>', '<', '='\n\n"RESET);
}
