// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <fcntl.h>
// #include <pthread.h>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <arpa/inet.h>

// void * doRecieving(void * sockID){

// 	int clientSocket = *((int *) sockID);

// 	while(1){

// 		char data[1024];
// 		int read = recv(clientSocket,data,1024,0);
// 		data[read] = '\0';
// 		printf("%s\n",data);

// 	}

// }

// int main(){

// 	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

// 	struct sockaddr_in serverAddr;

// 	serverAddr.sin_family = AF_INET;
// 	serverAddr.sin_port = htons(8080);
// 	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

// 	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

// 	printf("Connection established ............\n");

// 	pthread_t thread;
// 	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

// 	while(1){

// 		char input[1024];
// 		scanf("%s",input);

// 		if(strcmp(input,"LIST") == 0){

// 			send(clientSocket,input,1024,0);

// 		}
// 		if(strcmp(input,"SEND") == 0){

// 			send(clientSocket,input,1024,0);
			
// 			scanf("%s",input);
// 			send(clientSocket,input,1024,0);
			
// 			scanf("%[^\n]s",input);
// 			send(clientSocket,input,1024,0);

// 		}

// 	}


// }

#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<stdbool.h>
#define MAX 80 
//#define PORT 8080 
//#define PORT 5000 
#define SA struct sockaddr 


 void func(int sockfd){
  
    double f1,f2,fresult;
    int i1,i2,iresult,write_size,read_size;
    char str[255];
    char st[80];
 
   // for(;;)
    //{
      
  
  read_size= read(sockfd, str, sizeof(str)-1); 
	if (read_size < 0){
     fprintf(stderr,"Socket read failed!\n");
		  exit(1);
            }
        //ans = atoi(read(sockfd, result, sizeof(result)));
        str[read_size] = 0; 
        printf("From Server : %s\n", str);
        printf("client read %d bytes from server\n" ,read_size); 
        printf("length of message is %d\n",strlen(str));
        if (strstr(str, "TEXT TCP 1.0") ||strstr(str, "TEXT TCP 1.1") != NULL) {
    // contains

        bzero(str, sizeof(str));  
      
      
         char msg[5] = "OK\n";
         printf("len of msg:%d\n",strlen(msg));
         write_size = write(sockfd, msg, strlen(msg)); 
         printf("I've written %d bytes to server\n",write_size);
             
            if (write_size < 0){
               fprintf(stderr,"Socket write failed!\n");
		           exit(1);
            }
          bzero(msg, sizeof(msg)); 
	  read_size = read(sockfd, str, sizeof(str)-1);
            
            if (read_size < 0){
               fprintf(stderr,"Socket read failed!\n");
		           exit(1);
            }
            
            printf("client read %d bytes from the server\n" ,read_size);
            str[read_size] = 0;
            printf("Server sent: %s\n" ,str);
char input[] ="first second third forth";
char delimiter[] = " ";
char *firstWord, *secondWord,*thirdWord, *remainder, *context;

int inputLength = strlen(str);
char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
strncpy(inputCopy, str, inputLength);

firstWord = strtok_r (inputCopy, delimiter, &context);
secondWord = strtok_r (NULL, delimiter, &context);
thirdWord = strtok_r (NULL, delimiter, &context);
remainder = context;
// printf("%s\n", firstWord);
// printf("%s\n", secondWord);
// printf("%s\n", thirdWord);

if(firstWord[0]=='f'){
  
    if(strcmp(firstWord,"fadd")==0){
      f1 = atof(secondWord);
      f2 = atof(thirdWord);
      fresult= (f1+f2);
    } else if (strcmp(firstWord, "fsub")==0){
      f1 = atof(secondWord);
      f2 = atof(thirdWord);
      fresult= (f1-f2);
    } else if (strcmp(firstWord, "fmul")==0){
      f1 = atof(secondWord);
      f2 = atof(thirdWord);
      fresult = (f1*f2);
    } else if (strcmp(firstWord, "fdiv")==0){
      f1 = atof(secondWord);
      f2 = atof(thirdWord);
      fresult = (f1/f2);
    }
      bzero(st, sizeof(st)); 
            
            sprintf(st, "%8.8g", fresult);
            strcat(st,"\n");
	    printf("len of fresult is %d\n", strlen(st));
            printf("size of st is %d\n", sizeof(st));
            //printf("length of st is %d\n", strlen(st));
            
            //printf("len of st is %d\n", strlen(st));
            printf("Answer back to server: %s\n",st);
            
            write_size = write(sockfd, st, strlen(st)); 
            if (write_size < 0){
                fprintf(stderr,"Socket write failed!\n");
		            exit(1);
            }
            printf("client wrote %d bytes to server\n" ,write_size);
            bzero(st, sizeof(st)); 
            bzero(str, sizeof(str)); 
            read_size = read(sockfd, str, sizeof(str)-1);
            
            if (read_size < 0){
              fprintf(stderr,"Socket read failed!\n");
		          exit(1);
            }
            printf("client read %d bytes from the server\n" ,read_size);
            
            
            str[read_size] = 0;
            printf("Responds from Server : %s\n",str);

             free(inputCopy);
    
   
  } else {
    
   
    if(strcmp(firstWord,"add")==0){
      i1 = atoi(secondWord);
      i2 = atoi(thirdWord);
      iresult=i1+i2;
    } else if (strcmp(firstWord, "sub")==0){
      i1 = atoi(secondWord);
      i2 = atoi(thirdWord);
      iresult=(i1-i2);
      //printf("[%s %d %d = %d ]\n",firstWord,i1,i2,iresult);
    } else if (strcmp(firstWord, "mul")==0){
      i1 = atoi(secondWord);
      i2 = atoi(thirdWord);
      iresult=(i1*i2);
    } else if (strcmp(firstWord, "div")==0){
      i1 = atoi(secondWord);
      i2 = atoi(thirdWord);
      iresult=(i1/i2);
      
     }
     
     bzero(st, sizeof(st)); 
            
     sprintf(st, "%d", iresult);
            
            strcat(st,"\n");
	    printf("len of fresult is %d\n", strlen(st));
            printf("size of st is %d\n", sizeof(st));
        
            printf("len of st is %d\n", strlen(st));
            printf("Answer back to server: %s\n",st);
            
            write_size = write(sockfd, st, strlen(st)); 
            if (write_size < 0){
              fprintf(stderr,"Socket write failed!\n");
		          exit(1);
            }
            printf("client wrote %d bytes to server\n" ,write_size);
            bzero(st, sizeof(st)); 
            bzero(str, sizeof(str)); 
            read_size = read(sockfd, str, sizeof(str)-1);
            
            if (read_size < 0){
              fprintf(stderr,"Socket read failed!\n");
		          exit(1);
            }
            
            printf("client read %d bytes from the server\n" ,read_size);
            str[read_size] = 0; 
            
            printf("Responds from Server : %s\n",str);
            free(inputCopy);
  
  }
        
 bzero(str, sizeof(str)); 
 //exit(1);   
 
 }
 
 else {
 printf("Exiting because the protocol seems not to be tcp\n");
 bzero(str, sizeof(str));
 exit(1);
 }
//           }
}

int main(int argc, char *argv[]) 
{ 
	int sockfd, connfd, port; 
	struct sockaddr_in servaddr, cli; 
	struct hostent *server;
  if (argc != 2) {
		fprintf(stderr,"usage: ./client IP:PORT\n");
		exit(1);
	}
	char delim[]=":";
	char *Desthost=strtok(argv[1],delim);
        char *Destport=strtok(NULL,delim);
        port = atoi(Destport);
  //yikwenmein, @Yikwenmein1
	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr(Desthost); 
	 
	servaddr.sin_port = htons(port); 
	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(1); 
	} 
	else
             printf("connected to the server..\n"); 
	// function for chat 
	func(sockfd); 
        
	// close the socket 
	close(sockfd); 
} 

