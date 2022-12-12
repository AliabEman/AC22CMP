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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

apc_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) { //if file is not empty run the program
		program();
		printf("%s%s\n", STR_LANGNAME, ": Program parsed"); 
		//The use of recursion in my program keeps calling the program() function
	} 
	matchToken(SEOF_T, NO_ATTR); //expected to see SEOF_T at the end of the tokenizer
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
apc_void matchToken(apc_intg tokenCode, apc_intg tokenAttribute) {
	apc_intg matchFlag = 1;
	switch (lookahead.code) {
	case KEY_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
apc_void syncErrorHandler(apc_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
apc_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
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
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 * 
 * ApouC BNF for Program Statement:
 * <program> -> <statements>
 * def greeting(): <- recognizing this line with the first 4 matchTokens (KEY_T MNID_T CP_T LOGICSTMT_T)
        print("Hello World!") <- this line is a codeSession
	greeting() <- recognizing the MNID_T CP_T as a function call 
 * Ex of statements (function calling):
 * <functions> ->
 *			
 ***********************************************************
 */
apc_void program() {
	switch (lookahead.code) {
	case KEY_T:
		//if we are defining a function
		/*
		def greeting(): <- recognizing this line with the first 4 matchTokens (KEY_T MNID_T CP_T LOGICSTMT_T)
        print("Hello World!") <- this line is a codeSession
		greeting() <- recognizing the MNID_T CP_T as a function call
		*/
		//if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 4) == 0) {
			//if (strncmp(lookahead.code, KW_def, 5) == 0) {
		if (lookahead.attribute.codeType == KW_def) { //function definitions
			matchToken(KEY_T, KW_def); // def
			matchToken(MNID_T, NO_ATTR); // function0(
			matchToken(CP_T, NO_ATTR); // )
			matchToken(LOGICSTMT_T, NO_ATTR); // :
			matchToken(EOS_T, NO_ATTR); // \n
			matchToken(INDENT_T, NO_ATTR); // <tab>
			codeSession(); // printf("Hello World!")
			matchToken(MNID_T, NO_ATTR); // function0(
			matchToken(CP_T, NO_ATTR); // )
			break;
		}
		else {
			printError();
		}
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	case VID_T:
		codeSession();
		break;

	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}

	if (lookahead.code != SEOF_T) {
		//lookahead = tokenizer();
		program();
	}
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
//apc_void dataSession() {
	//matchToken(KEY_T, KW_data);
//	matchToken(LBR_T, NO_ATTR);
//	optVarListDeclarations();
//	matchToken(CP_T, NO_ATTR);
//	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
//}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
apc_void optVarListDeclarations() {
	switch (lookahead.code) {

	default: // e
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 * 
 * ApouC codeSession statement:
 * Ex: printf("Hello World!")
 * 
 * Ex: ab = 4 + 3
 ***********************************************************
 */
apc_void codeSession() {

//	matchToken(KEY_T, KW_code);
//	matchToken(OP_T, NO_ATTR);
	optionalStatements();
//	matchToken(CP_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
apc_void optionalStatements() {
	switch (lookahead.code) {
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, "", 6) == 0)
			) {
			statements();
			break;
		}
	case IL_T:
			matchToken(IL_T, NO_ATTR);
			statements();
			break;
	case FPL_T:
			matchToken(FPL_T, NO_ATTR);
			statements();
			break;
	case SL_T:
			matchToken(SL_T, NO_ATTR);
			statements();
			break;
	case CL_T:
			matchToken(IL_T, NO_ATTR);
			statements();
			break;
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		statements();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
apc_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
apc_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
		if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
		//	statements();
			break;
		}
		break;
	case IL_T:
			statements();
			break;
	case FPL_T:
			statements();
			break;
	case SL_T:
			statements();
			break;
	case CL_T:
			statements();
			break;
	case KEY_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 6) == 0) {
			statements();
			break;
		}
	case EQUALS_T:
		statements();
		break;

	case OP_T:
		statements();
		break;

	case OP_ADD:
	case OP_SUB:
	case OP_DIV:
	case OP_MUL:
		statements();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input( ), MNID_T(print( ) }
 ***********************************************************
 */
apc_void statement() {
	switch (lookahead.code) {
	case KEY_T:
		switch (lookahead.attribute.codeType) {
		case KW_if:
		break;
		
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 5) == 0) {
			outputStatement();
		}
		if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 5) == 0) {
			inputStatement();
		}
		break;
	case IL_T:
	case FPL_T:
	case SL_T:
	case CL_T:
		outputVariableList();
		break;

	case EQUALS_T:
		matchToken(EQUALS_T, NO_ATTR);
		statements();
		break;

	case VID_T:
		matchToken(VID_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;

	case OP_T:
	case CP_T:
		parenthesisOperators();
		break;

	case OP_ADD:
	case OP_SUB:
	case OP_DIV:
	case OP_MUL:
		statements();
		break;

	default:
		printError();
	}

	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

apc_void parenthesisOperators() {
	switch (lookahead.code) {
	case OP_T:
		matchToken(OP_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	case CP_T:
		matchToken(CP_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	default:
		;
	}
}



/*
 ************************************************************
 * Input Statement
 * BNF: <input statement> -> print& (<input statementPrime>);
 * FIRST(<input statement>) = { MNID_T[ input( ] }
 ***********************************************************
 */
apc_void inputStatement() {
	matchToken(MNID_T, KW_input); // input(
//	matchToken(LPR_T, NO_ATTR);
	outputVariableList(); //parameter
	matchToken(CP_T, NO_ATTR); // )
	matchToken(EOS_T, NO_ATTR); // \n
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T[ print( ] }
 ***********************************************************
 */
apc_void outputStatement() {
	matchToken(MNID_T, KW_print); // print(
	//	matchToken(LPR_T, NO_ATTR);
	outputVariableList(); // parameter
	matchToken(CP_T, NO_ATTR); // )
	matchToken(EOS_T, NO_ATTR); // \n
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IL_T, FPL_T, SL_T, CL_T, ϵ }
 ***********************************************************
 */
apc_void outputVariableList() {
	switch (lookahead.code) {
	case SL_T:
		matchToken(SL_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	case IL_T:
		matchToken(IL_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	case CL_T:
		matchToken(SL_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		outputArithmeticOperatorsList();
		break;
	default:
		printError();
	}
	if (lookahead.code == SEP_T) {
		outputVariableList();
	}

	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}



/*
 ************************************************************
 * Output Arithmetic Operators List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IL_T, FPL_T, SL_T, CL_T, ϵ }
 ***********************************************************
 */
apc_void outputArithmeticOperatorsList() {
	switch (lookahead.code) {
	case OP_ADD_T:
		matchToken(OP_ADD_T, NO_ATTR);
		break;
	case OP_SUB_T:
		matchToken(OP_SUB_T, NO_ATTR);
		break;
	case OP_MUL_T:
		matchToken(OP_MUL_T, NO_ATTR);
		break;
	case OP_DIV_T:
		matchToken(OP_DIV_T, NO_ATTR);
		break;
	default:
		;
	}
}