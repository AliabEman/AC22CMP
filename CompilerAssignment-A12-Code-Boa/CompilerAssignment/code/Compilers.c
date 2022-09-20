/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
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
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12, A22, A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

boa_intg main(int argc, char** argv) {
	boa_intg i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	boa_char option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	/*
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER ....]\n\n");
		mainScanner(argc, argv);
		break;
	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;
	*/
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: pRINT lOGO
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/
boa_void printLogo() {
	/*
	boa_char* strLogo = " _________________________________\n|                                 |\n| ........ BOA LANGUAGE ......... |\n|     __    __    __    __        |\n|    /  \\  /  \\  /  \\  /  \\       |\n| __/  __\\/  __\\/  __\\/  __\\__    |\n| _/  /__/  /__/  /__/  /_____|   |\n|  \\_/ \\   / \\   / \\   / \\  \\___  |\n|       \\_/   \\_/   \\_/   \\___o_> |\n|                                 |\n| .. ALGONQUIN COLLEGE - 2022F .. |\n|_________________________________|\n";
	printf("%s", strLogo);
	*/
	printf("%s%s%s%s%s%s%s%s%s%s%s%s",
		" _________________________________ \n",
		"|                                 |\n",
		"| ....... 'BOA' LANGUAGE ........ |\n",
		"|     __    __    __    __        |\n",
		"|    /  \\  /  \\  /  \\  /  \\       |\n",
		"| __/  __\\/  __\\/  __\\/  __\\__    |\n",
		"| _/  /__/  /__/  /__/  /_____|   |\n",
		"|  \\_/ \\   / \\   / \\   / \\  \\___  |\n",
		"|       \\_/   \\_/   \\_/   \\___o_> |\n",
		"|                                 |\n",
		"| .. ALGONQUIN COLLEGE - 2022F .. |\n",
		"|_________________________________|\n"
	);
}
