#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"project.h"
void process_request(void *fd)
{
  char buff[BUFSIZ+1],*temp,buff2[BUFSIZ];
  int cnt,i,file_fd,client_fd;
  client_fd=*(int*)fd;
  cnt=recv(client_fd,buff,BUFSIZ,0);
  printf("request recived:\n%s\n",buff);
  buff[cnt]='\0';
  
	  for(i=0;i<strlen(buff);i++)
	  {
	  	if(buff[i]=='\r'||buff[i]=='\n')
	        buff[i]='*';
	  }
	 
	  strcpy(buff2,buff);
	  temp=strstr(buff2,"/");
	  i=0;
          memset(&buff,'\0',sizeof(buff));
          do
	  {
               temp++;
	       buff[i]=*temp;
	       i++;
	  }while(isspace(*temp)==0);
	  
	  buff[i]='\0';
	  printf("buff:%s\n",buff);
	  printf("strcmp:%d\n",strcmp("/",buff));
	  if(strcmp(" ",buff)>=0)
	  {
	  //HTTP header for index file
	  	strcpy(buff,"HTTP/1.0 200 OK\r\nDate: Tue, 14 Sep 2013 02:14:58 GMT\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: text/html\r\nServer: Miracle\r\n\r\n");
	  	send(client_fd,buff,strlen(buff),0);

	  	file_fd=open("index.html",O_RDONLY);
	  	printf("open:%s\n",strerror(errno));
	  	while(read(file_fd,buff,BUFSIZ)>0)
	  	{
          		//printf("amount of data read:%d\n",cnt);
          		cnt=send(client_fd,buff,strlen(buff),0);
          		printf("amount of data sent:%d\n",cnt);
          	}
   	  }
          else
	  {
       		 printf("buff in if:%s\n",buff);
     		 memset(&temp,'\0',sizeof(temp));
      		 for(i=0;buff[i]!='\0';i++)
          	 {
           	 	if(isspace(buff[i])>0)
             		{
               			buff[i]='\0';
             		}
          	 }
     		 temp=strstr(buff,".");
     		 file_fd=open(&buff,O_RDONLY,0777);
		 printf("open:%s\n",strerror(errno));
   		 printf("temp:%s\n",temp);
   		 strcpy(buff,temp);
   
   		 //header for other diffrent files
   		 if(!strcmp(buff,".ogg"))
		 {
      		 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/ogg\r\nServer: Miracle\r\n\r\n");
		 }

 		 if(!strcmp(buff,".flv"))
		 {
	 	 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/flv\r\nServer: Miracle\r\n\r\n");
		 }
		
		 if(!strcmp(buff,".3gp"))
		 {
	 	 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/3gp\r\nServer: Miracle\r\n\r\n");
		 }

		 if(!strcmp(buff,".avi"))
		 {
	 	 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/avi\r\nServer: Miracle\r\n\r\n");
		 }

	         if(!strcmp(buff,".ico"))
  		 {
		 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: image/ico\r\nServer: Miracle\r\n\r\n");
		 }
 
		 if(!strcmp(buff,".png"))
		 {
	 	 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: image/png\r\nServer: Miracle\r\n\r\n");
		 }
		 printf("%s\n",temp);
  
		 if(!strcmp(buff,".html"))
  		 {
  		 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: text/html\r\nServer: Miracle\r\n\r\n");
  		 }
 		 printf("%s\n",temp);

		 if(!strcmp(buff,".mkv"))
  		 {
  		 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/mkv\r\nServer: Miracle\r\n\r\n");
  		 }
		
		 if(!strcmp(buff,".webm"))
  		 {
  		 strcpy(buff2,"HTTP/1.1 200 OK\r\nConnection: keep-alive\r\nCache-control: private\r\nContent-type: video/webm\r\nServer: Miracle\r\n\r\n");
  		 }
		 printf("%s\n",temp);


           	 send(client_fd,buff2,strlen(buff2),0);
           	 printf("sent data:\n%s\n",buff2);

   	         while(read(file_fd,buff2,1025)>0)
 		 {
         	 	cnt=send(client_fd,buff2,1025,0);
         		// printf("send:%s amount of data:%d\n",strerror(errno),cnt);
         	 }
      	}
   
}

