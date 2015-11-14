
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

#ifndef GAME_H
#define GAME_H

#include "constants.h"

int start_game();
void set_board( char board[BOARD_HEIGHT][BOARD_WIDTH], char mtx_brick[4][4],
                char brick, char y, char x );
int check_lines( char board[BOARD_HEIGHT][BOARD_WIDTH], int* score, int* lines );


#endif  // GAME_H
 
