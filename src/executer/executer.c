#include "executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_commands(char *input, Student_list **nodes) {
    char command[20];
    char name[STUDENT_NAME_SIZE];
    float grade;
    int id;

    if(strlen(input) == 0) return;
    sscanf(input,"%s",command);

    if(strcmp(command,"insert")==0) {
        const int tokensCount = 4;
        char *tokens[tokensCount];

        int count = 0;
        char *ptr = strtok(input, " ");
        while(ptr != NULL) {
            tokens[count++] = ptr;
            ptr = strtok(NULL, " ");
        }

        if(count == tokensCount) {
            char *endptr;
            id = strtol(tokens[1], &endptr, 10);
            if(*endptr != '\0') {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
                return;
            }

            grade = strtof(tokens[3], &endptr);
            if(*endptr != '\0') {
                printf(RED"\nError: Invalid arguments passed\n"RESET);
                printf(RED"Type: 'help' for more details\n\n"RESET);
                return;
            }

            strncpy(name,tokens[2],sizeof(name));
            name[sizeof(name)-1] = '\0';
            add_student_to_list(nodes, id, name, grade);
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"delete")==0) {
        const int tokensCount = 2;
        char *tokens[tokensCount];

        char *token = strtok(input," ");
        int count = 0;
        while(token != NULL) {
            tokens[count++] = token;
            token = strtok(NULL," ");
        }

        if(count == 1) {
            if(*nodes == NULL) {
                printf(RED"Error: Student list is empty\n"RESET);
                return;
            } else {
                free_list_nodes(*nodes);
                *nodes = NULL;
                printf(GREEN"Students deleted successfully\n"RESET);
                save_students_to_file(*nodes);
                return;
            }
        } else if(count == 2) {
            char *endPtr;
            id = strtol(tokens[1],&endPtr,10);
            if(*endPtr != '\0') {
                printf(RED"Error: Invalid ID\n"RESET);
                return;
            }
            
            delete_student_from_list(nodes,id);
            return;
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"select")==0) {
        const int tokensCount = 3; 
        char *tokens[tokensCount];

        char *token = strtok(input," ");
        int count = 0;
        while(token != NULL) {
            tokens[count++] = token;
            token = strtok(NULL," ");
        }

        if(count == 1) {
            sort_students_by_id(*nodes);
            print_student_list(*nodes);
        } else if(count == 2) {
            Student_list *tempPtr = *nodes;
            strcpy(name,tokens[1]);
            name[sizeof(name)-1] = '\0';

            while(tempPtr != NULL) {
                if(strcmp(tempPtr->name,name)==0) {
                    printf(BOLD YELLOW"ID: %d"RESET,tempPtr->id);
                    printf(" | ");
                    printf(BOLD YELLOW "Name: %s"RESET,tempPtr->name);
                    printf(" | ");
                    printf(BOLD YELLOW "Grade: %.2f\n"RESET,tempPtr->grade);
                    break;
                }
                tempPtr = tempPtr->next;
            }

            if(tempPtr == NULL) {
                printf(RED"Error: Student not found\n"RESET);
                return;
            }
        } else if(count == 3) {
            char *endPtr;
            float number = strtof(tokens[2],&endPtr);
            if(*endPtr != '\0') {
                printf(RED"Error: Invalid number\n"RESET);
                return;
            }

            char operation[2];
            strcpy(operation,tokens[1]);

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
                    printf(RED"Error: Students with grade > %.2f, not found\n"RESET,number);
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
                printf(RED"\nError: Invalid operation\n"RESET);
                printf(RED"Valid operations: '>', '<', '='\n\n"RESET);
            }
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(command,"update")==0) {
        const int tokensCount = 3; 
        char *tokens[tokensCount];

        char *token = strtok(input," ");
        int count = 0;
        while(token != NULL) {
            tokens[count++] = token;
            token = strtok(NULL," ");
        }

        if(count == tokensCount) {
            char *endPtr;
            id = strtol(tokens[1],&endPtr,10);
            if(*endPtr != '\0') {
                printf(RED"Error: Invalid ID\n"RESET);
                return;
            }

            float new_grade = strtof(tokens[2],&endPtr);
            if(*endPtr != '\0') {
                printf(RED"Error: Invalid grade\n"RESET);
                return;
            } 

            edit_student_grade(*nodes,id,new_grade);
            return;
        } else {
            printf(RED"\nError: Invalid arguments passed\n"RESET);
            printf(RED"Type: 'help' for more details\n\n"RESET);
        }
    }
    else if(strcmp(input,"count")==0) {
        int studentCount = find_students_count(*nodes);
        if(studentCount == -1) return;
        else if(studentCount == 1) {
            printf(BOLD YELLOW"There is"RESET);
            printf(GREEN" %d "RESET,studentCount);
            printf(BOLD YELLOW"student in the list\n"RESET); 
        }
        else if(studentCount > 1) {  
            printf(BOLD YELLOW"There are"RESET);
            printf(GREEN" %d "RESET,studentCount);
            printf(BOLD YELLOW"students in the list\n"RESET);
        }
    }
    else if(strcmp(input,"average")==0) {
        print_average_grade(*nodes);
    }
    else if(strcmp(input,"max")==0) {
        find_max_student(*nodes);
    } else if(strcmp(input,"min")==0) {
        find_min_student(*nodes);
    } else if(strcmp(input,"SELECT HELP")==0) {
        printf(BOLD YELLOW"\n3 usages:\n"RESET);
        printf(BOLD YELLOW"  select                | Prints all the students in the list\n"RESET);
        printf(BOLD YELLOW"  select <name>         | Prints the student with this name\n"RESET);
        printf(BOLD YELLOW"  select <op> <grade>   | Prints students with <op> <grade>\n"RESET);
        printf(BOLD YELLOW"\n\nAvailable OP: '>', '<', '='\n\n"RESET);
    }
    else if(strcmp(input,"help")==0) {
        help_show_commands();
    }
    else if(strcmp(input,"exit")==0) {
        printf(BOLD BLUE"Exiting...\n"RESET);
        free_list_nodes(*nodes);
        exit(0);
    }
    else if(strcmp(input,"cls")==0) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    else {
        printf(RED"\nError: Invalid command '%s'\n"RESET,input);
        printf(RED"Type: 'help' for more details\n\n"RESET);
    }
}
