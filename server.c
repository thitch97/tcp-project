#include <stdio.h>      /* for printf() and fprintf()*/
#include <sys/socket.h> /* for socket() , connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

/*
1. Create a TCP socket using socket()
2. Assign a port number to the socket with bind()
3. Tell the system to allow connection to be made to that port, using listen()
4. Repeatedly do the following:
  - Call accept() to get a new socket for each client connection
  - Communicate with the client via that new socket using send() and recv()
  - Close the client connection using close()
*/
#define MAXPENDING 5

void DieWithError(char *errorMessage);
void handle_client(int client_sock);

int main(int argc, char *argv[]){

  int serv_sock, client_sock;
  struct sockaddr_in serv_addr, client_addr;
  unsigned short serv_port;
  socklen_t client_len;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }

  serv_port = atoi(argv[1]);

  if ( (serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    DieWithError("socket() failed");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(serv_port);

  if( bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    DieWithError("bind() failed");

  if(listen(serv_sock, MAXPENDING) < 0)
    DieWithError("listen() failed");

  for(;;)
  {
    client_len = sizeof(client_addr);

    if ( (client_sock = accept(serv_sock, (struct sockaddr *) &client_addr, &client_len)) < 0)
      DieWithError("accept() failed");
    

    printf("Handling client %s\n", inet_ntoa(client_addr.sin_addr));
    handle_client(client_sock);

  }

}