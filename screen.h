
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

#ifndef SCREEN_H
#define SCREEN_H

#include "constants.h"

void init_screen();
void restore_screen();
void init_colors();

WINDOW* create_win( const unsigned int h, const unsigned int w,
                    const unsigned int y, const unsigned int x );
WINDOW* create_wboard();
WINDOW* create_wpreview();
WINDOW* create_wscore();
WINDOW* create_winstr();
WINDOW* create_wgeninstr();

void ck_mvaddch( int ck, int y, int x, const char ch );
void show_title();
void show_instr( WINDOW *win );
void show_score( WINDOW* win, const int score, const int level, const int lines );
void show_preview( WINDOW* win, const char brick );
void show_geninstr(WINDOW *win);
void clear_win( WINDOW* win );
void wait_start( WINDOW* win );
void draw_brick( WINDOW* win, char brick, char mtx_brick[4][4], char y, char x );
void clear_brick( WINDOW* win, char mtx_brick[4][4], char y, char x );
void show_board( WINDOW* win, char board[BOARD_HEIGHT][BOARD_WIDTH] );
void get_brick( char brick, char mtx_brick[4][4] );
void rotate_brick( char mtx_brick[4][4], char board[BOARD_HEIGHT][BOARD_WIDTH],
                   char* y, char* x, bool dir );
void adjust_brick( char mtx_brick[4][4] );
int check_brick( char mtx_brick[4][4], char board[BOARD_HEIGHT][BOARD_WIDTH],
                 char y, char x );
void move_brick( WINDOW* win, char board[BOARD_HEIGHT][BOARD_WIDTH], char mtx_brick[4][4],
                 char brick, char* y, char* x, char move );

#endif  // SCREEN_H 
