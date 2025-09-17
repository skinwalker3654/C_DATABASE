#ifndef UTILS_H
#define UTILS_H

#include "../commands/commands.h"
#include "../colors/colors.h"

void save_students_to_file(Student_list *studentPtr);
void load_students_from_file(Student_list **studentPtr);
void sort_students_by_id(Student_list *studentPtr);
void free_list_nodes(Student_list *studentPtr);
void help_show_select_command(void);
void help_show_delete_command(void);
void help_show_commands(void);

#endif
