#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "circular_buffer.h"

cbuf_handle_t cbuf_init(uint8_t* buffer, size_t size) {

	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));

	cbuf->buffer = buffer;
	cbuf->max = size;
	cbuf_reset(cbuf);

	return cbuf;
}

void cbuf_reset(cbuf_handle_t cbuf) {
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = false;
}

void cbuf_free(cbuf_handle_t cbuf) {
	free(cbuf);
}

void cbuf_put(cbuf_handle_t cbuf, uint8_t data) {

	cbuf->buffer[cbuf->head] = data;

	if(cbuf->full) {
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
	cbuf->full = (cbuf->head == cbuf->tail);
}

int cbuf_get(cbuf_handle_t cbuf, uint8_t* data) {
	int r = -1;

	if(!cbuf_empty(cbuf)) {
		*data = cbuf->buffer[cbuf->tail];
		cbuf->full = false;
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
		r = 0;
	}

	return r;
}

size_t cbuf_capacity(cbuf_handle_t cbuf) {
	return cbuf->max;
}

bool cbuf_empty(cbuf_handle_t cbuf) {
	return (!cbuf->full && (cbuf->head == cbuf->tail));
}

bool cbuf_full(cbuf_handle_t cbuf) {
	return cbuf->full;
}

size_t cbuf_size(cbuf_handle_t cbuf) {
	size_t size = cbuf->max;

	if(!cbuf->full) {
		if(cbuf->head >= cbuf->tail) {
			size = (cbuf->head - cbuf->tail);
		}
		else {
			size = (cbuf->max + cbuf->head - cbuf->tail);
		}
	}

	return size;
}