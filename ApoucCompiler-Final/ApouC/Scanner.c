/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
* Student: Aliab Eman, Matthew Vecchio
* Student Number: 041-000-420, 041-004-137
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
apc_intg line;								/* Current line number of the source code */
extern apc_intg errorNumber;				/* Defined in platy_st.c - run-time error number */

extern apc_intg stateType[];
extern apc_char* keywordTable[];
extern PTR_ACCFUN finalStateTable[];
extern apc_intg transitionTable[][TABLE_COLUMNS];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

apc_intg startScanner(ReaderPointer  psc_buf) {
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(apc_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	apc_char c;	/* input symbol */
	apc_intg state = 0;		/* initial state of the FSM */
	apc_intg lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	apc_intg lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	apc_intg lexLength;		/* token length */
	apc_intg i;				/* counter */
	apc_char newc;			/* new char */
	
	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
			break;
		case '\t':
			currentToken.code = INDENT_T;
			return currentToken;

		case ':':
			currentToken.code = LOGICSTMT_T;
			return currentToken;
		case '\f':
			break;
		case '\n':
			currentToken.code = EOS_T;
			line++;		
			return currentToken;
			break;
		/* Cases for symbols */
//		case '\'':
//			currentToken.code = SQ_T;
//			return currentToken;

//		case '\"':
//			currentToken.code = DQ_T;
//			break;

	//	case '=':
		//	currentToken.code = ASSIGN_T;
			//currentToken.attribute.charValue = ASSIGN_T;
			//			break;
			//return currentToken;

		case '.': 
			currentToken.code = PERIOD_T;
			break;

		case ',':
			currentToken.code = SEP_T;
			return currentToken;
		case '^':
			currentToken.code = EXP_T;
			return currentToken;

		case '_':
			currentToken.code = U_T;
			return currentToken;

		case '(':
			currentToken.code = OP_T;
			currentToken.attribute.charValue = OP_T;
			return currentToken;
	
		case ')':
			currentToken.code = CP_T;
			currentToken.attribute.charValue = CP_T;
//			break;
			return currentToken;

		/* Comments */
		case '{': //multiline comments
			//currentToken.code = LC_T;
			newc = readerGetChar(sourceBuffer);
			do {
				c = readerGetChar(sourceBuffer);
				if (c == CHARSEOF0 || c == CHARSEOF255) {
					readerRetract(sourceBuffer);
					//return currentToken; //removed comment 
				}
				else if (c == '\n') {
					line++;
				}

			} while (c != '}' && c != CHARSEOF0 && c != CHARSEOF255);
			//currentToken.code = RC_T;
			break;

		case '#': //Single Line comments
			//currentToken.code = SC_T;
			newc = readerGetChar(sourceBuffer);
			do {
				c = readerGetChar(sourceBuffer);
				if (c == CHARSEOF0 || c == CHARSEOF255) {
					readerRetract(sourceBuffer);
					//return currentToken; //removed comment 
				}
			} while (c != '\n' && c != CHARSEOF0 && c != CHARSEOF255 && ' ');
			break;


		/* Cases for Arithmetic Operators */

		case '+':
			newc = readerGetChar(sourceBuffer);
			//case 1
			if (isdigit(newc))
			currentToken.code = SIGNP_T;
			//case 2
			if (newc == ' ') {
				currentToken.code = OP_ADD_T;
				currentToken.attribute.arithmeticOperator = OP_ADD;
			}
			return currentToken;
		case '-':
			newc = readerGetChar(sourceBuffer);
			//case 1
			if (isdigit(newc))
			currentToken.code = SIGNN_T;
			//case 2
			if (newc == ' ') {
			currentToken.code = OP_SUB_T;
			currentToken.attribute.arithmeticOperator = OP_SUB;
			}
			return currentToken;
		case '*':
			currentToken.code = OP_MUL_T;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			return currentToken;
		case '/':
			currentToken.code = OP_DIV_T;
			currentToken.attribute.arithmeticOperator = OP_DIV;
			return currentToken;
		case '=':
			newc = readerGetChar(sourceBuffer);
			if (newc == ' ') {
				currentToken.code = EQUALS_T;
			}
			if (newc == '=') {
				currentToken.code = OP_EQ_T;
				currentToken.attribute.relationalOperator = OP_EQ;
			}
			return currentToken;
		case '!':
			newc = readerGetChar(sourceBuffer);
			if (newc == ' ') {
				currentToken.code = OP_NOT_T;
				currentToken.attribute.logicalOperator = OP_NOT;
			}
			if (newc == '=') {
			currentToken.code = OP_NE_T;
			currentToken.attribute.relationalOperator = OP_NE;
			}
			return currentToken;
		case '>':
			currentToken.code = OP_GT_T;
			currentToken.attribute.relationalOperator = OP_GT;
			return currentToken;
		case '<':
			currentToken.code = OP_LT_T;
			currentToken.attribute.relationalOperator = OP_LT;
			return currentToken;
		case '&':
			newc = readerGetChar(sourceBuffer);
			if (newc == '&') {
			currentToken.code = OP_AND_T;
			currentToken.attribute.logicalOperator = OP_AND;
			return currentToken;
			}
			break;
		case '|':
			newc = readerGetChar(sourceBuffer);
			if (newc == '|') {
			currentToken.code = OP_OR_T;
			currentToken.attribute.logicalOperator = OP_OR;
			return currentToken;
			}
			break;

		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((apc_intg)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

apc_intg nextState(apc_intg state, apc_char c) { //transform the char c into a class
	apc_intg col;
	apc_intg next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*  Changes to Transition Table, new count:
	[A-z] ,[0-9],    ' ,   " ,  #   ,  .  ,  ^  , +/- ,   _  ,   (   ,Other  ,    \e    ,    SEOF,  \n    }
	, L(0), D(1), SQ(2),DQ(3), SC(4), P(5), E(6), S(7), U(8) , OP( 9),  O(10), sigma(11), EOF(12), EOS(13)} */

apc_intg nextClass(apc_char c) {
	apc_intg val = -1;
	switch (c) {

	case SQ_T: //single quote: for char ID
		val = 2;
		break;
	case DQ_T: //double quote: for string ID
		val = 3;
		break;
//	case LC_T: //for left brace in MLC
//		val = 4;
//		break;
//	case RC_T: //for right brace in MLC
//		val = 5;
//		break;
	case SC_T: //hash for for SLC
		val = 4;
		break;
	case PERIOD_T: // for floating points
		val = 5;
		break;
	case EXP_T: //for exponential floats
		val = 6;
		break;
	case SIGNP_T: //for exponential floats
		val = 7;
		break;
	case SIGNN_T: //for exponential floats
		val = 7;
		break;
	case U_T: //underscore for identifying VID's
		val = 8;
		break;
	case OP_T: // for MNID's
		val = 9;
		break;
//	case CP_T: // for MNID's
//		val = 12;
//		break;
	case SIGMA_T:
		val = 11;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 12;
		break;

	case EOS_T:
		val = 13;
		break;

//	case INDENT_T:
//		val = 13;
//		break;

//	case LOGICSTMT_T:
//		val = 14;
//		break;

//	case EQUALS_T:
//		val = 14;
//		break;
	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else
			val = 10;
	}

	return val;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_long tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[29])(lexeme); 
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = IL_T;
			currentToken.attribute.intValue = (apc_intg)tlong;
		}
		else {
			currentToken = (*finalStateTable[29])(lexeme); 
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */
/* Need to check if ID is a MNID, if not, identify it as a KEYWORD/ ERROR*/


Token funcID(apc_char lexeme[]) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	apc_char lastch = lexeme[length -1];
	apc_intg isID = APC_FALSE;
	switch (lastch) {
	case MNIDPREFIX:
		currentToken.code = MNID_T;
		isID = APC_TRUE;
		break;

	default:
		// Test Keyword
		currentToken = funcKEY(lexeme);
		break;
	}
	if (isID == APC_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}

/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_intg i = 0, len = (apc_intg)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = SL_T;
	return currentToken;
}

/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_intg kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KEY_T;
		currentToken.attribute.codeType = kwindex; //kwindex
	}

	else {
		currentToken = funcErr(lexeme);
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_intg i = 0, len = (apc_intg)strlen(lexeme);
	apc_intg x = 0; //check

	for (int i = 0; i < len; i++) {
		if (lexeme[i] == ('\n'))
			x = 1;
	}

	if (x == 0) {
		currentToken.code = VID_T;
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
		return currentToken;
	}

	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

apc_void printToken(Token t) {
	extern apc_char* keywordTable[]; /* link to keyword table in */
	switch (t.code) {

		/*
		Operator Token attributes:
			OP_ADD, OP_SUB, OP_MUL, OP_DIV
	} AriOperator;
	typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
	typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
	typedef enum SourceEndOfFile {
		SEOF_0, SEOF_255
		*/


	//Functional Token Cases:
	case KEY_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;



	case EQUALS_T:
		printf("EQUALS_T\t\t%s\n", t.attribute.idLexeme);
		break;

	case IL_T:
		printf("IL_T\t\t%d\n", t.attribute.intValue);
		break;
//	case INDENT_T:
//		printf("INDENT_T\t\t%s\n", t.attribute.idLexeme);
//		break;
	case SQ_T:
		printf("SQ_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case FPL_T:
		printf("FPL_T\t\t%.4f\n", t.attribute.floatValue);
		break;
	case SEOF_T:
		printf("SEOF_T\n", t.attribute.seofType);
		break;
	case LOGICSTMT_T:
		printf("LOGICSTMT_T\t\t%s\n", t.attribute.idLexeme);
		break;
		//Broken Token Cases:
	case CL_T:
		printf("CL_T\t\t%d\t ", (apc_intg)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (apc_intg)t.attribute.codeType));
		break;
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;

	case EOS_T:
		printf("EOS_T\n");
		break;


	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;

	case VID_T:
		printf("VID_T\t\t%s\n", t.attribute.idLexeme);
		break;

	case SL_T:
		printf("STR_T\t\t%d\t ", (apc_intg)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (apc_intg)t.attribute.codeType));
		break;

	case SEP_T:
		printf("SEP_T\n");
		break;

	case OP_T:
		printf("OP_T\n");
		break;

	case CP_T:
		printf("CP_T\n");
		break;

		/* Arithmetic Operators		*/

	case SIGNP_T:
		printf("POSITIVE_EXP\t\t%d\n", t.attribute.arithmeticOperator);
		break;

	case SIGNN_T:
		printf("NEGATIVE_EXP\t\t%d\n", t.attribute.arithmeticOperator);
		break;

	case OP_ADD_T:
		printf("OP_ADD_T\n");
		break;
	case OP_SUB_T:
		printf("OP_SUB_T\n");
		break;
	case OP_MUL_T:
		printf("OP_MUL_T\n");
		break;
	case OP_DIV_T:
		printf("OP_DIV_T\n");
		break;
	case OP_EQ_T:
		printf("OP_EQ_T\n");
		break;
	case OP_NE_T:
		printf("OP_NE_T\n");
		break;
	case OP_GT_T:
		printf("OP_GT_T\n");
		break;
	case OP_LT_T:
		printf("OP_LT_T\n");
		break;
	case OP_AND_T:
		printf("OP_AND_T\n");
		break;
	case OP_OR_T:
		printf("OP_OR_T\n");
		break;
	case OP_NOT_T:
		printf("OP_NOT_T\n");
		break;

/*	case LC_T:
		printf("LPR_T\n");
		break;
	case LC_T:
		printf("LPR_T\n");
		break;
	case LC_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
*/
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/

/* Arithmetic Function:
OP_ADD_T, /* Add Operator 
OP_SUB_T, /* Subtract Operator 
OP_MUL_T, /* Multiply Operator 
OP_DIV_T, /* Division Operator 
OP_EQ_T, /* EQUALS (==) Operator 
OP_NE_T, /* NOT EQUAL (!=) Operator 
OP_GT_T, /* Greater Than Operator ( > )
OP_LT_T, /* Less Than Operator ( < ) 
OP_AND_T, /* AND Operator 
OP_OR_T, /* OR Operator 
OP_NOT_T /* NOT Operator
*/


Token funcCL(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_intg i = 0, len = (apc_intg)strlen(lexeme);
	currentToken.attribute.contentChar = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = CL_T;
	return currentToken;
}

Token funcMLC(apc_char lexeme[]) {
	Token currentToken = { 0 };
	return currentToken;
}

Token funcSLC(apc_char lexeme[]) {
	Token currentToken = { 0 };
	return currentToken;

}

Token funcVar(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_intg kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KEY_T;
		currentToken.attribute.codeType = kwindex;
	}

	else {
		currentToken = funcErr(lexeme);
	}
	return currentToken;
}


/* Floating point function taken from week 10 demo, hybridized to acknowledge
ApouC compiler floating point numbers */

Token funcFPL(apc_char lexeme[]) {
	Token currentToken = { 0 };
	apc_doub tDouble = atof(lexeme);
	if (tDouble == 0.0 || tDouble >= FLT_MIN && tDouble <= FLT_MAX) {
		currentToken.code = FPL_T;
		currentToken.attribute.floatValue = (apc_real)tDouble;
	}
	else {
		currentToken = (*finalStateTable[29])(lexeme);
	}

	return currentToken;
}
