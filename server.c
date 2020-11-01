
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include<stdbool.h> 
#include "calcLib.h"
#include "calcLib.c"
#define MAX 200 
#define char_size 20 
#define PORT 8080 
#define SA struct sockaddr 
#define CLADDR_LEN 100

char clientAddr[CLADDR_LEN];
char buffer[MAX]; 
char first[char_size],second[char_size];
 
void func(int sockfd) 
{ 
     char text[20] = "TEXT TCP 1.0\n";
     if (write(sockfd,text, sizeof(text)) < 0){
       printf("Error writing to client\n");
       }
       bzero(text, sizeof(text));
       
     bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
      printf("Client %s responded with: %s\n", clientAddr, buffer);  
	
  initCalcLib();
  char *ptr;
  ptr=randomType(); // Get a random arithemtic operator. 

  double f1,f2,fresult;
  int i1,i2,iresult;
  char good[] = "OK\n";
  char bad[] = "ERROR\n";
  /*
  printf("ptr = %p, \t", ptr );
  printf("string = %s, \n", ptr );
  */

  /* Act differently depending on what operator you got, judge type by first char in string. If 'f' then a float */
  
  if(ptr[0]=='f'){
    //printf("Float\t");
    f1=randomFloat();
    f2=randomFloat();

    /* At this point, ptr holds operator, f1 and f2 the operands. Now we work to determine the reference result. */
   
    if(strcmp(ptr,"fadd")==0){
      fresult=f1+f2;
      sprintf(first, "%f",f1);
      sprintf(second, "%f",f2);
      strcpy(buffer, "fadd");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second); 
      printf("Back to client: %s\n",buffer);
           
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       float results = atof(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted float: %f\n",results);
      if (abs(fresult- results) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      } 
      
      
    } else if (strcmp(ptr, "fsub")==0){
      fresult=f1-f2;
      sprintf(first, "%f",f1);
      sprintf(second, "%f",f2);
      strcpy(buffer, "fsub");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second); 
      printf("Back to client: %s\n",buffer);
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       float results = atof(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted float: %f\n",results);
      if (abs(fresult- results) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      }  
    } else if (strcmp(ptr, "fmul")==0){
      fresult=f1*f2;
      sprintf(first, "%f",f1);
      sprintf(second, "%f",f2);
      strcpy(buffer, "fmul");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second); 
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       float results = atof(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted float: %f\n",results);
      if (abs(fresult- results) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      
     write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      } 
    } else if (strcmp(ptr, "fdiv")==0){
      fresult=f1/f2;
      sprintf(first, "%f",f1);
      sprintf(second, "%f",f2);
      strcpy(buffer, "fdiv");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second);
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       float results = atof(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted float: %f\n",results);
      if (abs(fresult- results) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      } 
    }
   // printf("%s %8.8g %8.8g = %8.8g\n",ptr,f1,f2,fresult);
  } else {
    //printf("Int\t");
    i1=randomInt();
    i2=randomInt();

    if(strcmp(ptr,"add")==0){
      iresult=i1+i2;
      sprintf(first, "%d",i1);
      sprintf(second, "%d",i2);
      strcpy(buffer, "add");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second);
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       int result = atoi(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted integer: %d\n",result);
      if (abs(iresult- result) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      } 
    } else if (strcmp(ptr, "sub")==0){
      iresult=i1-i2;
      sprintf(first, "%d",i1);
      sprintf(second, "%d",i2);
      strcpy(buffer, "sub");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second);
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       int result = atoi(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted integer: %d\n",result);
      if (abs(iresult- result) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      } 
    } else if (strcmp(ptr, "mul")==0){
      iresult=i1*i2;
      sprintf(first, "%d",i1);
      sprintf(second, "%d",i2);
      strcpy(buffer, "mul");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second); 
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       int result = atoi(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted integer: %d\n",result);
      if (abs(iresult- result) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      }  
    } else if (strcmp(ptr, "div")==0){
      iresult=i1/i2;
      sprintf(first, "%d",i1);
      sprintf(second, "%d",i2);
      strcpy(buffer, "div");
      strcat(buffer, " ");
      strcat(buffer,first);
      strcat(buffer, " "); 
      strcat(buffer,second); 
      printf("Back to client: %s\n",buffer);
           
            //write(sockfd, res, sizeof(res));
      if (write(sockfd, buffer, sizeof(buffer)) < 0){
       printf("Error writing to client\n");
       }
       bzero(buffer, sizeof(buffer)); 
       if (read(sockfd, buffer, sizeof(buffer)) < 0){
       error("ERROR reading from socket");
       }
       int result = atoi(buffer); 
      printf("Answer from client: %s\n",buffer);
      printf("converted integer: %d\n",result);
      if (abs(iresult- result) < 0.01){
                  
      bzero(buffer, sizeof(buffer));  
      
      write(sockfd, good, sizeof(good)); 
      bzero(good, sizeof(good)); 
      //break;
      }
      else{
      write(sockfd, bad, sizeof(bad)); 
      bzero(bad, sizeof(bad)); 
      
      }  
    }

  }




}		

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
        pid_t childpid;
	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
        
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

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
	printf("server acccepted client: %s\n",clientAddr); 
           if ((childpid = fork()) == 0) { //creating a child process

   close(sockfd); 
//stop listening for new connections by the main process. 
//the child will continue to listen. 
//the main process now handles the connected client.

   for (;;) {
   func(connfd);
   
  }
	
	
	} 
   close(connfd);
} 
}
