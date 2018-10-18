#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void DieWithError(char *errorMessage);

void handle_client(int client_sock)
{
  /*TODO: Remember to handle receipt of messages in accordance with encoding in client
    - receive the amount of bytes corresponding to the first message
    - receive the amount of bytes corresponding to the units until there is no more to receive (while recv > 0)
    */

  char buffer[RCVBUFSIZE];
  int recvMsgSize;

  /* Receive message from client */
  if ((recvMsgSize = recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  while (recvMsgSize > 0)
  {
    if (send(client_sock, buffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");

    if ((recvMsgSize = recv(client_sock, buffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("recv() failed");

  }

  close(client_sock);
}