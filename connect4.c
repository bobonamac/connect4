/* Connect Four on a 7x6 board */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// data type and struct variable declaration
struct game  {
	int turn;
	char move;
	char * playerOne;
	char * playerTwo;
	char board[BOARD_SQUARES];
}thisGame;

// function prototypes
char * getPlayerName(void);
void drawBoard(void);
void promptMove(void);
int checkMove (void);
bool win(void);

/*
	Needed changes:
	- change win() to bool
	- fix multi-word player names
 	- fix multiple key input
*/


int main(void)
{
	// assign starting values
	thisGame.turn = 1;

	// fill board array with full-stop characters
	for (int i = 0; i < BOARD_SQUARES; i++){
		thisGame.board[i] = ASCII_FULL_STOP;
	}

	// get names and announce X and O
	thisGame.playerOne = getPlayerName();
	thisGame.playerTwo = getPlayerName();
	printf("\n%s gets x and %s gets o - let's go!!!\n", 
			thisGame.playerOne, thisGame.playerTwo);

	// prompts for moves until win
	do {
		drawBoard();
		thisGame.turn++;
		promptMove();
	}
	while (win() == false);

	// check for no winner
	if (thisGame.turn > MAX_MOVES) {
		printf("\n\n\nChecking for win... \n\n\n - no winner.\n");
	}
	// prevents this message before first move is made
	else if (thisGame.turn > 1) {
		printf("\n\n\nChecking for win... \n\n\n     - no win\n");
	}

	// end of game winning board display and message
	drawBoard();

	if (win() == false) {
		drawBoard();
		printf("Play again soon!\n\n");
	}
	else {
		drawBoard();
		printf("\nWay to go, %s!!!!!\n\n",
			thisGame.turn % 2 == 0 ? thisGame.playerOne : thisGame.playerTwo);
	}

	free(thisGame.playerOne);
	free(thisGame.playerTwo);

	return 0;
}

/*****************************************************************************/
/*****************************************************************************/

char * getPlayerName(void) {
	char * playerName = malloc(sizeof(char) * 25);
	printf("Player name: "); 
	scanf(" %s", playerName);

	return playerName;
}

/************************************/

void drawBoard(void) {
	printf("\n\n");
	printf("   a b c d e f g\n");
	for (int i = 0; i < BOARD_ROWS; i++) {
		printf("   %c %c %c %c %c %c %c\n", 
			thisGame.board[i * BOARD_COLUMNS + 0], 
			thisGame.board[i * BOARD_COLUMNS + 1], 
			thisGame.board[i * BOARD_COLUMNS + 2], 
			thisGame.board[i * BOARD_COLUMNS + 3], 
			thisGame.board[i * BOARD_COLUMNS + 4], 
			thisGame.board[i * BOARD_COLUMNS + 5], 
			thisGame.board[i * BOARD_COLUMNS + 6]);
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
	while (scanVal == 0 || ((thisGame.move < ASCII_A) || 
		(thisGame.move > ASCII_g)) || 
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
	// if not bottom row or taken, fills board with move
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

bool win(void) {

	// check for vertical win
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 3; y++) {
			if (thisGame.board[((y + 0) * BOARD_COLUMNS) + x] != 
				ASCII_FULL_STOP &&	

				thisGame.board[((y + 0) * BOARD_COLUMNS) + x] == 
				thisGame.board[((y + 1) * BOARD_COLUMNS) + x] &&

				thisGame.board[((y + 1) * BOARD_COLUMNS) + x] == 
				thisGame.board[((y + 2) * BOARD_COLUMNS) + x] && 

				thisGame.board[((y + 2) * BOARD_COLUMNS) + x] == 
				thisGame.board[((y + 3) * BOARD_COLUMNS) + x]) {
				printf("\n\n\nChecking for win... \n\n\n - %c "
					"wins vertically!\n", 
					thisGame.board[((y + 3) * BOARD_COLUMNS) + x]);
				return true;
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
				printf("\n\n\nChecking for win... \n\n\n - %c "
					"wins horizontally!\n", 
					thisGame.board[(y * BOARD_COLUMNS) + x + 3]);
				return true;
			}
		}
	}
	// check for back-slant diaginal win 
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			if (thisGame.board[(y * BOARD_COLUMNS) + x + 0] != 
				ASCII_FULL_STOP &&	

				thisGame.board[(y * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[((y + 1) * BOARD_COLUMNS) + x + 1] &&

				thisGame.board[((y + 1) * BOARD_COLUMNS) + x + 1] == 
				thisGame.board[((y + 2) * BOARD_COLUMNS) + x + 2] && 

				thisGame.board[((y + 2) * BOARD_COLUMNS) + x + 2] == 
				thisGame.board[((y + 3) * BOARD_COLUMNS) + x + 3]) {
				printf("\n\n\nChecking for win... \n\n\n - %c "
					"wins back-slash diagonally!\n", 
					thisGame.board[((y + 3) * BOARD_COLUMNS) + x + 3]);
				return true;
			}
		}
	}

	// check for forward-slant diaginal win 
	for (int y = 0; y < 3; y++) {
		for (int x = 3; x < 7; x++) {
			if (thisGame.board[((y + 0) * BOARD_COLUMNS) + x - 0] != 
				ASCII_FULL_STOP &&	

				thisGame.board[((y + 0) * BOARD_COLUMNS) + x + 0] == 
				thisGame.board[((y + 1) * BOARD_COLUMNS) + x - 1] &&

				thisGame.board[((y + 1) * BOARD_COLUMNS) + x - 1] == 
				thisGame.board[((y + 2) * BOARD_COLUMNS) + x - 2] && 

				thisGame.board[((y + 2) * BOARD_COLUMNS) + x - 2] == 
				thisGame.board[((y + 3) * BOARD_COLUMNS) + x - 3]) {
				printf("\n\n\nChecking for win... \n\n\n - %c "
					"wins forward-slash diaginally!\n", 
					thisGame.board[((y + 3) * BOARD_COLUMNS) + x - 3]);
				return true;
			}
		}
	}
	return false;	
}
