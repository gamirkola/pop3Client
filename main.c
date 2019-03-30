#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
//"in" per "sockaddr_in"
#include <netinet/in.h>
//"netdb" per "gethostbyname"
#include <netdb.h>





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
  h=gethostbyname("18.195.169.69");
  if (h==0)
  {
    printf("Gethostbyname fallito\n");
    exit(1);
  }
  bcopy(h->h_addr,&temp.sin_addr,h->h_length);
  //Creazione socket.
  sock=socket(AF_INET,SOCK_STREAM,0);
  //Connessione del socket. Esaminare errore per compiere azioni
  //opportune in caso di errore.
  errore=connect(sock, (struct sockaddr*) &temp, sizeof(temp));
  const char *buf[4096] = { 0 };
  const char *buf1[4096] = { 0 };
  const char *buf2[4096] = { 0 };
  const char *buf3[4096] = { 0 };
  const char *buf4[4096] = { 0 };
  if ( recv (sock, buf, 4096, 0) == -1){
       printf ("Error in recvng message\n");
       exit (-1);
     }
  printf(buf);

  //Spedisco il messaggio voluto
    if (send(sock,"USER mirko\n",strlen("USER mirko\n"),0)<0){
        printf("Impossibile mandare il messaggio.\n");
    }
    if ( recv (sock, buf1, 4096, 0) == -1){
       printf ("Error in recvng message\n");
       exit (-1);
     }
  printf(buf1);
    if (send(sock,"PASS mirko\n",strlen("PASS mirko\n"),0)<0){
        printf("Impossibile mandare il messaggio.\n");
    }
    if ( recv (sock, buf2, 4096, 0) == -1){
       printf ("Error in recvng message\n");
       exit (-1);
     }
  printf(buf2);
  if (send(sock,"LIST\n",strlen("LIST\n"),0)<0){
        printf("Impossibile mandare il messaggio.\n");
    }
    if ( recv (sock, buf3, 4096, 0) == -1){
       printf ("Error in recvng message\n");
       exit (-1);
     }
  printf(buf3);
  if (send(sock,"RETR 1\n",strlen("RETR 1\n"),0)<0){
        printf("Impossibile mandare il messaggio.\n");
    }
    if ( recv (sock, buf4, 4096, 0) == -1){
       printf ("Error in recvng message\n");
       exit (-1);
     }
  printf(buf4);


  //Chiudo il socket.
  close(sock);

  return 0;
}
