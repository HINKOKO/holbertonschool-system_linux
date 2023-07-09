# **Holberton School OBJDUMP**

## **Learning Objective**

The purpose of this folder is to built a C program that mimic the output of ```objdump -fs <binary_file>``` command.

## **Mapping in memory**

The function [map_file](./memory_mapping.c) is a useful technique, when we **map a file** into memory, it means we establish a direct mapping between the file's content and a region of memory in our program's address space.
This enables to access file's data (file is filled in => argv[1]) as if it were in memory, without the need for explicit **read operations.** <br>

- Efficiency => doing so avoid mutiple read operations to access the file's data.
Once the file is mapped, we can treat it as if it were a large array in memory, allowing for faster and more efficient data access.

- Random Access => We can directly access any part of the file by manipulating pointers in memory, which can be beneficial for the tool we built here, indeed **objdump** need to analyse different **sections** of the file.

- Simplified code => By mapping, we get rid of the need for explicit file I/O operations like reading and seeking. This simplifies the code and ease file's content manipulation.

Once the file is mapped in memory, we can use standard **pointers arithmetic** and memory access techniques to analyze file's content.
```
int map_file(void **map, const char *filename)
```
**map** is a pointer to a pointer, by doing so, using a **void **** parameter allows the function to modify the pointer to point to the memory mapped region, enabling the caller to access file's content in a convenient manner.
This allow the caller to access the mapped file data through the pointer.

**filename** simply a string that represents the file path or name that we want to map in memory.

[dumpper.c](./dumpper.c)

