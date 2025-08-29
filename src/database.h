#ifndef DATABASE_H
#define DATABASE_H

#define STUDENT_NAME_SIZE   50
#define MAX_STUDENT_GRADE   100
#define MIN_STUDENT_GRADE   0
#define MAX_STUDENTS_COUNT  100

typedef struct Student_t {
    char name[STUDENT_NAME_SIZE];
    float grade;
    int id;
} Student_t;

typedef struct Student_list {
    Student_t students[MAX_STUDENTS_COUNT];
    int count_students;
} Student_list;

void save_students_to_file(Student_list *studentPtr);
void load_students_from_file(Student_list *studentPtr);
void initialize_list(Student_list *studentPtr);

extern Student_list students;

void add_student_to_list(Student_list *studentPtr,int id,char *name,float grade);
void delete_student_from_list(Student_list *studentPtr,int id);
void print_student_list(Student_list *studentPtr);
void edit_student_grade(Student_list *studentPtr,int id,float newGrade);
void help_show_commands(void);

#endif
