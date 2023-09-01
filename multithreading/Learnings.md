# **Multithreading**

## **Learnings Covered in the project**

- ### [**1. What is a Thread ?**](#what)

  One could define a Thread as an execution unit that is part of a process, a set of logic sequential instruction, once again , <i>that is part of a process</i> => Threads are sometimes called <i>lightweigth processes</i><br>
  <br>
  A process can have multiple threads, all executing at the same time. <br>
  <br>

  **a Thread is a sequence of instructions within a program/process, that can be executed totally independently of other code**

  The project provided us in the resources this excellent [analogy](https://randu.org/tutorials/threads/#what) <br>
  A thread a thread... isn't it something you put through the eye of a sewing needle ? Absolutely. <br>
  We can think at our processors as sewing needles, and the threads in a program as the threads fiber, those thin strands that passes through the eye of the sewing needle, Yay !

- ### [**2. What are the differences between a thread and a process ?**](#diff)

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

Each one of a process's threads has its own context: its own ID, its own stack, its own instruction pointer, and processor registers. <br>
But since all of the threads are part of the same process, they share the same virtual memory address space: the same code, the same heap, the same shared libraries and same open file descriptors. <br>
Threads does not fall in the pattern of strict "parent-child" hierarchy like processes, they rather are like a \*_group of peers_, regardless of which one was created over another and so on... => Threads are like Holbies ! hum.. <br>

- ### [**3. What is the difference between concurrency and parallelism**](#concu)

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

- ### [**4. How to create a thread**]

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

- ### **5. How to properly exit a thread**

```

void *thread_fever(void *arg)
{
(void)arg;
printf("Hello from the Tdreeead !!\n");
printf("Thread is over\n");
pthread_exit(NULL);
}

int main(void)
{
pthread_t tid;

    pthread_create(&tid, NULL, thread_fever, NULL);
    /* pthread_join -> join with a temrinated thread*/
    pthread_join(&tid, NULL);
    printf("Main thread finished\n");
    return (0);

}

```

- ### [**6. How to handle mutual exclusion**]

**Mutex** is short for **M**utual **E**xclusion, and also called a "synchronization primitive". It's basically a "lock" that permits us to regulate access to data and prevent shared resources being used at the same time by different threads. <br>
We can think of **mutex** as the lock of the bathroom door. One thread locks it to indicate "occupied" and the other thread is waiting patiently that this locks indicates 'free' or 'opened'. <br>
Mutexes are a protocol to **serialize** the access to shared resources.

- ### [**7. What is a deadlock**]

  An important problem can happens with **mutexes** => a **deadlock**. Here's a basic situation: <br>
  Thread 1 locks **lock A** | Thread 2 locks **lock B** <br>
  Thread 1 now wants **lock B** | Thread 2 now wants **lock A** <br>
  ==> Instant **deadlock** A program can deadlock if two (or more) threads have stopped execution or are spinning permanently <br>
  It can also happen if threads do not unlock mutexes properly, for an example of proper unlocking, see this [sample](./practice_threads/practice_thread.c) in this Repo.

- ### [**8. What is a race condition**]

  A **race condition** occurs when threads access sharing data or resources without synchronization rules/protocol defined by the programmer. The access to the resources has not been serialized and you got multiple threads? you'll certainly face a race condition soon... see this [Not to do]() file,

  **COmpilation Trick**

  ```
  gcc -fsanitize=thread -g nottodo.c && ./a.out
  ```

  This "flag" will warn you if a race condition is present, Try to compile the file given in the link with this flag to see a beautiful explanation warning 😉. <br>
  Even if we decrease the **MAXCOUNT** to a small number, the program will be 'successfull', our two threads will manage to count up to 2 \* MAXCOUNT, but still a data race danger, with higher number, test it, you barely get the count... <br>
  Here's a nice video from ComputerPhile => [Watch this](https://www.youtube.com/watch?v=7ENFeb-J75k&ab_channel=Computerphile)

- ### **9. Aside Notes**

#### **Joining Threads**

In order to block the execution of a thread until another one finishes, we can use the **pthread_join** function call:

```
int pthread_join(pthread_t thread, void **retval)
```

**thread** => the ID of the thread that <i>this calling thread</i> (the one calling pthread_join) should wait for. <br>
**retval** => pointer towards a variable that can contain the return value of the thread's routine (**start_routine** supplied with **pthread_create** call), generally , a simple **NULL** would suffice.

<i>pthread_join()</i> function is the equivalent of <i>wait()</i> for processes. A call to <i>pthread_join()</i> blocks the calling thread <br>
until the thread with identifier equal to the first argument terminates. ( => pthread_join(<i>thread_id</i>, NULL))

- ### **10. What is a Gaussian Blur guys ?**

  Explanation to come



