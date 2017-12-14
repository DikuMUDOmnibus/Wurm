 
/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,
 *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Thanks to abaddon for proof-reading our comm.c and pointing out bugs.  *
 *  Any remaining bugs are, of course, our work, not his.  :)              *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
*	ROM 2.4 is copyright 1993-1996 Russ Taylor			   *
*	ROM has been brought to you by the ROM consortium		   *
*	    Russ Taylor (rtaylor@efn.org)				   *
*	    Gabrielle Taylor						   *
*	    Brian Moore (zump@rom.org)					   *
*	By using this code, you have agreed to follow the terms of the	   *
*	ROM license, in the file Rom24/doc/rom.license			   *
***************************************************************************/

/*
 * This file contains all of the OS-dependent stuff:
 *   startup, signals, BSD sockets for tcp/ip, i/o, timing.
 *
 * The data flow for input is:
 *    Game_loop ---> Read_from_descriptor ---> Read
 *    Game_loop ---> Read_from_buffer
 *
 * The data flow for output is:
 *    Game_loop ---> Process_Output ---> Write_to_descriptor -> Write
 *
 * The OS-dependent functions are Read_from_descriptor and Write_to_descriptor.
 * -- Furey  26 Jan 1993
 */

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "merc.h"
#include "recycle.h"

/* command procedures needed */
DECLARE_DO_FUN(do_help		);
DECLARE_DO_FUN(do_look		);
DECLARE_DO_FUN(do_skills	);
DECLARE_DO_FUN(do_outfit	);
DECLARE_DO_FUN(do_unread	);
DECLARE_DO_FUN(do_yell          );

/*
 * Malloc debugging stuff.
 */
#if defined(sun)
#undef MALLOC_DEBUG
#endif

#if defined(MALLOC_DEBUG)
#include <malloc.h>
extern	int	malloc_debug	args( ( int  ) );
extern	int	malloc_verify	args( ( void ) );
#endif



/*
 * Signal handling.
 * Apollo has a problem with __attribute(atomic) in signal.h,
 *   I dance around it.
 */
#if defined(apollo)
#define __attribute(x)
#endif

#if defined(unix)
#include <signal.h>
#endif

#if defined(apollo)
#undef __attribute
#endif



/*
 * Socket and TCP/IP stuff.
 */
#if	defined(macintosh) || defined(MSDOS)
const	char	echo_off_str	[] = { '\0' };
const	char	echo_on_str	[] = { '\0' };
const	char 	go_ahead_str	[] = { '\0' };
#endif

#if	defined(unix)
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "telnet.h"
const	char	echo_off_str	[] = { IAC, WILL, TELOPT_ECHO, '\0' };
const	char	echo_on_str	[] = { IAC, WONT, TELOPT_ECHO, '\0' };
const	char 	go_ahead_str	[] = { IAC, GA, '\0' };
#endif



/*
 * OS-dependent declarations.
 */
