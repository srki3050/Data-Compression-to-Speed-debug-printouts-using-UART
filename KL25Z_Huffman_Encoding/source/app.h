/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: app.h
 * Date	 				: 05/02/2022
 * Brief 				: Prototype file Command Process initialization routines. More processing routines on command_processor.c/.h
 */
#ifndef APP_H_
#define APP_H_

#include "stdio.h"
#include "command_processor.h"
#include "cbfifo.h"
#include "test_cbfifo.h"
/* Function : command_processor
 * Returns	: None
 * Arguments: None
 * Purpose	: this function should be called in the main while loop
 * 			  gets the characters and performs basic command processor operations
 */
void command_processor(char *name);

#endif /* APP_H_ */
