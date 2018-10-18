#include <stdio.h>      /* for printf() and fprintf()*/
#include <sys/socket.h> /* for socket() , connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);
/*
1. Create a TCP socket using socket()
2. Establish a connection to the server using connect()
3. Communicate using send() and recv()
4. Close the connection with close()

  args:
  - server IP
  - server port
  - file path
  - to format
  - to name
*/

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in serv_addr;
  unsigned short serv_port;
  char *serv_ip;
  char *file_path;
  char *to_format;
  char *to_name;

  if (argc != 5)
  {
    fprintf(stderr, "Usage: %s <Server IP> <Server Port> <File Path> <To Format> <To Name>\n", argv[0]);
    exit(1);
  }

  /* Catch argument values */
  serv_ip = argv[1];
  serv_port = atoi(argv[2]);
  file_path = argv[3];
  to_format = argv[4];
  to_name = argv[5];

  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    DieWithError("socket() failed");

  // Initialize the server address structure
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
  serv_addr.sin_port = htons(serv_port);

  //Start connection to the server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    DieWithError("connect() failed.");

  /* TODO: Open and read units from file */

  /* TODO: send info to the server */

  /* TODO: recv failure error message or success confirmation from server  */

  close(sock);
  exit(0);
}
