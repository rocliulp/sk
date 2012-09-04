#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv []) {
  struct sockaddr_in sk_addr;
  int ret = 0;
  int socket_fd;

  memset (& sk_addr, 0, sizeof (struct sockaddr_in));
  sk_addr.sin_family = AF_INET;
  sk_addr.sin_port = htons (1100);
  ret = inet_pton (AF_INET, "192.168.1.3", & sk_addr.sin_addr);
  if (ret < 0) {
    printf ("inet_pton (~) failed. \
        First parameter is not a valid address family.\n\r");
    return 1;
  } else if (ret == 0) {
    printf ("inet_pton (~) failed. \
        Second parameter does not contain valid ip address.\n\r");
    return 1;
  }

  socket_fd = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd == -1) {
    printf ("socket (~) failed\n\r");
    return 1;
  }

  ret = connect (socket_fd,
      (struct sockaddr *) & sk_addr,
      sizeof (struct sockaddr_in));
  if (ret == -1) {
    printf ("connect (~) failed\n\r");
    close (socket_fd);
    return 1;
  }

  /* Perform read / write operations. */

  shutdown (socket_fd, SHUT_RDWR);
  close (socket_fd);

  return 0;
}
