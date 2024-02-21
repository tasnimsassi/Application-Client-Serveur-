#ifndef message_h
#define message_h

#define NMAX 10


struct question {
    int numero_client ;
    int Question ;
};
struct reponse {
    int numero_serveur ;
    int Reponse [NMAX];
};


#endif