#ifndef STORAGE_H
#define STORAGE_H

#include "../commands/commands.h"

void save_students_to_file(Student_list *studentPtr);
void load_students_from_file(Student_list **studentPtr);

#endif
