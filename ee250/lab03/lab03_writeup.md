
1. The reliability of UDP changed once the loss was added since UDP prioritizes just sending information at any time instead of prioritizing the reliability.

2. The reliability of TCP did not change since the information was only sent when both "sides" were able to ensure the information was sent.

3. The speed of the TCP connection slowed considerably since it had to "wait" for a stable connection.


tcp.c questions
1. argc is argument count and argv is the argument vector - which contains the arguments when running the program

2. A unix file descriptor is an indicator to access a file, and a file table is a table of all files opened by the system.

3. A struct is a user-defined collection of variables similar to a class. SOCKADDR_IN specifies a transport address and port for connection.

4. The input parameters of socket are the domain (in this case ipv4 internet addresses) and the byte stream socket. The output is the file descriptor of the socket.

5. The input parameters of bind are the socket file descriptor, the sockaddress, and the length of the sockaddr struct. The output is 0 or -1 depending on it's success. The inputs of listen are the socket and an integer defining how many connections may wait before it refuses other connections.

6. While(1) allows the program to continuously listen for a connection, but without multithreading - the program is unable to handle more than 1 connection.

7. The fork() allows for concurrent listening in the program to handle multiple connections at once.