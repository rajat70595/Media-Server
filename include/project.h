#ifndef PROJECT_H
#define PROJECT_H



/******** configuring IP for the server************/
//it returns the useable ip address
char*config_ip(void);



/************html file editor******************/
//editing files inorder to make links usable
//it accepts the start file(index file of the server and the ip addrs
void html_editor(char*file,char*ipadd);



/************ process_request***********************/
//it handels the request from the browser and is responsible for sending the data
void process_request(void *fd);




#endif
