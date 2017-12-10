#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>


void child_process(int n,int newsockfd){
	char str[256];
	int no_of_send = 0;
	char filename[100];
	long long int bytes = 0;
	struct timeval tv1,tv2;
	read(newsockfd,filename,sizeof(filename));
	FILE *fp = fopen(filename,"r");
	if(fp == NULL) {printf("%s filename does not exist\n",filename); exit(1);}
	gettimeofday(&tv2,NULL);
	while(!feof(fp)){
		fread(str,256,1,fp);
		no_of_send+=send(newsockfd,str,sizeof(str),0);
		bytes+=256;
	}
	send(newsockfd,"END",sizeof("END"),0);
	gettimeofday(&tv1,NULL);
	fclose(fp);
	int sec = tv1.tv_sec-tv2.tv_sec;
	int usec = tv1.tv_usec-tv2.tv_usec;
	fp = fopen("logfile.txt","a");
	fprintf(fp,"Client-id: %d, bytes read = %lld, filename = %s, no of times send used = %d, time taken = %d sec, %d usec\n",n,bytes,filename,no_of_send,sec,usec);

	fclose(fp);  
}

int main(int argc, char *argv[]){
int sockfd, newsockfd, portno, clilen;
if(argc < 2){  printf("\nenter: %s [portno]",argv[0]); return 1;}
int n=1;
struct sockaddr_in serv_addr, cli_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0) { printf("Error creating socket...."); exit(1); }

bzero(&serv_addr,sizeof(struct sockaddr_in));
portno = atoi(argv[1]);
char str[256];
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
 { printf("\nBinding Error...."); exit(2);}


listen(sockfd,5);
while(1){
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0) printf("Connection failed.......");
	int pid = fork();
	if(pid == 0){ child_process(n,newsockfd); exit(1);}
	n++;
}



return 0;
}
