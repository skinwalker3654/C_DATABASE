# Student Management System (C)

A cli database like tool for managing students in C
It support **CROUD OPARATIONS** (Create, Read, Update, Delete) with saving on a file

---

## Features
- **Insert** new students (ID, Name, Grade)
- **Select** all students **or** select one by name
- **Edit** the grade of a student by using id
- **Delete** all students **or** deleted one by id
- Handls ctr+c signal in case you exit before Memory gets freed
- Auto save changes in `database.txt`
- ANSI COLORS

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
- It uses linked list so you can add as much students as you want
- Students get sorted by the ID (**Bubble Sort**) 
- If `database.txt` dosent exists than the program creats it 
- The colors are not same in all systems (Terminal configuration deppends)
