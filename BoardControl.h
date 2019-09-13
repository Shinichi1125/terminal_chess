// BoardControl.h

#ifndef __BOARDCONTROL_H__
#define __BOARDCONTROL_H__

#define ROW 8
#define COLUMN 8

#include <ctype.h>
#include <stdbool.h>

typedef struct piece_data
{
	char piece;
	char color;
}piece_t;

piece_t board[ROW][COLUMN];

typedef struct movement
{
    char column;
	int row;
	piece_t piece_data;
}move_t;


void board_init(void);

void set_all_pieces(void);

void board_print(void);

void print_upside_down(void);

char turn_change(char turn);

move_t ask_movement(void);

bool is_color_valid(char turn, move_t move);

bool is_move_canceled(move_t old_location, move_t move);

bool is_move_valid(move_t move);

void add_piece(void);

void put_kings(void);

bool is_king_captured(void);

#endif



