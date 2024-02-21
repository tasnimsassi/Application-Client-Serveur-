#ifndef serv_cli_fifo_h
#define serv_cli_fifo_h

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#define NMAX 10
#define FIFO_QUESTION "fifo1"
#define FIFO_REPONSE "fifo2"

struct question {
    int numero_client ;
    int Question ;
};
struct reponse {
    int numero_serveur ;
    int Reponse [NMAX];
};


#endif