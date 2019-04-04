#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>


void Invia(int sock, char *comando[]){
    printf(comando);
    if(send(sock,comando,strlen(comando),0)<0){
        printf ("Errore di invio\n");
        exit(-1);
    }
    return;
}

void Ricevi(int sock){
    char *buf[4096] = { 0 };

    if ( recv (sock, buf, 4096, 0)<0){
        printf ("Errore di ricezione\n");
        exit(-1);
    }
    printf(buf);

    return;
}

int main(int argc,char* argv[])
{

  //Creo e connetto il socket
  struct sockaddr_in temp;
  struct hostent *h;
  int sock;
  int errore;
  char *msg[4096];

  //Tipo di indirizzo
  temp.sin_family=AF_INET;
  temp.sin_port=htons(110);
//  printf("Inserisci l'indirizo del server di posta:"); //18.195.169.69
//  char srv[20];
//  fgets(srv, 20, stdin);
  h=gethostbyname("18.195.169.69");
  if (h==0)
  {
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
    fgets(msg, 4096, stdin);

    if(strcmp(msg,"esci")){
        exit(-1);
    }

     if(send(sock,msg,strlen(msg),0)<0){
        printf ("Errore di invio\n");
        exit(-1);
    }
    printf(msg);
    Ricevi(sock);

  }

  //Chiudo il socket.
  close(sock);

  return 0;
}
