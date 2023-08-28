# **Multithreading**

## **Learnings Covered in the project**

- **1. What is a Thread ?**

- **2. What are the differences between a thread and a process ?**

  It could be summarized as follow: A process can have sub-process, COol. Threads are **part of** a process. Threads (of a same process) run in a **shared memory space**, while processes run in **separate memory spaces**. Threads share things like the code and data sections, and processes have their own.

  (Source => EYNTK, made by Alexandre Gautier, Thanks Dude)

- **3. What is the difference between concurrency and parallelism**

- **4. How to create a thread**

- **5. How to properly exit a thread**

- **6. How to handle mutual exclusion**

- **7. What is a deadlock**

- **8. What is a race condition**

- **9. Aside Notes**

  <i>pthread_join()</i> function is the equivalent of <i>wait()</i> for processes. A call to <i>pthread_join()</i> blocks the calling thread <br>
  until the thread with identifier equal to the first argument terminates. ( => pthread_join(<i>thread_id</i>, NULL))
