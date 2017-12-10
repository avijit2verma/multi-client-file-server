#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>

int main(int argc,char **argv)
{
	if(argc < 4)
	{
		printf("usage %s <IP> <port> <no_of_clients>\n",argv[0]); exit(1);
	}
	int count = atoi(argv[3]);
	int fn = 1;
	while(count--){
		int pid = fork();
		if(pid == 0){
			int sockfd;
			struct sockaddr_in serv_addr;
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
			serv_addr.sin_port = htons(atoi(argv[2]));
	

			sockfd = socket(AF_INET,SOCK_STREAM,0);	
			if(sockfd == -1)
			{ 
				printf("Error creating socket");
				return 1; 
			}
			if( connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
			{
				printf("\nError connecting to server"); 
				return 1; 
			}
			char filename[100];
			sprintf(filename,"data/file%d",fn);
			send(sockfd,filename,sizeof(filename),0);
			char str[256];
			while(1){
				read(sockfd,str,sizeof(str));
				if(!strcmp(str,"END")) break;
			}
			exit(1);
		}
		
	fn++;

	}
	










return 0;
}












