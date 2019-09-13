// BoardControl.c

#include "BoardControl.h"
#include "Pieces.h"

#include <stdio.h>

void board_init(void)
{
	printf("\nInitializing the board\n");
	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			board[row][column].piece = ' ';
			board[row][column].color = ' ';
		}
	}
}

void set_all_pieces(void)
{
	printf("\nSetting the pieces in places\n");
	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			if(row < 2)
			{
				board[row][column].color = 'W';
				if(row == 0)
    			{
	    			if(column == 0 || column == COLUMN-1)
    	        	{
	    	        	board[row][column].piece = 'R';
		            }
    		        if(column == 1 || column == COLUMN-2)
	     	        {
		        	    board[row][column].piece = 'N';
			        }
    			    if(column == 2 || column == COLUMN-3)
	    		    {
		    	    	board[row][column].piece = 'B';
			    	}
				    if(column == 3)
				    {
					    board[row][column].piece = 'Q';
				    }
    				if(column == 4)
	    			{
		    			board[row][column].piece = 'K';
			    	}
			    }
			    if(row == 1)
    			{
	    			board[row][column].piece = 'P';
		    	}
			}

			if(row >= 2 && row <= 5)
			{
				board[row][column].piece = ' ';
		    	board[row][column].color = ' ';
			}

			if(row > 5)
			{
				board[row][column].color = 'B';
				if(row == ROW-1)
    			{
	    			if(column == 0 || column == COLUMN-1)
    	        	{
	    	        	board[row][column].piece = 'R';
		            }
    		        if(column == 1 || column == COLUMN-2)
	     	        {
		        	    board[row][column].piece = 'N';
			        }
    			    if(column == 2 || column == COLUMN-3)
	    		    {
		    	    	board[row][column].piece = 'B';
			    	}
				    if(column == 3)
				    {
					    board[row][column].piece = 'Q';
				    }
    				if(column == 4)
	    			{
		    			board[row][column].piece = 'K';
			    	}
			    }
			    if(row == ROW-2)
    			{
	    			board[row][column].piece = 'P';
		    	}
			}
		}
	}
}

void board_print(void)
{
	printf("\nPrinting out the board\n\n");

	// Print out the alphabets (a-h) above and below the board
	printf("  ");
	for(char alphabet = 'a'; alphabet < 'a' + COLUMN; alphabet++)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");

	for(int row = ROW - 1; row >= 0; row--)
	{
		printf("  ");
		for(int i = 0; i < COLUMN; i++)
		{
			printf("-----");
		}
		printf("\n");
		printf("%d ", row + 1); // Print the row number as well
		for(int column = 0; column < COLUMN; column++)
		{
			printf("| %c%c ", board[row][column].color ,board[row][column].piece);
		}
		printf("| ");
		printf("%d", row + 1);  // Print the row number as well
		printf("\n");
	}

	printf("  ");
	for(int i = 0; i < COLUMN; i++)
	{
		printf("-----");
	}
	printf("\n");

	printf("  ");
	for(char alphabet = 'a'; alphabet < 'a' + COLUMN; alphabet++)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");
}


void print_upside_down(void)
{
	printf("\nPrinting out the board (upside down))\n\n");

	// Print out the alphabets (a-h) above and below the board
	printf("  ");
	for(char alphabet = 'h'; alphabet > 'h' - COLUMN; alphabet--)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");

	for(int row = 0; row < ROW; row++)
	{
		printf("  ");
		for(int i = 0; i < COLUMN; i++)
		{
			printf("-----");
		}
		printf("\n");
		printf("%d ", row + 1); // Print the row number as well

		for(int column = COLUMN - 1; column >= 0; column--)
		{
			printf("| %c%c ", board[row][column].color ,board[row][column].piece);
		}
		printf("| ");
		printf("%d", row + 1);  // Print the row number as well
		printf("\n");
	}

	printf("  ");
	for(int i = 0; i < COLUMN; i++)
	{
		printf("-----");
	}
	printf("\n");

	printf("  ");
	for(char alphabet = 'h'; alphabet > 'h' - COLUMN; alphabet--)
	{
		printf("   %c ",alphabet);
	}

	printf("\n");
}


char turn_change(char turn)
{
	if(turn == 'W')
	{
		turn = 'B';
	}
	else if(turn == 'B')
	{
		turn = 'W';
	}

	return turn;
}

bool is_color_valid(char turn, move_t move)
{
	bool result;

	if(move.piece_data.color == turn)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if(result == false)
	{
		printf("You should pick a piece of your own color\n");
	}

	return result;
}

move_t ask_movement(void)
{
	move_t move;

	scanf(" %c %d %c", &move.column, &move.row, &move.piece_data.piece);

	move.column = tolower(move.column);    // in case the user enter an uppercase character
	move.column = move.column - 96;      // Convert the alphabet into number

	move.piece_data.piece = toupper(move.piece_data.piece); // in case the user enter a lowercase character

	return move;
}

bool is_move_canceled(move_t old_location, move_t move)
{
	bool result;

	if(old_location.row == move.row && old_location.column == move.column)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

bool is_move_valid(move_t move)
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
	// if it doesn't match any of the pieces that exist, false
	if(move.piece_data.piece != 'P' && move.piece_data.piece != 'N' && move.piece_data.piece != 'B' &&
	   move.piece_data.piece != 'R' && move.piece_data.piece != 'Q' && move.piece_data.piece != 'K')
	{
		check = false;
	}

	if(check == false)
	{
		printf("Invalid movement\n");
	}

	return check;
}

// experimental function
void add_piece(void)
{
	move_t move;
	bool check;
	char c;

	do
	{
		printf("Do you want to add a piece? (White:W, Black:B, Nope: N)  ");
		scanf(" %c",&c);
		c = toupper(c);
	}while(c != 'W' && c != 'B' && c != 'N');

	if(c != 'N')
	{
		do    // Ask the user to choose where and which piece to put
    	{
	    	printf("\nMake your move: ");
		    move = ask_movement();
		    check = is_move_valid(move);
    	}
	    while(check != true);

	    move.piece_data.color = c;

    	put_piece(move);   // Put the piece onto the designated location

    	board_print();
	}


}

// for test purpose
void put_kings(void)
{
	board[7][4].piece = 'K';
	board[7][4].color = 'B';

	board[0][4].piece = 'K';
	board[0][4].color = 'W';
}

bool is_king_captured(void)
{
	bool result = false;
	int king_count = 0;

	for(int row = 0; row < ROW; row++)
	{
		for(int column = 0; column < COLUMN; column++)
		{
			if(board[row][column].piece == 'K')
			{
				king_count++;
			}
		}
	}

	if(king_count != 2)
	{
		result = true;
		printf("\nThe king has been captured\n");
	}

	return result;
}




