#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<bits/socket.h>
#include<netinet/in.h>
#include<string.h>
#include"fd_pass.h"

#define BACKLOG 6
int main()
{
	int sfd=socket(AF_UNIX,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket()");
	}

	struct sockaddr_un s_addr;
	s_addr.sun_family=AF_UNIX;
	strcpy(s_addr.sun_path,UNIX_DOMIN_PATH);
	if(bind(sfd,(struct sockaddr*)&s_addr,sizeof(s_addr))==-1){
		perror("bind");
		exit(1);
	}

	if(listen(sfd,BACKLOG)==-1){
		perror("listen()");
		exit(1);
	}

	int tmpfd=dup(STDIN_FILENO);

	//int fd=open("");
	int cfd=accept(sfd,NULL,NULL);
	while(1)
	{	
		printf("unix fd : %d\n",cfd);
		char msg[]="hello world";
		int rfd=recv_fd(cfd);
		printf("received fd:%d\n",rfd);
//		send(rfd,msg,strlen(msg),0);
		if(send(rfd,msg,strlen(msg),0)==-1)
		{
			perror("send()");
			exit(1);
		}
	}

	return 0;
	
}
