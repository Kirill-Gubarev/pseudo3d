#include <stdint.h>
typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}RGB;

RGB subtractRGB(RGB color, uint8_t num);
