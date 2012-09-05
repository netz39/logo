/*******************************************************************//**
 *	@file	x16.c
 *
 *	Algorithmic creation of a logo image for Netz39.
 *
 *	@author	Alexander Dahl <post@lespocky.de>
 *	@date	Created: 2012-07-24
 *
 *	Copyright 2012 Netz39 e.V.
 **********************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <getopt.h>
#include <syslog.h>

#include "x16.h"
#include "x16_build.h"

#include <gd.h>

static char	*prog_name = NULL;

static int debug_flag = false;
static int verbose_flag = false;

int main( int argc, char *argv[] ) {
	struct cmd cmd_to_check = { NULL, NULL };
	static struct cmd commands[] = {
		{	"help",		cmd_help			},
		{	"logo",		cmd_logo			},
		{	"usage",	cmd_print_usage		},
		{	"version",	cmd_print_version	},
	};
	static const struct option long_options[] = {
		{	"debug",			no_argument,	NULL,	'd'	},
		{	"help",				no_argument,	NULL,	'h'	},
		{	"verbose",			no_argument,	NULL,	'v'	},
		{	"version",			no_argument,	NULL,	'V' },
		{	NULL,				0,				NULL,	0	}
	};
	int no_of_commands = sizeof(commands) / sizeof(struct cmd);
	int opt_index, opt_result;
	struct cmd *p_found_cmd;

	prog_name = argv[0];

	/*	process cmd line options	*/
	while( 1 ) {
		opt_result = getopt_long( argc, argv, "dhvV", long_options, &opt_index );

		if ( opt_result == -1 ) {
			break;	/*	end of list	*/
		}

		switch ( opt_result ) {
		case 'd':
			/*	-d or --debug	*/
			debug_flag = true;
			break;

		case 'h':
			print_help();
			return EXIT_SUCCESS;
			break;

		case 'v':
			/*	-v or --verbose	*/
			verbose_flag = true;
			break;

		case 'V':
			print_version();
			return EXIT_SUCCESS;
			break;

		/*	Parameters which set a flag cause getopt_long to return 0.
		 *	As long as this is not the case, this is not reached.	*/
		case 0:
			break;

		default:
			print_usage();
			return EXIT_FAILURE;
			break;
		}
	}

	/*	check if a command is given	*/
	if ( argc == optind ) {
		(void) fprintf( stderr, "No command given!\n" );
		print_usage();
		return EXIT_FAILURE;
	}

	/*	prepare command function pointer array	*/
	qsort( commands, no_of_commands, sizeof(struct cmd), cmd_cmp );

	/*	take first parameter as a command and call related function	*/
	cmd_to_check.cmd = argv[optind];
	p_found_cmd = (struct cmd *) bsearch( &cmd_to_check, commands,
			no_of_commands, sizeof(struct cmd), cmd_cmp );
	if ( p_found_cmd == NULL ) {
		(void) fprintf( stderr, "Unknown command '%s'!\n",
				cmd_to_check.cmd );
		return EXIT_FAILURE;
	} else {
		return p_found_cmd->func( argc, argv );
	}
}

/*	***	function implementations	***	*/
int cmd_cmp( const void *e1, const void *e2 ) {
	struct cmd *p_cmd_1 = (struct cmd *) e1;
	struct cmd *p_cmd_2 = (struct cmd *) e2;

	return strcmp( p_cmd_1->cmd, p_cmd_2->cmd );
}

int cmd_help( int argc, char **argv ) {
	if ( argc - optind > 1 ) {
		if ( !strcmp( argv[optind+1], "logo" ) ) {
			(void) printf( "%s [GLOBALOPTIONS] logo FOO\n\n", prog_name );
			(void) puts( "  FOO some parameter" );
		} else {
			(void) fprintf( stderr,
					"No help available for command '%s'!\n\n",
					argv[optind+1] );
			print_commands();
		}
	} else {
		print_help();
	}

	return EXIT_SUCCESS;
}

int cmd_logo( int aargc, char **aargv ) {
	gdImagePtr	im;
	FILE		*fp_png;
	int			black, white;

	im = gdImageCreate( 32, 32 );
	black = gdImageColorAllocate( im, 0, 0, 0 );
	white = gdImageColorAllocate( im, 255, 255, 255 );
	gdImageLine( im, 0, 0, 31, 31, white );
	fp_png = fopen( "test.png", "wb" );
	gdImagePng( im, fp_png );
	fclose( fp_png );
	gdImageDestroy( im );

	(void) puts( "this is senseless o_O" );
	return X16_ERR_NOT_IMPLEMENTED;
}

void print_commands( void ) {
	(void) puts( "Commands are:" );
	(void) puts( "  logo           create a logo" );
	(void) printf( "\n" );

	(void) printf( "Use '%s help COMMAND' for getting more help on a command.\n",
			prog_name );
}

void print_help( void ) {
	(void) printf( "Usage: %s [GLOBALOPTIONS] [COMMAND] [PARAMETERS]\n", prog_name );
	(void) printf( "\n" );

	(void) puts( "Global options are:" );
	(void) puts( "  -d, --debug    additional debug output" );
	(void) puts( "  -v, --verbose  more messages" );
	(void) printf( "\n" );

	(void) puts( "  -V, --version  show version information and exit" );
	(void) puts( "  -h, --help     show this help and exit" );
	(void) printf( "\n" );

	print_commands();
}

void print_usage( void ) {
	(void) fprintf( stderr, "Try '%s --help' to see possible parameters.\n",
			prog_name );
}

void print_version( void ) {
	(void) printf( "%s %s\n", prog_name, X16_VERSION );
	(void) printf( "Copyright %s Netz39 e.V.\n", X16_COPYRIGHT_YEARS );
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
