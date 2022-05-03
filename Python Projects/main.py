'''
/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: main.py
 * Date	 				: 05/02/2022
 * Brief 				: Given a file, generate a huffman tree and create the perfect .h file (huffcodes.h)
 * References			: https://www.programiz.com/dsa/huffman-coding
 */
Command to write all the contents of the file to a string
'''
string = ""
f = open("Log_files.txt","r")
contents = f.read()
string = str(contents)
# Creating tree nodes
'''
Build the huffman tree based on the file contents
A tree structure has a left and right side  for both parents and children until the root node
'''
class NodeTree(object):

    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right

    def children(self):
        return self.left, self.right

    def nodes(self):
        return self.left, self.right

    def __str__(self):
        return '%s_%s' % (self.left, self.right)
# Main function implementing huffman coding
def huffman_code_tree(node, left=True, binstring=''):
    if type(node) is str:
        return {node: binstring}
    (l, r) = node.children()
    d = dict()
    d.update(huffman_code_tree(l, True, binstring + '0'))
    d.update(huffman_code_tree(r, False, binstring + '1'))
    return d
# Calculating frequency
freq = {}
for c in string:
    if c in freq:
        freq[c] += 1
    else:
        freq[c] = 1
freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)
nodes = freq
while len(nodes) > 1:
    (key1, c1) = nodes[-1]
    (key2, c2) = nodes[-2]
    nodes = nodes[:-2]
    node = NodeTree(key1, key2)
    nodes.append((node, c1 + c2))
    nodes = sorted(nodes, key=lambda x: x[1], reverse=True)
huffmanCode = huffman_code_tree(nodes[0][0])

'''
Function to convert into decimal from right to left to make it comfortable for huffman table build
For eg. if code is 1111100001, then convert value would be 0x3E1, with length 10
'''
#convert the binary to hexadecimal format
def bin_to_dec(binary):
    solution = 0
    multiplier = 1
    for i in range(len(binary)-1, -1, -1):
        solution += int(binary[i]) * multiplier
        multiplier *= 2
    if solution > 9:
        return chr(solution + 87)
    return str(solution)
def binary_to_hex(binary):
    result = ""
    index = len(binary)
    while index >= 4:
        current = binary[index-4:index]
        result = result + bin_to_dec(current)
        index -= 4
    if index > 0:
        current = binary[:index]
        result = result + bin_to_dec(current)
    result = result[::-1]
    return result
'''
Extract the value from the huffman dictionary to get the correct hexvalue and length thereby generating the table
'''
values = list(huffmanCode.values())
keys = list(huffmanCode.keys())
length = list()
hex_values = list()
for i in range(len(values)):
    length.append(len(values[i]))
    hex_values.append(binary_to_hex(values[i]))
'''
Simple assert statements to check whether all the huffman elements are unique.
'''
assert len(set(values)) == len(values)
cdr = """\
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
#define HUFF_CODE_END_SYMBOL '\\0'
"""
print(cdr, end="")
print(f"#define HUFF_CODE_MIN_LENGTH ({min(length)})")
print(f"#define HUFF_CODE_MAX_LENGTH ({max(length)})")
print("")
print("huffman_code_t huffman_code[] = {")
for i in range(len(huffmanCode)):
    if i != 63:
        print("{", end="")
        print(f"'{keys[i]}',", end="")
        print(f"0x{hex_values[i]},", end="")
        print(f"{length[i]}", end="")
        print("},", end="")
        print(f"         // {keys[i]} : {values[i]}")
print("{HUFF_CODE_END_SYMBOL,0,0}};")
print("")
comments = """\
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
"""
print(comments)
print("")
print("#endif /* HUFFCODES_H_ */")