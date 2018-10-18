#include <stdio.h>      /* for printf() and fprintf()*/
#include <sys/socket.h> /* for socket() , connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define TARGETSTRSIZE 7
#define FORMATSTRSIZE 2

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
  char *destination_msg;
  char *serv_res; 
  int recvMsgSize;


  int bytes_recv, tot_bytes_recv;
  FILE *infp;

  if (argc != 6)
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

  sprintf(destination_msg, "%s%s ", to_format, to_name);
  int msglen = strlen(destination_msg);
  printf("Destination Message: %s\n", destination_msg);

  /* send destination info to the server */
  if (send(sock, to_format, strlen(to_format) + 1, 0) != strlen(to_format) + 1)
    DieWithError("send() sent a different number of bytes than expected");

  printf("To_name Length: %lu bytes\n", strlen(to_name));
  if (send(sock, to_name, strlen(to_name) + 1, 0) != strlen(to_name) + 1)
    DieWithError("send() sent a different number of bytes than expected");

  printf("Sending file ...\n\n");

  /* Open file*/
  infp = fopen(file_path, "rb");

  if (infp == NULL)
  {
    printf("%s", "File not found");
    exit(1);
  }

  //Move pointer to the end of file
  fseek(infp, 0, SEEK_END);

  //Get file size in bytes from ftell
  long int size = ftell(infp);
  printf("File size: %li\n", size);
  uint8_t file_buffer[size];

  /* Read file information*/
  fread(file_buffer, 1, size,infp);

  /* TODO: send file to the server */
  write(sock, file_buffer, size);
  fclose(infp);

  /* TODO: recv failure error message or success confirmation from server  */
  // if ((recvMsgSize = recv(sock, serv_res, strlen(serv_res), 0)) < 0)
  //   DieWithError("recv() failed");

  close(sock);
  exit(0);
}
