/*
 * Huffman codes
 *
 * THIS FILE IS AUTO-GENERATED...Do not Edit
 */
#ifndef HUFFCODES_H_
#define HUFFCODES_H_

#include<stdint.h>

typedef struct{
    unsigned char symbol;       //Symbol being Coded
    uint32_t code;              //Binary code for symbol
    int code_bits;              //Number of bits in code
}huffman_code_t;
#define HUFF_CODE_END_SYMBOL '\0'
#define HUFF_CODE_MIN_LENGTH (3)
#define HUFF_CODE_MAX_LENGTH (20)

huffman_code_t huffman_code[] = {
{'h',0x00,5},         // h : 00000
{'2',0x01,5},         // 2 : 00001
{':',0x1,4},         // : : 0001
{'G',0x100,11},         // G : 00100000000
{'>',0x101,11},         // > : 00100000001
{'X',0x081,10},         // X : 0010000001
{'F',0x041,9},         // F : 001000001
{'E',0x21,8},         // E : 00100001
{'S',0x22,8},         // S : 00100010
{'O',0x046,9},         // O : 001000110
{'Y',0x238,12},         // Y : 001000111000
{'~',0x0472,13},         // ~ : 0010001110010
{'!',0x08e6,14},         // ! : 00100011100110
{'<',0x08e7,14},         // < : 00100011100111
{'Q',0x23a,12},         // Q : 001000111010
{'+',0x23b,12},         // + : 001000111011
{'V',0x11e,11},         // V : 00100011110
{'H',0x11f,11},         // H : 00100011111
{'6',0x09,6},         // 6 : 001001
{'c',0x05,5},         // c : 00101
{'n',0x06,5},         // n : 00110
{'d',0x07,5},         // d : 00111
{'_',0x40,8},         // _ : 01000000
{'I',0x41,8},         // I : 01000001
{'R',0x42,8},         // R : 01000010
{'N',0x086,9},         // N : 010000110
{'U',0x087,9},         // U : 010000111
{'9',0x11,6},         // 9 : 010001
{'7',0x12,6},         // 7 : 010010
{'u',0x13,6},         // u : 010011
{'8',0x14,6},         // 8 : 010100
{'g',0x2a,7},         // g : 0101010
{'A',0x56,8},         // A : 01010110
{'T',0x0ae,9},         // T : 010101110
{'B',0x0af,9},         // B : 010101111
{'p',0x16,6},         // p : 010110
{'5',0x17,6},         // 5 : 010111
{'s',0x0c,5},         // s : 01100
{'-',0x34,7},         // - : 0110100
{'/',0x35,7},         // / : 0110101
{',',0x0d8,9},         // , : 011011000
{'M',0x0d9,9},         // M : 011011001
{'=',0x6d,8},         // = : 01101101
{'C',0x6e,8},         // C : 01101110
{'x',0x6f,8},         // x : 01101111
{'t',0x0e,5},         // t : 01110
{'i',0x0f,5},         // i : 01111
{' ',0x4,3},         //   : 100
{'r',0x14,5},         // r : 10100
{'P',0xa8,8},         // P : 10101000
{'L',0x152,9},         // L : 101010010
{'"',0x153,9},         // " : 101010011
{'b',0x55,7},         // b : 1010101
{'3',0x2b,6},         // 3 : 101011
{'0',0xb,4},         // 0 : 1011
{'f',0x60,7},         // f : 1100000
{'y',0xc2,8},         // y : 11000010
{'v',0xc3,8},         // v : 11000011
{'.',0x31,6},         // . : 110001
{'k',0x32,6},         // k : 110010
{'l',0x33,6},         // l : 110011
{'1',0x1a,5},         // 1 : 11010
{'m',0x6c,7},         // m : 1101100
{'o',0x37,6},         // o : 110111
{'e',0xe,4},         // e : 1110
{'4',0x3c,6},         // 4 : 111100
{'D',0x7a,7},         // D : 1111010
{'[',0x7b,7},         // [ : 1111011
{'a',0x3e,6},         // a : 111110
{']',0x7e,7},         // ] : 1111110
{'Z',0x3f80,14},         // Z : 11111110000000
{'%',0x3f81,14},         // % : 11111110000001
{'@',0x7f04,15},         // @ : 111111100000100
{'J',0x7f05,15},         // J : 111111100000101
{'#',0x3f83,14},         // # : 11111110000011
{'?',0x1fc2,13},         // ? : 1111111000010
{'*',0x7f0c,15},         // * : 111111100001100
{'&',0x7f0d,15},         // & : 111111100001101
{'^',0xfe1c,16},         // ^ : 1111111000011100
{'}',0xfe1d0,20},         // } : 11111110000111010000
{'{',0xfe1d1,20},         // { : 11111110000111010001
{'`',0x7f0e9,19},         // ` : 1111111000011101001
{'|',0x3f875,18},         // | : 111111100001110101
{'	',0x1fc3b,17},         // 	 : 11111110000111011
{';',0x7f0f,15},         // ; : 111111100001111
{'W',0x7f1,11},         // W : 11111110001
{'K',0xfe4,12},         // K : 111111100100
{'q',0x1fca,13},         // q : 1111111001010
{'j',0x1fcb,13},         // j : 1111111001011
{'z',0x7f3,11},         // z : 11111110011
{')',0x1fd,9},         // ) : 111111101
{'(',0x1fe,9},         // ( : 111111110
{'w',0x1ff,9},         // w : 111111111
{HUFF_CODE_END_SYMBOL,0,0}};

/* @brief - With the above specified huffman tree, this function writes the algorithm to encode
             every symbol to its corresponding huffman code to send over UART. Called in Sys_write
             system call function, the data is compressed in here.
*  Parameters
*  message - The entire message to be encoded
*  buffer  - A buffer to store the output encoded messages
*  nbytes  - Size of the buffer to ensure that there is no buffer overflow in any given scenario
*  Returns
            The number of bytes successfully encoded
*/
int huffman_encode(const char *message,uint8_t *buffer,size_t nbytes);

/* @brief - Once the huffman encoding is completed perform huffman decoding
*  Parameters
*  coded   					- The buffer which has the compressed bits
*  codebytes    			- size of the encoder buffer
*  resultant_buffer 		- The resultant buffer where you have to store the decoded string
*  Returns
            The number of bytes successfully encoded
*/
int huffman_decode(uint8_t *coded, size_t codedbytes,char *resultant_buffer);


#endif /* HUFFCODES_H_ */
