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

/*
	Needed changes:
	- fix multi-word player names
 	- fix multiple key input
*/

// data type and struct variable declaration
struct game  {
	int turn;
	char move;
	char * playerOne;
	char * playerTwo;
	char board[BOARD_SQUARES];
	bool winTrue;
	bool fullBoard;
}thisGame;

// function prototypes
void fillBoard(void);
void getPlayerNames(void);
void drawBoard(void);
void promptMove(void);
bool makeMove (void);
bool win(void);

int main(void)
{
	// assign starting values
	thisGame.turn = 1;
	thisGame.winTrue = false;
	thisGame.fullBoard = false;

	// fill board array with full-stop characters
	fillBoard();

	// get names and announce X and O
	getPlayerNames();

	// prompts for moves until win
	do {
		drawBoard();
		thisGame.turn++;
		promptMove();
		// check for no winner
		if (thisGame.turn > MAX_MOVES) {
			printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....no winner\n");
			thisGame.fullBoard = true;
			break;
		}
	}
	while (!win());
	// flips winTrue after breaking out of prompt move do/while
	thisGame.winTrue = true;
	// win message or no win message
	if (thisGame.winTrue && !(thisGame.fullBoard)) {
		drawBoard();
		printf("Way to go, %s!!!!!\n\n",
			thisGame.turn % 2 == 0 ? thisGame.playerOne : thisGame.playerTwo);
	}
	else {
		drawBoard();
		printf("No Winner - Play again soon!\n\n");
	}

	return 0;
}

/*****************************************************************************/
/*****************************************************************************/

void fillBoard(void) {
	for (int i = 0; i < BOARD_SQUARES; i++){
	thisGame.board[i] = ASCII_FULL_STOP;
	}
}

/************************************/

void getPlayerNames(void) {
	char * player1 = malloc(sizeof(char) * 25);
	printf("Player name: "); 
	scanf(" %s", player1);
	thisGame.playerOne = player1;

	char * player2 = malloc(sizeof(char) * 25);
	printf("Player name: "); 
	scanf(" %s", player2);
	thisGame.playerTwo = player2;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n%s gets x and %s gets o - let's go!!!\n", 
			thisGame.playerOne, thisGame.playerTwo);

	free(player1);
	free(player2);

	return;
}

/************************************/

void drawBoard(void) {
	printf("\n");
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
		scanVal = scanf(" %1c", &thisGame.move);
		fseek(stdin,0,SEEK_END);
		// consumes remaining characters preventing perpetual loop???
		if (scanVal == 0) {
			scanf("%*s");	
		}
	}
	while (scanVal == 0 || ((thisGame.move < ASCII_A) || 
		(thisGame.move > ASCII_g)) || 
		((thisGame.move > ASCII_G) && (thisGame.move < ASCII_a)) ||
		!makeMove());

	return;
}

/************************************/

bool makeMove (void) {

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
		return false;
	}
	// if not bottom row or taken, fills board with move
	while ((thisGame.move < FIRST_ELEMENT_BOTTOM_ROW) &&
			(thisGame.board[thisGame.move + BOARD_COLUMNS] != 'x') && 
			(thisGame.board[thisGame.move + BOARD_COLUMNS] != 'o')) {
		thisGame.move = thisGame.move + BOARD_COLUMNS;
	}
	// adds x or o to game board depending on turn
	thisGame.board[thisGame.move] = (thisGame.turn % 2 == 0 ? 'x' : 'o');

	return true;
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
				printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....%c "
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
				printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....%c "
					"wins horizontally!\n", 
					thisGame.board[(y * BOARD_COLUMNS) + x + 3]);
				return true;
			}
		}
	}
	// check for back-slash diaginal win 
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
				printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....%c "
					"wins back-slash diagonally!\n", 
					thisGame.board[((y + 3) * BOARD_COLUMNS) + x + 3]);
				return true;
			}
		}
	}

	// check for forward-slash diaginal win 
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
				printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....%c "
					"wins forward-slash diagonally!\n", 
					thisGame.board[((y + 3) * BOARD_COLUMNS) + x - 3]);
				return true;
			}
		}
	}
	// prevents check-for-win message before first move is made
	if (thisGame.turn > 1) {
		printf("\n\n\n\n\n\n\n\n\n\n\n\nChecking for win.....no winner yet\n");
	}

	return false;	
}
