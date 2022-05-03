/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: cbfifo.c
 * Date	 				: 05/02/2022
 * Brief 				: Command Processor Statements to print command line results as you require with the help of a command table
 * References			: Code inspired from Howdy Pierce's Lecture on Command Processors.
 */
#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_
#include "stdio.h"
#include "string.h"
#include "cbfifo.h"
#include "uart.h"
#include "stdbool.h"
#include "assert.h"
typedef void (*command_handler_t)(int, char *argv[]);
/* A table driven data structure which has a function pointer to it.
 * This structure accepts a string,
 * A function that redirects to that string
 * Description statement of that string.
 */
typedef struct{
	const char *name;
	command_handler_t handler;
	const char *help_string;
}command_table_t;
/* Stores the input data to a character buffer for command processing.
 * input  : the typed character in UART terminal (UART->D register)
 * output : the character stored in a character buffer for actual command processing
 */
char *accumulate();
/*
 * Lexicalisation based on ' '(SPACE), '\r' (CR), '\n (NL)
 * Input  : the accumulated string
 * Output : The string stored in argv[] array of strings bifurcated by
 * 			" " (SPACE), "\r" (CARRIAGE_RETURN), "\n" (NEW_LINE)
 * result : now argv[] contains the split strings.
 * e.g : if input is "Welcome to PES", output = argv[0] = Welcome, argv[1] = to, argv[2] = PES
 */
void process_command(char *input);

#endif /* COMMAND_PROCESSOR_H_ */
