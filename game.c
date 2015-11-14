
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

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "game.h"
#include "screen.h"

void set_board( char board[BOARD_HEIGHT][BOARD_WIDTH], char mtx_brick[4][4],
                char brick, char y, char x ){
	int i, j;
	for( i = 0; i < 4; i++ ) {
		for( j = 0; j < 4; j++ ) {
			if( mtx_brick[i][j]  && y + i >= 0) {
				board[ y + i ][ x + j * 2 ] = board[ y + i ][ x + j * 2 + 1 ] = brick;
			}
		}
	}
}


int check_lines(char board[BOARD_HEIGHT][BOARD_WIDTH], int* score, int* lines) {
	char tmp_board[BOARD_HEIGHT][BOARD_WIDTH];
	memset(tmp_board, 0, BOARD_HEIGHT * BOARD_WIDTH);
	char cont = 0;
	char lns = 0;
	int i, j;
	int ti = BOARD_HEIGHT - 1;
	for(i = BOARD_HEIGHT - 1; i >= 0; i--) {
		for(j = 0; j < BOARD_WIDTH; j++) {
			if(board[i][j]) {
				cont++;
			}
		}

		if(cont == BOARD_WIDTH) {
			cont = 0;
			lns++;
		}
		if(cont != 0) {
      			memcpy(tmp_board[ti--], board[i], BOARD_WIDTH);
      			cont = 0;
    		}
  	}

	if(lns != 0) {
		memcpy(board, tmp_board, BOARD_HEIGHT * BOARD_WIDTH);
		*lines += lns;
    		switch(lns) {
    			case 1:	*score += POINTS;
				break;
    			case 2: *score += POINTS * 2; 
				break;
    			case 3: *score += POINTS * 5;
				break;
    			case 4: *score += POINTS * 8;
				break;
    			default:*score += POINTS * 8;
				break;
    		}
  	}

	return lns;
}

/* The game function that controls the flow of the game */
int start_game(){
    	char board[BOARD_HEIGHT][BOARD_WIDTH];
    	char mtx_brick[4][4];
  	int score = 0;
  	int level = 0;
  	int lines = 0;
  	int tmp_lines = 0;
  	char x, y;
  	char brick;
  	char next_brick;
  	int vel = 20;
	char pause, pagain;
  	struct timespec req;				/* From time.h */
  	req.tv_sec = 0;
  	req.tv_nsec = vel * PULSE;

  	srand(time(0));
  	memset(board, 0, BOARD_HEIGHT * BOARD_WIDTH);
  	next_brick = rand() % 7 + 1;

  	init_screen();
	
  	WINDOW* wboard   = create_wboard();		/* Pointers to WINDOW from ncurses.h */
  	WINDOW* wpreview = create_wpreview();
  	WINDOW* wscore   = create_wscore();
	WINDOW* winstr	 = create_winstr();
	WINDOW* wgeninstr= create_wgeninstr();
  	show_title();
  	show_score(wscore, score, level, lines);
	show_instr(winstr);
	show_geninstr(wgeninstr);
  	wait_start(wboard);

  	bool play = true;
  	while( play ){
    		brick = next_brick;
    		next_brick = rand() % 7 + 1;

    		show_preview( wpreview, next_brick );
    		show_score( wscore, score, level, lines );
    		show_board( wboard, board );

    		x = ((BOARD_WIDTH / 3 ) % 2 == 0 ) ? BOARD_WIDTH / 3 : BOARD_WIDTH / 3 + 1;
    		y = - 3;
    
    		get_brick( brick, mtx_brick );

    		bool move = true;
    		int delay = 0;
  		while(move) {
      			switch(getch()) {
      				case KEY_UP:
    						move_brick( wboard, board, mtx_brick, brick, &y, &x, ROTATE_R );
						break;
      				case 'z':
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, ROTATE_R );
						break;
      				case 'x':
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, ROTATE_L );
						break;
      				case KEY_DOWN:
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, DOWN     );
						break;
      				case KEY_LEFT:
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, LEFT     );
						break;
      				case KEY_RIGHT:
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, RIGHT    );
						break;
      				case ' ':
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, BOTTOM   );
						break;
				case 's': 
        					move_brick( wboard, board, mtx_brick, brick, &y, &x, SHADOW   );
						break;
				case 'p':	while(pause = getchar()) {
							if(pause == 'p') {
								break;
							}
						}
						break;
				case 27:  	
						play = move = false;
						break;
      				case 'q': 
						play = move = false;
						break;
      				default: break;
      			} // switch( getch() )

      			if(++delay == DELAY_DOWN) {
        			move_brick(wboard, board, mtx_brick, brick, &y, &x, DOWN);
      			}
      			if(delay == DELAY_BOTTOM) {
        			delay = 0;
        			if(check_brick(mtx_brick, board, y + 1, x)){
          				move = false;
          				if(y < 0) {
						play = false;
					}
        			}
      			}

      			nanosleep( &req, 0 );
    		} // while( move )

    		set_board(board, mtx_brick, brick, y, x);
    		tmp_lines += check_lines(board, &score, &lines);

    		if(tmp_lines >= CH_LEV) {
      			req.tv_nsec = vel * PULSE;
      			score += 1;
      			level++;
      			if(vel > 1) {
				vel--;
			}
      			tmp_lines = tmp_lines % CH_LEV;
    		}

	}   // while( quit )
		delwin(wboard);
 		delwin(wpreview);
  		delwin(wscore);
		delwin(winstr);
  		wboard = create_wboard();
  		wait_end( wboard );
		while(pagain = getchar()) {
  			if(pagain == 'n') {
				restore_screen();
				return 0;
			}
  			if(pagain == 'y') {
				return 1;
			}
		}
}
