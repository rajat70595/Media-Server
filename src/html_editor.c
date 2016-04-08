#include<stdio.h>
#include<string.h>
#include<errno.h>
#include"project.h"
void html_editor(char*file,char*ipadd)
{
FILE *f1=NULL,*f2=NULL;
char fbuff[BUFSIZ];
char fbuff2[BUFSIZ];
char *ftemp;
char fbuff3[100]="<a href=";
fbuff3[strlen(fbuff3)]='"';		//fbuff3 has <a href="
f1=fopen(file,"r+");			//index.html will open
printf("fopen:%s\n",strerror(errno));
f2=fopen("temp.html","w+");
printf("fopen:%s\n",strerror(errno));
while(fgets(fbuff,sizeof(fbuff),f1))	//
{

strcpy(fbuff2,ipadd);
//printf("file content:\n%s\n",fbuff);
if(ftemp=strstr(fbuff,":9080"))		//href="192.168.1.14:9080 
{

printf("ftemp:%s\n",ftemp);
strcat(fbuff2,ftemp);			//
printf("fbuff2:%s\n",fbuff2);
sprintf(fbuff,"%shttp://%s",fbuff3,fbuff2);		//href="http://192.168.1.14:9080 
printf("fbuff:%s\n",fbuff);
}
fputs(fbuff,f2);					
}
rename("temp.html","start.html");
fclose(f2);
fclose(f1);
}


//href="http://192.168.1.14:9080/video1.html" 
