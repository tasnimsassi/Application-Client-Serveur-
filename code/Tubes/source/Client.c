#include "Handlers_Cli.h"
int main(){
/* Déclarations */
int Des_QUESTION , Des_REPONSE;
struct question question ;
struct reponse reponse ;
int readsucces,writesucces;
sigset_t newset , block_set ;
struct sigaction rien ;
/* Ouverture des tubes nommés */
Des_QUESTION = open(FIFO_QUESTION,O_WRONLY);
Des_REPONSE = open(FIFO_REPONSE,O_RDONLY);
/* Installation des Handlers */
rien.sa_flags=0;
rien.sa_handler=hand_reveil2;
sigemptyset(&rien.sa_mask);
if (sigaction (SIGUSR1,&rien,NULL)==-1)
    perror("sigaction problem !");
if (sigemptyset (&newset)==-1)
    perror("sigemptyset problem !");
if (sigaddset (&newset,SIGUSR1)==-1)
    perror("sigaddset problem !");
if (sigprocmask (SIG_SETMASK,&newset,NULL)==-1) //block jusqu'a la terminaison du handler
    perror("sigprocmask problem !");
if (sigemptyset (&block_set)==-1)
    perror("sigemptyset problem !");
//signal(SIGUSR1,hand_reveil2);
/* Construction et envoi d’une question */
srand ( getpid ());
question.numero_client = getpid();
question.Question = 1+rand()%NMAX ;
printf ("\n\n\t----------------------- DEBUT Client %d -----------------------\n",question.numero_client);
printf ("\n\t     Le nombre envoyée par le client =  %d \n", question.Question);
writesucces=write(Des_QUESTION,&question,sizeof(struct question));
if(writesucces==-1)
{
    printf("Erreur d'écriture \n");
    exit(2);
}
else
{
/* Attente de la réponse */
//pause();
sigsuspend (&block_set);
/* Lecture de la réponse */
readsucces=read(Des_REPONSE,&reponse,sizeof(struct reponse));
if(readsucces==-1)
{
    printf("Erreur de lecture");
    exit(2);
}
else
{
/* Envoi du signal SIGUSR1 au serveur */
kill(reponse.numero_serveur,SIGUSR1);
/* Traitement local de la réponse */
printf ("\n\t     Les nombres reçu du serveur PID %d = ",reponse.numero_serveur);
for(int i=0;i<question.Question;i++)
{
    printf("%d ",reponse.Reponse[i]);
}
printf ("\n\n\t----------------------- FIN Client %d ------------------------\n\n",question.numero_client);
}
}

close(Des_QUESTION);
close(Des_REPONSE);
exit(0);
}