
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include<stdbool.h> 
#include <errno.h>
#include "calcLib.h"
#include "calcLib.c"
#define PORT 8080 
#define SA struct sockaddr 
#define CLADDR_LEN 100

char clientAddr[CLADDR_LEN];
char task[200],buffer[10]; 
char value1[20],value2[20];
int write_size, read_size, intResults;
float floatResults;
void writeError()
{
    fprintf(stderr,"Error writing to socket\n");
		exit(1);
}
void readError()
{
    fprintf(stderr,"Error reading from socket\n");
		exit(1);
}
 
void func(int sockfd) 

{    
    struct timeval timeout;      
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof timeout)<0){
      error("setsockopt failed\n");
    }
      //printf("Timeout\n");        
        //error("setsockopt failed\n"); 
    
     char text[20] = "TEXT TCP 1.0\n\n";
     write_size = write(sockfd,text, strlen(text));
     if(write_size < 0){
     
       fprintf(stderr,"Error writing to socket\n");
		exit(1);		
	
       }
      
 
        
     bzero(buffer, sizeof(buffer)); 
       //read_size = read(sockfd, buffer, sizeof(buffer)-1);
       read_size = recv(sockfd, buffer, sizeof(buffer)-1, 0);
       if(read_size < 0){
         if(errno == EAGAIN ||EWOULDBLOCK){
            perror("Timeout Reached");
           // printf("I'm here now\n");
            write_size = send(sockfd,"ERROR TO\n", strlen("ERROR TO\n"),0); 
            if(write_size < 0){
     
           fprintf(stderr,"Error writing to socket\n");
           close(sockfd);
		       exit(0);		
	
       } 
        close(sockfd);
        exit(0);
         }
         else
         readError();
         close(sockfd);
         exit(0);
      
       }
       buffer[read_size] = '\0'; 
      printf("server read %d bytes from client\n" ,read_size);
      printf("Client %s responded with: %s\n", clientAddr, buffer);
       if (strncmp(buffer, "OK", 2) !=0 ){

         write_size = send(sockfd,"ERROR\n", strlen("ERROR\n"),0); 
            if(write_size < 0){
     
           fprintf(stderr,"Error writing to socket\n");
           close(sockfd);
		       exit(0);	
       } 
       close(sockfd);
        exit(0);
         }
      bzero(task, sizeof(task));  
	
  initCalcLib();
  char *ptr;
  ptr=randomType(); // Get a random arithemtic operator. 

  double f1,f2,fresult;
  int i1,i2,iresult;

  
  if(ptr[0]=='f'){
    //printf("Float\t");
    f1=randomFloat();
    f2=randomFloat();
    
    // converts float to a string
    sprintf(value1, "%8.8g",f1);
    sprintf(value2, "%8.8g",f2);

   
    if(strcmp(ptr,"fadd")==0){
      fresult=f1+f2;
      //build up string to send to client by string concatenation
      strcpy(task, "fadd");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2);
      strcat(task,"\n"); 
    } else if (strcmp(ptr, "fsub")==0){
      fresult=f1-f2;
      //build up string to send to client by string concatenation
      strcpy(task, "fsub");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2); 
      strcat(task,"\n"); 
    } else if (strcmp(ptr, "fmul")==0){
      fresult=f1*f2;
      //build up string to send to client by string concatenation
      strcpy(task, "fmul");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2); 
      strcat(task,"\n");
    } else if (strcmp(ptr, "fdiv")==0){
      fresult=f1/f2;
       //build up string to send to client by string concatenation
      strcpy(task, "fdiv");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2);
      strcat(task,"\n");      
    }
    
     
           
      write_size = write(sockfd, task, strlen(task));
       if (write_size < 0){
       writeError();
       }
      //  if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
      //           sizeof timeout) < 0)
      //   error("setsockopt failed\n");
       printf("Float Task given to client: %s\n",task);
       bzero(task, sizeof(task)); 
      //read_size = read(sockfd, task, sizeof(task));
       read_size = recv(sockfd, task, sizeof(task)-1, 0);
       if(read_size < 0){
         if(errno == EAGAIN ||EWOULDBLOCK){
            perror("Timeout Reached");
           // printf("I'm here now\n");
            write_size = send(sockfd,"ERROR TO\n", strlen("ERROR TO\n"),0); 
            if(write_size < 0){
     
           fprintf(stderr,"Error writing to socket\n");
           close(sockfd);
		       exit(0);		
	
       } 
        close(sockfd);
        exit(0);
         }
         else
         readError();
         close(sockfd);
         exit(0);
      
       }
        task[read_size] = '\0';
      //task[read_size] = 0; 
      printf("server read %d bytes from client\n" ,read_size);
      printf("Answer from client: %s\n",task);
      //convert the string received to a float
      floatResults = atof(task); 
      if (abs(fresult- floatResults) < 0.0001){
       printf("Expected: %8.8g, got: %8.8g\n",fresult,floatResults);
     
      printf("Response was OK\n");  
      //clear task buffer            
      bzero(task, sizeof(task));  
      
      write_size = write(sockfd, "OK\n", 3); 
      if (write_size < 0){
       writeError();
       }
      
      }
      else{
      write_size = write(sockfd, "ERROR\n",6); 
     if (write_size < 0){
       writeError();
       }
       printf("Response was bad\n"); 
      
      }
    
    
  } else{
    //printf("Int\t");
    i1=randomInt();
    i2=randomInt();
    sprintf(value1, "%d",i1);
    sprintf(value2, "%d",i2);

    if(strcmp(ptr,"add")==0){
      iresult=i1+i2;
      //build up string to send to client by string concatenation
      strcpy(task, "add");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2); 
      strcat(task,"\n"); 
    } else if (strcmp(ptr, "sub")==0){
      iresult=i1-i2;
      //build up string to send to client by string concatenation
      strcpy(task, "sub");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2); 
      strcat(task,"\n");
    } else if (strcmp(ptr, "mul")==0){
      iresult=i1*i2;
      //build up string to send to client by string concatenation
      strcpy(task, "mul");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2);  
      strcat(task,"\n");    
    } else if (strcmp(ptr, "div")==0){
      iresult=i1/i2;
      //build up string to send to client by string concatenation
      strcpy(task, "div");
      strcat(task, " ");
      strcat(task,value1);
      strcat(task, " "); 
      strcat(task,value2); 
      strcat(task,"\n");
       
    }
    
     
      write_size = write(sockfd, task, strlen(task));
       if (write_size < 0){
       writeError();
       }
      //  if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
      //           sizeof timeout) < 0)
      //   error("setsockopt failed\n");
        printf("Int Task given to client: %s\n",task);
           
       bzero(task, sizeof(task)); 
       //read_size = read(sockfd, task, sizeof(task));
       read_size = recv(sockfd, task, sizeof(task)-1, 0);
        if(read_size < 0){
         if(errno == EAGAIN ||EWOULDBLOCK){
            perror("Timeout Reached");
           // printf("I'm here now\n");
            write_size = send(sockfd,"ERROR TO\n", strlen("ERROR TO\n"),0); 
            if(write_size < 0){
     
           fprintf(stderr,"Error writing to socket\n");
           close(sockfd);
		       exit(0);		
	
       } 
        close(sockfd);
        exit(0);
         }
         else
         readError();
         close(sockfd);
         exit(0);
      
       }
      task[read_size] = '\0';
      printf("server read %d bytes from client\n" ,read_size);
      intResults = atoi(task); 
      printf("Answer from client: %s\n",task);
      //printf("converted to integer: %d\n",intResults);
      if (abs(iresult- intResults) < 0.0001){
      printf("Expected: %d, got: %d\n",iresult,intResults);
      //clear task buffer 
      printf("Response was OK\n");           
      bzero(task, sizeof(task));  
      
      write_size = write(sockfd, "OK\n", 3); 
      if (write_size < 0){
       writeError();
       }
      
      }
      else{
      write_size = write(sockfd, "ERROR\n",6); 
     if (write_size < 0){
       writeError();
       }
        printf("Response was bad\n"); 

  }
  
 // close(sockfd); 

}
 //close(sockfd); 
