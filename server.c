#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int factorial(int n)
{
    int fact=1;
    for(int i=1;i<=n;i++)
        fact=fact*i;
    return fact;
}

int main(int argc,char *argv[])
{
    char rdbuf[128],wrbuf[128];
    struct sockaddr_in srv,cln;
    int sockfd,newsfd;

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    srv.sin_family=AF_INET;
    srv.sin_port=htons(atoi(argv[1]));
    srv.sin_addr.s_addr=inet_addr("0.0.0.0");

    bind(sockfd,(struct sockaddr*)&srv,sizeof(srv));

    listen(sockfd,1);

    int len=sizeof(cln);
    newsfd=accept(sockfd,(struct sockaddr*)&cln,&len);

    while(1)
    {
        int n,temp,r,sum=0;
        bzero(rdbuf,sizeof(rdbuf));
        if(read(newsfd,rdbuf,sizeof(rdbuf))<=0)
            break;
        n=atoi(rdbuf);
        temp=n;
        while(temp)
        {
            r=temp%10;
            sum=sum+factorial(r);
            temp=temp/10;
        }

        if(sum==n)
        {
            sprintf(wrbuf,"%d is Strong Number",n);
        }
        else
        {
            sprintf(wrbuf,"%d is Not Strong Number",n);
        }

        write(newsfd,wrbuf,strlen(wrbuf)+1);
    }
}
//cc server.c -o server
//./server (1024-49151)
//run server 1st





