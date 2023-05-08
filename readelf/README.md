# **C - ELF: readelf**

## **Learning Objectives**

- **What is the ELF format**
	**ELF** is **NOT** a ***A type of supernatural being in Germanic mythology and folklore*** , it rather stands for <br>
	**E**xecutable and **L**inkable **F**ormat. <br>
	An ELF defines how instructions are stored in executable code.
	In C programming, generated by the Compiler and the Linker. <br>
	The Compiler --> produces an object files (containing compiled code and data) <br>
	The Linker --> combines that object files with other object files friends and libraries to produce an executable.
	By design, the ELF Format is cross-platform, flexible, extensible (support differents Endianesses for instance).
- **What kind of files are in the ELF format**

- **What are the different parts that constitute an ELF file**
	ELF file always starts with the **header** (mandatory part)
	besides the header, we've got these parts:
	- Program headers or Segments
	- Section headers or Sections
	- Data

- What information are present in the file header
- What information are present in the sections header table
- What information are present in the program header table
- How to parse an ELF file using C structures