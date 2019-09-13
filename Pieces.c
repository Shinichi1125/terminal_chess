// Pieces.c

#include "Pieces.h"


#include <stdio.h>

void put_piece(move_t put)
{
	board[put.row-1][put.column-1].piece = put.piece_data.piece;
	board[put.row-1][put.column-1].color = put.piece_data.color;
}

move_t choose_piece()
{
	move_t move;

	printf("Choose which piece to move: ");
	scanf(" %c %d", &move.column, &move.row);

	move.column = tolower(move.column);    // in case the user enter an uppercase character
	move.column = move.column - 96;
	move.piece_data.piece = board[move.row-1][move.column-1].piece;
	move.piece_data.color = board[move.row-1][move.column-1].color;

	return move;
}

bool is_choice_valid(move_t move)
{
	bool check = true;
	// if it's out of boundary, false
	if(move.column <= 0 || move.column > 8)
	{
		check = false;
	}
	// if it's out of boundary, false
	if(move.row <= 0 || move.row > 8)
	{
		check = false;
	}

	if(board[move.row-1][move.column-1].piece == ' ')
	{
		check = false;
	}

	if(check == false)
	{
		printf("Invalid choice\n");
	}

	return check;
}

move_t choose_destination(piece_t piece_data)
{
	move_t move;

	printf("Which square to move the piece to?  ");
	scanf(" %c %d", &move.column, &move.row);

	move.column = tolower(move.column);    // in case the user enter an uppercase character
	move.column = move.column - 96;

	move.piece_data.piece = piece_data.piece;
	move.piece_data.color = piece_data.color;

	return move;
}

void move_piece(move_t old_location, move_t move)
{
	board[old_location.row-1][old_location.column-1].piece = ' ';
	board[old_location.row-1][old_location.column-1].color = ' ';
	board[move.row-1][move.column-1].piece = move.piece_data.piece;
	board[move.row-1][move.column-1].color = move.piece_data.color;
}


