#include "events.h"
#include "stdio.h"
#include "player.h"

char keyEvents(){
	char ch = getchar();
	if		(ch == 'w') movePlayerForward(0.2);
	else if (ch == 's')	movePlayerForward(-0.2);
	else if (ch == 'd') movePlayerSide(0.2);
	else if (ch == 'a') movePlayerSide(-0.2);
	else if (ch == 'q') addAngle(-10);
	else if (ch == 'e') addAngle(10);
	return ch;
}
