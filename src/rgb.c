#include "rgb.h"

static uint8_t handleAddOverflow(uint8_t colorCode, int num){
	int temp = colorCode + num;
	if (temp > 255) return 255;
	if (temp < 0) return 0;
	return temp;
}

RGB RGBaddInt(RGB color, int num){
	return (RGB){
		handleAddOverflow(color.r, num),
		handleAddOverflow(color.g, num),
		handleAddOverflow(color.b, num)
	};
}
