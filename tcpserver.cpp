#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>		// for AF_INET, SOCK_STREAM 
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

void error(std::string error_type) {
	std::cout << error_type << '\n';
}

/*
** 	Use perror() instead of error()
	example:
	
	int n;
	cin >> n;
	if (n < 0 ) {
		perrror("Negative input is not allowed");
	}
	else {
		std::cout << sqrt(n);
	}

*/

int main(int argc, char *argv[1]) {
	/*	1. Create a socket with the socket() system call.
	**	2. Connect the socket to the address of the server using the connect() system call.
	** 	3. Send and receive data. There are a number of ways to do this, but the simplest is to use the read() and write() system call.
	*/

	//	The steps involved in establishing a socket on the server side are as follows:
	/*	1. Create a socket with the socket() system call.
	**	2. Bind the socket to an address using the bind() system call. For a server socket on the Internet, an address consist of a port number on the host machine.
	**	3. Listen for connections with the listen() system call
	** 	4. Accept a connection with the accept() system call. This call typically blocks until a client connects with the server.
	**	5. Send and receive data.
	*/
	/*---------------------------------------*/
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	if (argc < 2) {
		fprintf(stderr, "Error, no port provided\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror ("ERROR opening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
	
	
	std::cout << "Hello World!\n";
	return 0;
}

//source code : https://www.linuxhowtos.org/C_C++/socket.htm
// for error() function
/* https://linux.die.net/man/3/error */

