

 /***********SERVER CODE***********/

#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>		
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<ifaddrs.h>
#include<fcntl.h>
#include<signal.h>
#include"project.h"
#define PORT 9080
#define QUEUE_LEN 7
int main()
{
  int server_fd,client_fd;
  pid_t pid;


  int *arg;


char ipadd[20];
  struct sockaddr_in server,client;
  struct in_addr client_addr;
  socklen_t length=0;
   signal(SIGCLD, SIG_IGN);
/************************ configuring IP address*********************/

strcpy(ipadd,config_ip());

// setting all the html pages to the given IP
html_editor("/home/rajat/Desktop/Project/http Audio-Video Streaming Server/obj/video1.html",ipadd);		
// steting up the server using LINUX APIs

  server_fd=socket(AF_INET,SOCK_STREAM,0);
  printf("socket:%s\n",strerror(errno));
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr.s_addr=inet_addr(ipadd);
  bind(server_fd,(struct sockaddr*)&server,sizeof(server));
  printf("bind:%s\n",strerror(errno));
  listen(server_fd,QUEUE_LEN);
  printf("listen:%s\n",strerror(errno));
  while(1)
  {
    printf("serveris waiting:\n");
    
    client_fd=accept(server_fd,(struct sockaddr*)&client,&length);
    client_addr=client.sin_addr;				
    printf("request recived from:%s\n",inet_ntoa(client_addr));
    arg=&client_fd;
    

    
   
    pid=fork();							
    printf("fork:%s\n",strerror(errno));
    if(pid==0)
    { 
      process_request(arg);
    
      exit(23);
    
    }
  else
   { 
     close(client_fd);
     printf("close:%s\n",strerror(errno));
   }
    
  }
return 0;
}


