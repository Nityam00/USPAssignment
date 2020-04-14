#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>
#include<stdlib.h>

short SocketCreate(void)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}
int BindCreatedSocket(int hSocket)
{
    int iRetval=-1;
    int ClientPort = 90185;
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); /* Local port */
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
    return iRetval;
}

void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig); 
    if(sig==8)
    {
    	printf("Caught FPE\n");
    	exit(0);
    }
} 

void socket1()
{
	int socket_desc, sock, clientLen, read_size;
    struct sockaddr_in server, client;
    char client_message[200]= {0};
    char message[100] = {0};
    //Create socket
    socket_desc = SocketCreate();
	    if (socket_desc == -1)
    {
        printf("Could not create socket");
        return ;
    }
    printf("Socket created\n");
    //Bind
    if( BindCreatedSocket(socket_desc) < 0)
    {
        //print the error message
        perror("bind failed.");
        return ;
    }
    printf("bind done\n");
    //Listen
    listen(socket_desc, 3);
    //Accept and incoming connection
    signal(SIGINT, handle_sigint);
    while(1)
    {
        printf("Waiting for incoming connections...\n");
        clientLen = sizeof(struct sockaddr_in);
        //accept connection from an incoming client
        sock = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
        if (sock < 0)
        {
            perror("accept failed");
            return ;
        }
        printf("Connection accepted\n");
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        //Receive a reply from the client
        if( recv(sock, client_message, 200, 0) < 0)
        {
            printf("recv failed");
            break;
        }
        int a=0,flag1=0,b=0;
        printf("Client reply : %s\n",client_message);
        for(int i=0;i<strlen(client_message);i++)
        {
        	if(client_message[i]>47 && client_message[i]<58)
        	{
        		if(flag1==0)
        		a=a*10+client_message[i]-'0';
        		else
        		b=b*10+client_message[i]-'0';
        	}
        	else
        	flag1=1;
        }
        
        if(b==0)
        {
            strcpy(message,"Cannot divide");
        }
        else
        {
        	     strcpy(message,"Can divide");
        }
        // Send some data
        if( send(sock, message, strlen(message), 0) < 0)
        {
            printf("Send failed");
            return ;
        }
        printf("%d\n",a/b);
        close(sock);
        sleep(1);
    }
	
}
int main(int argc, char *argv[])
{
     
    pid_t child_pid = fork();
    signal(SIGCHLD, handle_sigint);
     
  	// Parent process  
  	int flag=0;
    if (child_pid > 0) 
       {
      		signal(SIGFPE,handle_sigint);
       		flag=1;
       		socket1();
       	}
    // Child Process
       else
       {	
  			exit(0);
       }
    return 0;
}
 
