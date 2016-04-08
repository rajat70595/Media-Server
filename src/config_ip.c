#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<ifaddrs.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include"project.h"
char *config_ip(void)
{
struct ifaddrs *addr;
struct sockaddr_in addr2;
char ipadd[20];
char *ipaddr;
getifaddrs(&addr);
printf("getifaddrs:%s\n",strerror(errno));
do
{
if(addr->ifa_addr->sa_family==AF_INET)
{
addr2=*(struct sockaddr_in*)(addr->ifa_addr);
if(strcmp("192.168.11.8",inet_ntoa((struct in_addr)addr2.sin_addr)))				
{
printf("ip addr:%s\n",inet_ntoa((struct in_addr)addr2.sin_addr));
strcpy(ipadd,inet_ntoa((struct in_addr)addr2.sin_addr));
}
}
addr=addr->ifa_next;
}
while(addr!=NULL);
freeifaddrs(addr);										
printf("freeifaddrs:%s\n",strerror(errno));
ipaddr=ipadd;
return ipaddr;
}
