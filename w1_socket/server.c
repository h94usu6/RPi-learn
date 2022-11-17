// Server side C
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[]) {
	int server_fd, new_socket, valread;
	int opt = 1;
	char* hello = "Hello from server";
	char buffer[1024] = { 0 };

	// Creating socket file descriptor
	// int socket(int domain, int type, int protocol);
	// return a file descriptor for the new socket on success, or -1 if error
	// domain: Internet Protocols e.g. AF_INET(IPv4), AF_INET6(IPv6), AF_UNI(local)
	// type: e.g. SOCK_STREAM(<-> && reliable, TCP), SOCK_DGRAM(non-wire datagrams, UDP), SOCK_SEQPACKET(<-> && reliable packet), SOCK_RAW(Network Layer, original IP)	
	// protocal: Transmission Control Protocol, 0: default
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	// int setsockopt( int socket, int level, int option_name, const void *option_value, size_t option_len);
	// option_name(depend on level),option_value: e.g. SO_REUSEADDR,1(open reuse address) | SO_REUSEPORT,1(allow binding the same ip)
	// option_len: len of opt
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// address: socket's information
	/*struct sockaddr_in {  
		short            sin_family;   // e.g. AF_INET, AF_INET6  
		unsigned short   sin_port;     // Host to Network Short e.g. htons(3490)
		struct in_addr   sin_addr;     // see struct in_addr, below  
		char             sin_zero[8];  // zero this if you want to
	};
	struct in_addr {  
		unsigned long s_addr;          // load with inet_pton()  
	};  
	*/ 
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	address.sin_family = AF_INET;  //IPv4
	address.sin_addr.s_addr = INADDR_ANY;  //allow connecting any internet connection
	address.sin_port = htons(PORT);  //8080 to 36895

	// int bind(int sockfd, const struct sockaddr *address, socklen_t address_len);
	// return 0 for successful; otherwise, -1 if error
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	// int listen(int sockfd, int backlog);
	// return 0 if success, otherwise, -1 for error
	// backlog: size of accept queue
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	// int accept(int sockfd, struct sockaddr *restrict address, socklen_t *restrict address_len);
	// return the non-negative file descriptor of the accepted socket if success, Otherwise, -1 if error
	// address: record socket from client's socket
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}

