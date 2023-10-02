# **Learnings about sockets**

- ### **1. What is a socket and how it is represented on a Linux/UNIX system**

  A socket is a Low-Level endpoint for interprocess-communication on a computer network, it allows different software processes to communicate over a network using standard protocols (like TCP/IP or UDP). <br>
  **Like a pipe**, a socket is represented on a Linux/UNIX system as a **file descriptor**. <br> Each socket within the network has a unique name associated with it called a **socket descriptor**
  **Unlike pipes**, sockets supports communication between unrelated processes, even between processes running on different machines. <br>
  **Sockets** provides a Low-Level API for network communication, they allow **processes** to establish **connections**, **send & receive** data over a network, and handle network related tasks.<br>
  <br>

  <quote>
  If you"re familiar with **Go routines channel** in Golang,it has some similarities in the sense that both facilitates communication between different parts of a program or between different processes.</quote>

- ### **2. What are the different types of sockets**

  **Stream sockets:** Reliable, stream-oriented connection between two programs. Commonly used with the <strong>Transmission Control Protocol (TCP) in the Internet Protocol (IP)</strong>
  suite.

  **Datagram sockets:** Unreliable, message-oriented connection between two programs.
  Commonly used with the **User Datagram Protocol (UDP)** in the IP suite.

  **Raw sockets:** These allow programs to send and receive IP packets directly without the transport-layer protocol (TCP or UDP). Raw sockets are often used for **Low-Level network
  programming and for network security applications.**

  **Sequential packet sockets** similar to stream sockets
  , preserve message boundaries and can be used to send and receive discrete messages rather than a continuous stream of data.

  **Raw Ethernet sockets:** Bypass the network stack of the OS, Raw Ethernet sockets are commonly used in network sniffers and other network monitoring tools.

  **Unix Domain sockets:** Provides a mechanism for IPC between processes running on the same system. Unix domain sockets use a special file system <i>namespace</i> and can be used with both stream and datagram protocols.

  <quote>Each type of sockets comes of course with its own set of pros & cons. The choice will depend of the requirements of the application you want to set up</quote>

### **3. What are the different socket domains**

### **4. How to create a socket, and bind it to an address/port**

A socket can easily be created by using the **socket system call** which got this signature: <br>
```
int socket(int domain, int type, int protocol)
```
The <i>domain</i> a.k.a as <i>address family</i> is e.g AF_INET for IPv4 or AF_INET6 for, hence, IPv6. (a list of address family understood by Linux Kernel can be found at `man socket (2)`)<br>
The socket <i>type</i> e.g. **SOCK_STREAM** for **TCP** or **SOCK_DGRAM** for **UDP** <br>
Finally the socket <i>protocol</i> which is usually **0**, allowing the system to pick for us the appropriate protocol.
