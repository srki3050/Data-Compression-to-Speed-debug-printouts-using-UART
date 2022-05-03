/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: huffcodes.c
 * Date	 				: 05/02/2022
 * Brief 				: Huffman Encoding and decoding operations to test in command processor.
 * References			: Code used from Howdy' Pierce's Lecture on Media Compression
 *						  For documentation see huffcodes.h
 */
#include "huffcodes.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define MASK(x)	((1U << x) - 1)
/* Function		: grab_code()
 * Brief		: gets the huffman for the current object.
 * Parameters	: coded	  :	pointer to the coded data that is yet to be decoded
 * 				  consumer: Total number of bits consumed already before the current pointer.
 * 				  num_bits:	current bits, (equal to the current length in the huffman_table)
 * Returns		: the code for the current symbol
 */
static uint32_t grab_code(uint8_t *coded, int consumed, int num_bits){
    uint32_t ret = 0;
    int idx = 0;
    int bits_grabbed = 0;
    while(bits_grabbed < num_bits){
        int this_grab = min(num_bits - bits_grabbed, 8 - consumed);
        int read_shift = 8 - consumed - this_grab;
        uint32_t tmp = (coded[idx] >> read_shift) & MASK(this_grab);
        int write_shift = num_bits - bits_grabbed - this_grab;
        ret |= tmp << write_shift;
        bits_grabbed += this_grab;
        if(this_grab + consumed == 8){
            idx++;
            consumed = 0;
        }
    }
    return ret;
}
int huffman_encode(const char *message,uint8_t *buffer,size_t nbytes)
{
	int buf_idx = 0; //Current write position encoded
	int bits_written = 0; // Number of bits already written at buf_idx
	int hc_idx;	//Huffman code index for the current symbol

	memset(buffer,0,nbytes);

	for(const char *p = message; *p!= '\0'; p++)
	{
		for(hc_idx = 0; huffman_code[hc_idx].symbol != *p; hc_idx++)
			assert(huffman_code[hc_idx].symbol != HUFF_CODE_END_SYMBOL);

		uint32_t code = huffman_code[hc_idx].code;
		int code_bits = huffman_code[hc_idx].code_bits;

		while(code_bits > 0)
		{
			//this_write: the number of bits to encode in this step
			int this_write = min(8-bits_written, code_bits);
			assert(bits_written + this_write <= 8);

			//read_shift: position within code to get the bits from
			//tmp: bits to write, shifted down to lsb
			int read_shift = code_bits - this_write;
			uint32_t tmp = (code >> read_shift) & MASK(this_write);

			//buff[buf_idx]: buffer we're writing into
			//write_shift: shift to fit into this byte of the buffer
			int write_shift = 8 - bits_written - this_write;
			buffer[buf_idx] |= tmp << write_shift;

			bits_written += this_write;
			code_bits -= this_write;

			if(bits_written == 8)
			{
				bits_written = 0;
				buf_idx++;
				assert(buf_idx < nbytes);
			}
		}
	}
	return buf_idx;
}
int huffman_decode(uint8_t *coded, size_t codedbytes,char *resultant_buffer){
    char *p = resultant_buffer;      //position in message buffer
    uint32_t cur_code;      //current candidate code
    int codelen = 0;        //current candidate code length
    int coded_idx = 0;      //current position in coded data
    int bits_consumed = 0;  //number of bits consumed from current byte
    int hc_idx = 0;         //index into the huffman table

    while(coded_idx < codedbytes){
        for(codelen = HUFF_CODE_MIN_LENGTH; codelen <= HUFF_CODE_MAX_LENGTH;codelen++){
            //grab codelen bits from the buffer
            cur_code = grab_code(coded+coded_idx,bits_consumed,codelen);
            //lookup code in the huffcodes array
            for(hc_idx = 0;huffman_code[hc_idx].symbol != HUFF_CODE_END_SYMBOL;hc_idx++)
                if(codelen == huffman_code[hc_idx].code_bits && cur_code == huffman_code[hc_idx].code)
                    break;
            if(huffman_code[hc_idx].symbol == HUFF_CODE_END_SYMBOL)
                continue;
            break;
        }
        assert(codelen <= HUFF_CODE_MAX_LENGTH);
        //if we're here, we've found the code
        *p++ = (char)huffman_code[hc_idx].symbol;
        bits_consumed += codelen;
        while(bits_consumed > 8){
            bits_consumed -= 8;
            coded_idx++;
        }
    }
    *p = 0;
    return p-resultant_buffer;
}
