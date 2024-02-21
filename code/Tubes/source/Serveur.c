#include "Handlers_Serv.h"
int main(){
/*Déclarations */
int Des_QUESTION , Des_REPONSE;
struct question question ;
struct reponse reponse ;
int readsucces,writesucces;
int creation_QUESTION,creation_REPONSE;
mode_t mode =S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;
struct sigaction rien ;
sigset_t newset , block_set ;
/* Création des tubes nommés */
creation_QUESTION = mkfifo ("fifo1",mode);
creation_REPONSE = mkfifo ("fifo2",mode);
if(creation_QUESTION == -1)
{
printf ("La creation de tube QUESTION est impossible \n ");
exit (2);
};
if(creation_REPONSE == -1)
{
printf("La creation de tube REPONSE est impossible \n ");
exit(2);
};
/*initialisation du générateur de nombres aléatoires*/
srand(getpid());
/* Ouverture des tubes nommés */
Des_QUESTION = open(FIFO_QUESTION,O_RDONLY);
Des_REPONSE = open(FIFO_REPONSE,O_WRONLY);
/* Installation des Handlers */
for (int sign= 1; sign < NSIG ; sign++)
{
    signal(sign,fin_serveur);
}

//Installation de hand SIGUSR1 avec le norme POSIX sigaction
rien.sa_handler=hand_reveil;
rien.sa_flags=0;
sigemptyset(&rien.sa_mask);
if(sigaction (SIGUSR1,&rien , NULL)==-1)
    perror("sigaction problem !");
if(sigemptyset (&newset)==-1)
    perror("sigemptyset problem !");    
if(sigaddset (&newset,SIGUSR1)==-1)
    perror("sigaddset problem !");  
if(sigprocmask (SIG_SETMASK ,&newset ,NULL))
    perror("sigprocmask problem !");  
sigemptyset (&block_set );
//signal(SIGUSR1,hand_reveil);
while(1){
/* lecture d’une question */

if(read(Des_QUESTION,&question,sizeof(struct question))<=0)
{
    close(Des_QUESTION); 
    Des_QUESTION = open (FIFO_QUESTION,O_RDONLY );
}
else
{
printf ("\n\n\t---------------------- DEBUT SERVEUR %d ----------------------",getpid());
printf("\n\n\t\t Traitement du client ayant pid = %d ",question.numero_client);
printf("\n\t            > Question = %d",question.Question);
/* construction de la réponse */
reponse.numero_serveur = getpid();
for ( int i = 0; i < question.Question ; i++)
reponse.Reponse[i]= rand()%10;
/* envoi de la réponse */
writesucces=write(Des_REPONSE,&reponse,sizeof(struct reponse));
if(writesucces==-1)
{
    printf("Erreur d'écriture");
    fin_serveur(-1);
}
else
{
    printf("\n\t            > Reponse =");
    for ( int i = 0; i < question.Question ; i++)
    {
        printf(" %d",reponse.Reponse[i]);
    }

/* envoi du signal SIGUSR1 au client concerné */
kill(question.numero_client,SIGUSR1);
//pause();
sigsuspend (&block_set);
printf ("\n\n\t---------------------- FIN SERVEUR %d ------------------------\n\n",getpid());
}
}
}
}
