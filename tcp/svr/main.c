#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

int main (void) {
  int ret = 0;
  struct sockaddr_in sk_addr;

  memset (& sk_addr, 0, sizeof (sockaddr_in));
  sk_addr.sin_family = AF_INET;
  sk_addr.sin_port = htons (1100);
  sk_addr.sin_addr.s_addr = INADDR_ANY;

  int socket_fd = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd == -1) {
    printf ("socket (~) failed.\n\r");
    return 1;
  }

  ret = bind (socket_fd, (struct sockaddr *) & sk_addr, sizeof (sockaddr_in));
  if (ret == -1) {
    printf ("bind (~) failed.\n\r");
    close (socket_fd);
    return 1;
  }

  return 0;
}
