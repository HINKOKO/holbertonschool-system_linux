# **Sockets** :electric_plug:

## **General Learnings**

- [**What is a socket and how it is represented on a Linux/UNIX system**](./Learnings.md#1-what-is-a-socket-and-how-it-is-represented-on-a-linuxunix-system)
- [**What are the different types of sockets**](./Learnings.md#2-what-are-the-different-types-of-sockets)
- [**What are the different socket domains**](./Learnings.md#3-what-are-the-different-socket-domains)
- [**How to create a socket, and bind to address/port**](./Learnings.md#4-how-to-create-a-socket-and-bind-it-to-an-addressport)
- **How to listen and accept incoming traffic**
- **How to connect to a remote application**
- **What is the HTTP protocol**
- **How to create a simple HTTP server**

## **General requirements**

- All your files will be compiled on Ubuntu 14.04 LTS
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
- All your files should end with a new line
- A **README.md** file, at the root of the folder of the project, is mandatory
- Your code should use the **Betty style.** It will be checked using betty-style.pl and betty-doc.pl
- You are not allowed to have more than 5 functions per file
- All your header files should be include guarded
- Unless specified otherwise, you are allowed to use the C standard library

## **More Info**

- For the **REST API** part of this project, you can easily test your HTTP server, using curl, Postman, or even your browser … <br>

- You are free to use any data structure that suits you as long as their purpose is well defined
REST API <br>
<hr><hr>

**=> The goal of this project is to build a simple HTTP REST API in C.**

This is going to be a really simple API, allowing us to manage a list of things to do (a.k.a a TODO list). Our database will be the **RAM**, meaning we <i>won’t have any persistent storage.</i> It’s not the purpose of this project anyway. Every time you start your server, the list of todos is empty.

<u style="font-size: 1.25rem">A todo contains at least the following fields:</u>

- **id** -> Positive integer, starting from 0
- **title** -> String
- **description** -> String

<u style="font-size: 1.25rem">Here are the different routes that will have to be implemented:</u>

- **/todos**

  - POST -> Creates a new todo
  - GET -> Retrieve all the todos
    <br>

- **/todos?id={id}** (where {id} is a positive integer)
  - GET -> Retrieve the todo with the corresponding id
  - DELETE -> Delete the todo with the corresponding id

<hr>
