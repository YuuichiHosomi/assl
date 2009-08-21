#ifndef AGGLOMERATEDSSL_H
#define AGGLOMERATEDSSL_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

#define ASSL_DEFAULT_PORT	"4433"

enum assl_method {
	ASSL_M_ALL,
	ASSL_M_ALL_CLIENT,
	ASSL_M_ALL_SERVER,
	ASSL_M_SSLV2,
	ASSL_M_SSLV2_CLIENT,
	ASSL_M_SSLV2_SERVER,
	ASSL_M_SSLV3,
	ASSL_M_SSLV3_CLIENT,
	ASSL_M_SSLV3_SERVER,
	ASSL_M_TLSV1,
	ASSL_M_TLSV1_CLIENT,
	ASSL_M_TLSV1_SERVER
};

struct assl_context {
	/* generic */
	int			as_nonblock;	/* set to enable nb io */
	int			as_server;	/* 1 if in server role */
	SSL			*as_ssl;
	int			as_sock;
	BIO			*as_sbio;

	/* client */
	struct sockaddr_in	as_addr;
	struct hostent		*as_raddr;

	/* openssl */
	SSL_METHOD		*as_method;
	SSL_CTX			*as_ctx;
	X509			*as_ca;
	X509			*as_cert;
	EVP_PKEY		*as_key;
	int			as_verify_mode;
	int			as_verify_depth;
};

void			assl_initialize(void);
struct assl_context	*assl_alloc_context(enum assl_method);
int			assl_load_file_certs(struct assl_context *, char *,
			    char *, char *);
int			assl_connect(struct assl_context *, char *, char *);
int			assl_serve(char *, char *, void (*)(int));
int			assl_accept(struct assl_context *, int);
#endif /* AGGLOMERATEDSSL_H */
