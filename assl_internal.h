/* $assl$ */
/*
 * Copyright (c) 2010, 2011 Marco Peereboom <marco@peereboom.us>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/socket.h>
#include <sys/queue.h>
#include <sys/tree.h>

int		assl_is_nonblock(struct assl_context *, int);
int		assl_set_nonblock(int);
int		assl_set_keepalive(int);
void		assl_set_tos(int, int);
void		assl_fatalx(const char *, ...);

/* pre-loaded certificates */
struct assl_mem_cert {
	RB_ENTRY(assl_mem_cert)	entry;

	void			*assl_token;
	void			*assl_mem_ca;
	off_t			assl_mem_ca_len;
	void			*assl_mem_cert;
	off_t			assl_mem_cert_len;
	void			*assl_mem_key;
	off_t			assl_mem_key_len;
};

#ifdef ASSL_NO_FANCY_ERRORS
#define ERROR_OUT(e, g) do { goto g; } while (0)
#define assl_err_stack_unwind() do { } while (0)
#define assl_err_own(s, ...) do { } while (0)
#else
#define ERR_LIBC	(0)
#define ERR_SSL		(1)
#define ERR_OWN		(2)

#define ERROR_OUT(e, g)	do { assl_push_error(__FILE__, __FUNCTION__, __LINE__, e); goto g; } while(0)

struct assl_error {
	SLIST_ENTRY(assl_error)	link;

	char			*file;
	char			*func;
	int			line;
	char			*errstr;
};
extern char			assl_last_error[1024];
extern struct assl_error_stack	aes;

/* set to indicate this is a child process */
char		*assl_geterror(int);
void		assl_push_error(const char *, const char *, int, int);
void		assl_err_stack_unwind(void);
void		assl_err_own(char *, ...);
#endif /* ASSL_NO_FANCY_ERRORS */
