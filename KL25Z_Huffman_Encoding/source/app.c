/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: app.c
 * Date	 				: 05/02/2022
 * Brief 				: Command Process initialization routines. More processing routines on command_processor.c/.h
 * 						  For documentation see app.h
 */
#include "app.h"

void command_processor(char *name){
	char c = getchar();
		  if(c == '?'){
			  printf("%c ",c);
			  accumulate(name);
			  printf("\r\n");
			  process_command(name);
		  }
		  else{
			  putchar(c);
			  printf("\r\n");
		  }
}
