/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
* Student: Aliab Eman, Matthew Vecchio
* Student Number: 041-000-420, 041-004-137
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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/


ReaderPointer readerCreate(apc_intg size, apc_intg increment, apc_intg mode) {
	ReaderPointer readerPointer;  
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	if (mode != MODE_ADDIT && mode != MODE_MULTI && mode != MODE_FIXED) {
		return NULL;
	}	
	if (!size) {
		size = READER_DEFAULT_SIZE;	
		increment = READER_DEFAULT_INCREMENT;
	}
	if (!increment) {
		mode = MODE_FIXED;
	}

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	readerPointer->content = (apc_char*)malloc(size); 
	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	for (apc_intg i=0;i<NCHAR;i++)
		readerPointer->histogram[i] = 0;
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	readerPointer->flags = READER_EMP;
	return readerPointer;
	
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added 
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, apc_char ch) {
	apc_char* tempReader = NULL;
	apc_intg newSize = 0;
	/* TO_DO: Defensive programming */
	/* TO_DO: Reset Reallocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (apc_intg)sizeof(apc_char) < readerPointer->size) { //"if the reader is not full..."
		/* TO_DO: This buffer is NOT full */
		//readerPointer->position.wrte = readerPointer->position.wrte + READER_DEFAULT_INCREMENT;
		return readerPointer;
	} else {
		/* TO_DO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			tempReader = readerPointer->size + READER_DEFAULT_INCREMENT;
			/* TO_DO: Defensive programming */
			if (tempReader > READER_MAX_SIZE || tempReader < 0)
				tempReader = NULL;
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			tempReader = readerPointer->size * readerPointer->position.wrte + READER_DEFAULT_INCREMENT;
			/* TO_DO: Defensive programming */
			if (tempReader > READER_MAX_SIZE || tempReader < 0)
				tempReader = NULL;
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		tempReader = realloc(readerPointer->content, READER_DEFAULT_INCREMENT);
		readerPointer->size = tempReader;
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */
	}
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;
	/* TO_DO: Updates histogram */
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	return APC_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return APC_FALSE;
	/* TO_DO: Free pointers */
	free(readerPointer);
	return APC_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	return APC_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	return APC_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerSetMark(ReaderPointer const readerPointer, apc_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return APC_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return APC_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerPrint(ReaderPointer const readerPointer) {
	apc_intg cont = 0;
	apc_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	apc_intg size = 0; //size of file (amount of chars)
	apc_char c; //value of char.
	/* TO_DO: Defensive programming */
	if (!fileDescriptor)
		return READER_ERROR;
	c = (apc_char)fgetc(fileDescriptor); //store the file in c
	while (!feof(fileDescriptor)) { //while not in the end of file, loops from beginning of file until the end
		if (!readerAddChar(readerPointer, c)) { //if you can't add any more characters
			ungetc(c, fileDescriptor); //remove char at fileDescriptor pointer
			return READER_ERROR; //return reader error
		}
		if (fileDescriptor) {
				c = (apc_char)fgetc(fileDescriptor); //c is a character in the file input
		size++;
		}
	}
	/* TO_DO: Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0; //AE
	readerPointer->position.mark = 0; //AE
	return APC_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->position.read < 0) {
		printf("Cannot retract... reader position would go EOB");
		return APC_FALSE;
	}
	else {
		readerPointer->position.read -= READER_DEFAULT_INCREMENT;
	return APC_TRUE;
	}
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read/mark) */
	return APC_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_char* readerGetContent(ReaderPointer const readerPointer, apc_intg pos) {
	apc_char position;
	/* TO_DO: Defensive programming */
	if (pos < 0) {
		return NULL;
	}
	if (!readerPointer) {
		return NULL;
	}
	/* TO_DO: Return content (string) */
	position = readerPointer->content[pos];
	return position;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	return 0;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	apc_intg cont;
/* TO_DO: Defensive programming */
	if (readerPointer->position.wrte < 0)
		return NULL;
	/* TO_DO: Return wrte */
	cont = readerPointer->position.wrte;
	return cont;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	return 0;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetSize(ReaderPointer const readerPointer) {
	apc_intg sizeReader;

	/* TO_DO: Defensive programming */
	if (!readerPointer->size)
		readerPointer->size = READER_DEFAULT_SIZE;
	/* TO_DO: Return size */
	sizeReader = readerPointer->size;
	return sizeReader;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer->increment < 0)
		readerPointer->increment = READER_DEFAULT_INCREMENT;
	/* TO_DO: Return increment */
	apc_intg bufferIncrement;
	bufferIncrement = readerPointer->increment;
	return bufferIncrement;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	apc_intg readerMode;
	readerMode = readerPointer->mode;
	return readerMode;
	return 0;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return flags */
	switch (readerPointer->flags) {
	case(READER_DEFAULT_FLAG):
		return READER_DEFAULT_FLAG;
	case(READER_FUL):
		return READER_FUL;
	case(READER_EMP):
		return READER_EMP;
	case(READER_REL):
		return READER_REL;
	case(READER_END):
		return READER_END;
	default:
		return NULL;
	}
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
apc_intg readerShowStat(ReaderPointer const readerPointer) {
	apc_intg count = 0;
	apc_intg i = 0;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	/* TO_DO: Updates the histogram */
	while (readerPointer->histogram[i] != '\0') {
		count++;
		i++;
	}
	return count;
}
