# **Multithreading**

## **Learnings Covered in the project**

- ### **1. What is a Thread ?**

  One could define a Thread as an execution unit that is part of a process, a set of logic sequential instruction, once again , <i>that is part of a process</i> => Threads are sometimes called <i>lightweigth processes</i><br>
  <br>
  A process can have multiple threads, all executing at the same time.

  The project provided us in the resources this excellent [analogy](https://randu.org/tutorials/threads/#what) <br>
  A thread a thread... isn't it something you put through the eye of a sewing needle ? Absolutely. <br>
  We can think at our processors as sewing needles, and the threads in a program as the threads fiber, those thin strands that passes through the eye of the sewing needle, Yay !

- ### **2. What are the differences between a thread and a process ?**

- #### **2.1 What is a process**

  A computer program **becomes** a process when it is loaded from some storage location in your machine to the computer's memory (RAM) and begins its execution. (process can be executed by one processor or a set of several ones) <br>
  A process in memory "carries some information" about itself, such as program counter (keeping track of the which instruction is currently being executed), registers, variables, file handles, signals... <br>
  And .. a **thread** is a sequence of such instructions within a program, that can run <i>independently</i> of other code.

  - #### **speaking of differences**

It could be summarized as follow: A process can have sub-process, COol. Threads are **part of** a process. Threads (of a same process) run in a **shared memory space**, while processes run in **separate memory spaces**. Threads share things like the code and data sections, while processes have their own.

Here some facts about those two terms:

| Parameter  |              Process               |                 Thread                 |
| :--------: | :--------------------------------: | :------------------------------------: |
|   Memory   |          Mostly isolated           |   Threads share memory (Heap level)    |
|    Data    |       Do not share any data        |       share data with each other       |
| Definition | Process means program in execution | Threads means a 'segment' of a process |

(Sources => EYNTK, made by Alexandre Gautier, Thanks Dude <br>
=> [TheRandu](https://randu.org/tutorials/threads))

- ### **3. What is the difference between concurrency and parallelism**

  #### **3.1 Concurrency**

  **Concurrency** means multiple tasks which start, run, and complete in <i>overlapping time periods</i> in no specific orders. Of course we talk about concurrency essentially for a minimum of two tasks or more. <br>
  Though tasks **look like running simultaneously**, but essentialy they MAY NOT. They take advantage of <a href="https://cpu.land/slice-dat-time">**CPU-Time-Slicing**</a> feature of the OS, where each task run parts of its task and then goes to the waiting state. <br>
  Modern Operating systems on modern computers - haha - based on the priority of tasks, thus, assings CPU and other resources (e.g. memory); turn by turn to all tasks and allow them to complete all. To the user-perspective, it seems that all tasks are running in **parallell**, magic uh ? this is called <i><bold>CONCURRENCY</bold></i>

  ##### **Go Go Gophers !**

  Golang or 'Go' is considered a good choice for concurrency:

  - **Goroutines** they are lightweigth, independently scheduled threads in Go. Managed by the Go runtime, more efficient than "traditional" threads, as they can be multiplexed onto a smaller number of operatin system threads.
  - **Channels** Go provides channels, which are communication mechanisms that allow safe and synchronized data sharing between goroutines. Channels promotes the passing of data rather than sharing memory, reducing the likehoof of race conditions and other sync issues.

  #### **3.2 Parallelism**

  'Parallelism' does not require two tasks to exist. It basically run **parts of tasks** || **multiple tasks** at the same time using the multi-core infrastructure of your CPU, by assigning one core to each task/sub-task. <br>
  But it does require, a hardware with **multiple processing units** essentially. <br>
  <br>

  Best sentence I've ever read: <br>

  <blockquote>Concurrency is about <strong>dealing with lots of things at once</strong>
  Parallelism is about <strong>doing lots of things at once</strong></blockquote>
  <br>

  Thanks to [Lokesh Gupta](https://howtodoinjava.com/java/multi-threading/concurrency-vs-parallelism/)

- **4. How to create a thread**

In Low-level Specialization, we play mostly with **C-programming**, **multithreading** is not supported by the language standard <br>
No worries, we got a standard interface in C to manipulate threads with its **<pthread.h>** library. It is gathering around 60 functions to **create** and **join** threads, as well as managing them. <br>
Now we asked "how to create" , it's done with the function:

```
int pthread_create(pthread_t *restrict thread,
                   const pthread_attr_t *restrict attr,
                   void *(*start_routine)(void *),
                   void *restrict arg);
```

Arguments explanation:

- **thread** pointer to a pthread_t type variable, to store the ID of the thread we will create.
- **attr** allows us to change the defaults attributes of the new thread. Really beyond the scope of this project :smile:
- **start_routine** the function where the thread will start its execution. basically a function with this prototype:

```
void *function_name(void *arg)
```

- **arg** pointer to an argument to pass to the **thread's start_routine** function, kiddo if you wish to pass several parameters to the function, you'll need to give it a pointer to a data structure.

- **Return value** 0 if successful, error code if not.
  <br>
  **Task 0** is a good demonstration about **thread creation**

  ```

  void *thread_entry(void *arg)
  {
    printf("%s\n", (char *)arg);
    pthread_exit(NULL);
    return (0);
  }


  int main(void)
  {
    /* tid -> integer used to identify the thread in the system */
    pthread_t tid;

    pthread_create(&tid, NULL, &thread_entry, "Holberton School");

    sleep(1);
    printf("Created thread ID -> %lu\n", tid);
    thread_entry("C is fun");
    return (EXIT_SUCCESS);
  }
  ```

```

- **5. How to properly exit a thread**

- **6. How to handle mutual exclusion**

- **7. What is a deadlock**

- **8. What is a race condition**

- **9. Aside Notes**

  <i>pthread_join()</i> function is the equivalent of <i>wait()</i> for processes. A call to <i>pthread_join()</i> blocks the calling thread <br>
  until the thread with identifier equal to the first argument terminates. ( => pthread_join(<i>thread_id</i>, NULL))

- **10. What is a Gaussian Blur guys ?**

Matrix of the form for the kernel convolution, (an example with 3 by 3)

| 1 | 2 | 1 | <br>
| 2 | 4 | 2 | <br>
| 1 | 2 | 1 | <br>
```
