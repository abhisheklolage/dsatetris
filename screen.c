
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

/*  This file contains all the functions built with the help of ncurses library
 *  which display the screen to the user.   
 */


#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "brick.h"

#define SHADOWON 	1
#define SHADOWOFF	0

int shadow = 0;

void init_screen() {
	if(!initscr()) {
		fprintf( stderr, "ERROR in init_screen() \n");
		exit(1);
	}

	if(!has_colors()) {
		endwin();
		printf("ERROR with colors! \n" );
		exit(1);
	}
    	
	start_color();
    	init_colors();
    	clear();
    	noecho();
    	keypad(stdscr, TRUE);
    	cbreak();
    	curs_set(FALSE);
}

void restore_screen() {
    	endwin();
}

void init_colors() {
	int i, j, ck = 1;
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {
			init_pair(ck++, i, j);
		}
	}
}

WINDOW* create_win(const unsigned int h, const unsigned int w,
			const unsigned int y, const unsigned int x) {
	WINDOW* win = newwin( h, w, y, x );
	box( win, 0, 0 );
	refresh();
	wrefresh( win );
	return win;
}

WINDOW* create_wboard() {
	return create_win(WBOARD_HEIGHT, WBOARD_WIDTH, WBOARD_Y, WBOARD_X);
}

WINDOW* create_wpreview() {
	return create_win(WPREV_HEIGHT, WPREV_WIDTH, WPREV_Y, WPREV_X);
}

WINDOW* create_wscore() {
	return create_win(WSCORE_HEIGHT, WSCORE_WIDTH, WSCORE_Y, WSCORE_X);
}

WINDOW* create_winstr() {
	return create_win(WINSTR_HEIGHT, WINSTR_WIDTH, WINSTR_Y, WINSTR_X);
}
WINDOW* create_wgeninstr() {
	return create_win(WGENINSTR_HEIGHT, WGENINSTR_WIDTH, WGENINSTR_Y, WGENINSTR_X);
}

void wait_start(WINDOW *win){
	wattron(win, COLOR_PAIR(RB));
	mvwprintw(win, WBOARD_HEIGHT/2  - 1, (WBOARD_WIDTH - 12)/2 - 5 , "PRESS AY KEY TO START!");
	wattroff(win, COLOR_PAIR(RB));
	wrefresh(win);
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
}

void wait_end(WINDOW *win){
	wattron(win, COLOR_PAIR(RB));
	mvwprintw(win, WBOARD_HEIGHT/2  - 1, 3, "Do you want to play again?");
	mvwprintw(win, WBOARD_HEIGHT/2 , 3, "Press y for yes OR n for no");
	wattroff(win, COLOR_PAIR(RB));
	wrefresh(win);
	nodelay(stdscr, FALSE);
	nodelay(stdscr, TRUE);
}
void color_char(int ck, int y, int x, const char ch ){
	attron(COLOR_PAIR(ck));
	mvaddch(y, x, ch);
	attroff(COLOR_PAIR(ck));
}

void show_title() {
	color_char(CB, 1, 36, 'T');
	color_char(MB, 1, 36 + 13, 'E');
	color_char(YB, 1, 36 + 13 + 13, 'T');
	color_char(WB, 1, 36 + 13 + 13 + 13, 'R');
	color_char(GB, 1, 36 + 13 + 13 + 13 + 13, 'I');
	color_char(CB, 1, 36 + 13 + 13 + 13 + 13 + 13, 'S');
}

void show_preview( WINDOW* win, const char brick ){
	clear_win(win);
	int color;
	switch(brick){
		case 1:	color = WY;
			break;
		case 2: color = WR;
			break;
		case 3: color = WW;
			break;
		case 4: color = WC;
			break;
		case 5: color = WG;
			break;
		case 6: color = WR;
			break;
		case 7: color = WM;
			break;
		default:color =  0;
			break;
	}

	if(color != 0) {
		wattron(win, COLOR_PAIR(color));
	}

	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(matrix_brick[brick - 1][i][j]) {
				mvwaddstr(win, i + 1, j * 2 + 3, "  ");
			}
		}
	}

	if(color != 0) {
		wattroff(win, COLOR_PAIR(color));
  	}
	wrefresh(win);
}


