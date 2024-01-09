#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*These are constants defining the server host, server port, client port, and a message to be sent by the client.*/
#define SERVER_HOST "localhost"
#define SERVER_PORT 1234
#define CLIENT_PORT 1235
#define MSG "I'm client\n"

int main()
{
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	/*This creates a socket using the socket function with the AF_INET address family and SOCK_STREAM socket type.*/
	
	struct sockaddr_in client, server;
	memset((char *)&client, '\0', sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = INADDR_ANY;
	client.sin_port = htons(CLIENT_PORT);
	bind(sock, reinterpret_cast<struct sockaddr *>(&client), sizeof(client));
	/*These lines set up the client's address configuration, including the port to bind to. 
	The bind function associates a socket with a specific address and port.*/
	
	memset((char *)&server, '\0', sizeof(server));
	h = gethostbyname(SERVER_HOST);
	server.sin_family = AF_INET;
	memcpy((char *)&server.sin_addr, h->h_addr, h->h_length);
	server.sin_port = htons(SERVER_PORT);
	/*This section configures the server's address information, 
	using the gethostbyname function to retrieve the server's IP address.*/
	
	connect(sock, reinterpret_cast<struct sockaddr *>(&server), sizeof(server));
	/*The connect function establishes a connection to the server.*/

    ans_len = recv(sock, buffer, BUF_SIZE, 0);
	write(1, buffer, ans_len);
	send(sock, MSG, sizeof(MSG), 0);
	/*These lines receive data from the server, display it to the console using write, 
	and then send a message (MSG) to the server.*/
	
	close(sock);

	return 0;
}

