/* Connect Four on a 7x6 board */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define ASCII_FULL_STOP 46
#define ASCII_0 48
#define ASCII_A 65
#define ASCII_G 71
#define ASCII_a 97
#define ASCII_g 103
#define ADCII_A_to_a 32
#define BOARD_SQUARES 42
#define FIRST_ELEMENT_BOTTOM_ROW 35
#define BOARD_COLUMNS 7
#define BOARD_ROWS 6
#define MAX_MOVES 42

// data type declaration
struct game  {
	int turn;
	char move;
	char * playerOne;
	char * playerTwo;
	char board[BOARD_SQUARES];
}thisGame;

// prototypes
char * playerName(void);
void drawBoard(void);
void promptMove(void);
int checkMove (void);
int win(void);

int main(void)
{
	// assign starting values
 	thisGame.turn = 1;
 	// fill board array with chars 1-42
 	for (int i = 0; i < BOARD_SQUARES; i++){
 		thisGame.board[i] = ASCII_FULL_STOP;
 	}

	// get names and announce X and O
	thisGame.playerOne = playerName();
	thisGame.playerTwo = playerName();
	printf("\n%s gets x and %s gets o - let's go!!!\n", 
			thisGame.playerOne, thisGame.playerTwo);

	// prompts for moves until win
	do {
		drawBoard();
		thisGame.turn++;
		promptMove();
	}
	while (win() == 0);

	// end of game winning board display and message
	drawBoard();

	if (win() == 2) {
		printf("Play again soon!\n\n");
	}
	else {
		printf("Way to go, %s!!!\n\n",
		    thisGame.turn % 2 == 0 ? thisGame.playerOne : thisGame.playerTwo);
	}

	// free(playerName);?????????

	return 0;
}

/*****************************************************************************/
/*****************************************************************************/

char * playerName(void) {
	char * playerName = malloc(sizeof(char) * 25);
	printf("Player name: "); 
	scanf(" %s", playerName);

	return playerName;
}

/************************************/

