#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 5000
#define MAXLINE 1000

void server () {
    char buffer[100];
    int servsockfd, len,n;
    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    // Create a UDP Socket
    servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    // bind server address to socket descriptor
    bind(servsockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    int start = 0;
}

void client() {

}

void help() {
    printf("USAGE: udp -[cs]\n");
    printf(" c\t run client\n");
    printf(" s\t run server\n");
}

int main(int argc, char * argv[]) {
    if ( argc != 2 ) {
        help();
    }
    if ( argv[1][1] == 'c' ) {
        client();
    } else if ( argv[1][1] == 's' ) {
        server();
    } else {
        // you need help
        help();
    }
}