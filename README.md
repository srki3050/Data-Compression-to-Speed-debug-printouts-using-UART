# ECEN-5813---Course-Project
Print Debug Printouts using Huffman Compression and Decompression using KL25Z

Contents
1. Overall Summary
2. Python Code to Generate a huffcodes.h file
3. Huffman Encoding Explanation
4. Huffman Decoding Explanation
5. Command Processor Explanation
6. Overall Program Flow
7. Test Suites
8. Final Working Image Screenshot
9. Conclusion
10. References
11. Proposal Questions

Overall Summary

This course project develops Huffman Encoding and Decoding Algorithm and write data to KL25Z.
1. Technically, the decoding should have been done in the PC side. But since I only posses a windows machine, I just had to print my encoded and decoded
   Strings in the command line processor.
2. I have written a python code that develops the .h file for any given text file. I have used my friend's debug files from his linux system so that, 
   I am able to do python coding to generate the huffman table for that. (main.py)
3. Then I perform the huffman Encoding on the command processor on typing command = "encoded"
4. Decoding is performed by typing the command = "Decoded"
5. The gains from huffman calculation is figured out by the formula gains = ((original_length - compressed_length)/(original_length))
   gains in percentage = gains * 100, so that you can display integer values, it is generally difficult and not advisable to use float prints in embedded system microcontrollers.

Python Code to Generate a huffcodes.h file
1. There is a python project attached with the folder name Python Projects that has a python code that outputs a huffcodes.h file
   step.1 Create a log_files.txt file that has the terminal debug printouts
   step.2 Store the contents of the file into a python string
   step.3 create a huffman tree.
   step.4 Print the necessary statements as a part of the .h file
   step.5 Extract the values from the created dictionary and change it into huffcodes.h format (You may need to do some math conversions and stuff.
   step.6 Print that in the order that it makes it easier for the user to directly use the stdout to the file huffman.h

Huffman Encoding

So, when we are outputting symbols, at some point we have outputted a byte and 5 symbols of the next byte. Then we have 3 bits left. 
Now we have an output buffer where there is a pointer that is currently at the last encoded bit. And records that 5bits of that byte are encoded.
Now you need to encode a symbol that is 4 bits
Now the current byte has 5 bits filled and you need to encode a 4bit symbol (say 1010)
The last 3 bits will be filled with 101 and move to the next byte to stick in the last number (0) in the first bit of that byte.
Caller passes in a message, a buffer where they want the output to be stored, and the number of bytes in that buffer to prevent overflow.
Now we traverse through the input message until the end of the message. (Via for loop).
Inside that for loop, we perform a linear search of the Huffman code table looking for the first character in the table (i.e., the symbol) until it is equal to the character we are looking for (i.e., p)
	Note: There is a sentinel at the bottom of the table. So, when we have an illegal input, we somehow fall out loop at some point. Hence, we assert to keep testing whether the table has ended.
Once we fall out of the loop.
Now, store the Huffman code and Huffman code length of the current symbol in a variable.
Start encoding the bits
Now, find the minimum of number of bits of the current Huffman code, and then compare it with the number of available bits of the current byte. Test whether the sum of current bits and current written bits is less than a byte.
Now, the next bits will shift it to the right (i.e., move to the next byte), and MASK of the rest of the bits of that byte.

grab_code (static function)

Gets the code remaining to be decoded and returns the huffman code required for the current symbol.
Huffman Decoding

Huffman decoding is generally the reverse of a huffman encoding.
Here you store the length of the current huffman bit and check whether if that bit is received. Print that back to the system
The static function grab_code get the code for that particular symbol.
Test if the code is less than the max length of the code and start storing that in a variable P.
once p is fully filled out, print p.


Command Processor Commands

Case insensitive, backspace functionality added along with carriage return and line feed functionalities.

1. Author: Prints the author name
2. Original:	Prints the string that you want to print
3. Encoded :	Prints the encoded strings through UART
4. Decoded :	Prints the decoded strings back to the same UART terminal. Decoded string produces an error message if not yet encoded.
5. Analyze : 	Calculates the compression gains (in percentage) with formula used - (original length - compressed length)/(original_length) * 100
6. Other   :	Just a function to let the user know that command table is scalable
7. help	   :	Prints the help box for all the commands. (the entire command table)

Overall Program Flow
![software flow](https://user-images.githubusercontent.com/89497188/166406431-8e126303-cb03-4279-bb8a-d5df84951ea5.jpg)

Test Suites
1. Python code testing done to test whether huffman tree is getting generated for any kind of file for any characters in the ASCII range
2. Circular buffer working test under various conditions
3. Huffman Encoding and Decoding test for a given message
4. Command processor test commands like author, etc... given to test the command processor operation.

Final Working Image Screenshot
![PES_PROJECT_SUBMISSION_SCREENSHOT](https://user-images.githubusercontent.com/89497188/166405261-35e58a93-0bdb-4d50-b610-cda4763b90c7.jpg)

Conclusion

This is a basic project to let the user know about the huffman coding and decoding process on a KL25Z embedded system ARM cortex M0+ processor
Even though this is not the best route, I have to designed a working model that inputs and outputs the encoded and decoded strings in the terminal via UART.
I have done this because of lack of that much availability of resources to connect to a serial port on a windows machine. I have created a command processor to demonstrate the working. Apologies for that. Given another chance I would definitely work towards getting the serial port part also working on a windows or a linux machine byt obtaining one or possibly dual-booting my system.

Further Enhancements

This project can be enhanced to produce a large number of message handling. And can further be explored in audio and video for the same.

Acknowledgments

I express my gratitude to professor Howdy Pierce for giving me an opportunity to do this project and develop an indepth understanding and imbibing good confidence on developing programs on embedded C.
I extend my thanks to the Teaching Assistants Ms Mukta Darekar and Mr Nimish bhide for the continuous support throughout this journey, without them I couldnt have managed to crack the bi-weekly assignments and inturn the course.
I also am thankful to my fellow colleagues for giving a helping hand whenever I was in dire need of technical assistance.

References

1. https://www.programiz.com/python-programming/examples/ascii-character
2. Professor Howdy' Pierce lecture on command processing, serial part II and media compression
3. Alexander Dean Chapter 8 codes on Serial Communication (Especially UART)

Proposal Questions
1. Functionality project estimated - Huffman Compression and Decompression
2. Technologie used: Python code to generate huffman tree, C code to integrate huffman encoding and decoding with a command processor for a message.
3. Key Learnings: Python functions, class initialisation, thereby basics of OOPS concepts. 
                  C code to develop huffman encoding and decoding with bit-packing. Integrating with command processor to process byte-by-byte transitions over UART
4. Additional Hardware Requirement: No
5. Test Suites: Testing is both in python and C
	5a. Python testing
		Test the histogram and huffman build tree functionality for different files consisting of various characters in ASCII limits
	5b. Embedded C testing
		UART functionlity for random messages
		command processor function for any commands via UART
		Huffman encoding and decoding for different messages
