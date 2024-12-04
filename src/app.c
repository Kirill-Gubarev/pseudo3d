#include "app.h"

#include "player.h"
#include "terminal.h"
#include "rendering.h"
#include "events.h"

void appInit(){
    setInstantInputMode(1);
	playerInit(10, 10, 0);
}
void appExec(){
    while(keyEvents() != 27){
		render();
    }
}
void appTerminate(){
    setInstantInputMode(0);
}
