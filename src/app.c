#include "app.h"

#include "player.h"
#include "terminal.h"
#include "rendering.h"
#include "events.h"

void appInit(){
	setAltBuf(1);
    setInstantInputMode(1);
	setCursorVisibility(0);

	playerInit(10, 10, 0);
}
void appTerminate(){
	setCursorVisibility(1);
    setInstantInputMode(0);
	setAltBuf(0);
}
void appExec(){
    while(keyEvents() != 27){
		render();
    }
}
