/*
 * buffer.h
 *
 *  Created on: Dec 5, 2017
 *      Author: Brandon
 */

#ifndef BUFFER_H_
#define BUFFER_H_

typedef struct {
    volatile uint32_t num_items;
    volatile uint32_t capacity;
    volatile uint32_t head;
    volatile uint32_t tail;
    uint8_t * buffer;
} buffer;

void buffer_configure(void);
void uart_send(uint8_t byte);
void uart_print(uint8_t * bytes);
buffer * buffer_initialize(uint32_t len);
int8_t buffer_clear(buffer * buf);
int8_t buffer_delete(buffer * buf);
int8_t buffer_isfull(buffer * buf);
int8_t buffer_isempty(buffer * buf);
int8_t buffer_length(buffer *buf);
int8_t buffer_add(buffer * buf, uint8_t item);
uint8_t buffer_get(buffer * buf);
uint32_t inc(uint32_t var, uint32_t cap);

#endif /* BUFFER_H_ */
