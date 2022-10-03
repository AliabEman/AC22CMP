/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
* Student: Aliab Eman / Matt Vecchio
* Student Number: 041-000-420 / 041-004-137
************************************************************
 _________________________________
|                                 |
| ....... 'APOUC' LANGUAGE ...... |
|///// /\\------\\\\\\\\\\\\\\\\\\|
|//// // \\  \_\ \\\\\\\\\\\\\\\  |
|/// //___\\   __/\\\\\           |
|// //     \\__\\\\\\\            |
|\\\\\  *  / // /\\\\             |
|\\\\\\___/ // /\\\\\             |
|\\\\\\\\/ // /\\\\\\             |
|///////\\ \\ \\\\\\\\            |
|///////\\\ \\ \\\\\\\\\\\\\\\\\  |
|//////\\\\\    \\\\\\\\\\\\\\\\\\|
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */
 
/* Logical constants - adapt for your language */
#define APC_TRUE  1
#define APC_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
//my user defined datatype for characters in the ApouC language
typedef char			apc_char;
//my user defined datatype for any integers in the ApouC language
typedef int				apc_intg;
//my user defined datatype for any floating point numbers in the ApouC language
typedef float			apc_real;
//my user defined datatype for any void in the ApouC language
typedef void			apc_void;
//my user defined datatype for any boolean values (0,1) in the ApouC language
typedef unsigned char	apc_boln;
//my user defined datatype for any byte in the ApouC language
typedef unsigned char	apc_byte;
//my user defined datatype for any long integers in the ApouC language
typedef long			apc_long;
//my user defined datatype for any doubles in the ApouC language
typedef double			apc_doub;
//my user defined datatype for any short integers in the ApouC language
typedef short			apc_short;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/

/*
*	Function Name: mainReader
*	Purpose: 
*	Parameters: argc, argv
*	Return Value: apc_intg 
*	Algorithm:
*/
apc_intg mainReader  (apc_intg argc, apc_char** argv);
/*
apc_intg mainScanner (apc_intg argc, apc_char** argv);
apc_intg mainParser  (apc_intg argc, apc_char** argv);
*/
apc_void printLogo();

#endif
