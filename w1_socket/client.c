// Client side Socket with C
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd;
	char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	
	// set IPv4 Internet Protocol + detect error
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;  // (short) 2 bytes
	serv_addr.sin_port = htons(PORT);  // (unsigned short) 2 bytes

	// Convert IPv4 address from text to binary
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	// int connect(int sockfd, const struct sockaddr *address, socklen_t address_len);
	// return 0 if success, otherwise, -1 for error
	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);

	// closing the connected socket
	close(client_fd);
	return 0;
}

