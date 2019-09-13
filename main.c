// main.c

#include "BoardControl.h"
#include "Pieces.h"

#include <stdio.h>

int main(void)
{
	set_all_pieces();
	board_print();

	char turn = 'W';

	move_t move;
	move_t old_location;

	bool check;
	bool color_check;
	bool promotion_check;
	bool game_end = false;
	bool move_canceled = false;

	while(game_end == false)
	{
		do
		{
			do    // Ask the user to choose which piece to move
	    	{
	    		printf("\n%c, it's your turn\n", turn);
		    	move = choose_piece();
			    check = is_choice_valid(move);
			    color_check = is_color_valid(turn, move);
		    }
		    while(check != true || color_check != true);

	        old_location.column = move.column;
	        old_location.row = move.row;
	        old_location.piece_data.piece = move.piece_data.piece;
	        old_location.piece_data.color = move.piece_data.color;

	        do    // The user moves the piece
		    {
			    move = choose_destination(move.piece_data);
			    check = is_destination_valid(old_location, move);
			    promotion_check = pawn_promotion_check(move);

			    move_canceled = is_move_canceled(old_location, move);

			    if(promotion_check == true)
			    {
			    	move = pawn_promote(move);
				}
	    	}
		    while(check != true);
	    }while(move_canceled == true);

	    move_canceled = false;

    	move_piece(old_location, move);

	    if(turn == 'W')
	    {
	    	print_upside_down();
		}
		else if(turn == 'B')
		{
			board_print();
		}

    	game_end = is_king_captured();

    	if(game_end == true)
    	{
    		printf("%c wins!\n", turn);
		}

    	turn = turn_change(turn);
	}

	return 0;
}




