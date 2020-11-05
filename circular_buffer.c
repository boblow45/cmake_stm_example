<"stdint.h">


// The hidden definition of our circular buffer structure
typedef struct circular_buf_t {
	uint8_t* buffer;
	uint32_t head;
	uint32_t tail;
	uint32_t max; //of the buffer
} circular_buf_t;


circular_buf_t* cbuf_init(uint8_t* buffer, uint32_t size) {
	circular_buf_t* cbuf = malloc(sizeof(circular_buf_t));

	cbuf->buffer = buffer;
	cbuf->max = size;
	return cbuf;
}

void cbuf_put(circular_buf_t* cbuf, uint8_t data) {

	cbuf->buffer[cbuf->head] = data;

	if(cbuf->head == cbuf->tail) {
		cbuf->tail = (cbuf->tail + 1) % cbuf->max;
	}

	cbuf->head = (cbuf->head + 1) % cbuf->max;
}

