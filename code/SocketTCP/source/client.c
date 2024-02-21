#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include "message.h"
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include "message.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void displayServices() {
    printf("Services disponibles :\n");
    printf("1. Envoie de la date et l'heure du serveur\n");
    printf("2. Envoie de la liste des fichiers d'un répertoire\n");
    printf("3. Envoie de la durée écoulée depuis le début de la connexion\n");
    printf("4. Envoie du contenu d'un fichier\n");
    printf("5. Fin du programme\n");
}
int authenticate(int sockfd) {
    struct question question;
    struct reponse reponse;

    char username[MAX], password[MAX];

    printf("Authentification\n");
    printf("Nom d'utilisateur : ");
    scanf("%s", username);
    printf("Mot de passe : ");
    scanf("%s", password);

    // Envoi des informations d'authentification au serveur
    strcpy(question.username, username);
    strcpy(question.password, password);
    strcpy(question.service, "authentification");
    write(sockfd, &question, sizeof(struct question));

    read(sockfd, &reponse, sizeof(struct reponse));
    if (strcmp(reponse.date, "Authentification réussie") != 0) {
        printf("Échec de l'authentification\n");
        return 0; // Échec d'authentification
    }
    printf("Authentification réussie\n");
    return 1; // Authentification réussie
}
void func(int sockfd) {
    struct question question;
    struct reponse reponse;
    int choice;

    if (!authenticate(sockfd)) {
        close(sockfd);
        exit(0);
    }

 while (1) {
        displayServices();
        printf("\n Entrez votre choix ou '5' pour terminer : ");
        scanf("%d", &choice);

        strcpy(question.service, ""); // Réinitialisation du service dans la question

        switch (choice) {
            // Assigner le service approprié basé sur le choix de l'utilisateur
            case 1:
                strcpy(question.service, "date");
                break;
            case 2:
                strcpy(question.service, "liste_fichiers");
                break;
            case 3:
                strcpy(question.service, "connection_duration");
                break;
            case 4:
                strcpy(question.service, "file_content");
                break;
            case 5:
                printf("Au revoir...\n");
                
                return;
            default:
                printf("Service non reconnu ou '5' saisi.\n");
                continue;
        }

        // Envoyer la demande de service au serveur
        write(sockfd, &question, sizeof(struct question));

        // Lire et afficher la réponse du serveur
        read(sockfd, &reponse, sizeof(struct reponse));

        if (strcmp(reponse.service, "unknown") == 0) {
            printf("Service non reconnu.\n");
        } else {
            // Afficher la réponse en fonction du service
            switch (choice) {
                case 1:
                    printf("\n\n  Date : %s\n\n", reponse.date);
                    break;
                case 2:
                    printf("\n\n Liste des fichiers :\n%s\n\n", reponse.liste_fichiers);
                    break;
                case 3:
                    printf("\n\n Durée de la connexion : %d\n\n", reponse.connection_duration);
                    break;
                case 4:
                    printf("\n\nContenu du fichier :\n%s\n\n", reponse.file_content);
                    break;
            }
        }
    }
}


int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Échec de la création de la socket...\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    printf("Tentative de connexion au serveur...\n");

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Échec de la connexion avec le serveur...\n");
        exit(0);
    } else {
        printf("Connexion établie avec le serveur...\n");
    }

    // Appel à la fonction pour la communication client-serveur
    func(sockfd);

    close(sockfd);
    
    return 0;
}

