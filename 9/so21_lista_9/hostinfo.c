#include "csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  char buf[MAXLINE], buf2[MAXLINE];
  int rc, flags;

  if (argc != 2)
    app_error("usage: %s <domain name>\n", argv[0]);
    
	const char *domain;
	const char *service; 
    
    switch(argc)
    {
    	case 2:
    		domain = argv[1];
    		service = NULL;
    	case 3:
    		domain = argv[1];
    		service = argv[2];
    	default:
    		app_error("usage: %s <domain name>\n", argv[0]);
    }//zwiekszona lista argumentow o 1 opcjonalny

  /* Get a list of addrinfo records */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = /*AF_INET*/ AF_UNSPEC; /* IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; //change to 0 for tftp
  /* Connections only */
  if ((rc = getaddrinfo(domain, service, &hints, &listp)) != 0)
    gai_error(rc, "getaddrinfo");

  /* Walk the list and display each IP address */
  flags = NI_NUMERICHOST | NI_NUMERICSERV; /* Display address string instead of domain name */
  for (p = listp; p; p = p->ai_next) {
    Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, buf2, MAXLINE, flags);
    
    if(service && p->ai_family == AF_INET6) printf("[%s]:%s\n", buf, buf2);
    else if(service) printf("%s:%s\n", buf, buf2);
    else printf("%s\n", buf);
  }

  /* Clean up */
  freeaddrinfo(listp);

  return EXIT_SUCCESS;
}
