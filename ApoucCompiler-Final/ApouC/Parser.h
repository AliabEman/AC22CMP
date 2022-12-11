/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ apc LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern apc_intg line; // gives the line for where errors occur
extern Token tokenizer(apc_void);
extern apc_char* keywordTable[];
apc_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"ApouC"
#define LANG_WRTE		"print("
#define LANG_READ		"input("
#define LANG_MAIN		"def"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_int,
	KW_float,
	KW_string,
	KW_char,
	KW_if,
	KW_elif,
	KW_else,
	KW_return,
	KW_do,
	KW_break,
	KW_def,
	KW_print
};

/* Function definitions */
apc_void startParser();
apc_void matchToken(apc_intg, apc_intg);
apc_void syncErrorHandler(apc_intg);
apc_void printError();

/* TO_DO: Place ALL non-terminal function declarations 
Related with functions supposed to match with Null terminals*/
apc_void program();
apc_void dataSession();
apc_void outputVariableList();
apc_void optVarListDeclarations();
apc_void codeSession();
apc_void optionalStatements();
apc_void outputStatement();
apc_void statement();
apc_void statements();
apc_void statementsPrime();

#endif
