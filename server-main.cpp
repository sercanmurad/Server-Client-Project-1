/*These include directives add the necessary libraries for working with sockets,
 strings, and other standard operations in your code.*/
#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*Whit this constants we define port number,buffer size and mesage to send to new client*/
#define SERVER_PORT 1234
#define BUF_SIZE 64
#define MSG_TO_SEND "HELLO\n"


int main()
{
	/*Create variables for sockets,response lenghth(ans_len),counter (total),a buffer size and adress structure */
	int sock1, sock2;
	int ans_len, total = 0;
	char buffer[BUF_SIZE];
	struct sockaddr_in sin, client;
	/*A socket (sock1) is created, and the server address (sin) is configured. Then, the socket is bound to the address.*/
	sock1 = socket(AF_INET, SOCK_STREAM, 0);
	memset((char*)&sin, '\0', sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);
	bind(sock1, (struct sockaddr*)&sin, sizeof(sin));
	/*output for the clients*/
	std::cout << "Server is running ...\n";
	/*listen the client*/
	listen(sock1, 3);
	while (1) {
		/*Accept Connection and Send Message*/
		ans_len = sizeof(client);
		sock2 = accept(sock1, (struct sockaddr*)&client, (socklen_t*)&ans_len);
		write(sock2, MSG_TO_SEND, sizeof(MSG_TO_SEND));
		/*Increment Counter and Read from the Client*/
		total += 1;
		ans_len = read(sock2, buffer, BUF_SIZE);
		/*Print the Message and Client Number*/
		write(1, buffer, ans_len);
		std::cout << "Client no " << total << "\n";
		/*Shutdown the Connection and Close the Socket*/
		shutdown(sock2, 0);
		close(sock2);
	};
	
	return 0;
}


