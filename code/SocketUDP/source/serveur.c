// Server side implementation of UDP client-server model 
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
    void func(int sockfd, struct sockaddr_in cliaddr){
     int len, n; 
    len = sizeof(cliaddr);  //len is value/result 
    struct question question ;
    struct reponse reponse ;
    recvfrom(sockfd,&question,sizeof(struct question),  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    printf("\n\n\t\t Traitement du client ayant pid = %d ",question.numero_client);
    printf("\n\t            > Question = %d",question.Question);
    /* construction de la réponse */
    reponse.numero_serveur = getpid();
    printf("\n\t            > Reponse =");
    for ( int i = 0; i < question.Question ; i++)
    {
        reponse.Reponse[i]= rand()%10;
        printf(" %d",reponse.Reponse[i]);
    }
    // and send that buffer to client
    sendto(sockfd, &reponse,sizeof(struct reponse),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
   close(sockfd); 
    }
// Driver code 
int main() { 
    int sockfd;
    struct sockaddr_in servaddr, cliaddr; 
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    // Function for chatting between client and server
    printf ("\n\n\t--------------------- DEBUT SERVEUR %d ---------------------",getpid());
    func(sockfd,cliaddr);
    printf ("\n\n\t---------------------- FIN SERVEUR %d ----------------------\n\n",getpid());
    
    }


