#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv []) {
  int ret = 0;
  struct sockaddr_in socket_addr;
  int socket_fd = -1;
  char buffer [256] = {'\0'};

  socket_fd = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_fd == -1) {
    printf ("socket (~) failed.\n\r");
    return 1;
  }
  memset (& socket_addr, 0, sizeof (socket_addr));
  socket_addr.sin_family = AF_INET;
  socket_addr.sin_port = htons (7654);
  socket_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
  strcpy (buffer, "Hello world!");
  ret = sendto (socket_fd, buffer, strlen (buffer), 0,
      (struct sockaddr *) & socket_addr, sizeof (socket_addr));
  if (ret < 0) {
    printf ("sendto (~) failed.\n\r");
    return 1;
  }
  close (socket_fd);

  return 0;
}
