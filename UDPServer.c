#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 12345

int main(){
	int sock;
	struct sockaddr_in saddr,caddr;
	char buffer[1024];
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("Socket creation failed!");
		exit(0);
	}
	printf("Socket created successfully...\n");
	
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(PORT);
	
	if(bind(sock,(struct sockaddr*)&saddr,sizeof(saddr))<0){
		printf("Socket binding failed!");
		exit(0);
	}
	
	socklen_t len;
	len = sizeof(caddr);
	
	int n;
	for(;;){
		n = recvfrom(sock,buffer,1024,0,(struct sockaddr*)&caddr,&len);
		buffer[n] = '\0';
		
		printf("From client: %s\n",buffer);
		if(strcmp(buffer,"exit")==0){
			printf("Client closed\n");
			break;
		}
		/*printf("To client:");
		scanf("%s",buffer);
		sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&caddr,sizeof(caddr));
		if(strcmp(buffer,"exit")==0)
			break;*/
	}
	
	close(sock);
		
	return 0;
}

	
