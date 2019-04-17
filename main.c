#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>
#include <malloc.h>
#include <string.h>

int str_comp(char a[], char b[]){
    int c = 0;

    while (a[c] == b[c]) {
        if (a[c] == '\n')
            break;
        c++;
    }

    if (a[c] == '\n')
        return 0;
    else
        return -1;
}

void Invia(int sock, char *comando[]){
    if(send(sock,comando,strlen(comando),0)<0){
        printf ("Errore di invio\n");
        exit(-1);
    }
    return;
}

void Ricevi(int sock){
    char *buf = (char *) malloc(sizeof(char *) * 4096);

    if ( recv (sock, buf, 4096, 0)<0){
        printf ("Errore di ricezione\n");
        exit(-1);
    }

    printf(buf);
    buf = "";

    return;
}

int main(int argc,char* argv[]){

    //Creo e connetto il socket
    struct sockaddr_in temp;
    struct hostent *h;
    int sock;
    int errore;
    char *msg = (char *)malloc(sizeof(char *)*2048);

    //Tipo di indirizzo
    temp.sin_family=AF_INET;
    temp.sin_port=htons(110);

    h=gethostbyname("18.195.169.69");

    if (h==0){
        printf("Gethostbyname fallito\n");
        exit(-1);
    }

    bcopy(h->h_addr,&temp.sin_addr,h->h_length);
    //Creazione socket.
    sock=socket(AF_INET,SOCK_STREAM,0);
    //Connessione del socket. Esaminare errore per compiere azioni
    //opportune in caso di errore.
    errore=connect(sock, (struct sockaddr*) &temp, sizeof(temp));
    Ricevi(sock);

    while(1){

        printf("Inserisci un comando: ");
        fgets(msg, 2048, stdin);


        if(str_comp(msg,"esci")==0){
        printf ("Grazie di avermi utilizzato! alla prossima\n");
        close(sock);
        return 0;
        }
        //        printf(msg);
        Invia(sock, msg);

        Ricevi(sock);
    }
    free(msg);

    //Chiudo il socket.
    close(sock);

return 0;
}