void show_score(WINDOW *win, const int score, const int level, const int lines) {
	mvwprintw(win, 1, 2, "Level:");
	mvwprintw(win, 5, 2, "Score:");
	mvwprintw(win, 9, 2, "lines:");
	wattron(win, COLOR_PAIR(RB) );
	mvwprintw(win, 3, 2, "%7i", level );
	mvwprintw(win, 7, 2, "%7i", score );
	mvwprintw(win, 11, 2, "%7i", lines );
	wattroff(win, COLOR_PAIR(RB) );
	wrefresh(win);
}

void show_instr(WINDOW *win) {
	mvwprintw(win, 1, 2, "p: Pause-Unpase. ");
	mvwprintw(win, 5, 2, "SPACE: Drop brick. ");
	mvwprintw(win, 9, 2, "s: Shadow On-Off. ");
	mvwprintw(win, 13, 2, "q: Quit. ");
	wattron(win, 5 );
	wattroff(win, COLOR_PAIR(RB));
	wrefresh(win);
}
void show_geninstr(WINDOW *win) {
	mvwprintw(win, 1, 2, "UP-ARROW: Rotate brick. ");
	mvwprintw(win, 5, 2, "LEFT-ARROW: Move left. ");
	mvwprintw(win, 9, 2, "RIGHT-ARROW: Move Right. ");
	mvwprintw(win, 13, 2, "DOWN-ARROW: Move Down. ");
	wattron(win, 5 );
	wattroff(win, COLOR_PAIR(RB));
	wrefresh(win);
}

void show_board(WINDOW* win, char board[BOARD_HEIGHT][BOARD_WIDTH]) {
	clear_win(win);
	int color;
	int i, j;
	for(i = 0; i < BOARD_HEIGHT; i++) {
		for(j = 0; j < BOARD_WIDTH; j++) {
			if(board[i][j]){
        			switch(board[i][j]){
        				case 1: color = WY;
						break;
        				case 2: color = WR;
						break;
        				case 3: color = WW;
						break;
        				case 4: color = WC;
						break;
        				case 5: color = WG;
						break;
       					case 6: color = WR;
						break;
					case 7: color = WM;
						break;
        				default:color =  0;
						break;
        			}

        			if(color != 0) {
					wattron(win, COLOR_PAIR(color));
        			}
				mvwaddch(win, i + 1, j + 1, ' ');
        			if(color != 0) {
					wattroff(win, COLOR_PAIR(color));
      				}
			}
		}
	}

	wrefresh(win);
}

void clear_win(WINDOW* win){
	wclear(win);
	box(win, 0, 0);
}

/* This function will copy contents from brick.h into the brick */
void get_brick(char brick, char mtx_brick[4][4]){
	memcpy(mtx_brick, matrix_brick[ brick - 1 ], sizeof(char) * 4 * 4);
}
/* Function for rotating brick - manipulation of the brick matrix */
void rotate_brick(char mtx_brick[4][4], char board[BOARD_HEIGHT][BOARD_WIDTH],
                   char* y, char* x, bool dir){
	char tmp_brick[4][4];
  	int i, j;
  	if(dir) {
		for(i = 0; i < 4; i++) {
      			for( j = 0; j < 4; j++) {
        			tmp_brick[i][j] = mtx_brick[3 - j][i];
			}
		}
  	}
	else {
    		for(i = 0; i < 4; i++) {
      			for(j = 0; j < 4; j++) {
        			tmp_brick[i][j] = mtx_brick[j][3 - i];
			}
		}
	}

	adjust_brick( tmp_brick );
	if(!check_brick(tmp_brick, board, *y, *x)) {
		memcpy( mtx_brick, tmp_brick, sizeof(char) * 4 * 4);
	}
}

void adjust_brick(char mtx_brick[4][4]){
	char tmp_brick[4][4];
	memset(tmp_brick, 0, sizeof(char) * 4 * 4);
	int i, j;
	int ti = 0;
	int tj = 4;
	bool change;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(mtx_brick[i][j]) {
        			if(j < tj) {
					tj = j;
				}
			}
		}
	}

	for(i = 0; i < 4; i++) {
    		change = false;
    		for( j = 0; j < 4; j++) {
      			if(mtx_brick[i][j]){
        			tmp_brick[ti][j - tj] = mtx_brick[i][j];
        			change = true;
      			}
		}
    		
		if(change) {
			ti++;
		}
	}
	memcpy(mtx_brick, tmp_brick, sizeof(char) * 4 * 4);
}