#if	defined(_AIX)
#include <sys/select.h>
int	accept		args( ( int s, struct sockaddr *addr, int *addrlen ) );
int	bind		args( ( int s, struct sockaddr *name, int namelen ) );
void	bzero		args( ( char *b, int length ) );
int	getpeername	args( ( int s, struct sockaddr *name, int *namelen ) );
int	getsockname	args( ( int s, struct sockaddr *name, int *namelen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
int	listen		args( ( int s, int backlog ) );
int	setsockopt	args( ( int s, int level, int optname, void *optval,
			    int optlen ) );
int	socket		args( ( int domain, int type, int protocol ) );
#endif

#if	defined(apollo)
#include <unistd.h>
void	bzero		args( ( char *b, int length ) );
#endif
 void    html_who (int fd,char *argument);
#if	defined(__hpux)
int	accept		args( ( int s, void *addr, int *addrlen ) );
int	bind		args( ( int s, const void *addr, int addrlen ) );
void	bzero		args( ( char *b, int length ) );
int	getpeername	args( ( int s, void *addr, int *addrlen ) );
int	getsockname	args( ( int s, void *name, int *addrlen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
int	listen		args( ( int s, int backlog ) );
int	setsockopt	args( ( int s, int level, int optname,
 				const void *optval, int optlen ) );
int	socket		args( ( int domain, int type, int protocol ) );
#endif

#if	defined(interactive)
#include <net/errno.h>
#include <sys/fnctl.h>
#endif

#if	defined(linux)
/* 
    Linux shouldn't need these. If you have a problem compiling, try
    uncommenting accept and bind.
int	accept		args( ( int s, struct sockaddr *addr, int *addrlen ) );
int	bind		args( ( int s, struct sockaddr *name, int namelen ) );
*/

int	close		args( ( int fd ) );
int	getpeername	args( ( int s, struct sockaddr *name, int *namelen ) );
int	getsockname	args( ( int s, struct sockaddr *name, int *namelen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
int	listen		args( ( int s, int backlog ) );
int	read		args( ( int fd, char *buf, int nbyte ) );
int	select		args( ( int width, fd_set *readfds, fd_set *writefds,
			    fd_set *exceptfds, struct timeval *timeout ) );
int	socket		args( ( int domain, int type, int protocol ) );
int	write		args( ( int fd, char *buf, int nbyte ) );
#endif

#if	defined(macintosh)
#include <console.h>
#include <fcntl.h>
#include <unix.h>
struct	timeval
{
	time_t	tv_sec;
	time_t	tv_usec;
};
#if	!defined(isascii)
#define	isascii(c)		( (c) < 0200 )
#endif
static	long			theKeys	[4];

int	gettimeofday		args( ( struct timeval *tp, void *tzp ) );
#endif

#if	defined(MIPS_OS)
extern	int		errno;
#endif

#if	defined(MSDOS)
int	gettimeofday	args( ( struct timeval *tp, void *tzp ) );
int	kbhit		args( ( void ) );
#endif

#if	defined(NeXT)
int	close		args( ( int fd ) );
int	fcntl		args( ( int fd, int cmd, int arg ) );
#if	!defined(htons)
u_short	htons		args( ( u_short hostshort ) );
#endif
#if	!defined(ntohl)
u_long	ntohl		args( ( u_long hostlong ) );
#endif
int	read		args( ( int fd, char *buf, int nbyte ) );
int	select		args( ( int width, fd_set *readfds, fd_set *writefds,
			    fd_set *exceptfds, struct timeval *timeout ) );
int	write		args( ( int fd, char *buf, int nbyte ) );
#endif

#if	defined(sequent)
int	accept		args( ( int s, struct sockaddr *addr, int *addrlen ) );
int	bind		args( ( int s, struct sockaddr *name, int namelen ) );
int	close		args( ( int fd ) );
int	fcntl		args( ( int fd, int cmd, int arg ) );
int	getpeername	args( ( int s, struct sockaddr *name, int *namelen ) );
int	getsockname	args( ( int s, struct sockaddr *name, int *namelen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
#if	!defined(htons)
u_short	htons		args( ( u_short hostshort ) );
#endif
int	listen		args( ( int s, int backlog ) );
#if	!defined(ntohl)
u_long	ntohl		args( ( u_long hostlong ) );
#endif
int	read		args( ( int fd, char *buf, int nbyte ) );
int	select		args( ( int width, fd_set *readfds, fd_set *writefds,
			    fd_set *exceptfds, struct timeval *timeout ) );
int	setsockopt	args( ( int s, int level, int optname, caddr_t optval,
			    int optlen ) );
int	socket		args( ( int domain, int type, int protocol ) );
int	write		args( ( int fd, char *buf, int nbyte ) );
#endif

/* This includes Solaris Sys V as well */
#if defined(sun)
int	accept		args( ( int s, struct sockaddr *addr, int *addrlen ) );
int	bind		args( ( int s, struct sockaddr *name, int namelen ) );
void	bzero		args( ( char *b, int length ) );
int	close		args( ( int fd ) );
int	getpeername	args( ( int s, struct sockaddr *name, int *namelen ) );
int	getsockname	args( ( int s, struct sockaddr *name, int *namelen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
int	listen		args( ( int s, int backlog ) );
int	read		args( ( int fd, char *buf, int nbyte ) );
int	select		args( ( int width, fd_set *readfds, fd_set *writefds,
			    fd_set *exceptfds, struct timeval *timeout ) );
#if defined(SYSV)
int setsockopt		args( ( int s, int level, int optname,
			    const char *optval, int optlen ) );
#else
int	setsockopt	args( ( int s, int level, int optname, void *optval,
			    int optlen ) );
#endif
int	socket		args( ( int domain, int type, int protocol ) );
int	write		args( ( int fd, char *buf, int nbyte ) );
#endif

#if defined(ultrix)
int	accept		args( ( int s, struct sockaddr *addr, int *addrlen ) );
int	bind		args( ( int s, struct sockaddr *name, int namelen ) );
void	bzero		args( ( char *b, int length ) );
int	close		args( ( int fd ) );
int	getpeername	args( ( int s, struct sockaddr *name, int *namelen ) );
int	getsockname	args( ( int s, struct sockaddr *name, int *namelen ) );
int	gettimeofday	args( ( struct timeval *tp, struct timezone *tzp ) );
int	listen		args( ( int s, int backlog ) );
int	read		args( ( int fd, char *buf, int nbyte ) );
int	select		args( ( int width, fd_set *readfds, fd_set *writefds,
			    fd_set *exceptfds, struct timeval *timeout ) );
int	setsockopt	args( ( int s, int level, int optname, void *optval,
			    int optlen ) );
int	socket		args( ( int domain, int type, int protocol ) );
int	write		args( ( int fd, char *buf, int nbyte ) );
#endif



/*
 * Global variables.
 */
DESCRIPTOR_DATA *   descriptor_list;	/* All open descriptors		*/
DESCRIPTOR_DATA *   d_next;		/* Next descriptor in loop	*/
FILE *		    fpReserve;		/* Reserved file handle		*/
bool		    god;		/* All new chars are gods!	*/
bool		    merc_down;		/* Shutdown			*/
struct sockaddr_in who_sa;
bool		    wizlock;		/* Game is wizlocked		*/
bool		    newlock;		/* Game is newlocked		*/
char		    str_boot_time[MAX_INPUT_LENGTH];
time_t		    current_time;	/* time of this pulse */	
bool                MOBtrigger = TRUE; /*act switch*/
int 		    who_socket;     /*Descritriptor for WHO/HTLM*/
LOG_TYPE	    player_log[10];
int		    log_head=0;

/*
 * OS-dependent local functions.
 */
#if defined(macintosh) || defined(MSDOS)
void	game_loop_mac_msdos	args( ( void ) );
bool	read_from_descriptor	args( ( DESCRIPTOR_DATA *d ) );
bool	write_to_descriptor	args( ( int desc, char *txt, int length ) );
#endif

#if defined(unix)
void	game_loop_unix		args( ( int control ) );
int	init_socket		args( ( int port,int who_port ) );
void	init_descriptor		args( ( int control ) );
bool	read_from_descriptor	args( ( DESCRIPTOR_DATA *d ) );
bool	write_to_descriptor	args( ( int desc, char *txt, int length ) );
#endif




/*
 * Other local functions (OS-independent).
 */
bool	check_parse_name	args( ( char *name ) );
bool	check_reconnect		args( ( DESCRIPTOR_DATA *d, char *name,
				        bool    fConn ) );
void 	who_do_time		    ( int fd );
bool	check_playing		args( ( DESCRIPTOR_DATA *d, char *name ) );
int	main			args( ( int argc, char **argv ) );
void	nanny			args( ( DESCRIPTOR_DATA *d, char *argument ) );
bool	process_output		args( ( DESCRIPTOR_DATA *d, bool fPrompt ) );
void	read_from_buffer	args( ( DESCRIPTOR_DATA *d ) );
void	stop_idling		args( ( CHAR_DATA *ch ) );
void    bust_a_prompt           args( ( CHAR_DATA *ch ) );

// defined in handler.c

 int  hometown_lookup	    (const char *town);

int main( int argc, char **argv )
{
    struct timeval now_time;
    int port;
    int who_port;
#if defined(unix)
    int control;
#endif

    /*
     * Memory debugging if needed.
     */
#if defined(MALLOC_DEBUG)
    malloc_debug( 2 );
#endif

    /*
     * Init time.
     */
    gettimeofday( &now_time, NULL );
    current_time 	= (time_t) now_time.tv_sec;
    strcpy( str_boot_time, ctime( &current_time ) );

    /*
     * Macintosh console initialization.
     */
#if defined(macintosh)
    console_options.nrows = 31;
    cshow( stdout );
    csetmode( C_RAW, stdin );
    cecho2file( "log file", 1, stderr );
#endif

    /*
     * Reserve one channel for our use.
     */
    if ( ( fpReserve = fopen( NULL_FILE, "r" ) ) == NULL )
    {
	perror( NULL_FILE );
	exit( 1 );
    }

    /*
     * Get the port number.
     */
    port = 4000;
    who_port = 2080;
    if ( argc > 1 )
    {
	if ( !is_number( argv[1] ) )
	{
	    fprintf( stderr, "Usage: %s [port #] [who port #]\n", argv[0]);
	    exit( 1 );
	}
	else if ( ( port = atoi( argv[1] ) ) <= 1024 )
	{
	    fprintf( stderr, "Port number must be above 1024.\n" );
	    exit( 1 );
	}
	if ( !is_number( argv[2] ) )
	{
	    fprintf( stderr, "Usage: %s [port #] [who port #]\n", argv[0]);
	    exit( 1 );
	}
	else if ( ( who_port = atoi( argv[2] ) ) <= 1024 )
	{
	    fprintf( stderr, "Who Port number must be above 1024.\n" );
	    fprintf( stderr, "And Diffrent from the main port..\n" );
	    exit( 1 );
	}
    }

    /*
     * Run the game.
     */
#if defined(macintosh) || defined(MSDOS)
    boot_db( );
    log_string( "Merc is ready to rock." );
    game_loop_mac_msdos( );
#endif

#if defined(unix)
    control = init_socket( port,who_port );
    boot_db( );
    sprintf( log_buf, "ROM is ready to rock on port %d who port %d.", port, who_port);
    log_string( log_buf );
    game_loop_unix( control );
    close (control);
        close(who_socket);

#endif

    /*
     * That's all, folks.
     */
    log_string( "Normal termination of game." );
    exit( 0 );
    return 0;
}



#if defined(unix)
int init_socket( int port,int who_port )
{
    static struct sockaddr_in sa_zero;
    struct sockaddr_in sa;
    int x = 1;
    int fd,who_fd;

    if ( ( fd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
	perror( "Init_socket: socket" );
	exit( 1 );
    }
    
if ( ( who_fd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
	perror( "Init_who_socket: socket" );
	exit( 1 );
    }

    if ( setsockopt( fd, SOL_SOCKET, SO_REUSEADDR,
    (char *) &x, sizeof(x) ) < 0 )
    {
	perror( "Init_socket: SO_REUSEADDR" );
	close(fd);
	close(who_fd);
	exit( 1 );
    }

#if defined(SO_DONTLINGER) && !defined(SYSV)
    {
	struct	linger	ld;

	ld.l_onoff  = 1;
	ld.l_linger = 1000;

	if ( setsockopt( fd, SOL_SOCKET, SO_DONTLINGER,
	(char *) &ld, sizeof(ld) ) < 0 )
	{
	    perror( "Init_socket: SO_DONTLINGER" );
	    close(fd);
	    exit( 1 );
	}
    }
#endif

    sa		    = sa_zero;
    sa.sin_family   = AF_INET;
    sa.sin_port	    = htons( port );

    if ( bind( fd, (struct sockaddr *) &sa, sizeof(sa) ) < 0 )
    {
	perror("Init socket: bind" );
	close(fd);
	        close(who_fd);
	exit(1);
    }
  
    who_sa                  = sa_zero;
    who_sa.sin_family       = AF_INET;   
    who_sa.sin_port         = htons( who_port );

if ( bind(who_fd, (struct sockaddr *) &who_sa, sizeof(who_sa) ) < 0 )
    {
        perror("Init who socket: bind(already in use)" );
        close(who_fd);
    }
               
   
        


    if ( listen( fd, 3 ) < 0 )
    {
	perror("Init socket: listen");
	        close(who_fd);
	close(fd);
	exit(1);
    }

    
      if ( listen( who_fd, 3 ) < 0 )
    {   
        perror("Init who socket: listen");
        close(who_fd);
        exit(1);
    }
    who_socket=who_fd;
    fcntl(who_fd,F_SETFL,O_NONBLOCK);
    return fd;

return fd;
}
#endif



#if defined(macintosh) || defined(MSDOS)
void game_loop_mac_msdos( void )
{
    struct timeval last_time;
    struct timeval now_time;
    static DESCRIPTOR_DATA dcon;

    gettimeofday( &last_time, NULL );
    current_time = (time_t) last_time.tv_sec;

    /*
     * New_descriptor analogue.
     */
    dcon.descriptor	= 0;
    dcon.connected	= CON_ANSI;
    dcon.host		= str_dup( "localhost" );
    dcon.outsize	= 2000;
    dcon.outbuf		= alloc_mem( dcon.outsize );
    dcon.next		= descriptor_list;
    dcon.showstr_head	= NULL;
    dcon.showstr_point	= NULL;
    dcon.pEdit         = NULL;                 /* OLC */
    dcon.pString       = NULL;                 /* OLC */
    dcon.editor                = 0;                    /* OLC */

    descriptor_list	= &dcon;

    /*
     * Send the greeting.
     */

    {
	extern char * help_greeting;
	if ( help_greeting[0] == '.' )
	    write_to_buffer( &dcon, help_greeting+1, 0 );
	else
	    write_to_buffer( &dcon, help_greeting  , 0 );
    }

    /* Main loop */
    while ( !merc_down )
    {
	DESCRIPTOR_DATA *d;

	/*
	 * Process input.
	 */
	for ( d = descriptor_list; d != NULL; d = d_next )
	{
	    d_next	= d->next;
	    d->fcommand	= FALSE;

#if defined(MSDOS)
	    if ( kbhit( ) )
#endif
	    {
		if ( d->character != NULL )
		    d->character->timer = 0;
		if ( !read_from_descriptor( d ) )
		{
		    if ( d->character != NULL && d->connected == CON_PLAYING)
			save_char_obj( d->character );
		    d->outtop	= 0;
		    close_socket( d );
		    continue;
		}
	    }

	    if (d->character != NULL && d->character->daze > 0)
		--d->character->daze;

	    if ( d->character != NULL && d->character->wait > 0 )
	    {
		--d->character->wait;
		continue;
	    }

	    read_from_buffer( d );
	    if ( d->incomm[0] != '\0' )
	    {
		d->fcommand	= TRUE;
		stop_idling( d->character );

               /* OLC */
               if ( d->showstr_point )
                   show_string( d, d->incomm );
               else
               if ( d->pString )
                   string_add( d->character, d->incomm );
               else
                   switch ( d->connected )
                   {
                       case CON_PLAYING:
                           if ( !run_olc_editor( d ) )
                               substitute_alias( d, d->incomm );
                           break;
                       default:
                           nanny( d, d->incomm );
                           break;
                   }


		d->incomm[0]	= '\0';
	    }
	}



	/*
	 * Autonomous game motion.
	 */
	update_handler( );



	/*
	 * Output.
	 */
	for ( d = descriptor_list; d != NULL; d = d_next )
	{
	    d_next = d->next;

	    if ( ( d->fcommand || d->outtop > 0 ) )
	    {
		if ( !process_output( d, TRUE ) )
		{
		    if ( d->character != NULL && d->connected == CON_PLAYING)
			save_char_obj( d->character );
		    d->outtop	= 0;
		    close_socket( d );
		}
	    }
	}



	/*
	 * Synchronize to a clock.
	 * Busy wait (blargh).
	 */
	now_time = last_time;
	for ( ; ; )
	{
	    int delta;

#if defined(MSDOS)
	    if ( kbhit( ) )
#endif
	    {
		if ( dcon.character != NULL )
		    dcon.character->timer = 0;
		if ( !read_from_descriptor( &dcon ) )
		{
		    if ( dcon.character != NULL && d->connected == CON_PLAYING)
			save_char_obj( d->character );
		    dcon.outtop	= 0;
		    close_socket( &dcon );
		}
#if defined(MSDOS)
		break;
#endif
	    }

	    gettimeofday( &now_time, NULL );
	    delta = ( now_time.tv_sec  - last_time.tv_sec  ) * 1000 * 1000
		  + ( now_time.tv_usec - last_time.tv_usec );
	    if ( delta >= 1000000 / PULSE_PER_SECOND )
		break;
	}
	last_time    = now_time;
	current_time = (time_t) last_time.tv_sec;
    }

    return;
}
#endif



#if defined(unix)
void game_loop_unix( int control )
{
    static struct timeval null_time;
    struct timeval last_time;
    int len,temp_fd;
     

    signal( SIGPIPE, SIG_IGN );
    gettimeofday( &last_time, NULL );
    current_time = (time_t) last_time.tv_sec;

  init_player_log(player_log,log_head);
  fread_apt();

    /* Main loop */
    while ( !merc_down )
    {
	fd_set in_set;
	fd_set out_set;
	fd_set exc_set;
	DESCRIPTOR_DATA *d;
	int maxdesc;

#if defined(MALLOC_DEBUG)
	if ( malloc_verify( ) != 1 )
	    abort( );
#endif

	/*
	 * Poll all active descriptors.
	 */
	FD_ZERO( &in_set  );
	FD_ZERO( &out_set );
	FD_ZERO( &exc_set );
	FD_SET( control, &in_set );
	maxdesc	= control;
	for ( d = descriptor_list; d; d = d->next )
	{
	    maxdesc = UMAX( maxdesc, d->descriptor );
	    FD_SET( d->descriptor, &in_set  );
	    FD_SET( d->descriptor, &out_set );
	    FD_SET( d->descriptor, &exc_set );
	}

	if ( select( maxdesc+1, &in_set, &out_set, &exc_set, &null_time ) < 0 )
	{
	    perror( "Game_loop: select: poll" );
	    exit( 1 );
	}

	/*
	 * New connection?
	 */
	if ( FD_ISSET( control, &in_set ) )
	    init_descriptor( control );

	/*
	 * Kick out the freaky folks.
	 */
	for ( d = descriptor_list; d != NULL; d = d_next )
	{
	    d_next = d->next;   
	    if ( FD_ISSET( d->descriptor, &exc_set ) )
	    {
		FD_CLR( d->descriptor, &in_set  );
		FD_CLR( d->descriptor, &out_set );
		if ( d->character && d->connected == CON_PLAYING)
		    save_char_obj( d->character );
		d->outtop	= 0;
		close_socket( d );
	    }
	}

	   /* Process Who Request */
       len=sizeof(who_sa);
       temp_fd=accept(who_socket,(struct sockaddr *) &who_sa,&len);

if(temp_fd!=-1){who_do_time(temp_fd);html_who(temp_fd,"");close(temp_fd);}
               

         /*
	 * Process input.
	 */
	for ( d = descriptor_list; d != NULL; d = d_next )
	{
	    d_next	= d->next;
	    d->fcommand	= FALSE;

	    if ( FD_ISSET( d->descriptor, &in_set ) )
	    {
		if ( d->character != NULL )
		    d->character->timer = 0;
		if ( !read_from_descriptor( d ) )
		{
		    FD_CLR( d->descriptor, &out_set );
		    if ( d->character != NULL && d->connected == CON_PLAYING)
			save_char_obj( d->character );
		    d->outtop	= 0;
		    close_socket( d );
		    continue;
		}
	    }

	    if (d->character != NULL && d->character->daze > 0)
		--d->character->daze;

	    if ( d->character != NULL && d->character->wait > 0 )
	    {
		--d->character->wait;
		continue;
	    }

	    read_from_buffer( d );
	    if ( d->incomm[0] != '\0' )
	    {
		d->fcommand	= TRUE;
		stop_idling( d->character );

       /* OLC */
       if ( d->showstr_point )
           show_string( d, d->incomm );
       else
       if ( d->pString )
           string_add( d->character, d->incomm );
       else
           switch ( d->connected )
           {
               case CON_PLAYING:
                   if ( !run_olc_editor( d ) )
                       substitute_alias( d, d->incomm );
                   break;
               default:
              
		    nanny( d, d->incomm );
  break;
}

		d->incomm[0]	= '\0';
	    }
	}



	/*
	 * Autonomous game motion.
	 */
	update_handler( );



	/*
	 * Output.
	 */
	for ( d = descriptor_list; d != NULL; d = d_next )
	{
	    d_next = d->next;

	    if ( ( d->fcommand || d->outtop > 0 )
	    &&   FD_ISSET(d->descriptor, &out_set) )
	    {
		if ( !process_output( d, TRUE ) )
		{
		    if ( d->character != NULL && d->connected == CON_PLAYING)
			save_char_obj( d->character );
		    d->outtop	= 0;
		    close_socket( d );
		}
	    }
	}



	/*
	 * Synchronize to a clock.
	 * Sleep( last_time + 1/PULSE_PER_SECOND - now ).
	 * Careful here of signed versus unsigned arithmetic.
	 */
	{
	    struct timeval now_time;
	    long secDelta;
	    long usecDelta;

	    gettimeofday( &now_time, NULL );
	    usecDelta	= ((int) last_time.tv_usec) - ((int) now_time.tv_usec)
			+ 1000000 / PULSE_PER_SECOND;
	    secDelta	= ((int) last_time.tv_sec ) - ((int) now_time.tv_sec );
	    while ( usecDelta < 0 )
	    {
		usecDelta += 1000000;
		secDelta  -= 1;
	    }

	    while ( usecDelta >= 1000000 )
	    {
		usecDelta -= 1000000;
		secDelta  += 1;
	    }

	    if ( secDelta > 0 || ( secDelta == 0 && usecDelta > 0 ) )
	    {
		struct timeval stall_time;

		stall_time.tv_usec = usecDelta;
		stall_time.tv_sec  = secDelta;
		if ( select( 0, NULL, NULL, NULL, &stall_time ) < 0 )
		{
		    perror( "Game_loop: select: stall" );
		    exit( 1 );
		}
	    }
	}

	gettimeofday( &last_time, NULL );
	current_time = (time_t) last_time.tv_sec;
    }
    
    fwrite_apt();
    return;
}
#endif



#if defined(unix)
void init_descriptor( int control )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *dnew;
    struct sockaddr_in sock;
    struct hostent *from;
    int desc;
    int size;

    size = sizeof(sock);
    getsockname( control, (struct sockaddr *) &sock, &size );
    if ( ( desc = accept( control, (struct sockaddr *) &sock, &size) ) <0)
    {
	perror( "New_descriptor: accept" );
	return;
    }

#if !defined(FNDELAY)
#define FNDELAY O_NDELAY
#endif

    if ( fcntl( desc, F_SETFL, FNDELAY ) == -1 )
    {
	perror( "New_descriptor: fcntl: FNDELAY" );
	return;
    }

    /*
     * Cons a new descriptor.
     */
    dnew = new_descriptor();

    dnew->descriptor	= desc;
    dnew->connected	= CON_ANSI;
    dnew->showstr_head	= NULL;
    dnew->showstr_point = NULL;
    dnew->outsize	= 2000;
    dnew->pEdit                = NULL;                 /* OLC */
    dnew->pString      = NULL;                 /* OLC */
    dnew->editor       = 0;                    /* OLC */
    dnew->outbuf	= alloc_mem( dnew->outsize );

    size = sizeof(sock);
    if ( getpeername( desc, (struct sockaddr *) &sock, &size ) < 0 )
    {
	perror( "New_descriptor: getpeername" );
	dnew->host = str_dup( "(unknown)" );
    }
    else
    {
	/*
	 * Would be nice to use inet_ntoa here but it takes a struct arg,
	 * which ain't very compatible between gcc and system libraries.
	 */
	int addr;

	addr = ntohl( sock.sin_addr.s_addr );
	sprintf( buf, "%d.%d.%d.%d",
	    ( addr >> 24 ) & 0xFF, ( addr >> 16 ) & 0xFF,
	    ( addr >>  8 ) & 0xFF, ( addr       ) & 0xFF
	    );
	sprintf( log_buf, "Sock.sinaddr:  %s", buf );
	log_string( log_buf );
	from = gethostbyaddr( (char *) &sock.sin_addr,
	    sizeof(sock.sin_addr), AF_INET );
	dnew->host = str_dup( from ? from->h_name : buf );
    }
	
    /*
     * Swiftest: I added the following to ban sites.  I don't
     * endorse banning of sites, but Copper has few descriptors now
     * and some people from certain sites keep abusing access by
     * using automated 'autodialers' and leaving connections hanging.
     *
     * Furey: added suffix check by request of Nickel of HiddenWorlds.
     */
    if ( check_ban(dnew->host,BAN_ALL))
    {
	write_to_descriptor( desc,
	    "Your site has been banned from this mud.\n\r", 0 );
	close( desc );
	free_descriptor(dnew);
	return;
    }
    /*
     * Init descriptor data.
     */
    dnew->next			= descriptor_list;
    descriptor_list		= dnew;

    /*
     * Send the greeting.
     */
    
{
write_to_buffer( dnew, "\n\rDo you want ANSI color [Y/N]?",0);
return;
}
}
#endif



void close_socket( DESCRIPTOR_DATA *dclose )
{
    CHAR_DATA *ch;

    if ( dclose->outtop > 0 )
	process_output( dclose, FALSE );

    if ( dclose->snoop_by != NULL )
    {
	write_to_buffer( dclose->snoop_by,
	    "Your victim has left the game.\n\r", 0 );
    }

    {
	DESCRIPTOR_DATA *d;

	for ( d = descriptor_list; d != NULL; d = d->next )
	{
	    if ( d->snoop_by == dclose )
		d->snoop_by = NULL;
	}
    }

    if ( ( ch = dclose->character ) != NULL )
    {
	sprintf( log_buf, "Closing link to %s.", ch->name );
	log_string( log_buf );
	/* cut down on wiznet spam when rebooting */
	if ( dclose->connected == CON_PLAYING && !merc_down)
	{
	    act( "$n has lost $s link.", ch, NULL, NULL, TO_ROOM );
	    wiznet("Net death has claimed $N.",ch,NULL,WIZ_LINKS,0,0);
	    ch->desc = NULL;
	}
	else
	{
	    free_char(dclose->original ? dclose->original : 
		dclose->character );
	}
    }

    if ( d_next == dclose )
	d_next = d_next->next;   

    if ( dclose == descriptor_list )
    {
	descriptor_list = descriptor_list->next;
    }
    else
    {
	DESCRIPTOR_DATA *d;

	for ( d = descriptor_list; d && d->next != dclose; d = d->next )
	    ;
	if ( d != NULL )
	    d->next = dclose->next;
	else
	    bug( "Close_socket: dclose not found.", 0 );
    }

    close( dclose->descriptor );
    free_descriptor(dclose);
#if defined(MSDOS) || defined(macintosh)
    exit(1);
#endif
    return;
}



bool read_from_descriptor( DESCRIPTOR_DATA *d )
{
    int iStart;

    /* Hold horses if pending command already. */
    if ( d->incomm[0] != '\0' )
	return TRUE;

    /* Check for overflow. */
    iStart = strlen(d->inbuf);
    if ( iStart >= sizeof(d->inbuf) - 10 )
    {
	sprintf( log_buf, "%s input overflow!", d->host );
	log_string( log_buf );
	write_to_descriptor( d->descriptor,
	    "\n\r*** PUT A LID ON IT!!! ***\n\r", 0 );
	return FALSE;
    }

    /* Snarf input. */
#if defined(macintosh)
    for ( ; ; )
    {
	int c;
	c = getc( stdin );
	if ( c == '\0' || c == EOF )
	    break;
	putc( c, stdout );
	if ( c == '\r' )
	    putc( '\n', stdout );
	d->inbuf[iStart++] = c;
	if ( iStart > sizeof(d->inbuf) - 10 )
	    break;
    }
#endif

#if defined(MSDOS) || defined(unix)
    for ( ; ; )
    {
	int nRead;

	nRead = read( d->descriptor, d->inbuf + iStart,
	    sizeof(d->inbuf) - 10 - iStart );
	if ( nRead > 0 )
	{
	    iStart += nRead;
	    if ( d->inbuf[iStart-1] == '\n' || d->inbuf[iStart-1] == '\r' )
		break;
	}
	else if ( nRead == 0 )
	{
	    log_string( "EOF encountered on read." );
	    return FALSE;
	}
	else if ( errno == EWOULDBLOCK )
	    break;
	else
	{
	    perror( "Read_from_descriptor" );
	    return FALSE;
	}
    }
#endif

    d->inbuf[iStart] = '\0';
    return TRUE;
}



/*
 * Transfer one line from input buffer to input line.
 */
void read_from_buffer( DESCRIPTOR_DATA *d )
{
    int i, j, k;

    /*
     * Hold horses if pending command already.
     */
    if ( d->incomm[0] != '\0' )
	return;

    /*
     * Look for at least one new line.
     */
    for ( i = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r'; i++ )
    {
	if ( d->inbuf[i] == '\0' )
	    return;
    }

    /*
     * Canonical input processing.
     */
    for ( i = 0, k = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r'; i++ )
    {
	if ( k >= MAX_INPUT_LENGTH - 2 )
	{
	    write_to_descriptor( d->descriptor, "Line too long.\n\r", 0 );

	    /* skip the rest of the line */
	    for ( ; d->inbuf[i] != '\0'; i++ )
	    {
		if ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
		    break;
	    }
	    d->inbuf[i]   = '\n';
	    d->inbuf[i+1] = '\0';
	    break;
	}

	if ( d->inbuf[i] == '\b' && k > 0 )
	    --k;
	else if ( isascii(d->inbuf[i]) && isprint(d->inbuf[i]) )
	    d->incomm[k++] = d->inbuf[i];
    }

    /*
     * Finish off the line.
     */
    if ( k == 0 )
	d->incomm[k++] = ' ';
    d->incomm[k] = '\0';

    /*
     * Deal with bozos with #repeat 1000 ...
     */

    if ( k > 1 || d->incomm[0] == '!' )
    {
    	if ( d->incomm[0] != '!' && strcmp( d->incomm, d->inlast ) )
	{
	    d->repeat = 0;
	}
	else
	{
	    if (++d->repeat >= 25 && d->character
	    &&  d->connected == CON_PLAYING)
	    {
		sprintf( log_buf, "%s input spamming!", d->host );
		log_string( log_buf );
		wiznet("Spam spam spam $N spam spam spam spam spam!",
		       d->character,NULL,WIZ_SPAM,0,get_trust(d->character));
		if (d->incomm[0] == '!')
		    wiznet(d->inlast,d->character,NULL,WIZ_SPAM,0,
			get_trust(d->character));
		else
		    wiznet(d->incomm,d->character,NULL,WIZ_SPAM,0,
			get_trust(d->character));

		d->repeat = 0;
/*
		write_to_descriptor( d->descriptor,
		    "\n\r*** PUT A LID ON IT!!! ***\n\r", 0 );
		strcpy( d->incomm, "quit" );
*/
	    }
	}
    }


    /*
     * Do '!' substitution.
     */
    if ( d->incomm[0] == '!' )
	strcpy( d->incomm, d->inlast );
    else
	strcpy( d->inlast, d->incomm );

    /*
     * Shift the input buffer.
     */
    while ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
	i++;
    for ( j = 0; ( d->inbuf[j] = d->inbuf[i+j] ) != '\0'; j++ )
	;
    return;
}



/*
 * Low level output function.
 */
bool process_output( DESCRIPTOR_DATA *d, bool fPrompt )
{
    extern bool merc_down;

    /*
     * Bust a prompt.
     */

    if ( !merc_down )
       if ( d->showstr_point )
           write_to_buffer( d, "[Hit Return to continue]\n\r", 0 );
       else if ( fPrompt && d->pString && d->connected == CON_PLAYING )
           write_to_buffer( d, "> ", 2 );
       else if ( fPrompt && d->connected == CON_PLAYING )
       {
           CHAR_DATA *ch;

	CHAR_DATA *victim;

	ch = d->character;

        /* battle prompt */
        if ((victim = ch->fighting) != NULL && can_see(ch,victim))
        {
            int percent;
            char wound[100];
	    char *pbuff;
	    char buf[MAX_STRING_LENGTH];
	    char buffer[MAX_STRING_LENGTH*2];
 
            if (victim->max_hit > 0)
                percent = victim->hit * 100 / victim->max_hit;
            else
                percent = -1;
 
            if (percent >= 100)
                sprintf(wound,"is strong and healthy.");
            else if (percent >= 90)
                sprintf(wound,"has a few knicks.");
            else if (percent >= 75)
                sprintf(wound,"is looking a bit bloody.");
            else if (percent >= 50)
                sprintf(wound,"has quite a few wounds.");
            else if (percent >= 30)
                sprintf(wound,"is gushing blood profusely.");
            else if (percent >= 15)
                sprintf(wound,"is leaking its entrails.");
            else if (percent >= 0)
                sprintf(wound,"is about to die.");
            else
                sprintf(wound,"is bleeding to death.");
 
            sprintf(buf,"%s %s \n\r", 
	            IS_NPC(victim) ? victim->short_descr : victim->name,wound);
	    buf[0]	= UPPER( buf[0] );
	    pbuff	= buffer;
	    colourconv( pbuff, buf, d->character );
            write_to_buffer( d, buffer, 0);
        }


	ch = d->original ? d->original : d->character;
	if (!IS_SET(ch->comm, COMM_COMPACT) )
	    write_to_buffer( d, "\n\r", 2 );


        if ( IS_SET(ch->comm, COMM_PROMPT) )
            bust_a_prompt( d->character );

	if (IS_SET(ch->comm,COMM_TELNET_GA))
	    write_to_buffer(d,go_ahead_str,0);
    }

    /*
     * Short-circuit if nothing to write.
     */
    if ( d->outtop == 0 )
	return TRUE;

    /*
     * Snoop-o-rama.
     */
    if ( d->snoop_by != NULL )
    {
	if (d->character != NULL)
	    write_to_buffer( d->snoop_by, d->character->name,0);
	write_to_buffer( d->snoop_by, "> ", 2 );
	write_to_buffer( d->snoop_by, d->outbuf, d->outtop );
    }

    /*
     * OS-dependent output.
     */
    if ( !write_to_descriptor( d->descriptor, d->outbuf, d->outtop ) )
    {
	d->outtop = 0;
	return FALSE;
    }
    else
    {
	d->outtop = 0;
	return TRUE;
    }
}

/*
 * Bust a prompt (player settable prompt)
 * coded by Morgenes for Aldara Mud
 */

void bust_a_prompt( CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    char buf2[MAX_STRING_LENGTH];
    const char *str;
    const char *i;
    char *point;
    char *pbuff;
    char buffer[ MAX_STRING_LENGTH*2 ];
    char doors[MAX_INPUT_LENGTH];
    EXIT_DATA *pexit;
    bool found;
    const char *dir_name[] = {"N","E","S","W","U","D"};
    int door;
    int prcnt;
    int to_level;
 
    point = buf;
    str = ch->prompt;
    if( !str || str[0] == '\0')
    {
	prcnt = ch->hit / ch->max_hit;
sprintf( buf, "{b-{Y%d{Whp {Y%d{Wm {Y%d{Wmv{b-{x %s",
	    prcnt, ch->mana, ch->move, ch->prefix );
	send_to_char( buf, ch );
	return;
    }

   if (IS_SET(ch->comm,COMM_AFK))
   {
	send_to_char("<AFK> ",ch);
	return;
   }

   while( *str != '\0' )
   {
      if( *str != '%' )
      {
         *point++ = *str++;
         continue;
      }
      ++str;
      switch( *str )
      {
         default :
            i = " "; break;
	case 'e':
	    found = FALSE;
	    doors[0] = '\0';
	    for (door = 0; door < 6; door++)
	    {
		if ((pexit = ch->in_room->exit[door]) != NULL
		&&  pexit ->u1.to_room != NULL
		&&  (can_see_room(ch,pexit->u1.to_room)
		||   (IS_AFFECTED(ch,AFF_INFRARED) 
		&&    !IS_AFFECTED(ch,AFF_BLIND)))
		&&  !IS_SET(pexit->exit_info,EX_CLOSED))
		{
		    found = TRUE;
		    strcat(doors,dir_name[door]);
		}
	    }
	    if (!found)
	 	strcat(buf,"none");
	    sprintf(buf2,"%s",doors);
	    i = buf2; break;
 	 case 'c' :
	    sprintf(buf2,"%s","\n\r");
	    i = buf2; break;
         case 'h' :
            sprintf( buf2, "%d", ch->hit );
            i = buf2; break;
         case 'H' :
            sprintf( buf2, "%d", ch->max_hit );
            i = buf2; break;
         case 'P' :
            sprintf(buf2,"%.0f",((float)ch->hit/(float)ch->max_hit)*100.00 );
            i = buf2; break;
         case 'p' :
	sprintf(buf2,"%.0f",((float)ch->mana/(float)ch->max_mana)*100.00 );
            i = buf2; break;
         case 'b' :
 	sprintf(buf2,"%.0f",((float)ch->move/(float)ch->max_move)*100.00 );
            i = buf2; break;
         case 'm' :
            sprintf( buf2, "%d", ch->mana );
            i = buf2; break;
         case 'M' :
            sprintf( buf2, "%d", ch->max_mana );
            i = buf2; break;
         case 'v' :
            sprintf( buf2, "%d", ch->move );
            i = buf2; break;
         case 'V' :
            sprintf( buf2, "%d", ch->max_move );
            i = buf2; break;
         case 'x' :
            sprintf( buf2, "%d", ch->exp );
            i = buf2; break;
	 case 'X' :
            to_level = exp_per_level(ch,ch->pcdata->points);
	    sprintf(buf2, "%d", IS_NPC(ch) ? 0 :
            ((ch->level+1)*to_level-ch->exp));
	    i = buf2; break;
         case 'g' :
            sprintf( buf2, "%ld", ch->gold);
            i = buf2; break;
	 case 's' :
	    sprintf( buf2, "%ld", ch->silver);
	    i = buf2; break;
         case 'a' :
            if( ch->level > 9 )
               sprintf( buf2, "%d", ch->alignment );
            else
               sprintf( buf2, "%s", IS_GOOD(ch) ? "good" : IS_EVIL(ch) ?
                "evil" : "neutral" );
            i = buf2; break;
         case 'r' :
            if( ch->in_room != NULL )
               sprintf( buf2, "%s", 
		((!IS_NPC(ch) && IS_SET(ch->act,PLR_HOLYLIGHT)) ||
		 (!IS_AFFECTED(ch,AFF_BLIND) && !room_is_dark( ch->in_room )))
		? ch->in_room->name : "darkness");
            else
               sprintf( buf2, " " );
            i = buf2; break;
         case 'R' :
            if( IS_IMMORTAL( ch ) && ch->in_room != NULL )
               sprintf( buf2, "%d", ch->in_room->vnum );
            else
               sprintf( buf2, " " );
            i = buf2; break;
         case 'z' :
            if( IS_IMMORTAL( ch ) && ch->in_room != NULL )
               sprintf( buf2, "%s", ch->in_room->area->name );
            else
               sprintf( buf2, " " );
            i = buf2; break;
         case '%' :
            sprintf( buf2, "%%" );
            i = buf2; break;
         case 'o' :
            sprintf( buf2, "%s", olc_ed_name(ch) );
            i = buf2; break;
        case 'O' :
           sprintf( buf2, "%s", olc_ed_vnum(ch) );
           i = buf2; break;


      }
      ++str;
      while( (*point = *i) != '\0' )
         ++point, ++i;
   }
   *point	= '\0';
   pbuff	= buffer;
   colourconv( pbuff, buf, ch );
   write_to_buffer( ch->desc, buffer, 0 );

   if (ch->prefix[0] != '\0')
        write_to_buffer(ch->desc,ch->prefix,0);
   return;
}



/*
 * Append onto an output buffer.
 */
void write_to_buffer( DESCRIPTOR_DATA *d, const char *txt, int length )
{
    /*
     * Find length in case caller didn't.
     */
    if ( length <= 0 )
	length = strlen(txt);

    /*
     * Initial \n\r if needed.
     */
    if ( d->outtop == 0 && !d->fcommand )
    {
	d->outbuf[0]	= '\n';
	d->outbuf[1]	= '\r';
	d->outtop	= 2;
    }

    /*
     * Expand the buffer as needed.
     */
    while ( d->outtop + length >= d->outsize )
    {
	char *outbuf;

        if (d->outsize >= 32000)
	{
	    bug("Buffer overflow. Closing.\n\r",0);
	    close_socket(d);
	    return;
 	}
	outbuf      = alloc_mem( 2 * d->outsize );
	strncpy( outbuf, d->outbuf, d->outtop );
	free_mem( d->outbuf, d->outsize );
	d->outbuf   = outbuf;
	d->outsize *= 2;
    }

    /*
     * Copy.
     */
/*  strcpy( d->outbuf + d->outtop, txt ); */
    strncpy( d->outbuf + d->outtop, txt, length );
    d->outtop += length;
    return;
}



/*
 * Lowest level output function.
 * Write a block of text to the file descriptor.
 * If this gives errors on very long blocks (like 'ofind all'),
 *   try lowering the max block size.
 */

bool write_to_descriptor( int desc, char *txt, int length )
{
    int iStart;
    int nWrite;
    int nBlock;

#if defined(macintosh) || defined(MSDOS)
    if ( desc == 0 )
	desc = 1;
#endif

    if ( length <= 0 )
	length = strlen(txt);

    for ( iStart = 0; iStart < length; iStart += nWrite )
    {
	nBlock = UMIN( length - iStart, 4096 );
	if ( ( nWrite = write( desc, txt + iStart, nBlock ) ) < 0 )
	    { perror( "Write_to_descriptor" ); return FALSE; }
    } 

    return TRUE;
}



/*
 * Deal with sockets that haven't logged in yet.
 */

void nanny( DESCRIPTOR_DATA *d, char *argument )
{
    DESCRIPTOR_DATA *d_old, *d_next;
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *ch;
    char *pwdnew;
    char *p;
//    int htown,iClass,
    int race,i,weapon;
    bool fOld;
    race=0;
    while ( isspace(*argument) )
	argument++;

    ch = d->character;

    switch ( d->connected )
    {

    default:
	bug( "Nanny: bad d->connected %d.", d->connected );
	close_socket( d );
	return;


    case CON_ANSI:


	if ( argument[0] == '\0' || UPPER(argument[0]) == 'Y' )
	{
	d->ansi = TRUE;
	write_to_buffer(d,"\n\r
\033[31mA\033[32mn\033[33ms\033[34mi\033[37m Enabled!\n\r",0);
	d->connected = CON_MENU;

	{
	extern char * help_greeting;
	if ( help_greeting[0] == '.' )
	write_to_buffer(d, help_greeting+1, 0);
	else
	write_to_buffer(d, help_greeting , 0);
	}
	break;
        }

	if (UPPER(argument[0]) == 'N')
	{
	d->ansi = FALSE;   
	write_to_buffer(d,"\n\rAnsi disabled!\n\r",0);
	d->connected = CON_MENU;

	{
	extern char * help_greeting;
	if ( help_greeting[0] == '.' )
	write_to_buffer(d, help_greeting+1, 0);
	else
	write_to_buffer(d, help_greeting , 0);
        }
	break;
	}

	else
	{

	write_to_buffer(d,"\n\rDo you want ANSI color? [Y/N] ",0);
	return;
	}

    case CON_GET_NAME:

	if ( argument[0] == '\0' )
	{
	    close_socket( d );
	    return;
	}


argument[0] = UPPER(argument[0]);
	if ( !check_parse_name( argument ) )
	{
	    write_to_buffer( d, "Illegal name, try another.\n\rName: ", 0 );
	    return;
	}

	fOld = load_char_obj( d, argument );
	ch   = d->character;

	if (IS_SET(ch->act, PLR_DENY))
	{
	    sprintf( log_buf, "Denying access to %s@%s.", argument, d->host );
	    log_string( log_buf );
	    write_to_buffer( d, "You are denied access.\n\r", 0 );
	    close_socket( d );
	    return;
	}

	if (check_ban(d->host,BAN_PERMIT) && !IS_SET(ch->act,PLR_PERMIT))
	{
	    write_to_buffer(d,"Your site has been banned from this mud.\n\r",0);
	    close_socket(d);
	    return;
	}

	if ( check_reconnect( d, argument, FALSE ) )
	{
	    fOld = TRUE;
	}
	else
	{
	    if ( wizlock && !IS_IMMORTAL(ch)) 
	    {
		write_to_buffer( d, "The game is wizlocked.\n\r", 0 );
		close_socket( d );
		return;
	    }
	}

	if ( fOld )
	{
	    /* Old player */
	    write_to_buffer( d, "\033[34mPassword\033[37m: ", 0 );
	    write_to_buffer( d, echo_off_str, 0 );
	    d->connected = CON_GET_OLD_PASSWORD;
	    return;
	}
	else
	{
	    /* New player */
 	    if (newlock)
	    {
                write_to_buffer( d, "The game is newlocked.\n\r", 0 );
                close_socket( d );
                return;
            }

	    if (check_ban(d->host,BAN_NEWBIES))
	    {
		write_to_buffer(d,
		    "New players are not allowed from your site.\n\r",0);
		close_socket(d);
		return;
	    }
	
	    sprintf( buf, "Are You Sure? %s (Y/N)? ", argument );
	    write_to_buffer( d, buf, 0 );
	    d->connected = CON_CONFIRM_NEW_NAME;
	    return;
	}
	break;

    case CON_GET_OLD_PASSWORD:
#if defined(unix)
	write_to_buffer( d, "\n\r", 2 );
#endif

	if ( strcmp( crypt( argument, ch->pcdata->pwd ), ch->pcdata->pwd ))
	{
	    write_to_buffer( d, "Password is not right.\n\r", 0 );
	    close_socket( d );
	    return;
	}
 
	write_to_buffer( d, echo_on_str, 0 );

	if (check_playing(d,ch->name))
	    return;

	if ( check_reconnect( d, ch->name, TRUE ) )
	    return;
     
	sprintf( log_buf, "%s@%s has connected.", ch->name, d->host );
        ch->log_name = log_buf;
	log_head = add_log_entry(ch,player_log,log_head);

	log_string( log_buf );
	wiznet(log_buf,NULL,NULL,WIZ_SITES,0,get_trust(ch));


        if (ch->desc->ansi)
	SET_BIT(ch->act, PLR_COLOUR);
	else REMOVE_BIT(ch->act, PLR_COLOUR);


	if ( IS_IMMORTAL(ch) )
	{
	   sprintf(buf,"\n\r\n\r{bWelcome {Y%s{x@{Y%s{x!\n\r",
		   ch->name,
		   d->host);
	send_to_char( buf,ch );

            write_to_buffer(d,"\n\r-[ HIT RETURN ]-",0);

	    d->connected = CON_READ_IMOTD;
        }
	
        else
	{
  sprintf(buf,"\n\r{bWelcome {Y%s{x@{Y%s{x!\n\r",
		   ch->name,
		   d->host);
	send_to_char( buf,ch );

            write_to_buffer(d,"\n\r-[ HIT RETURN ]-",0);

	    d->connected = CON_READ_MOTD;
	}
	break;



    case CON_MENU:

        if ( argument[0] == '\0' || UPPER(argument[0]) == 'E' )
	{
        write_to_buffer(d,"\n\r\033[34mEnter Your Name\033[37m :",0);
        d->connected = CON_GET_NAME;
	break;
        }
     

        if ( argument[0] == 'C' || 'c' )
	{
        write_to_buffer(d,"\n\r\033[34mEnter Your Name\033[37m :",0);
        d->connected = CON_GET_NAME;
	break;
        }

        if ( argument[0] == 'F'|| 'f' )
	{
	write_to_buffer(d,"\n\rLeaving Already.....",0);
        close_socket(d);
        break;
	}


/* RT code for breaking link */
 
    case CON_BREAK_CONNECT:
	switch( *argument )
	{
	case 'y' : case 'Y':
            for ( d_old = descriptor_list; d_old != NULL; d_old = d_next )
	    {
		d_next = d_old->next;
		if (d_old == d || d_old->character == NULL)
		    continue;

		if (str_cmp(ch->name,d_old->original ?
		    d_old->original->name : d_old->character->name))
		    continue;

		close_socket(d_old);
	    }
	    if (check_reconnect(d,ch->name,TRUE))
	    	return;
	    write_to_buffer(d,"Reconnect attempt failed.\n\rName: ",0);
            if ( d->character != NULL )
            {
                free_char( d->character );
                d->character = NULL;
            }
	    d->connected = CON_GET_NAME;
	    break;

	case 'n' : case 'N':
	    write_to_buffer(d,"Name: ",0);
            if ( d->character != NULL )
            {
                free_char( d->character );
                d->character = NULL;
            }
	    d->connected = CON_GET_NAME;
	    break;

	default:
	    write_to_buffer(d,"Please type Y or N? ",0);
	    break;
	}
	break;

    case CON_CONFIRM_NEW_NAME:
	switch ( *argument )
	{	
	case 'y': case 'Y':
        write_to_buffer(d,"\n\rIs This Name In the dictionary (Y/N)?",0);
	d->connected = CON_CONFIRM_NAME;
        break;

	case 'n': case 'N':
	    write_to_buffer( d, "What is it, then: ", 0 );
	    free_char( d->character );
	    d->character = NULL;
	    d->connected = CON_GET_NAME;
	    break;

	default:
	    write_to_buffer( d, "Please type Yes or No? ", 0 );
	    break;
	}
	break;
    

    case CON_CONFIRM_NAME:
	switch ( *argument )
	{
	
	case 'y': case 'Y':
        send_to_char("\n\rYou CANNOT use a dictionary word!",ch);
        close_socket(d);
        break;

	case 'n': case 'N':
 	
	write_to_buffer(d,"\n\r Checking the Dictionary...\n\r",0);
	sprintf(buf,"grep -ix %s bad.names > /dev/null",ch->name);
	printf("Checking dictionary using command [%s]\n\r",buf);
	if(0==system(buf)) {
	write_to_buffer(d,"\n\r This name is in my dictionary!",0);
			close_socket(d); break;}
          
write_to_buffer(d,
"\n\rIs this name in a book or movie? Is this name considered
vulgar or profane? Is this name a combination of two dictionary
words, possibly spelled oddly (Y/N)? ",0);
        d->connected = CON_CONFIRM_NAME2;
        break;

	default:
	    write_to_buffer( d, "Please type Yes or No? ", 0 );
	    break;
	}
	break;

  case CON_CONFIRM_NAME2:
	switch ( *argument )
	{
	case 'y': case 'Y':
        send_to_char("\n\rYou CANNOT use that name!",ch);
        close_socket(d);
        break;

	case 'n': case 'N':
            
        write_to_buffer(d,
        "\n\rAre you sure this name is acceptable (Y/N)? ",0);
        d->connected = CON_CONFIRM_NAME3;
        break;

	default:
	    write_to_buffer( d, "Please type Yes or No? ", 0 );
	    break;
	}
	break;

  case CON_CONFIRM_NAME3:
	switch ( *argument )
	{
	case 'y': case 'Y':

            sprintf( buf, "\n\rPassword for %s: %s", ch->name,
            echo_off_str );
	    write_to_buffer( d, buf, 0 );
	    d->connected = CON_GET_NEW_PASSWORD;
	    break;

	case 'n': case 'N':
        send_to_char("\n\rYou CANNOT use that name!",ch);
        close_socket(d);
        break;
            
	default:
	    write_to_buffer( d, "Please type Yes or No? ", 0 );
	    break;
	}
	break;

    case CON_GET_NEW_PASSWORD:
#if defined(unix)
	write_to_buffer( d, "\n\r", 2 );
#endif

	if ( strlen(argument) < 5 )
	{
	    write_to_buffer( d,
		"That is too short.\n\rPWD-> ",
		0 );
	    return;
	}

	pwdnew = crypt( argument, ch->name );
	for ( p = pwdnew; *p != '\0'; p++ )
	{
	    if ( *p == '~' )
	    {
		write_to_buffer( d,
		    "I Dont Think SO, try again.\n\rPWD-> ",
		    0 );
		return;
	    }
	}

	free_string( ch->pcdata->pwd );
	ch->pcdata->pwd	= str_dup( pwdnew );
	write_to_buffer( d, "Restate your password: ", 0 );
	d->connected = CON_CONFIRM_NEW_PASSWORD;
	break;

    case CON_CONFIRM_NEW_PASSWORD:
#if defined(unix)
	write_to_buffer( d, "\n\r", 2 );
#endif

	if ( strcmp( crypt( argument, ch->pcdata->pwd ), ch->pcdata->pwd ) )
	{
	    write_to_buffer( d, "Passwords don't match.\n\rRetype password: ",
		0 );
	    d->connected = CON_GET_NEW_PASSWORD;
	    return;
	}
/*
write_to_buffer(d, echo_on_str, 0 );
write_to_buffer(d,"\n\rYou may be good, neutral or evil.\n\r",0);
write_to_buffer(d,"
Alignment is the way your character should act.\n\r",0);
write_to_buffer(d,"Which alignment (G/N/E)?",0);
*/

send_to_char("\n\r",ch);
send_to_char("Available races for first time players\n\r",ch);

send_to_char("=+=+=+=+=+=+=+=+=+=\n\r",ch);
send_to_char("Jezram   Kang    Sethuut\n\r\n\r",ch);
send_to_char("Races Needing Character Approval\n\r\n\r",ch);
send_to_char("Sylvan  Thstaar  Hobbit  Saurig  Nrsang\n\r",ch);
send_to_char("\n\r=+=+=+=+=+=+=+=+=+=\n\r",ch);

	write_to_buffer( d, echo_on_str, 0 );
	write_to_buffer(d,"\n\r",0);
	write_to_buffer(d,"What is your race (help for more information)? ",0);
	d->connected = CON_GET_NEW_RACE;
ch->alignment = 0;
break;

case CON_GET_ALIGNMENT:
/*
switch( argument[0])
{
case 'g' : case 'G' : ch->alignment = 750; break;
case 'n' : case 'N' : ch->alignment = 0; break;
case 'e' : case 'E' : ch->alignment = -750; break;
}
write_to_buffer(d,"\n\r",0);
*/
/*BEGIN DEITY*/
send_to_char("\n\r\n\r",ch);
do_help( ch, "wgf");
write_to_buffer( d, echo_on_str, 0 );
write_to_buffer(d,"The following spheres are available:\n\r",0);
send_to_char("\n\r",ch);
for ( god = 0; god < MAX_GOD; god++ )
{
if ((god_table[god].pc_evil && ch->alignment == -750)
||  (god_table[god].pc_neutral && ch->alignment == 0 )
||  (god_table[god].pc_good && ch->alignment == 750 ))
{
write_to_buffer(d,god_table[god].name,0);
write_to_buffer(d," ",1);
}
}
write_to_buffer(d,"\n\r",0);
send_to_char("\n\r",ch);
write_to_buffer(d,"What sphere do you follow?",0);
d->connected = CON_GET_GOD;
break;

case CON_GET_GOD:
one_argument(argument,arg);

if (!strcmp(arg,"help"))
{
argument = one_argument(argument,arg);
if (argument[0] == '\0')
do_help(ch,"wizlist");
else
do_help(ch,argument);
write_to_buffer(d,"What sphere do you follow?",0);
break;
}
god = god_lookup(argument);
if ( god == 0
|| (!god_table[god].pc_evil && ch->alignment == -750)
|| (!god_table[god].pc_neutral && ch->alignment == 0 )
|| (!god_table[god].pc_good && ch->alignment == 750 ))
{
write_to_buffer(d,"Thats not a valid sphere.\n\r",0);
write_to_buffer(d,"The following spheres are available:\n\r",0);

for ( god = 0; god < MAX_GOD; god++ )
{
if ((god_table[god].pc_evil && ch->alignment == -750)
||  (god_table[god].pc_neutral && ch->alignment == 0 )
||  (god_table[god].pc_good && ch->alignment == 750 ))
{
write_to_buffer(d,god_table[god].name,0);
write_to_buffer(d," ",1);
}
}
write_to_buffer(d,"\n\r",0);
write_to_buffer(d,"What sphere do you want to follow?",0);
break;
}

ch->god = god;
send_to_char("-[ HIT RETURN ]-\n\r",ch);
d->connected = CON_GET_PATH;
break;


    case CON_GET_NEW_RACE:
	one_argument(argument,arg);

	if (!strcmp(arg,"help"))
	{
	    argument = one_argument(argument,arg);
	    if (argument[0] == '\0')
		do_help(ch,"race help");
	    else
		do_help(ch,argument);
            write_to_buffer(d,
		"What is your race (help for more information)? ",0);
	    break;
  	}

	race = race_lookup(argument);

	if (race == 0 || !race_table[race].pc_race)
	{
	    write_to_buffer(d,"That is not a valid race.\n\r",0);
            write_to_buffer(d,"The following races are available:\n\r  ",0);
            for ( race = 1; race_table[race].name != NULL; race++ )
  
          {
            	if (!race_table[race].pc_race)
                    break;
            	write_to_buffer(d,race_table[race].name,0);
            	write_to_buffer(d," ",1);
            }

           write_to_buffer(d,"\n\r",0);
            write_to_buffer(d,
		"What is your race? (help for more information) ",0);
	    break;
	}

        ch->race = race;
        /* roll_stats */
roll:
    i = number_range(8, 20);
/*	for (i < MAX_STATS; i++)*/
/*	    ch->perm_stat[i] = pc_race_table[race].stats[i];*/


send_to_char("Choose Your Stats Wisely.\n\r",ch);
i = number_range(8, 20);
ch->perm_stat[STAT_STR] = i;
i = number_range(8, 20);
ch->perm_stat[STAT_INT] = i;
i = number_range(8, 20);
ch->perm_stat[STAT_WIS] = i;
i = number_range(8, 20);
ch->perm_stat[STAT_DEX] = i;
i = number_range(8, 20);
ch->perm_stat[STAT_CON] = i;

	ch->affected_by = ch->affected_by|race_table[race].aff;
	ch->imm_flags	= ch->imm_flags|race_table[race].imm;
	ch->res_flags	= ch->res_flags|race_table[race].res;
	ch->vuln_flags	= ch->vuln_flags|race_table[race].vuln;
	ch->form	= race_table[race].form;
	ch->parts	= race_table[race].parts;

   send_to_char( "\n\rStatistics Info.\n\r", ch);
   sprintf(buf, "\n\rSTR [%d] INT [%d] WIS [%d] DEX [%d] CON [%d]\n\r
Range 8-20 for non prime stats, you can train later\n\r",
        ch->perm_stat[STAT_STR],
        ch->perm_stat[STAT_INT],
        ch->perm_stat[STAT_WIS],
        ch->perm_stat[STAT_DEX],
        ch->perm_stat[STAT_CON] );
        send_to_char( buf, ch );
      
        write_to_buffer( d,"\n\rKeep These Stats? (Y/N)", 0);
        d->connected = CON_REROLL_STATS;      
        break;
        
        case CON_REROLL_STATS:
        switch ( argument [0] )
        {
        case 'y': case 'Y':
        break;
        case 'n': case 'N':                    
        goto roll;
        break;
        default:
        write_to_buffer( d, "Keep These Stats? (Y/N)\n\r",0);
        return;
        } 

        /* add skills */
	for (i = 0; i < 5; i++)
	{
	    if (pc_race_table[race].skills[i] == NULL)
	 	break;
	    group_add(ch,pc_race_table[race].skills[i],FALSE);
	}
	/* add cost */
	ch->pcdata->points = pc_race_table[race].points;
	ch->size = pc_race_table[race].size;

        write_to_buffer( d, "What is your sex (M/F)? ", 0 );
        d->connected = CON_GET_NEW_SEX;
        break;
        

    case CON_GET_NEW_SEX:
	switch ( argument[0] )
	{
	case 'm': case 'M': ch->sex = SEX_MALE;    
			    ch->pcdata->true_sex = SEX_MALE;
			    break;
	case 'f': case 'F': ch->sex = SEX_FEMALE; 
			    ch->pcdata->true_sex = SEX_FEMALE;
			    break;
	default:
	    write_to_buffer( d, "That's not a sex.\n\rWhat IS your sex? ", 0 );
	    return;
	}
	one_argument(argument,arg);
	
send_to_char("\n\r",ch);
send_to_char("{YUntil level 10 you will in the Adventurers Guild.\n\r",ch);
send_to_char("{b...........................................\n\r{x",ch);
send_to_char("\n\r{WType HELP GUILD for more information.\n\r",ch);
send_to_char("\n\r{b...............................................{x\n\r",ch);
/*

	strcpy( buf, "\n\r" );
	strcat( buf, "Select-> " );
	write_to_buffer( d, buf, 0 );
	
        d->connected = CON_GET_NEW_CLASS;
	break;

    case CON_GET_NEW_CLASS:
	iClass = class_lookup(argument);


if ( iClass == -1 )
	{
	    argument = one_argument(argument,arg);
	    if (argument[0] == '\0')
		do_help(ch,"class help");
	    else
		do_help(ch,argument);
            write_to_buffer(d,
                "What is your guild (help for more information)? ",0);
	    break;
  	}
*/
/*
        ch->class = iClass;
*/
ch->class = 0;

	sprintf( log_buf, "%s@%s new player.", ch->name, d->host );
	log_string( log_buf );
        wiznet("New Player  $N sighted.",ch,NULL,WIZ_NEWBIE,0,0);
        wiznet(log_buf,NULL,NULL,WIZ_SITES,0,get_trust(ch));
/*
write_to_buffer( d, "\n\r", 2 );
do_help( ch, "hometown" );
write_to_buffer( d,"\n\r{bPick A Starting Point.{Y\n\r",0);
write_to_buffer( d, "Calinth    
New Thalos
Ofcol     
Malathar
             
        write_to_buffer( d, "{bWhich one{W: ",0);
	d->connected = CON_GET_HOMETOWN;
	break;

case CON_GET_HOMETOWN:
      one_argument(argument,arg);
      if (!strcmp(arg,"help"))
      {
       argument = one_argument(argument, arg);
       if (argument[0] == '\0')
          do_help(ch, "hometown help");
       else
          do_help(ch, argument);
       write_to_buffer(d,"\n\rPick a hometown (or help)? ",0);
       break;
       }

       htown = hometown_lookup(argument);

       if(htown==-1)
       {
        write_to_buffer(d,"Thats not a town!\n\rPick a hometown -> ",0);
        return;
       }
     
       ch->hometown = htown;
       
       if(htown ==-1)
       {
        write_to_buffer(d,"Thats not a town!\n\rPick a hometown -> ",0);
        return;
       }
       ch->hometown = htown;
*/
	write_to_buffer(d,"\n\r",0);
        group_add(ch,"rom basics",FALSE);
        group_add(ch,class_table[ch->class].base_group,FALSE);
        group_add(ch,class_table[ch->class].default_group,FALSE);
        ch->pcdata->learned[gsn_recall] = 20;
	d->connected=CON_GET_ALIGNMENT;
	write_to_buffer(d,"[Hit Return]\n\r",0);
	break;

case CON_GET_SHORTY:
        if ( argument[0] == '\0' )
	{
	write_to_buffer(d,"You MUST enter a short description!\n\r",0);
	return;
	}
	ch->short_descr = argument;
	ch->short_descr = str_dup(argument);
	write_to_buffer(d,"\n\r",2);

send_to_char("\n\rYou must enter a long description now\n\r",ch);
send_to_char("Below is a good example of a long description\n\r",ch);
send_to_char("\n\rAn Elf of medium height, apparently in his fifties.\n\r",ch);
send_to_char("He has iron gray hair and craggy features. His eyes\n\r",ch);
send_to_char("are a deep green and seem to look through you. His\n\r",ch);
send_to_char("skin is a pale white and void of marks. His build is\n\r",ch);
send_to_char("muscular but slim.\n\r",ch);
send_to_char("\n\rDescriptions MUST be at least 5 lines in length!\n\r",ch);
send_to_char("\n\rMake what you entered for SHORT DESC match your\n\r",ch);
send_to_char("LONG DESC, no blue eyes there and black here!\n\r",ch);
send_to_char("\n\rLONG DESC MUST BE ALL PHYSICAL TRAITS, NO BACKGROUND!\n\r",ch);
send_to_char("\n\rEnter Long Desc Now: Hit Return After Ending:\n\r",ch);
string_edit(ch,&ch->description);
d->connected = CON_GET_LONGY;
break;

case CON_GET_LONGY:
/*
        if ( argument[0] == '\0' )
	{
	write_to_buffer(d,"You MUST enter a long description!\n\r",0);
	return;
	}
	ch->description = argument;
	ch->description = str_dup(argument);
	write_to_buffer(d,"\n\r",2);
*/

send_to_char("\n\rYou must enter a background now\n\r",ch);
send_to_char("Below is a good example of a background\n\r",ch);
send_to_char("DO NOT hit enter until you are done!!\n\r",ch);
send_to_char("\n\rEnter Background Now:\n\r",ch);
string_edit(ch,&ch->backy);
d->connected = CON_GET_BACKY;
break;


case CON_GET_BACKY:
/*
        if ( argument[0] == '\0' )
	{
	write_to_buffer(d,"You MUST enter a long description!\n\r",0);
	return;
	}

	ch->backy = argument;
	ch->backy = str_dup(argument);
	write_to_buffer(d,"\n\r",2);
*/
send_to_char("[HIT RETURN]\n\r",ch);

	    write_to_buffer(d,
		"Please pick a weapon from the following choices:\n\r",0);
	    buf[0] = '\0';
	    for ( i = 0; weapon_table[i].name != NULL; i++)
		if (ch->pcdata->learned[*weapon_table[i].gsn] > 0)
		{
		    strcat(buf,weapon_table[i].name);
		    strcat(buf," ");
		}
	    strcat(buf,"\n\rYour choice? ");
	    write_to_buffer(d,buf,0);
            d->connected = CON_PICK_WEAPON;
          break;

case CON_GET_PATH:
	write_to_buffer(d,"\n\r",2);
	write_to_buffer(d,
"Short descriptions are very important to game play. They should include 
information about your character that others would see. Do include
physical attributes, do not include clothing, items, or anything that is
not physical in nature. Use the following examples to make yours.

Short Descriptions
A tall, golden haired man.
A skinny, blue eyed woman.
A lithe elf, with brown hair.
A chubby dwarf with a facial scar.
A lanky drow, with black eyes.

Notice it is all physical in nature.
A bad short desc will get you deleted, if you need help
send up a pray after you login.

Please enter your short description:\n\r",0);
d->connected = CON_GET_SHORTY;
break;

    case CON_PICK_WEAPON:
	write_to_buffer(d,"\n\r",2);
	weapon = weapon_lookup(argument);
	if (weapon == -1 || ch->pcdata->learned[*weapon_table[weapon].gsn] <= 0)
	{
write_to_buffer(d,"That's not a valid selection. Choices are:\n\r",0);
            buf[0] = '\0';
            for ( i = 0; weapon_table[i].name != NULL; i++)
                if (ch->pcdata->learned[*weapon_table[i].gsn] > 0)
                {
                    strcat(buf,weapon_table[i].name);
		    strcat(buf," ");
                }
            strcat(buf,"\n\rYour choice? ");
            write_to_buffer(d,buf,0);
	    return;
	}

            SET_BIT(ch->act,PLR_CANLOOT);
            REMOVE_BIT(ch->act,PLR_NOSUMMON);
            SET_BIT(ch->act,PLR_AUTOEXIT);
            SET_BIT(ch->act,PLR_AUTOGOLD);
            SET_BIT(ch->act,PLR_AUTOLOOT);
            SET_BIT(ch->comm,COMM_SHOW_AFFECTS);
            do_help(ch,"NEWBIE INFO");


	if ( ch->level == 0 )
	{

	    ch->perm_stat[class_table[ch->class].attr_prime] += 2;

	    ch->level	= 1;
	    ch->exp	= exp_per_level(ch,ch->pcdata->points);
	    ch->hit	= ch->max_hit;
	    ch->mana	= ch->max_mana;
	    ch->move	= ch->max_move;
	    ch->train	 = 3;
	    ch->practice = 5;
            ch->silver   = 10;

	    sprintf( buf, "the %s",
		title_table [ch->class] [ch->level]
		[ch->sex == SEX_FEMALE ? 1 : 0] );
	    set_title( ch, buf );

	do_outfit(ch,"");
        obj_to_char(create_object(get_obj_index(OBJ_VNUM_MAP),0),ch);
	ch->pcdata->learned[*weapon_table[weapon].gsn] = 40;
	write_to_buffer(d,"\n\r",2);
        if(ch->desc->ansi)
	SET_BIT(ch->act, PLR_COLOUR);
	else REMOVE_BIT(ch->act, PLR_COLOUR);
	d->connected = CON_READ_MOTD;
	break;

    case CON_GEN_GROUPS:
	send_to_char("\n\r",ch);
       	if (!str_cmp(argument,"done"))
       	{
	    sprintf(buf,"Creation points: %d\n\r",ch->pcdata->points);
	    send_to_char(buf,ch);
	    sprintf(buf,"Experience per level: %d\n\r",
	            exp_per_level(ch,ch->gen_data->points_chosen));
	    if (ch->pcdata->points < 40)
		ch->train = (40 - ch->pcdata->points + 1) / 2;
	    free_gen_data(ch->gen_data);
	    ch->gen_data = NULL;
	    send_to_char(buf,ch);
            write_to_buffer( d, "\n\r", 2 );
            write_to_buffer(d,
                "Please pick a weapon from the following choices:\n\r",0);
            buf[0] = '\0';
            for ( i = 0; weapon_table[i].name != NULL; i++)
                if (ch->pcdata->learned[*weapon_table[i].gsn] > 0)
                {
                    strcat(buf,weapon_table[i].name);
		    strcat(buf," ");
                }
            strcat(buf,"\n\rYour choice? ");
            write_to_buffer(d,buf,0);
            d->connected = CON_PICK_WEAPON;
            break;
        }

        if (!parse_gen_groups(ch,argument))
        send_to_char(
        "Choices are: list,learned,premise,add,drop,info,help, and done.\n\r"
        ,ch);

        do_help(ch,"menu choice");
        break;

    case CON_READ_IMOTD:
	write_to_buffer(d,"\n\r",2);
        do_help( ch, "motd" );
        d->connected = CON_READ_MOTD;
	break;

    case CON_READ_MOTD:
        if ( ch->pcdata == NULL || ch->pcdata->pwd[0] == '\0')
        {
            write_to_buffer( d, "Warning! Null password!\n\r",0 );
            write_to_buffer( d, "Please report old password with bug.\n\r",0);
            write_to_buffer( d,
                "Type 'password null <new password>' to fix.\n\r",0);
        }

	write_to_buffer( d,"\n\rWelcome to WURM Mud.\n\r",0 );
	ch->next	= char_list;
	char_list	= ch;
	d->connected	= CON_PLAYING;
        show_player_log(ch,player_log,log_head);
	reset_char(ch);
        }

/* SEND TO NEWTOWN */
        
        if ( ch->level < 2 )
        {
	    char_to_room( ch, get_room_index( ROOM_VNUM_SCHOOL ) );
	    send_to_char("\n\r",ch);
        }
          
	else if ( ch->in_room != NULL )
	{
	    char_to_room( ch, ch->in_room );
	}

	else if ( IS_IMMORTAL(ch) )
	{
	    char_to_room( ch, get_room_index( ROOM_VNUM_CHAT ) );
	}

	else
	{
	    char_to_room( ch, get_room_index( ROOM_VNUM_TEMPLE ) );
	}

	act( "$n has entered the game.", ch, NULL, NULL, TO_ROOM );
	do_look( ch, "auto" );
        
        wiznet("$N has joined the game.",ch,NULL,
		WIZ_LOGINS,WIZ_SITES,get_trust(ch));

	if (ch->pet != NULL)
	{
	    char_to_room(ch->pet,ch->in_room);
	    act("$n has entered the game.",ch->pet,NULL,NULL,TO_ROOM);
	}

	do_unread(ch,"");
	break;
    }

    return;
}



/*
 * Parse a name for acceptability.
 */
bool check_parse_name( char *name )
{
    /*
     * Reserved words.
     */
    if ( is_name( name, 
	"all auto immortal self someone something the you demise balance
         circle loner honor fucker fuck shit piss puke cunt bitch whore
         loser gandalf bilbo dick pussy chicken asshole blowjob lick
         joe bob steve guest hugh mike brian alex dave david coolio
         raistlin magic fag queer faggot dyke lesbian lesbo god lord
         goddess aries zeus gemini capricorn taurus fucking fuckyou
         ass dildo bung bunghole masterbate thor hitler skin skinhead
         vagina labia lips chink nigger honkey spick wetback tits
         breast boob boobs slit slut none") )
	return FALSE;
	
    if (str_cmp(capitalize(name),"Alander") && (!str_prefix("Alan",name)
    || !str_suffix("Alander",name)))
	return FALSE;

    /*
     * Length restrictions.
     */
     
    if ( strlen(name) <  2 )
	return FALSE;

#if defined(MSDOS)
    if ( strlen(name) >  8 )
	return FALSE;
#endif

#if defined(macintosh) || defined(unix)
    if ( strlen(name) > 12 )
	return FALSE;
#endif

    /*
     * Alphanumerics only.
     * Lock out IllIll twits.
     */
    {
	char *pc;
	bool fIll,adjcaps = FALSE,cleancaps = FALSE;
 	int total_caps = 0;

	fIll = TRUE;
	for ( pc = name; *pc != '\0'; pc++ )
	{
	    if ( !isalpha(*pc) )
		return FALSE;

	    if ( isupper(*pc)) /* ugly anti-caps hack */
	    {
		if (adjcaps)
		    cleancaps = TRUE;
		total_caps++;
		adjcaps = TRUE;
	    }
	    else
		adjcaps = FALSE;

	    if ( LOWER(*pc) != 'i' && LOWER(*pc) != 'l' )
		fIll = FALSE;
	}

	if ( fIll )
	    return FALSE;

	if (cleancaps || (total_caps > (strlen(name)) / 2 && strlen(name) < 3))
	    return FALSE;
    }

    /*
     * Prevent players from naming themselves after mobs.
     */
    {
	extern MOB_INDEX_DATA *mob_index_hash[MAX_KEY_HASH];
	MOB_INDEX_DATA *pMobIndex;
	int iHash;

	for ( iHash = 0; iHash < MAX_KEY_HASH; iHash++ )
	{
	    for ( pMobIndex  = mob_index_hash[iHash];
		  pMobIndex != NULL;
		  pMobIndex  = pMobIndex->next )
	    {
		if ( is_name( name, pMobIndex->player_name ) )
		    return FALSE;
	    }
	}
    }

    return TRUE;
}



/*
 * Look for link-dead player to reconnect.
 */
bool check_reconnect( DESCRIPTOR_DATA *d, char *name, bool fConn )
{
    CHAR_DATA *ch;

    for ( ch = char_list; ch != NULL; ch = ch->next )
    {
	if ( !IS_NPC(ch)
	&&   (!fConn || ch->desc == NULL)
	&&   !str_cmp( d->character->name, ch->name ) )
	{
	    if ( fConn == FALSE )
	    {
		free_string( d->character->pcdata->pwd );
		d->character->pcdata->pwd = str_dup( ch->pcdata->pwd );
	    }
	    else
	    {
		free_char( d->character );
		d->character = ch;
		ch->desc	 = d;
		ch->timer	 = 0;
		send_to_char(
		    "Reconnecting. Type replay to see missed tells.\n\r", ch );
		act( "$n has reconnected.", ch, NULL, NULL, TO_ROOM );

		sprintf( log_buf, "%s@%s reconnected.", ch->name, d->host );
		log_string( log_buf );
		wiznet("$N groks the fullness of $S link.",
		    ch,NULL,WIZ_LINKS,0,0);
		d->connected = CON_PLAYING;
//  show_player_log(ch,player_log);
	    }
	    return TRUE;
	}
    }

    return FALSE;
}



/*
 * Check if already playing.
 */
bool check_playing( DESCRIPTOR_DATA *d, char *name )
{
    DESCRIPTOR_DATA *dold;

    for ( dold = descriptor_list; dold; dold = dold->next )
    {
	if ( dold != d
	&&   dold->character != NULL
	&&   dold->connected != CON_GET_NAME
	&&   dold->connected != CON_GET_OLD_PASSWORD
	&&   !str_cmp( name, dold->original
	         ? dold->original->name : dold->character->name ) )
	{
	    write_to_buffer( d, "That character is already playing.\n\r",0);
	    write_to_buffer( d, "Do you wish to connect anyway (Y/N)?",0);
	    d->connected = CON_BREAK_CONNECT;
	    return TRUE;
	}
    }

    return FALSE;
}



void stop_idling( CHAR_DATA *ch )
{
    if ( ch == NULL
    ||   ch->desc == NULL
    ||   ch->desc->connected != CON_PLAYING
    ||   ch->was_in_room == NULL 
    ||   ch->in_room != get_room_index(ROOM_VNUM_LIMBO))
	return;

    ch->timer = 0;
    char_from_room( ch );
    char_to_room( ch, ch->was_in_room );
    ch->was_in_room	= NULL;
    act( "$n has returned from the void.", ch, NULL, NULL, TO_ROOM );
    return;
}



/*
 * Write to one char.
 */
void send_to_char_bw( const char *txt, CHAR_DATA *ch )
{
    if ( txt != NULL && ch->desc != NULL )
        write_to_buffer( ch->desc, txt, strlen(txt) );
    return;
}

/*
 * Write to one char, new colour version, by Lope.
 */
void send_to_char( const char *txt, CHAR_DATA *ch )
{
    const	char 	*point;
    		char 	*point2;
    		char 	buf[ MAX_STRING_LENGTH*4 ];
		int	skip = 0;

    buf[0] = '\0';
    point2 = buf;
    if( txt && ch->desc )
	{
	    if( IS_SET( ch->act, PLR_COLOUR ) )
	    {
		for( point = txt ; *point ; point++ )
	        {
		    if( *point == '{' )
		    {
			point++;
			skip = colour( *point, ch, point2 );
			while( skip-- > 0 )
			    ++point2;
			continue;
		    }
		    *point2 = *point;
		    *++point2 = '\0';
		}			
		*point2 = '\0';
        	write_to_buffer( ch->desc, buf, point2 - buf );
	    }
	    else
	    {
		for( point = txt ; *point ; point++ )
	        {
		    if( *point == '{' )
		    {
			point++;
			continue;
		    }
		    *point2 = *point;
		    *++point2 = '\0';
		}
		*point2 = '\0';
        	
write_to_buffer( ch->desc, buf, point2 - buf );
	    }
	}
    return;
}

/*
 * Send a page to one char.
 */
void page_to_char_bw( const char *txt, CHAR_DATA *ch )
{
    if ( txt == NULL || ch->desc == NULL)


    if (ch->lines == 0 )
    {
	send_to_char(txt,ch);
	return;
    }
	
#if defined(macintosh)
	send_to_char(txt,ch);
#else
    ch->desc->showstr_head = alloc_mem(strlen(txt) + 1);
    strcpy(ch->desc->showstr_head,txt);
    ch->desc->showstr_point = ch->desc->showstr_head;
    show_string(ch->desc,"");
#endif
}

/*
 * Page to one char, new colour version, by Lope.
 */
void page_to_char( const char *txt, CHAR_DATA *ch )
{
    const	char	*point;
    		char	*point2;
    		char	buf[ MAX_STRING_LENGTH * 4 ];
		int	skip = 0;

    buf[0] = '\0';
    point2 = buf;
    if( txt && ch->desc )
	{
	    if( IS_SET( ch->act, PLR_COLOUR ) )
	    {
		for( point = txt ; *point ; point++ )
	        {
		    if( *point == '{' )
		    {
			point++;
			skip = colour( *point, ch, point2 );
			while( skip-- > 0 )
			    ++point2;
			continue;
		    }
		    *point2 = *point;
		    *++point2 = '\0';
		}			
		*point2 = '\0';
		ch->desc->showstr_head  = alloc_mem( strlen( buf ) + 1 );
		strcpy( ch->desc->showstr_head, buf );
		ch->desc->showstr_point = ch->desc->showstr_head;
		show_string( ch->desc, "" );
	    }
	    else
	    {
		for( point = txt ; *point ; point++ )
	        {
		    if( *point == '{' )
		    {
			point++;
			continue;
		    }
		    *point2 = *point;
		    *++point2 = '\0';
		}
		*point2 = '\0';
		ch->desc->showstr_head  = alloc_mem( strlen( buf ) + 1 );
		strcpy( ch->desc->showstr_head, buf );
		ch->desc->showstr_point = ch->desc->showstr_head;
		show_string( ch->desc, "" );
	    }
	}
    return;
}


/* string pager */
void show_string(struct descriptor_data *d, char *input)
{
    char buffer[4*MAX_STRING_LENGTH];
    char buf[MAX_INPUT_LENGTH];
    register char *scan, *chk;
    int lines = 0, toggle = 1;
    int show_lines;

    one_argument(input,buf);
    if (buf[0] != '\0')
    {
	if (d->showstr_head)
	{
	    free_mem(d->showstr_head,strlen(d->showstr_head));
	    d->showstr_head = 0;
	}
    	d->showstr_point  = 0;
	return;
    }

    if (d->character)
	show_lines = d->character->lines;
    else
	show_lines = 0;

    for (scan = buffer; ; scan++, d->showstr_point++)
    {
	if (((*scan = *d->showstr_point) == '\n' || *scan == '\r')
	    && (toggle = -toggle) < 0)
	    lines++;

	else if (!*scan || (show_lines > 0 && lines >= show_lines))
	{
	    *scan = '\0';
	    write_to_buffer(d,buffer,strlen(buffer));
	    for (chk = d->showstr_point; isspace(*chk); chk++);
	    {
		if (!*chk)
		{
		    if (d->showstr_head)
        	    {
            		free_mem(d->showstr_head,strlen(d->showstr_head));
            		d->showstr_head = 0;
        	    }
        	    d->showstr_point  = 0;
    		}
	    }
	    return;
	}
    }
    return;
}
	

/* quick sex fixer */
void fix_sex(CHAR_DATA *ch)
{
    if (ch->sex < 0 || ch->sex > 2)
    	ch->sex = IS_NPC(ch) ? 0 : ch->pcdata->true_sex;
}

void act (const char *format, CHAR_DATA *ch, const void *arg1, const void *arg2,
	  int type)
{
    /* to be compatible with older code */
    act_new(format,ch,arg1,arg2,type,POS_RESTING);
}

/*
 * The colour version of the act_new( ) function, -Lope
 */
void act_new( const char *format, CHAR_DATA *ch, const void *arg1, 
	      const void *arg2, int type, int min_pos )
{
    static char * const he_she  [] = { "it",  "he",  "she" };
    static char * const him_her [] = { "it",  "him", "her" };
    static char * const his_her [] = { "its", "his", "hers" };
 
    CHAR_DATA 		*to;
    CHAR_DATA 		*vch = ( CHAR_DATA * ) arg2;
    OBJ_DATA 		*obj1 = ( OBJ_DATA  * ) arg1;
    OBJ_DATA 		*obj2 = ( OBJ_DATA  * ) arg2;
    const 	char 	*str;
    char 		*i = NULL;
    char 		*point;
    char 		*pbuff;
    char 		buffer[ MAX_STRING_LENGTH*2 ];
    char 		buf[ MAX_STRING_LENGTH   ];
    char 		fname[ MAX_INPUT_LENGTH  ];
    bool		fColour = FALSE;

    /*
     * Discard null and zero-length messages.
     */
    if( !format || !*format )
        return;

    /* discard null rooms and chars */
    if( !ch || !ch->in_room )
	return;

    to = ch->in_room->people;
    if( type == TO_VICT )
    {
        if( !vch )
        {
            bug( "Act: null vch with TO_VICT.", 0 );
            return;
        }

	if( !vch->in_room )
	    return;

        to = vch->in_room->people;
    }
 
    for( ; to ; to = to->next_in_room )
    {
    if ( (!IS_NPC(to) && to->desc == NULL )
       ||   ( IS_NPC(to) && !HAS_TRIGGER(to, TRIG_ACT) )
       ||    to->position < min_pos )

            continue;
 
        if( ( type == TO_CHAR ) && to != ch )
            continue;
        if( type == TO_VICT && ( to != vch || to == ch ) )
            continue;
        if( type == TO_ROOM && to == ch )
            continue;
        if( type == TO_NOTVICT && (to == ch || to == vch) )
            continue;
 
        point   = buf;
        str     = format;
        while( *str != '\0' )
        {
            if( *str != '$' )
            {
                *point++ = *str++;
                continue;
            }
 
	    fColour = TRUE;
	    ++str;
	    i = " <@@@> ";
            if( !arg2 && *str >= 'A' && *str <= 'Z' )
            {
                bug( "Act: missing arg2 for code %d.", *str );
                i = " <@@@> ";
            }
            else
            {
                switch ( *str )
                {
                default:  bug( "Act: bad code %d.", *str );
                          i = " <@@@> ";                                break;
                /* Thx alex for 't' idea */
                case 't': i = (char *) arg1;                            break;
                case 'T': i = (char *) arg2;                            break;
                case 'n': i = PERS( ch,  to  );                         break;
                case 'N': i = PERS( vch, to  );                         break;
                case 'e': i = he_she  [URANGE(0, ch  ->sex, 2)];        break;
                case 'E': i = he_she  [URANGE(0, vch ->sex, 2)];        break;
                case 'm': i = him_her [URANGE(0, ch  ->sex, 2)];        break;
                case 'M': i = him_her [URANGE(0, vch ->sex, 2)];        break;
                case 's': i = his_her [URANGE(0, ch  ->sex, 2)];        break;
                case 'S': i = his_her [URANGE(0, vch ->sex, 2)];        break;
                case 'g': i = god_table[ch->god].name;                  break;
                case 'p':
                    i = can_see_obj( to, obj1 )
                            ? obj1->short_descr
                            : "something";
                    break;
 
                case 'P':
                    i = can_see_obj( to, obj2 )
                            ? obj2->short_descr
                            : "something";
                    break;
 
                case 'd':
                    if ( arg2 == NULL || ((char *) arg2)[0] == '\0' )
                    {
                        i = "door";
                    }
                    else
                    {
                        one_argument( (char *) arg2, fname );
                        i = fname;
                    }
                    break;
                }
            }
 
            ++str;
            while ( ( *point = *i ) != '\0' )
                ++point, ++i;
        }
 
        *point++ = '\n';
        *point++ = '\r';
	*point	 = '\0';
        buf[0]   = UPPER(buf[0]);
	pbuff	 = buffer;
	colourconv( pbuff, buf, to );
        if ( to->desc != NULL )
	write_to_buffer( to->desc, buffer, 0 );
/* OLC color FIX
        write_to_buffer( to->desc, buf, point - buf );
*/
        else
        if ( MOBtrigger )
        mp_act_trigger( buf, to, ch, arg1, arg2, TRIG_ACT );
    }
 
    return;
}



/*
 * Macintosh support functions.
 */
#if defined(macintosh)
int gettimeofday( struct timeval *tp, void *tzp )
{
    tp->tv_sec  = time( NULL );
    tp->tv_usec = 0;
}
#endif

int colour( char type, CHAR_DATA *ch, char *string )
{
    char	code[ 20 ];
    char	*p = '\0';

    if( IS_NPC( ch ) )
	return( 0 );

    switch( type )
    {
	default:
	    sprintf( code, CLEAR );
	    break;
	case 'x':
	    sprintf( code, CLEAR );
	    break;
	case 'b':
	    sprintf( code, C_BLUE );
	    break;
	case 'c':
	    sprintf( code, C_CYAN );
	    break;
	case 'g':
	    sprintf( code, C_GREEN );
	    break;
	case 'm':
	    sprintf( code, C_MAGENTA );
	    break;
	case 'r':
	    sprintf( code, C_RED );
	    break;
	case 'w':
	    sprintf( code, C_WHITE );
	    break;
	case 'y':
	    sprintf( code, C_YELLOW );
	    break;
	case 'B':
	    sprintf( code, C_B_BLUE );
	    break;
	case 'C':
	    sprintf( code, C_B_CYAN );
	    break;
	case 'G':
	    sprintf( code, C_B_GREEN );
	    break;
	case 'M':
	    sprintf( code, C_B_MAGENTA );
	    break;
	case 'R':
	    sprintf( code, C_B_RED );
	    break;
	case 'W':
	    sprintf( code, C_B_WHITE );
	    break;
	case 'Y':
	    sprintf( code, C_B_YELLOW );
	    break;
	case 'D':
	    sprintf( code, C_D_GREY );
	    break;
	case '*':
	    sprintf( code, "%c", 007 );
	    break;
	case '/':
	    sprintf( code, "%c", 012 );
	    break;
	case '{':
	    sprintf( code, "%c", '{' );
	    break;
    }

    p = code;
    while( *p != '\0' )
    {
	*string = *p++;
	*++string = '\0';
    }

    return( strlen( code ) );
}

void colourconv( char *buffer, const char *txt, CHAR_DATA *ch )
{
    const	char	*point;
		int	skip = 0;

    if( ch->desc && txt )
    {
	if( IS_SET( ch->act, PLR_COLOUR ) )
	{
	    for( point = txt ; *point ; point++ )
	    {
		if( *point == '{' )
		{
		    point++;
		    skip = colour( *point, ch, buffer );
		    while( skip-- > 0 )
			++buffer;
		    continue;
		}
		*buffer = *point;
		*++buffer = '\0';
	    }			
	    *buffer = '\0';
	}
	else
	{
	    for( point = txt ; *point ; point++ )
	    {
		if( *point == '{' )
		{
		    point++;
		    continue;
		}
		*buffer = *point;
		*++buffer = '\0';
	    }
	    *buffer = '\0';
	}
    }
    return;
}
char *  const   who_day_name        [] =
{
    "the Moon", "the Bull", "Deception", "Thunder", "Freedom",
    "the Great Gods", "the Sun"
};
        
char *  const  who_month_name      [] =
{
    "Winter", "the Winter Wolf", "the Frost Giant", "the Old Forces",
    "the Grand Struggle", "the Spring", "Nature", "Futility", "the
Dragon",
    "the Sun", "the Heat", "the Battle", "the Dark Shades", "the
Shadows",   
    "the Long Shadows", "the Ancient Darkness", "the Great Evil"
};
      
void who_do_time( int fd)
{
    extern char str_boot_time[];
    char buf[MAX_STRING_LENGTH];
    char *suf;
    int day;
    
    day     = time_info.day + 1;
      
   /* else if ( day % 10 ==  1       ) suf = "st";
    else if ( day % 10 ==  2       ) suf = "nd";
    else if ( day % 10 ==  3       ) suf = "rd";
    else */                            suf = "th";
    
    sprintf( buf,
        "It is %d o'clock %s, <B> Day of %s, %d%s </B> the Month of %s.\n\r<BR>",(time_info.hour % 12 == 0) ? 12 : time_info.hour %12,time_info.hour >= 12 ? "pm" : "am",who_day_name[day % 7],day, suf,who_month_name[time_info.month]);
    write(fd,buf,strlen(buf));
    sprintf(buf,"Wurm started up at<B> %s\n\r</B> <BR> The system time is %s.\n\r<BR>",
        str_boot_time,
        (char *) ctime( &current_time )

       );
    
       write(fd,buf,strlen(buf));
    return;
}

    
void printf_to_char (CHAR_DATA *ch, char *fmt, ...)
{
char buf[MAX_STRING_LENGTH];
va_list args;
va_start (args, fmt);
vsprintf (buf, fmt, args);
va_end (args);

send_to_char (buf, ch);
}

