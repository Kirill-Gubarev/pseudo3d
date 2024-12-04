#ifndef TERMINAL_H
#define TERMINAL_H
#include "rgb.h"

void setInstantInputMode(char enable);
void clearTerminal();
void setColor(RGB color);
void setCursorVisibility(char enable);

#endif//TERMINAL_H
