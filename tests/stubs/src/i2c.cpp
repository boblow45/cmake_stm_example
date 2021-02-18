#include "i2c.hpp"


I2C::I2C(void) {
}

void I2C::write(uint16_t device_add, uint16_t mem_add, uint16_t mem_add_size, uint8_t* data, uint16_t size) {
    uint32_t val = device_add + mem_add + mem_add_size + *data + size;
    val++;
}

void I2C::read(uint16_t device_add, uint16_t mem_add, uint16_t mem_add_size, uint8_t* data, uint16_t size) {
    uint32_t val = device_add + mem_add + mem_add_size + *data + size;
    val++;
}

