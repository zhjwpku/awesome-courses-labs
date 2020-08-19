/* include fig01 */
#include	"unp.h"
#include	<sys/epoll.h>

#define MAX_EVENTS 64

int
main(int argc, char **argv)
{
	int					i, epfd, listenfd, connfd, sockfd, on;
	int					nready;
	ssize_t				n;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	struct epoll_event	ev;
	struct epoll_event	evlist[MAX_EVENTS];

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		err_sys("setsockopt of SO_REUSEADDR error");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	if ((epfd = epoll_create(MAX_EVENTS)) < 0) {
		err_sys("epoll_create error");
	}

	ev.data.fd = listenfd;
	ev.events = EPOLLIN;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) < 0) {
		err_sys("epoll_ctl EPOLL_CTL_ADD listenfd error");
	}

/* end fig01 */

/* include fig02 */
	for ( ; ; ) {
		nready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
		if (nready == -1) {
			if (errno == EINTR) {
				continue;
			} else {
				err_sys("epoll_wait error");
			}
		}

		for (i = 0; i < nready; i++) {	/* check all events */
			printf(" fd=%d; events: %s%s%s%s\n", evlist[i].data.fd,
				(evlist[i].events & EPOLLIN) ? "EPOLLIN " : "",
				(evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
				(evlist[i].events & EPOLLERR) ? "EPOLLERR " : "",
				(evlist[i].events & EPOLLRDHUP) ? "EPOLLRDHUP " : "");

			if ((evlist[i].events & EPOLLIN) && evlist[i].data.fd == listenfd) {
				clilen = sizeof(cliaddr);
				connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
				printf("new client: %s\n", Sock_ntop((SA *)&cliaddr, clilen));
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLRDHUP;
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) < 0) {
					err_sys("epoll_ctl EPOLL_CTL_ADD connfd error");
				}
			} else if (evlist[i].events & EPOLLIN) {
				sockfd = evlist[i].data.fd;
				if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
					if (errno == ECONNRESET) {
						/*4connection reset by client */
						printf("client[%d] aborted connection\n", sockfd);
						Close(sockfd);
					} else
						err_sys("read error");
				} else if (n == 0) {
					/*4connection closed by client */
					printf("client[%d] closed connection\n", sockfd);
					Close(sockfd);
				} else
					Writen(sockfd, buf, n);
			} else {
				printf("events: %d\n", evlist[i].events);
				err_sys("unknown error");
			}
		}
	}
}
/* end fig02 */
