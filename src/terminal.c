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
