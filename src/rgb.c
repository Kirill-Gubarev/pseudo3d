#include "rgb.h"

RGB subtractRGB(RGB color, uint8_t num){
	return (RGB){color.r - num, color.g - num, color.b - num};
}
