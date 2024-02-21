#include "Handlers_Serv.h"
void hand_reveil(int sig)
{

printf("\n \t Wake UP Serveur ! Signal : %d \n ",sig);
}
void fin_serveur(int sig)
{
printf("\n \t TERMINATION OF Serveur ! .... SIGNAL : %d \n",sig);
unlink (FIFO_QUESTION);
unlink (FIFO_REPONSE);
exit(5);
}
