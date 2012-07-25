/*******************************************************************//**
 *	@file	x16.h
 *
 *	Declarations for additional functions in main program.
 *
 *	@author	Alexander Dahl <post@lespocky.de>
 *	@date	Created: 2012-07-24
 *
 *	Copyright 2012 Netz39 e.V.
 **********************************************************************/

#ifndef _X16_H_
#define _X16_H_

#include <stdlib.h>

#define X16_ERR_NONE			0
#define X16_ERR_UNKNOWN			1
#define X16_ERR_PARAM_COUNT		2
#define X16_ERR_NOT_IMPLEMENTED	3
#define X16_ERR_PARAM_FORMAT	4
#define X16_ERR_SYSTEM			5
#define X16_ERR_RANGE			6

/**	Function pointer type for command evaluation.	*/
typedef int (*t_cmd_func)( int argc, char **argv );

/**
 *	Command evaluation structure containing the string of the command
 *	itself and a function pointer to the function to be executed.
 */
struct cmd {
	const char	*cmd;
	t_cmd_func	func;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 *	Compare function for qsort() and bsearch() comparing structures of
 *	type struct t_cmd.
 *
 *	@param[in]	e1	pointer to first struct
 *	@param[in]	e2	pointer to second struct
 *
 *	@return -1, 0 or 1 depending which is less, equal or greater.
 */
static int cmd_cmp( const void *e1, const void *e2 );

/**
 *	Echo help for a specific command or generic help if no further
 *	argument is given!
 *
 *	@param[in]	argc	pass argc from main
 *	@param[in]	**argv	pass argv from main
 *
 *	@return	Zero in case of success, else some error code.
 */
static int cmd_help( int argc, char **argv );

/**
 *	Create a logo.
 *
 *	@param[in]	aargc	pass argc from main
 *	@param[in]	**aargv	pass argv from main
 *
 *	@return	Zero in case of success, else some error code.
 */
static int cmd_logo( int aargc, char **aargv );

/**
 *	Print short list of commands.
 */
static void print_commands( void );

/**
 *	Print help message shortly listing all available options.
 */
static void print_help( void );

/**
 *	Print short usage information if no options given.
 */
static void print_usage( void );

/**
 *	Print version information.
 */
static void print_version( void );

/*	***	inline functions	***	*/

/**
 *	Just call print_help() and throw away command parameters.
 *
 *	@return zero
 */
inline int cmd_print_help( int argc, char **argv ) {
	print_help();
	return X16_ERR_NONE;
}

/**
 *	Just call print_usage() and throw away command parameters.
 *
 *	@return zero
 */
inline int cmd_print_usage( int argc, char **argv ) {
	print_usage();
	return EXIT_SUCCESS;
}

/**
 *	Just call print_version() and throw away command parameters.
 *
 *	@return zero
 */
inline int cmd_print_version( int argc, char **argv ) {
	print_version();
	return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

#endif	/* _X16_H_ */

/* vim: set noet sts=0 ts=4 sw=4 sr: */
