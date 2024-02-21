#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_SERVICE_LENGTH 50
#define MAX_DATE_LENGTH 50
#define MAX_FILE_CONTENT_LENGTH 1024
#define MAX 80
#define PORT 8080
#define MAX_FILE_LIST_LENGTH 1024 // Définissez la taille maximale de la liste des fichiers

struct question {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char service[MAX_SERVICE_LENGTH];
};

struct reponse {
    char service[MAX_SERVICE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char file_content[MAX_FILE_CONTENT_LENGTH];
    int connection_duration;
    char liste_fichiers[MAX_FILE_LIST_LENGTH]; // Remplacez MAX_FILE_LIST_LENGTH par la taille maximale de la liste des fichiers
};
void handleDate(struct reponse *reponse);
void handleFileList(struct reponse *reponse);
void handleConnectionDuration(struct reponse *reponse);
void handleFileContent(struct reponse *reponse);
#endif


