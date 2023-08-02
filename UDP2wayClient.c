#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 12345

int main(){
	int sock,n;
	struct sockaddr_in saddr;
	char buffer[1024];
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("Socket creation failed!");
		exit(0);
	}
	printf("Socket creation successful...\n");
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	
	inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr);
	
	socklen_t len;
	len = sizeof(saddr);
	
	for(;;){
		printf("To Server:");
		scanf("%s",buffer);
		sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&saddr,sizeof(saddr));
		if(strcmp(buffer,"exit")==0)
			break;
		
		n = recvfrom(sock,buffer,1024,0,(struct sockaddr*)&saddr,&len);
		buffer[n]='\0';
		if(strcmp(buffer,"exit")==0){
			printf("Server closed\n");
			break;
		}
		printf("From server: %s\n",buffer);
	}
	
	close(sock);
	
	return 0;
}
	
