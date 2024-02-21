// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include "message.h"
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
    
#define PORT     8080 
#define MAXLINE 1024 
void func(int sockfd,struct sockaddr_in servaddr)
   {
    struct question question ;
    struct reponse reponse ;
    int n, len; 
    srand ( getpid ());
    question.numero_client = getpid();
    question.Question = 1+rand()%NMAX ;
    printf ("\n\n\t--------------------- DEBUT Client %d ---------------------\n",question.numero_client);
    printf ("\n\t     Le nombre envoyée par le client =  %d \n", question.Question);
    sendto(sockfd, &question,sizeof(struct question), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));  
            
    recvfrom(sockfd,&reponse,sizeof(struct reponse),  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
   printf ("\n\t     Les nombres reçu du serveur PID %d = ",reponse.numero_serveur);
    for(int i=0;i<question.Question;i++)
    {
        printf("%d ",reponse.Reponse[i]);
    }
    printf ("\n\n\t---------------------- FIN Client %d ----------------------\n\n",question.numero_client);
    close(sockfd); 
   } 
// Driver code 
int main() { 
    int sockfd; 
    struct sockaddr_in     servaddr; 
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    func(sockfd,servaddr);
    return 0; 
}
