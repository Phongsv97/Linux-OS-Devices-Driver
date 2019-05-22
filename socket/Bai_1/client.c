#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LEN 256

int main(int argc, char *argv[])
{
    int portno;
    int numb_write, numb_read;
    int socket_fd;
    struct sockaddr_in serv_addr;

    /*buffer read-write*/
    char recvbuff[MAX_LEN];
    char sendbuff[MAX_LEN];

    /*initialize value*/
	memset(sendbuff, 0, MAX_LEN);
	memset(recvbuff, '0', MAX_LEN);
	memset(&serv_addr, '0',sizeof(serv_addr));

    /*read port number in cmdline*/
    if(argc < 3){
        perror("Please use cmdline : ./client serv_address portnumbere\n");
        exit(0);
    }
    portno = atoi(argv[2]);

    /*initialize client_addr*/
    serv_addr.sin_family = AF_INET;   /*default*/
    serv_addr.sin_port   = htons(portno);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0){
        perror("ERROR inet_pton error occured\n");
        exit(1);
    }

    /*creat socket*/
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd < 0)
        perror("ERROR socket() error occured\n");

    /*connect server*/
    if(connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("ERROR connect fail\n");
        exit(1);
    }

    printf("Plese enter the message : ");
    fgets(sendbuff, MAX_LEN, stdin);

    /*send message to server - write socket*/
    numb_write = write(socket_fd,sendbuff,MAX_LEN);
    if (numb_write < 0)     
         perror("ERROR writing to socket");
    
    /*recv message from server*/
    numb_read = read(socket_fd,recvbuff,MAX_LEN);
    if (numb_read < 0) 
         perror("ERROR reading from socket");
    printf("%s\n",recvbuff);
   
    close(socket_fd); /*close*/ 
    return 0;
}
