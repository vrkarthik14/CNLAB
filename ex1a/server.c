#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h> 

#define bufsize 1024

int main(){

  /*	Steps involved in establishing a socket on the server side are:
	1. Create a socket with the socket() system call
	2. Bind the socket to an address using the bind() system call. For a server socket on the 		   Internet, an address consists of a port number on the host machine.
	3. Listen for connections with the listen() system call
	4. Accept a connection with the accept() system call. This call typically blocks until a client 	   connects with the server.
	5. Send and receive data
  */
  int serverSocket, newSocket;
  char buffer[bufsize];
  char fname[255];
  int fd,n;
  struct sockaddr_in serverAddr,cleint_addr;//from netinet.h header
  //struct sockaddr_storage serverStorage;
  int addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /*  Adress domain
	*Internet domain(process to process b/w two hosts
	*Unix domain two process which share common file system communicate
      Stream socket
	*SOCK_STREAM continuous stream of charecters - TCP protocol
	*DATAGRAM socket have to read entire message at once - UDP protocol
      Default protocol (TCP in this case) */
  serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order
	FTP -21
	PORT number above 2000 are available. 
	instead of simply copying the port number to this field, it is necessary to convert this to network byte order using the function htons() which converts a port number in host byte order to a port number in network byte order.
*/

  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

  /*---- Bind the address struct to the socket ----*/
  bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(serverSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof cleint_addr;
  newSocket = accept(serverSocket, (struct sockaddr *) &cleint_addr, &addr_size);

  /*---- receive file name from the incoming connection ----
  socket:The socket descriptor.
buf:The pointer to the buffer that receives the data.
len:The length in bytes of the buffer pointed to by the buf parameter. If the MSG_CONNTERM flag is set, the length of the buffer must be zero.
flags:The flags parameter is set by specifying one or more of the following flags. If more than one flag is specified, the logical OR operator ( | ) must be used to separate them. The MSG_CONNTERM flag is mutually exclusive with other flags.
  */
  recv(newSocket,fname,255,0);

/*
File descriptors are an index into a file descriptor table stored by the kernel. The kernel creates 
a file descriptor in response to an open call and associates the file descriptor with some abstraction of an
underlying file-like object, be that an actual hardware device, or a file system
*/
  fd=open(fname,O_RDONLY);
  if(fd==-1){
    strcpy(buffer,"No file found!");
    n = strlen(buffer);    
  }
  else{
    n=read(fd,buffer,bufsize);
  }
  

  send(newSocket,buffer,n,0);
  
  close(newSocket);
  return close(serverSocket);
	
//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
}