void clear_brick(WINDOW* win, char mtx_brick[4][4], char y, char x) {
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(mtx_brick[i][j]) {
				if(y + i >= 0) {
          				mvwaddstr(win, y + i + 1, x + j * 2 + 1, "  ");
				}
			}
		}
	}
}

void draw_brick(WINDOW* win, char brick, char mtx_brick[4][4], char y, char x){
	int color;
  	switch(brick){
  		case 1: color = WY;
			break;
  		case 2: color = WR;
			break;
  		case 3: color = WW;
			break;
  		case 4: color = WC;
			break;
  		case 5: color = WG;
			break;
		case 6: color = WR;
			break;
  		case 7: color = WM;
			break;
		default:color =  0;
			break;
	}
	
	wattron(win, COLOR_PAIR(color));
	int i, j;
	for(i = 0; i < 4; i++) {
    		for(j = 0; j < 4; j++) {
      			if(mtx_brick[i][j]) {
        			if(y + i >= 0) {
          				mvwaddstr( win, y + i + 1, x + j * 2 + 1, "  " );
				}
			}
		}
	}
  	wattroff(win, COLOR_PAIR(color));
  	wrefresh(win);
}

int check_brick(char mtx_brick[4][4], char board[BOARD_HEIGHT][BOARD_WIDTH],
                 char y, char x) {
	int i, j;
  	for(i = 0; i < 4; i++) {
    		for(j = 0; j < 4; j++) {
      			if(mtx_brick[i][j]) {
        			if(y + i >= BOARD_HEIGHT) {
					return 1;
				}
        			if(x + j * 2 >= BOARD_WIDTH) {
					return 1;
				}
        			if(x + j * 2 < 0) {
					return 1;
				}
				if(y + i >= 0) {
          				if(board[y + i][x + j * 2]) {
            					return 1;
      					}
				}
			}
    		}
  	}
  	return 0;
}

void move_brick( WINDOW* win, char board[BOARD_HEIGHT][BOARD_WIDTH], char mtx_brick[4][4],
                char brick, char* y, char* x, char move) {

	int y_orig;
	clear_brick(win, mtx_brick, *y, *x);
	if(shadow) {
		y_orig = *y;
		while(!check_brick(mtx_brick, board, (*y) + 1, *x)) {
			*y += 1;
		}
		
		clear_brick(win, mtx_brick, *y, *x);
		*y = y_orig;
	}
	/*if(shadow) {
		clear_brick( win, mtx_brick, *y, *x );
	}*/
	switch(move) {
		case MOVE:
    				break;
  		case LEFT:	
				if(!check_brick(mtx_brick, board, *y, (*x) - 2)) {
					*x -= 2;
				}
    				break;
  		case RIGHT:	
				if(!check_brick(mtx_brick, board, *y, (*x) + 2)) {
					*x += 2;
				}
				break;
  		case DOWN:	
				if(!check_brick(mtx_brick, board, (*y) + 1, *x)) {
					*y += 1;
				}
    				break;
  		case BOTTOM:
				while(!check_brick(mtx_brick, board, (*y) + 1, *x)) {
					*y += 1;
				}
   				break;
  		case ROTATE_L:	
				rotate_brick(mtx_brick, board, y, x, 0);
    				break;
  		case ROTATE_R: 
				rotate_brick(mtx_brick, board, y, x, 1);
    				break;
  		case SHADOW:	
				if(shadow) {
					shadow = SHADOWOFF;
					break;
				}
				if(!shadow) {
					shadow = SHADOWON;
					break;
				}
		default:
				break;
	}
	
	//draw_brick( win, brick, mtx_brick, *y, *x );
	if(shadow) {
		y_orig = *y;
		while(!check_brick(mtx_brick, board, (*y) + 1, *x)) {
			*y += 1;
		}
		
		draw_brick(win, 3, mtx_brick, *y, *x);
		*y = y_orig;
	}
	draw_brick(win, brick, mtx_brick, *y, *x);
} 
