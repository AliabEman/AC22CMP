/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Student: Aliab Eman, Matthew Vecchio
* Student Number: 041-000-420, 041-004-137
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif 

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	
 

	ERR_T,		/*  0: Error token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */

//	MNID_T, /* Method Name Identifier Token */
//	KEY_T, /* Keyword Token*/
//	SL_T, /*String Literal */
//	CL_T, /*Character Literal */
//	FPL_T, /*Floating Point Literal */
//	IL_T, /*Integer Literal */
//	MLC_T, /*Multi-Line Comment Token*/
//	SLC /*Single-Line Comment Token*/

};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	apc_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	apc_intg intValue;						/* integer literal attribute (value) */
	apc_intg keywordIndex;					/* keyword index in the keyword table */
	apc_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	apc_real floatValue;					/* floating-point literal attribute (value) */
	apc_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	apc_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	apc_byte flags;			/* Flags information */
	union {
		apc_intg intValue;				/* Integer value */
		apc_real floatValue;			/* Float value */
		apc_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	apc_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */


#define LETTER	[A,z]	/* 0: Letter Token [a-z,A-Z] */
#define DIGIT	[0,9]	/* 1: Digit Token [0-9]		 */
#define SQ_T	27		/* 2: Single Quote Token ['] */
#define DQ_T	34		/* 3: Double Quote Token ["] */
#define LC_T	'{'		/* 4: Left Parenthesis Token [{] */
#define RC_T	'}'		/* 5: Right Parenthesis Token [}] */
#define SC_T	'#'		/* 6: Hash Symbol Token [#] */
#define PERIOD	'.'		/* 7: Decimal Period Token [.] */
#define EXP		'e'		/* 8: Exponent Token [e] */
#define SIGN	{'+','-'} /* 9: Sign Token [+|-} */
#define U_T		'_'		/* 10: Underscore Token */
#define OPENP	'('	/* 11: Open Parenthesis Token [(] */
#define CLOSEP	')'	/* 12: Close Parenthesis Token [)] */
#define OTHER	!(LETTER || DIGIT || SQ_T || Q_T || LC_T || RC_T || SC_T || P_T || E_T || S_T || U_T || OP_T || CP_T)/* 13: Other Tokens */
#define SIGMA	''	/* 14: Empty Token */

/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 7

/* TO_DO: Transition table - type of states defined in separate table */
static apc_intg transitionTable[][TABLE_COLUMNS] = {
/*   [A-z] , [0-9],    _,    &,    ", SEOF, other
	   L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) */
	{     1,  ESNR, ESNR, ESNR,    4, ESWR, ESNR}, // S0: NOAS
	{     1,     1,    1,    2, ESNR, ESWR,    3}, // S1: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S2: ASNR (MVID)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S3: ASWR (KEY)
	{     4,     4,    4,    4,    5, ESWR,    4}, // S4: NOAS
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S5: ASNR (SL)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S6: ASNR (ES)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}  // S7: ASWR (ER)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */ 
static apc_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	FSNR, /* 06 (Err1 - no retract) */
	FSWR,  /* 07 (Err2 - retract) */

	NOFS, /* 00 */
	NOFS, /* 01 */
	NOFS, /* 02 */
	FSNR, /* 03 (MNID) - Method Name Identifier */
	FSWR, /* 04 (KEY) - Keyword */
	NOFS, /* 05 */
	FSWR, /* 06 (SL_T) - String Literal Token */
	NOFS, /* 07 */
	NOFS, /* 08 */
	FSNR, /* 09 (CL_T) - Character Literal Token (Ex: 'x' or '9') */
	NOFS, /* 10 */
	NOFS, /* 11 */
	NOFS, /* 12 */
	FSNR, /* 13 (FPL_T) - Floating Point Literal (Ex: 123.456) */
	NOFS, /* 14 */
	NOFS, /* 15 */
	NOFS, /* 16 */
	NOFS, /* 17 */
	FSNR, /* 18 (FPL_T) - Floating Point Literal (Ex: 4e+33 OR 4e-33) */
	FSNR, /* 19 (IL_T) - Integer Literal (Ex: 123456) */
	NOFS, /* 20 */
	FSNR, /* 21 (MLC_T) - Multiline Comment */
	NOFS, /* 22 */
	FSNR, /* 23 (SLC_T) - Single Line Comment */
	NOFS, /* 24 */
	FSNR, /* 25 (FPL_T) - Floating Point Literal (Ex: 12.33e+44 OR 12.33e-5) */
	NOFS, /* 26 */
	NOFS, /* 27 */
	FSNR, /* 28 (VID_T) - Variable Identifier (Ex: _x OR _hands) */



};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
apc_intg startScanner(ReaderPointer psc_buf);
static apc_intg nextClass(apc_char c);			/* character class function */
static apc_intg nextState(apc_intg, apc_char);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(apc_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(apc_char lexeme[]);
Token funcID	(apc_char lexeme[]);
Token funcKEY	(apc_char lexeme[]);
Token funcErr	(apc_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static apc_char* keywordTable[KWT_SIZE] = {
	"data",
	"code",
	"int",
	"real",
	"string",
	"if",
	"then",
	"else",
	"while",
	"do"
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	apc_char indentationCharType;
	apc_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
