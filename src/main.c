#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static const int recv_conn = 5;

static void usage(const char*);
static void print_sock(struct sockaddr *addr);
static int binding(const char*, const char*);
static int spawn(int, char* const[]);

int main (int argc, char* const *argv) {
	if (argc < 4) {
		usage(argv[0]);
		return 1;
	}

	int sfd = binding(argv[1], argv[2]);
	if (sfd < 0) {
		fprintf(stderr, "binding() faild\n");
		return -1;
	}

	if (listen(sfd, recv_conn) == -1) {
		perror("listen(): ");
		close(sfd);
		return -1;
	}

	for(;;) {
		int cfd = accept(sfd, NULL, 0);
		if (spawn(cfd, argv+3) != 0) {
			fprintf(stderr, "spawn()");
			return -1;
		}
		close(cfd);
	}

	return 0;
}


static void usage(const char* prog) {
	fprintf(stderr, "%s addr service program [program_args...]\n", prog);
}


static int binding(const char* node, const char* service) {
	int err;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	struct addrinfo *res = NULL;

	if((err = getaddrinfo(node, service, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(err));
		return -1;
	}

	int sfd;
	struct addrinfo *rp = NULL;
	for (rp = res; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sfd);
	 }

	if (rp == NULL) {
		fprintf(stderr, "Could not bind\n");
		return -1;
	}

	print_sock(rp->ai_addr);
	freeaddrinfo(res);

	return sfd;
}


static void print_sock(struct sockaddr *addr) {
	char buf[128];
	switch(addr->sa_family) {
	case AF_INET: {
		struct sockaddr_in *v4 = (struct sockaddr_in*)addr;
		inet_ntop(addr->sa_family, &(v4->sin_addr), buf, sizeof(buf));
		printf("ipv4: addr:%s, port:%hu\n", buf, ntohs(v4->sin_port));
		break;
		}
	case AF_INET6: {
		struct sockaddr_in6 *v6 = (struct sockaddr_in6*)addr;
		inet_ntop(addr->sa_family, &(v6->sin6_addr), buf, sizeof(buf));
		printf("ipv6: addr:%s, port:%hu\n", buf, ntohs(v6->sin6_port));
		break;
		}
	default:
		puts("unimplements");
	}
}


int spawn(int cfd, char* const argv[]) {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork()");
		return -1;
	}
	if (pid > 0) {
		return 0;
	}
	// child process
	if (dup2(cfd, 0) == -1) {
		perror("dup2()");
		exit(0);
	}

	if (execv(argv[0], argv) == -1) {
		perror("execv()");
	}
	return 1;
}