printf("=======================================================\n");
  exit(0);
}		

// Driver function 
int main(int argc, char *argv[]) 
{ 
	int sockfd, connfd, len, port,status; 
	struct sockaddr_in servaddr, cli; 
        pid_t childpid;
        if (argc != 2) {
	   fprintf(stderr,"usage: ./server IP:PORT\n");
	   exit(1);
	}
        char delim[]=":";
	      char *Desthost=strtok(argv[1],delim);
        char *Destport=strtok(NULL,delim);
        port = atoi(Destport);
	// socket create and verification 




// testing this 

struct addrinfo hints, *res;


// first, load up address structs with getaddrinfo():

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
printf("%s\n",Desthost);
printf("%d\n",port);
status = getaddrinfo(Desthost,Destport, &hints, &res);
if (status!=0){
  perror("Error: ");
}

// make a socket:




//end of test

	//sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	//servaddr.sin_family = AF_INET; 
	
	//servaddr.sin_addr.s_addr = inet_addr(Desthost);

	//servaddr.sin_port = htons( port);
        
	// Binding newly created socket to given IP and verification 
  
	if ((bind(sockfd, res->ai_addr, res->ai_addrlen)) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 
  freeaddrinfo(res);
	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
        for (;;) { 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
	inet_ntop(AF_INET, &(cli.sin_addr), clientAddr, CLADDR_LEN);
	printf("=======================================================\n");
	printf("server acccepted client: %s\n",clientAddr); 
	printf("Handling client %s\n", clientAddr);
	
        if ((childpid = fork()) == 0) { //creating a child process

        close(sockfd); 

   for (;;) {
   func(connfd);
   exit(0);
  
  }
 		
	} 
   close(connfd);
} 
}





