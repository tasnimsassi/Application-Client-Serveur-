
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include "message.h"
#define MAX 80
#define PORT 8080
#define MAX_FILE_CONTENT_LENGTH 1024



time_t connection_start_time;

void handleDate(struct reponse *reponse) {
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(reponse->date, sizeof(reponse->date), "%x %X", time_info);
}


void handleFileList(struct reponse *reponse) {
    DIR *directory;
    struct dirent *file;

    reponse->liste_fichiers[0] = '\0'; // Réinitialisation de la chaîne

    directory = opendir("/home/tasnim/Desktop/tp_sassi_tasnim_achour_malek"); // Remplacez par votre chemin
    if (directory) {
        while ((file = readdir(directory)) != NULL) {
            strcat(reponse->liste_fichiers, file->d_name);
            strcat(reponse->liste_fichiers, "\n");
        }
        closedir(directory);
    }
}



void handleConnectionDuration(struct reponse *reponse) {
    time_t current_time = time(NULL);
    int duration = difftime(current_time, connection_start_time);
    reponse->connection_duration = duration;
}

void handleFileContent(struct reponse *reponse) {
    FILE *file_pointer;
    char file_buffer[MAX_FILE_CONTENT_LENGTH];

    file_pointer = fopen("/home/tasnim/Desktop/test/hello", "r"); // Remplacez par votre chemin
    if (file_pointer) {
        while (fgets(file_buffer, sizeof(file_buffer), file_pointer) != NULL) {
            strcat(reponse->file_content, file_buffer);
        }
        fclose(file_pointer);
    }
}

void handleClientRequest(int connfd) {
    struct question question;
    struct reponse reponse;

    read(connfd, &question, sizeof(struct question));

    const char* authorized_users[][2] = {
        {"tasnim", "tasnouma"},
        {"user2", "password2"},
        // Ajoutez d'autres utilisateurs autorisés ici
    };

    int is_authenticated = 0;
    for (int i = 0; i < sizeof(authorized_users) / sizeof(authorized_users[0]); ++i) {
        if (strcmp(question.username, authorized_users[i][0]) == 0 &&
            strcmp(question.password, authorized_users[i][1]) == 0) {
            is_authenticated = 1;
            break;
        }
    }

    if (!is_authenticated) {
    strcpy(reponse.service, "authentification");
    strcpy(reponse.date, "Échec d'authentification");
    write(connfd, &reponse, sizeof(struct reponse));
    close(connfd);
    exit(0);
}

// Envoi de la réponse d'authentification réussie
    strcpy(reponse.service, "authentification");
    strcpy(reponse.date, "Authentification réussie");
    write(connfd, &reponse, sizeof(struct reponse));

    while (1) {
        // Lecture de la demande de service du client
        read(connfd, &question, sizeof(struct question));

        if (strcmp(question.service, "date") == 0) {
            handleDate(&reponse);
            write(connfd, &reponse, sizeof(struct reponse));
        } else if (strcmp(question.service, "liste_fichiers") == 0) {
            handleFileList(&reponse);
            write(connfd, &reponse, sizeof(struct reponse));
        } else if (strcmp(question.service, "connection_duration") == 0) {
            handleConnectionDuration(&reponse);
            write(connfd, &reponse, sizeof(struct reponse));
        } else if (strcmp(question.service, "file_content") == 0) {
            handleFileContent(&reponse);
            write(connfd, &reponse, sizeof(struct reponse));
        } else {
            // Service non reconnu
            strcpy(reponse.service, "unknown");
            write(connfd, &reponse, sizeof(struct reponse));
        }
    }
}
int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    struct reponse reponse;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        printf("Échec de la création de la socket...\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Échec du binding de la socket...\n");
        exit(0);
    }

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }

    len = sizeof(cli);
printf("Serveur en attente de connexions...\n");
   


while (1) {
    connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
    if (connfd < 0) {
        printf("Échec de la connexion avec le client...\n");
        exit(0);
    } else {
        printf("Client connecté...\n");
        int fils = fork();
        if (fils == 0) {
            printf("Communication avec le client...\n");
            handleClientRequest(connfd); // Appel pour gérer la requête du client
            handleDate(&reponse);
            handleFileList(&reponse);
            handleConnectionDuration(&reponse);
            handleFileContent(&reponse);
            close(connfd); // Fermeture de la connexion dans le processus fils
            exit(0); // Terminaison du processus fils
        } else if (fils < 0) {
            printf("Erreur lors de la création du processus fils...\n");
        }
        close(connfd); // Fermeture de la connexion dans le processus parent
    }
}


    return 0;
}
