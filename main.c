#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <malloc.h>
#include <string.h>
#include <zconf.h>

#define HOSTNAME "18.195.169.69"
#define PORT 110
#define BUFLEN 4096

/**
 * Esce con messaggio.
 * se errorstr é uguale a NULL, allora il messaggio di errore viene fornito dal sistema.
 */
int die(int code, const char * errorstr){
    if(errorstr == NULL){
        char errbuf[255];
        snprintf(errbuf, 255, "Uscendo con errore %i", code);
        perror(errbuf);
    } else
        fprintf(stderr, "Uscendo con errore %i: %s", code, errorstr);
    exit(code);
    return 1;
}

void invia(int sock, const char *comando) {
    ssize_t sent = send(sock, comando, strlen(comando), 0);
    if (sent < 0) die(-126, "Errore di invio");
}

void ricevi(int sock, char *buf, int msglen) {

    ssize_t len = recv(sock, buf, msglen - 1 , 0);
    if (len < 0) die(-125, "Errore di ricezione");
    buf[len] = 0; //string terminator overriding \n
    printf("%s> %s", HOSTNAME, buf);

}

int main(int argc, char *argv[]) {

    printf("Connessione in corso... ");
    fflush(stdout);

    //Ottiene indirizzo di connessione
    struct hostent * h = (struct hostent *) gethostbyname(HOSTNAME);
    if(h == NULL) die(-1, "Impossibile ottenere l'hostname");

    int sock;
    char * msg = (char *) malloc(sizeof(char) * BUFLEN);

    //Parametri della connessione
    struct sockaddr_in temp;
    temp.sin_family = AF_INET;
    temp.sin_port = htons(PORT);

    bcopy(h->h_addr, &temp.sin_addr, h->h_length);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    int errore = connect(sock, (struct sockaddr *) &temp, sizeof(temp));
    if(errore != 0) die(errore, NULL);

    printf("connesso\nScrivi \"esci\" per uscire.\n\n");

    ricevi(sock, msg, BUFLEN);

    while (1) {

        printf("client ready > ");
        fgets(msg, BUFLEN, stdin);

        if (!strcmp(msg, "esci\n")) break;

        invia(sock, msg);
        ricevi(sock, msg, BUFLEN);
    }

    printf("Grazie di avermi utilizzato! alla prossima!\n");
    close(sock);
    return 0;
}
