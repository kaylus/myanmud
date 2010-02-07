/*
 * This file is part of DGD, http://dgd-osr.sourceforge.net/
 * Copyright (C) 1993-2010 Dworkin B.V.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

# if defined(__STDC__) || defined(__cplusplus)
#  define P(proto)	proto
#  define cvoid		const void
# else
#  define P(proto)	()
#  define cvoid		char
# endif


# ifdef WIN32

typedef int Int;
typedef unsigned int Uint;

# include <limits.h>
# include <sys\types.h>
# include <malloc.h>

# ifdef INCLUDE_FILE_IO
# include <io.h>
# include <direct.h>
# include <fcntl.h>
# include <sys\stat.h>

# define F_OK	0
# define R_OK	4
# define W_OK	2
# endif

# ifdef INCLUDE_CTYPE
# include <ctype.h>
# endif

# ifdef INCLUDE_TELNET
# include "host\telnet.h"
# endif

# include <stdlib.h>
# include <string.h>
# include <setjmp.h>
# include <stdio.h>

# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# define FS_BLOCK_SIZE		2048

# define Uuint			unsigned __int64
# define bool			dgd_bool
# define exit			dgd_exit
# define abort			dgd_abort

extern void dgd_exit(int);
extern void dgd_abort(void);

# endif	/* WIN32 */


# ifdef SUNOS4

# define GENERIC_BSD

# include <alloca.h>
# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# endif	/* SUNOS4 */


# ifdef SOLARIS

# define GENERIC_SYSV

# include <alloca.h>
# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# include <sys/file.h>		/* for FNDELAY */

# endif	/* SOLARIS */


# ifdef DECALPHA

# define GENERIC_SYSV

# include <alloca.h>
# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# endif /* DECALPHA */


# if defined(DARWIN) || defined(NETBSD) || defined(FREEBSD) || defined(OPENBSD)

# define GENERIC_BSD

# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# endif /* DARWIN || NETBSD || FREEBSD || OPENBSD */


# ifdef LINUX

# define GENERIC_SYSV

# define ALLOCA(type, size)	((type *) alloca(sizeof(type) * \
							     (size_t) (size)))
# define AFREE(ptr)		/* on function return */

# endif /* LINUX */


# ifdef GENERIC_BSD

typedef int Int;
typedef unsigned int Uint;

# include <limits.h>
# include <sys/types.h>
# include <unistd.h>

# ifdef INCLUDE_FILE_IO
# include <fcntl.h>
# include <sys/stat.h>
# endif

# ifdef INCLUDE_CTYPE
# include <ctype.h>
# endif

# ifdef INCLUDE_TELNET
# include "host/telnet.h"
# endif

# include <stdlib.h>
# include <string.h>
# include <setjmp.h>
# include <stdio.h>

# ifndef ALLOCA
# define ALLOCA(type, size)	ALLOC(type, size)
# define AFREE(ptr)		FREE(ptr)
# endif

# define FS_BLOCK_SIZE		8192

# endif	/* GENERIC_BSD */


# ifdef GENERIC_SYSV

typedef int Int;
typedef unsigned int Uint;

# include <limits.h>
# include <sys/types.h>
# include <unistd.h>

# ifdef INCLUDE_FILE_IO
# include <fcntl.h>
# include <sys/stat.h>
# ifndef FNDELAY
# define FNDELAY	O_NDELAY
# endif
# endif

# ifdef INCLUDE_CTYPE
# include <ctype.h>
# endif

# ifdef INCLUDE_TELNET
# include "host/telnet.h"
# endif

# include <stdlib.h>
# include <string.h>
# include <setjmp.h>
# include <stdio.h>

# ifndef ALLOCA
# define ALLOCA(type, size)	ALLOC(type, size)
# define AFREE(ptr)		FREE(ptr)
# endif

# define FS_BLOCK_SIZE		8192

# endif	/* GENERIC_SYSV */


typedef char bool;
# ifndef TRUE
# define TRUE		1
# define FALSE		0
# endif

# if defined(__GNUC__) && __GNUC__ >= 2
# define Uuint unsigned long long
# endif

extern void  P_message	P((char*));

# ifndef O_BINARY
# define O_BINARY	0
# endif

# ifdef INCLUDE_FILE_IO
# if defined(GENERIC_BSD) || defined(GENERIC_SYSV)
	/* no filename translation */
# define path_native(buf, path)	(path)

# define P_open		open
# define P_close	close
# define P_read		read
# define P_write	write
# define P_lseek	lseek
# define P_fstat	fstat
# define P_stat		stat
# define P_access	access
# define P_unlink	unlink
# define P_rename	rename
# define P_mkdir	mkdir
# define P_rmdir	rmdir
# define P_chdir	chdir
# else
	/* filename translation */
extern char *path_native	P((char*, char*));

extern int P_open	P((char*, int, int));
extern int P_close	P((int));
extern int P_read	P((int, char*, int));
extern int P_write	P((int, char*, int));
extern long P_lseek	P((int, long, int));
extern int P_fstat	P((int, struct stat*));
extern int P_stat	P((char*, struct stat*));
extern int P_access	P((char*, int));
extern int P_unlink	P((char*));
extern int P_rename	P((char*, char*));
extern int P_mkdir	P((char*, int));
extern int P_rmdir	P((char*));
extern int P_chdir	P((char*));
# endif
# endif /* INCLUDE_FILE_IO */

extern bool  P_opendir	P((char*));
extern char *P_readdir	P((void));
extern void  P_closedir	P((void));

extern void  P_srandom	P((long));
extern long  P_random	P((void));

extern Uint  P_time	P((void));
extern Uint  P_mtime	P((unsigned short*));
extern char *P_ctime	P((char*, Uint));

/* these must be the same on all hosts */
# define BEL	'\007'
# define BS	'\010'
# define HT	'\011'
# define LF	'\012'
# define VT	'\013'
# define FF	'\014'
# define CR	'\015'

struct _struct_al_ { long l; short s; };
# define STRUCT_AL	(sizeof(struct _struct_al_) - sizeof(long))
# define ALGN(x, s)	(((x) + (s) - 1) & ~((s) - 1))


# if defined(CHAR_MAX) && CHAR_MAX == 255
# define UCHAR(c)	((char) (c))			/* unsigned character */
# define SCHAR(c)	((((char) (c)) - 128) ^ -128)	/* signed character */
# else
# define UCHAR(c)	((int) ((c) & 0xff))		/* unsigned character */
# define SCHAR(c)	((char) (c))			/* signed character */
# endif
