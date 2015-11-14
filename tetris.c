#include <ncurses.h>
#include <stdlib.h>
#include "tetris.h"
#include "game.h"
#include "screen.h"

int main( int argc, char* argv[] ){
	char play = 1;
	while(play = start_game()) {
		if(!play) {
			break;
		}
	}
	return 0;
} 
