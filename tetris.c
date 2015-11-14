
/* 	<TETRIS Game in C using ncurses>
 *	Copyright (C)
 *	<2015>  <Abhishek Lolage>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

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
