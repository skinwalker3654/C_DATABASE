# Student Management System (C)

A cli database like tool for managing students in C
It support **CROUD OPARATIONS** (Create, Read, Update, Delete) with saving on a file

---

## Features
- **Insert** new students (id, όνομα, βαθμός)
- **Select** all students
- **Edit** the grade of a student by using id
- **Delete** students by id
- Auto save changes in `database.txt`

---

## Requirments:
`gcc` compiler and `GNU MAKE`

### build and run:
```bash
make 
make run
```
### when you want to delete executables:
```bash
make clean
```
---

## Then you can write commands like:

### Insert student
```bash
insert 1 John Doe 8.5
```

### Select students
```bash
select
```

### Edit student grade
```bash
edit 1 9.7
```

### Delete student
```bash
delete 1
```

---

## Database file
The students are saved in `database.txt` with form:

```
id|name|grade
```

example:

```
1|John Doe|8.5
2|Alice Smith|9.2
```

---

## 📌 Notes
- Name can have spaces (example. `John Michael Doe`).
- Max name size: **49 characters**.
- if `database.txt` dosent exists than the program creats it 
