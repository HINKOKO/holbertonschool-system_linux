# **C - Signals** :loudspeaker:

## **Learnings**

- **What is a signal**

  Signals are software interrupts used to notify a process of a event that requires attention. <br>
  A signal is an **asynchronous** "notification" sent to process/thread to notify it from an event.

- **Why do they exist**

  Signals were born as a means of inter-process communication and to handle various asynchronous events in computer systems. They are useful to the OS to notify a process about certain events or conditions that happens outside of normal program execution flow.
  With the help of signals, we can achieve, for example, these actions:

  - **Process Termination** The OS can notify a process that it should terminate
    For example, we all like our famous **"Ctrl^C"** when we are bored of a process or when we don't know how to stop the mess or an infinite loop !!
  - **Error handling** I think everybody who programs in C has already seen its terminal saying "segmentation fault",

- **When are they delivered and by whom**
- **What are the default actions of signals**
- **How to set up a handler for a signal**
- **How to send signals**
- **What signals can’t be caught**
  These two **_bad-ass signals_** **SIGKILL** and **SIGSTOP** cannot be blocked, ignored or caught
