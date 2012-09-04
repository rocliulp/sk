#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv []) {
  int ret = 0;
  struct sockaddr_in socket_addr;
  int socket_fd;
  int addr_size;
  char buffer [1024];

  memset (& socket_addr, 0, sizeof (socket_addr));
  socket_addr.sin_family = AF_INET;
  socket_addr.sin_port = htons (7654);
  socket_addr.sin_addr.s_addr = INADDR_ANY;
  addr_size = sizeof (socket_addr);

  socket_fd = socket (PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_fd == -1) {
    printf ("socket (~) failed.\n\r");
    return 1;
  }
  ret = bind (socket_fd,
      (struct sockaddr *) & socket_addr,
      addr_size
      );
  if (ret == -1) {
    printf ("bind (~) failed.\n\r");
    close (socket_fd);
    return 1;
  }

  while (1) {
    printf ("recvfrom (~) test...\n\r");
    ret = recvfrom (socket_fd, (void *) buffer, sizeof (buffer), 0,
        (struct sockaddr *) & socket_addr, & addr_size);
    if (ret < 0) {
      printf ("recvfrom (~) failed.\n\r");
      return 1;
    }
    printf ("received size: %d\n\r", ret);
    sleep (1);
    printf ("datagram: %d, %s\n\r", ret, buffer);
  }
  return 0;
}
