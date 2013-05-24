// crt_perror.c
// compile with: /W1
/* This program attempts to open a file named
 * NOSUCHF.ILE. Because this file probably doesn't exist,
 * an error message is displayed. The same message is
 * created using perror, strerror, and _strerror.
 */
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>


int main( void )
{
//	int fh;

//	if( _sopen_s( &fh, "NOSUCHF.ILE", _O_RDONLY, _SH_DENYNO, 0 ) != 0 )
	{
		/* Three ways to create error message: */
//		perror( "perror says open failed" );
		errno = 10;
		printf( "strerror says open failed: %s\n", strerror( errno ) ); // C4996
		//printf( strerror( "_strerror says open failed" ) ); // C4996

		//Note: strerror and _strerror are deprecated; consider
		// using strerror_s and _strerror_s instead.
	}	
/*
	else
	{
		printf( "open succeeded on input file\n" );
		_close( fh );
	}	
*/
}
