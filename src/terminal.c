#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static struct termios oldSettings;
void setInstantInputMode(char enable){
    if(enable){
		tcgetattr(STDIN_FILENO, &oldSettings);
        struct termios newSettings = oldSettings;
        newSettings.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    }
    else{
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    }
}
void clearTerminal(){
	printf("\033[2J\033[H");
}
void startPosTerminal(){
	printf("\033[H");
}
void setBackgroundColor(RGB color){
	printf("\033[48;2;%u;%u;%um",color.r ,color.g, color.b);
}
void setForegroundColor(RGB color){
	printf("\033[38;2;%u;%u;%um",color.r ,color.g, color.b);
}
void setCursorVisibility(char enable){
	if(enable)
		printf("\033[?25h");
	else
		printf("\033[?25l");
}
void setAltBuf(char enable){
	if(enable) printf("\033[?1049h");
	else printf("\033[?1049l");
}
