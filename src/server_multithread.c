#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h> 
#include <fcntl.h>
#include <string.h>

#define SERVPORT 3333
#define BACKLOG 10
#define MAXDATASIZE 15


/*
* Thread callback function
* Echo data to clinets
*/
void *data_process(void *arg)
{
	int client_fd = *(int *)arg;
   	char buf[MAXDATASIZE];

    while(1){
	memset(buf,0,sizeof(buf));
        int recvbytes = recv(client_fd,buf,MAXDATASIZE,0);
        if(recvbytes < 0) {
            printf("recv error: %d\n",recvbytes);
            exit(1);
        }else if(recvbytes == 0){
            printf("The connection has been closed by the client");
            break;
        }else{
            printf("received data : %s,,%d\n",buf,recvbytes);
            int send_ret = send(client_fd,buf,recvbytes,0);
            if (send_ret < 0){
                perror("send");
                exit(1);
            }                      
        }	
    }
}


int
main(int argc,char *argv[]) {
    struct sockaddr_in server_sockaddr;
    int                sin_size,recvbytes;
    int                sockfd,client_fd;
    char               buf[MAXDATASIZE];

    /*
    * Create an AF_INET stream socket to receive and send data 
    */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("Socket");
        exit(1);
    }

    server_sockaddr.sin_family 		= AF_INET;
    server_sockaddr.sin_port 		= htons(SERVPORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero),8);

    if((bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))) < 0) {
        perror("bind");
        exit(-1);
    }

    if(listen(sockfd,BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    printf("listening ... \n");

    while(1)
    {
        if((client_fd = accept(sockfd,NULL,&sin_size)) == -1) {
            perror("accept");
            exit(1);
        }

        /*
        * Create child thread to process new connection.
        */
        pthread_t child;
        pthread_create(&child, NULL, data_process, &client_fd);
    }

    return 0;
}


