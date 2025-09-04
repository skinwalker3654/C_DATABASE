#ifndef DATABASE_H
#define DATABASE_H

#define STUDENT_NAME_SIZE   50
#define MAX_STUDENT_GRADE   100
#define MIN_STUDENT_GRADE   0
#define MIN_STUDENT_IDNUM   1

typedef struct Student_list {
    char name[STUDENT_NAME_SIZE];
    float grade;
    int id;
    struct Student_list *next;
} Student_list;

/*UTIL FUNCTIONS*/
void save_students_to_file(Student_list *studentPtr);
void load_students_from_file(Student_list **studentPtr);
void sort_students_by_id(Student_list *studentPtr);
void free_list_nodes(Student_list *studentPtr);

/*MAIN FUNCTIONS*/
void add_student_to_list(Student_list **studentPtr,int id,char *name,float grade);
void delete_student_from_list(Student_list **studentPtr,int id);
void print_student_list(Student_list *studentPtr);
void edit_student_grade(Student_list *studentPtr,int id,float newGrade);
void help_show_commands(void);

#endif
