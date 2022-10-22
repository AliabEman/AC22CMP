/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
* Student: Aliab Eman
* Student Number: 041-000-420
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
#define READER_FUL 0x08				/* (0000.1000)_2 = (008)_10 */
/* TO_DO: BIT 2: EMP: Empty */
#define READER_EMP 0x04				/* (0000.0100)_2 = (004)_10 */
/* TO_DO: BIT 1: REL = Relocation */
#define READER_REL 0x02				/* (0000.0010)_2 = (002)_10 */
/* TO_DO: BIT 0: END = EndOfBuffer */
#define READER_END 0x01				/* (0000.0001)_2 = (001)_10 */

#define NCHAR		128				/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	apc_intg mark;			/* the offset to the mark position (in chars) */
	apc_intg read;			/* the offset to the get a char position (in chars) */
	apc_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	apc_char*	content;			/* pointer to the beginning of character array (character buffer) */
	apc_intg	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	apc_intg	increment;			/* character array increment factor */
	apc_intg	mode;				/* operational mode indicator */
	apc_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	apc_intg	histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */

/*
*	Function Name: readerCreate
*	Purpose: Create a new reader in memory heap.
*	Parameters: size, increment, mode
*	Return Value: readerPointer
*	Algorithm:
*/
ReaderPointer	readerCreate		(apc_intg, apc_intg, apc_intg);
/*
*	Function Name: readerAddChar
*	Purpose: To add a char to the reader.
*	Parameters: readerPointer, ch
*	Return Value: readerPointer
*	Algorithm:
*/
ReaderPointer	readerAddChar		(ReaderPointer const, apc_char);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerClear		    (ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerFree		    (ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerIsFull		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerIsEmpty		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerSetMark		(ReaderPointer const, apc_intg);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerPrint		    (ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerLoad			(ReaderPointer const, FILE* const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerRecover		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerRetract		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_boln		readerRestore		(ReaderPointer const);

/* Getters */
apc_char		readerGetChar		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_char*		readerGetContent	(ReaderPointer const, apc_intg);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerGetPosRead	(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerGetPosWrte	(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerGetPosMark	(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerGetInc		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerGetMode		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_byte		readerGetFlags		(ReaderPointer const);
/*
*	Function Name:
*	Purpose:
*	Parameters:
*	Return Value:
*	Algorithm:
*/
apc_intg		readerShowStat		(ReaderPointer const);

#endif
