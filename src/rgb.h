#ifndef RGB_H
#define RGB_H
#include <stdint.h>
typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}RGB;

RGB RGBaddInt(RGB color, int num);
#endif//RGB_H
