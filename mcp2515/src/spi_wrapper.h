#include <stdint.h>
#include <stdbool.h>
bool spi_send_byte(uint8_t*);
bool spi_receive_byte(uint8_t*);
bool spi_start_com(uint32_t pin);
bool spi_end_com(uint32_t pin);