#ifndef UTILS_H
#define UTILS_H

#include "../commands/commands.h"

/*UTIL FUNCTIONS*/
void sort_students_by_id(Student_list *studentPtr);
void free_list_nodes(Student_list *studentPtr);

/*OPERATIONS*/
void select_operations(Student_list **nodes,char *operation,float number);
void delete_operations(Student_list **nodes,char *operation,float number);

/*HELP PANNELS*/
void help_show_select_command(void);
void help_show_delete_command(void);
void help_show_commands(void);

#endif
