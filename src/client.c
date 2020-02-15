#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>

#define SERVPORT 3333
 
int 
main(int argc,char *argv[]) 
{
    int                sockfd,sendbytes;
    struct sockaddr_in serv_addr;

    /*
    * Create an AF_INET stream socket to receive and send data 
    */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        exit(1);
    }

    /*
    * Set the server address     
    */
    serv_addr.sin_family 	= AF_INET; 
    serv_addr.sin_port 		= htons(SERVPORT);
    serv_addr.sin_addr.s_addr   = inet_addr("192.168.1.106"); 
    bzero(&(serv_addr.sin_zero),8);

    if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))) < 0) {
        perror("connect failed!");
        exit(1);
    }

    printf("connect successful! \n");

    /*
    * Send and receive data 
    */
    while(1){
        if((sendbytes = send(sockfd,"hello",5,0)) < 0) {
            perror("send");
            exit(1);
        }else{
            printf("send successful! %d \n",sendbytes);
        }

        usleep(1000000);

        if((sendbytes = send(sockfd,"hahaha",6,0)) < 0) {
            perror("send");
            exit(1);
        }else{
            printf("send successful! %d \n",sendbytes);
        }

        usleep(1000000);

        char buf[20];/* receive buffer */

	    int recvbytes = recv(sockfd,buf,20,0);

        if(recvbytes < 0) {
            printf("recv error: %d\n",recvbytes);
            exit(1);
        }else if(recvbytes == 0){
            printf("The connection has been closed by the server.");
            exit(1);
        }else{
            printf("received data : %s,,%d\n",buf,recvbytes);
        }

        static int i = 0;
        if(i++ > 5){
            printf(" break .\n");
            i = 0;
            break;
        }
    }

    sleep(10);

    close(sockfd);

    return 0;
}





