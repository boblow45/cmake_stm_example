#ifndef __CIR_BUFFER__
#define __CIR_BUFFER__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

// The hidden definition of our circular buffer structure
typedef struct circular_buf_t {
	uint8_t* buffer;
	size_t head;
	size_t tail;
	size_t max; //of the buffer
	bool full;
} circular_buf_t;

typedef circular_buf_t* cbuf_handle_t;

/// Pass in a storage buffer and size
/// Returns a circular buffer handle
cbuf_handle_t cbuf_init(uint8_t* buffer, size_t size);

/// Free a circular buffer structure.
/// Does not free data buffer; owner is responsible for that
void cbuf_free(cbuf_handle_t cbuf);

/// Reset the circular buffer to empty, head == tail
void cbuf_reset(cbuf_handle_t cbuf);

/// Put version 1 continues to add data if the buffer is full
/// Old data is overwritten
void cbuf_put(cbuf_handle_t cbuf, uint8_t data);

/// Retrieve a value from the buffer
/// Returns 0 on success, -1 if the buffer is empty
int cbuf_get(cbuf_handle_t cbuf, uint8_t* data);

/// Returns true if the buffer is empty
bool cbuf_empty(cbuf_handle_t cbuf);

/// Returns true if the buffer is full
bool cbuf_full(cbuf_handle_t cbuf);

/// Returns the maximum capacity of the buffer
size_t cbuf_capacity(cbuf_handle_t cbuf);

/// Returns the current number of elements in the buffer
size_t cbuf_size(cbuf_handle_t cbuf);

#endif // __CIR_BUFFER__