bool is_destination_valid(move_t old_location, move_t move)
{
	bool check = true;

	if(old_location.row == move.row && old_location.column == move.column)
	{

	}
	else
	{
		// if it's out of boundary, false
		if(move.column <= 0 || move.column > 8)
		{
			check = false;
		}
		// if it's out of boundary, false
		if(move.row <= 0 || move.row > 8)
		{
			check = false;
		}

		// check if Pawn's movement is valid
		if(move.piece_data.piece == 'P')
	    {
	    	bool result = check_pawn_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Rook's movement is valid
		if(move.piece_data.piece == 'R')
		{
			bool result = check_vertical_horizontal(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if King's movement is valid
		if(move.piece_data.piece == 'K')
		{
			bool result = check_king_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Knight's movement is valid
		if(move.piece_data.piece == 'N')
		{
			bool result = check_knight_movement(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Bishop's movement is valid
		if(move.piece_data.piece == 'B')
		{
		    bool result = check_diagonal(old_location, move);
			if(result == false)
			{
				check = false;
			}
		}

		// check if Queen's movement is valid
		if(move.piece_data.piece == 'Q')
		{
			bool resultVH;
			bool resultD;
			resultVH = check_vertical_horizontal(old_location, move);
			resultD = check_diagonal(old_location, move);
			// if the movement is none of valid vertical,
			// horizontal or diagonal movements, return false
			if(resultVH == false && resultD == false)
			{
				check = false;
			}
		}

		if(check == false)
		{
			printf("Invalid destination\n");
		}
    }

	return check;
}

bool check_pawn_movement(move_t old_location, move_t move)
{
	bool check = true;

	if(move.piece_data.color == 'W')
	{
		if(old_location.row == 2)
		{
			if((old_location.row == move.row-1&& old_location.column == move.column
       		   && board[move.row-1][move.column-1].piece == ' ') ||
	       	   (board[move.row-1][move.column-1].color != move.piece_data.color &&
	            board[move.row-1][move.column-1].color != ' ') ||
				(old_location.row == move.row-2 && old_location.column == move.column
				&& board[move.row-1][move.column-1].piece == ' ')){}
	        else
	        {
		        check = false;
	        }
		}
		else
		{
			if((old_location.row == move.row-1&& old_location.column == move.column
       		   && board[move.row-1][move.column-1].piece == ' ') ||
	       	   (board[move.row-1][move.column-1].color != move.piece_data.color &&
	            board[move.row-1][move.column-1].color != ' ')){}
	        else
	        {
		        check = false;
	        }
		}
	}
	if(move.piece_data.color == 'B')
	{
		if(old_location.row == 7)
		{
			if((old_location.row == move.row+1&& old_location.column == move.column
       		   && board[move.row-1][move.column-1].piece == ' ') ||
	       	   (board[move.row-1][move.column-1].color != move.piece_data.color &&
	            board[move.row-1][move.column-1].color != ' ') ||
				(old_location.row == move.row+2 && old_location.column == move.column
				&& board[move.row-1][move.column-1].piece == ' ')){}
	        else
	        {
		        check = false;
	        }
		}
		else
		{
			if((old_location.row == move.row+1&& old_location.column == move.column
       	   && board[move.row-1][move.column-1].piece == ' ') ||
	       	   (board[move.row-1][move.column-1].color != move.piece_data.color &&
	            board[move.row-1][move.column-1].color != ' ')){}
	        else
	        {
		        check = false;
	        }
		}
	}

	return check;
}

bool pawn_promotion_check(move_t move)
{
	bool result = false;

	if(move.piece_data.piece == 'P' && move.piece_data.color == 'W' && move.row == 8)
	{
		result = true;
	}

	if(move.piece_data.piece == 'P' && move.piece_data.color == 'B' && move.row == 1)
	{
		result = true;
	}

	return result;
}

move_t pawn_promote(move_t move)
{
	char promotion;
	do
	{
		printf("This pawn should be promoted to Q, B, N, or R ");
		scanf(" %c",&promotion);
		promotion = toupper(promotion);
	}while(promotion != 'Q'&& promotion != 'B'&& promotion != 'N'&& promotion != 'R');

	move.piece_data.piece = promotion;

	return move;
}

bool check_king_movement(move_t old_location, move_t move)
{
	bool check = true;

	if(old_location.row - move.row < 2 && move.row - old_location.row < 2 &&
		old_location.column - move.column < 2 && move.column - old_location.column < 2
	    && board[move.row-1][move.column-1].color != move.piece_data.color){}
	else
	{
		check = false;
	}

	return check;
}

bool check_knight_movement(move_t old_location, move_t move)
{
	bool check = true;

	if((move.row - old_location.row == 2 && move.column - old_location.column == 1
	&& board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (move.row - old_location.row == 2 && old_location.column - move.column == 1
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (old_location.row - move.row == 2 && move.column - old_location.column == 1
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (old_location.row - move.row == 2 && old_location.column - move.column == 1
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (move.row - old_location.row == 1 && move.column - old_location.column == 2
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (move.row - old_location.row == 1 && old_location.column - move.column == 2
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (old_location.row - move.row == 1 && move.column - old_location.column == 2
	   && board[move.row-1][move.column-1].color != move.piece_data.color)
	|| (old_location.row - move.row == 1 && old_location.column - move.column == 2
	   && board[move.row-1][move.column-1].color != move.piece_data.color)){}
	else
	{
		check = false;
	}

	return check;
}

bool check_vertical_horizontal(move_t old_location, move_t move)
{
	bool check = true;

	// check if the movement is horizontal or vertical
	// and destination is not occupied by another piece of the same color
	if((old_location.row == move.row || old_location.column == move.column)
	  && (board[move.row-1][move.column-1].color != move.piece_data.color)){}
	else
	{
		check = false;
	}


	int blocked = 0;
	int column_distance;

	// save the distance of the horizontal movement (to the right)
	column_distance = move.column - old_location.column;
	if(column_distance >= 2)
    {
		for(int i = 1; i <= column_distance;i++)
		{
			// if there is the opponent's piece that blocks the way, return false
			if(board[move.row-1][old_location.column-1+i].color != ' ')
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < column_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	column_distance = old_location.column - move.column;
	if(column_distance >= 2)
	{
		for(int i = 1; i <= column_distance;i++)
		{
			if(board[move.row-1][old_location.column-1-i].color != ' ')
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < column_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	int row_distance;
	row_distance = move.row - old_location.row;
	if(row_distance >= 2)
	{
		for(int i = 1; i <= row_distance;i++)
		{
			if(board[old_location.row-1+i][move.column-1].color != ' ')
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < row_distance)
			{
				check = false;
			}
		}
	}

	blocked = 0;
	row_distance = old_location.row - move.row;
	if(row_distance >= 2)
	{
		for(int i = 1; i <= row_distance;i++)
		{
			if(board[old_location.row-1-i][move.column-1].color != ' ')
			{
				blocked = i;
			}

			if(blocked > 0 && blocked < row_distance)
			{
				check = false;
			}
		}
	}

	return check;
}

bool check_diagonal(move_t old_location, move_t move)
{
	bool check = true;

	if(((move.column - old_location.column == move.row - old_location.row)
	|| ((move.column - old_location.column) + (move.row - old_location.row) == 0))
	&& (board[move.row-1][move.column-1].color != move.piece_data.color)){}
	else
	{
		check = false;
	}

	// check if there is an obstacle on the way (right up)
	int distance;
	int blocked = 0;
	if(old_location.row < move.row && old_location.column < move.column)
	{
	    distance = move.column - old_location.column;
	    if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(board[old_location.row-1+i][old_location.column-1+i].color != ' ')
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (left down)
	blocked = 0;
	if(move.row < old_location.row && move.column < old_location.column)
	{
		distance = old_location.column - move.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(board[old_location.row-1-i][old_location.column-1-i].color != ' ')
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (right down)
	blocked = 0;
	if(move.row < old_location.row && old_location.column < move.column)
	{
		distance = move.column - old_location.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(board[old_location.row-1-i][old_location.column-1+i].color != ' ')
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	// check if there is an obstacle on the way (left up)
	blocked = 0;
	if(old_location.row < move.row && move.column < old_location.column)
	{
		distance = old_location.column - move.column;
		if(distance >= 2)
	    {
	    	for(int i = 1; i <= distance; i++)
	    	{
				if(board[old_location.row-1+i][old_location.column-1-i].color != ' ')
				{
					blocked = i;
				}

				if(blocked > 0 && blocked < distance)
				{
					check = false;
				}
			}
		}
	}

	return check;
}



