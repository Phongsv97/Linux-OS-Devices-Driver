#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LEN 	256

int main(int argc, char *argv[])
{
	int newsockfd, server_fd;
    int portno;
    int numb_read, numb_write;
	int len;

	struct sockaddr_in serv_addr, client_addr;
	
	/*buffer read - write*/
	char sendbuff[MAX_LEN];
	char recvbuff[MAX_LEN];

	/*server read portnumber from commandline*/
	if(argc < 2){
		perror("Error, no port provided\n");
		exit(0);
	}
	portno = atoi(argv[1]);

	/*initialize value*/
	memset(sendbuff, '0', MAX_LEN);
	memset(recvbuff, '0', MAX_LEN);
	memset(&serv_addr, '0',sizeof(serv_addr));
	memset(&client_addr, '0', sizeof(client_addr));

	/*setup server addr*/
	serv_addr.sin_family      = AF_INET;		/* default */
	serv_addr.sin_addr.s_addr = INADDR_ANY;		/*ipserver : 0.0.0.0*/
	serv_addr.sin_port	  = htons(portno);

	/*creat socket*/
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0)
		perror("ERROR opening socket\n");
	
	/*bind socket*/
	if(bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR on binding\n");

	/*listening - max = 5 backlog in queue*/
	if(listen(server_fd,5) < 0){
		perror("listen\n");
		exit(EXIT_FAILURE);
	}

	/*get info client addr conecting*/
	len = sizeof(client_addr);

	while(1){
		printf("Server is listening at port : %d \n",portno);
		newsockfd  = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len); 
		if(newsockfd < 0){
			perror("ERROR acept\n");
			exit(EXIT_FAILURE);
		}
		
		/*convert the network add structure src in the add family into a character string0*/
		char temp[MAX_LEN];
		inet_ntop(client_addr.sin_family, (struct sockaddr*)&client_addr, temp, sizeof(temp));
		
		printf("server : got connection from %s\n", temp);
		
		/*read data from socket*/
		numb_read = read(newsockfd, recvbuff, MAX_LEN); /*block util client send data*/
		if(numb_read < 0)
			perror("ERROR reading from socket\n");
		printf("Message from client : %s\n", recvbuff);

		/*write data via socket*/
		strcpy(sendbuff, "Server has got message\n");
		numb_write = write(newsockfd, sendbuff, MAX_LEN);
		if(numb_write < 0)
			perror("ERROR writing to socket\n");
		 close(newsockfd);
		 sleep(1);

	}
	close(newsockfd);
	return 0;

}











































