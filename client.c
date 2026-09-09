#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    int n;
    char rdbuf[128];
    struct sockaddr_in srv;
    int sockfd;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    srv.sin_family=AF_INET;
    srv.sin_port=htons(atoi(argv[1]));
    srv.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(sockfd,(struct sockaddr *)&srv,sizeof(srv));

    while(1)
    {
        printf("Enter number : ");
        scanf("%d",&n);

        write(sockfd,&n,sizeof(n));

        read(sockfd,rdbuf,sizeof(rdbuf));

        printf("%s\n",rdbuf);
    }
}
//cc client.c -o client
//./client (1024-49151)
