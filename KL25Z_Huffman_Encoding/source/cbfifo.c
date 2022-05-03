/* Name  				: Sricharan Kidambi S
 * Course				: ECEN 5813 - Embedded System Design - Course Project
 * Title				: Huffman Compression and Decompression of Debug Printouts
 * Instructor			: Howdy Pierce
 * Teaching Assistants	: Mukta Darekar, Nimish Bhide
 * File  				: cbfifo.c
 * Date	 				: 05/02/2022
 * Brief 				: Circular buffer function definitions, to build an error free circular buffer with size of 256 bytes
 * References			: Code majorly inspired by assignment 2 FIFO operations for the course.
 * 						  Support obtained from Professor Howdy Pierce and course TA's for that assignment
 * 						  For documentation see cbfifo.h
 */
#include "cbfifo.h"
#include "assert.h"
#include "stddef.h"
#include "MKL25Z4.h"
void initialize(cbfifo_t *cb){
    cb->head = 0;
    cb->tail = 0;
    cb->length = 0;
    __builtin_memset(cb->buf,'_',MAX_SIZE);
}
size_t enqueue(cbfifo_t *cb,void *buf,size_t nbytes){
	uint32_t mask;
    if(buf == NULL)
    	return -1;
    if(cb->length == MAX_SIZE)
        return 0;
    if(cb->length + nbytes > MAX_SIZE)
        nbytes = MAX_SIZE - cb->length;
    mask = __get_PRIMASK();
    for(int i = 0;i < nbytes;i++){
        cb->buf[cb->tail] = * (uint8_t *)buf++;//[cb->buffer_position];
        cb->tail = ((cb->tail + 1) & (MAX_SIZE - 1));
        cb->length += 1;
    }
    __set_PRIMASK(mask);
    return nbytes;
}
size_t dequeue(cbfifo_t *cb,void *buf,size_t nbytes){
	uint32_t mask;
    if(buf == NULL)
    	return -1;
    if(cb->length == 0)
        return 0;
    if(cb->length < nbytes)
        nbytes = cb->length;
    mask = __get_PRIMASK();
    for(int i = 0;i < nbytes;i++){
        *(uint8_t *)buf++ = cb->buf[cb->head];
        cb->buf[cb->head] = '_';
        cb->head = ((cb->head + 1) & (MAX_SIZE - 1));
        cb->length -= 1;
    }
    __set_PRIMASK(mask);
    return nbytes;
}
bool bufferfull(cbfifo_t *cb){
	if(cb->length == MAX_SIZE)
		return 1;
	else{
		return 0;
	}
}
bool bufferempty(cbfifo_t *cb){
	if(cb->length == 0)
		return 1;
	else{
		return 0;
	}
}
uint32_t length(cbfifo_t *cb){
	return cb->length;
}
