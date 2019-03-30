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
  char msg[2048];

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

  //Spedisco il messaggio voluto
    if (write(sock,"USER mirko",strlen("USER mirko"))<0)
      {
        printf("Impossibile mandare il messaggio.\n");
        close(sock);
        exit(1);
      }
      if(recv(sock,msg,sizeof(msg),0)<0)
        printf("errore di ricezione");
      else
        printf("messaggio dal server:", msg);
      if (write(sock,"PASS mirko",strlen("PASS mirko"))<0)
      {
        printf("Impossibile mandare il messaggio.\n");
        close(sock);
        exit(1);
      }
      printf("Messaggio spedito con successo.\n");

  //Chiudo il socket.
  close(sock);

  return 0;
}
