#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define TARGETSTRSIZE 7
#define FORMATSTRSIZE 2

void DieWithError(char *errorMessage);

void handle_client(int client_sock)
{
  /*TODO: Remember to handle receipt of messages in accordance with encoding in client
    - receive the amount of bytes corresponding to the first message
    - receive the amount of bytes corresponding to the units until there is no more to receive (while recv > 0)
    */

  char target[TARGETSTRSIZE];
  char format[FORMATSTRSIZE];
  int recvMsgSize;
  int bytes_recv = 0;
  char *error = "Formatting is incorrect.";
  uint8_t type;

  /* Receive message from client */
  if ((recvMsgSize = recv(client_sock, format, FORMATSTRSIZE, 0)) < 0)
    DieWithError("recv() failed");

  if ((recvMsgSize = recv(client_sock, target, TARGETSTRSIZE, 0)) < 0)
    DieWithError("recv() failed");
  /* TODO: Write a receive that only takes one byte at a time and read until the delimiters are reached */
  /* TODO: Immediately after, receive one unit at a time until all units are received */

  while (recvMsgSize > 0)
  {
    if ((recvMsgSize = recv(client_sock, &type, 1, 0)) < 0)
      DieWithError("recv() failed");

    if (type == 0)
    {
      // Read a type 0 unit
      printf("Type 0\n");
    }
    else if (type == 1)
    {
      // Read a type 1 unit
      printf("Type 1\n");
    }
    else{
      // printf("Type is invalid\n");
      // if (send(client_sock, error, strlen(error) + 1, 0) != strlen(error) + 1)
      //   DieWithError("send() sent a different number of bytes than expected");
    }

  }



  printf("Format: %s\nTarget: %s\n", format, target);
  close(client_sock);
}