void drawBoard(void) {
	printf("\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("   a b c d e f g\n");
	for (int i = 0; i < BOARD_ROWS; i++) {
		printf("   %c %c %c %c %c %c %c\n", thisGame.board[i * BOARD_COLUMNS + 0], 
			thisGame.board[i * BOARD_COLUMNS + 1], thisGame.board[i * BOARD_COLUMNS + 2], 
			thisGame.board[i * BOARD_COLUMNS + 3], thisGame.board[i * BOARD_COLUMNS + 4], 
		    thisGame.board[i * BOARD_COLUMNS + 5], thisGame.board[i * BOARD_COLUMNS + 6]);
	}
	printf("\n");

	return;
}

/************************************/

void promptMove(void) {

	// number of items scanned
	int scanVal;

	do {
		printf("%s - choose column a thru g: ", 
		thisGame.turn % 2 == 0 ? thisGame.playerOne : thisGame.playerTwo);
		scanVal = scanf(" %c", &thisGame.move);
		// consumes remaining characters preventing perpetual loop
		if (scanVal == 0) {
			scanf("%*s");	
		}
	}
	while (scanVal == 0 || ((thisGame.move < ASCII_A) || (thisGame.move > ASCII_g)) || 
		  ((thisGame.move > ASCII_G) && (thisGame.move < ASCII_a)) ||
	      (checkMove() == 1));

	return;
}

/************************************/

int checkMove (void) {

	// converts UPPER to lower case, then to 0 thru 6 for array elements
	if ((thisGame.move >= ASCII_A) && (thisGame.move <= ASCII_G)) {
		thisGame.move = (thisGame.move + ADCII_A_to_a - ASCII_a);
	}
	// converts lower case to 0 thru 6 for array elements
	else if ((thisGame.move >= ASCII_a) && (thisGame.move <= ASCII_g)) {
		thisGame.move = (thisGame.move - ASCII_a);
	}
	// checks for full column
	if (thisGame.board[thisGame.move] != ASCII_FULL_STOP) {
		printf("That column is full\n\n");
		return 1;
	}
	while ((thisGame.move < FIRST_ELEMENT_BOTTOM_ROW) &&
	 		(thisGame.board[thisGame.move + BOARD_COLUMNS] != 'x') && 
	 		(thisGame.board[thisGame.move + BOARD_COLUMNS] != 'o')) {
		thisGame.move = thisGame.move + BOARD_COLUMNS;
	}
	// adds x or o to game board depending on turn
	thisGame.board[thisGame.move] = (thisGame.turn % 2 == 0 ? 'x' : 'o');

	return 0;
}

/************************************/

int win(void) {

	// printf("win() called*********\n");

	// check for vertical win
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 3; y++) {
			if (thisGame.board[(y * BOARD_COLUMNS) + x + 0] != 
				ASCII_FULL_STOP &&	

				thisGame.board[(y * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[(y * BOARD_COLUMNS) + x + 7] &&

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 7] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 14] && 

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 14] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 21]) {
				printf("Checking for win - %c wins vertically!\n", 
					thisGame.board[0]);
				return 1;
			}

			else {
				// printf("Vertical check x=%i, y=%i\n", x, y);
			}
		}
	}
	// check for horizontal win
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 4; x++) {
			if (thisGame.board[(y * BOARD_COLUMNS) + x + 0] != 
				ASCII_FULL_STOP &&

				thisGame.board[(y * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[(y * BOARD_COLUMNS) + x + 1] &&

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 1] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 2] && 

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 2] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 3]) {
				printf("Checking for win - %c wins horizontally!\n", thisGame.board[0]);
				// printf("Last element: %c\n", thisGame.board[(y * BOARD_COLUMNS) + x + 3]);
				return 1;
	        }
	        else {
	        	// printf("horizontal checkx=%i, y=%i\n", x, y);
	        }
		}
	}

	// check for back-slant diaginal win 
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (thisGame.board[(y * BOARD_COLUMNS) + x + 0] != 
				ASCII_FULL_STOP &&	

				thisGame.board[(y * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[(y * BOARD_COLUMNS) + x + 8] &&

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 8] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 16] && 

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 16] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 24]) {
				printf("Checking for win - %c wins vertically!\n", 
					thisGame.board[0]);
				return 1;
			}

			else {
				// printf("back-slant check x=%i, y=%i\n", x, y);
			}
		}
	}

	// check for forward-slant diaginal win 
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (thisGame.board[(y * BOARD_COLUMNS) + x + 0] != 
				ASCII_FULL_STOP &&	

				thisGame.board[(y * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[(y * BOARD_COLUMNS) + x + 6] &&

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 6] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 12] && 

			 	thisGame.board[(y * BOARD_COLUMNS) + x + 12] == 
			 	thisGame.board[(y * BOARD_COLUMNS) + x + 18]) {
				printf("Checking for win - %c wins vertically!\n", 
					thisGame.board[0]);
				return 1;
			}

			else {
				// printf("forward-slant check x=%i, y=%i\n", x, y);
			}
		}
	}

	
	// if (thisGame.board[0] == thisGame.board[4] && 
	// 	thisGame.board[4] == thisGame.board[8] && 
	// 	thisGame.board[0] != ASCII_FULL_STOP) {
	// 	printf("Checking for win - %c wins diagonally!\n", thisGame.board[0]);
	// 	return 1;
	// }
	// // check for forward-slant diaginal win
	// else if (thisGame.board[2] == thisGame.board[4] && 
	// 		 thisGame.board[4] == thisGame.board[6] && 
	// 		 thisGame.board[2] != ASCII_FULL_STOP) {
	// 	printf("Checking for win - %c wins diagonally!\n", thisGame.board[2]);
	// 	return 1;
	// }
	// check for no winner
	if (thisGame.turn > MAX_MOVES) {
		printf("Checking for win - no winner.\n");
		return 2;
	}
	else {
		// prevents this message befor first move is made
		if (thisGame.turn > 1) {
			printf("\nChecking for win - no win\n");
		}
		return 0;
	}	
}
