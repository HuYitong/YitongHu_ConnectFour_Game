#include <iostream>
#include "CFgame.h"
using namespace std;

void GameSetUp();
void StartGame();
void InsertOrRemove();
void IsWon();
void IsWonWrap();
void IsTie();
void WonRecord();
void StopGame();
void SwitchPlayer();
void RestartGame();

int rows, columns, num;
int top[20];
char board[20][20];
bool columnFull[20];
int newx, newy;
bool isPlayerOne = true, isWon = false, isWonWrap = false, isTie = false;
bool stopGame = false, restartGame = true;
bool wrap = false, drop = false;
int xWon = 0, oWon = 0;

int main() {
	system("color 1f");
	do {
		GameSetUp();
		StartGame();
		do {
			InsertOrRemove();
			StopGame();
			SwitchPlayer();
		} while (!stopGame);
		RestartGame();
	} while (restartGame);
	cout << endl;
	system("pause");
	return 0;
}

void GameSetUp() {
	bool keepAsk = false;
	do { //customize the board
		cout << "How many rows do you want (4-20)?" << endl;
		cin >> rows;
		keepAsk = false;
		if (rows > 20 || rows < 4) {
			cout << "Please select from 4 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "How many columns do you want (4-20)?" << endl;
		cin >> columns;
		keepAsk = false;
		if (columns > 20 || columns < 4) {
			cout << "Please select from 4 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do { //customize the rule
		cout << "How many linked pieces do you require to win (3-20)?" << endl;
		cin >> num;
		keepAsk = false;
		if (num > 20 || num < 3) {
			cout << "Please select from 3 to 20." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "Do you want to enable Wrap Around Mode (y/n)?" << endl; //an optional mode where the left and right sides of the grid “wrap around” for the purposes of lining up pieces to win 
		char yn;
		cin >> yn;
		keepAsk = false;
		if (yn == 'Y' || yn == 'y')
			wrap = true;
		else if (yn == 'N' || yn == 'n')
			wrap = false;
		else {
			cout << "Please input y or n." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	do {
		cout << "Do you want to enable Remove Bottom Mode (y/n)?" << endl; //an optional mode where, instead of adding a piece to the top of the grid, the player can remove one of their own pieces from the bottom of the grid
		char yn;
		cin >> yn;
		keepAsk = false;
		if (yn == 'Y' || yn == 'y')
			drop = true;
		else if (yn == 'N' || yn == 'n')
			drop = false;
		else {
			cout << "Please input y or n." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
	system("cls");
}

void StartGame() {
	for (int n = 1; n <= columns; n++)
		cout << ' ' << n;
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << '|';
		for (int j = 0; j < columns; j++) {
			board[i][j] = '.';
			cout << board[i][j] << '|';
		}
		cout << endl;
	}
	for (int t = 0; t < columns; t++) 
		top[t] = 0; //how many pieces in each column
	for (int c = 0; c < columns; c++)
		columnFull[c] = false;
	isPlayerOne = true;
	stopGame = false;
	isWon = false;
	isWonWrap = false;
	isTie = false;
	xWon = 0;
	oWon = 0;
}

void InsertOrRemove() {
	if (isPlayerOne)
		cout << "Player X's turn! Type the column number to insert or remove a piece." << endl;
	else
		cout << "Player O's turn! Type the column number to insert or remove a piece." << endl;
	int input, s;
	bool stopSelect = false;
	char cur;
	cur = isPlayerOne == true ? 'X' : 'O';
	do {
		cin >> input;
		while (!cin.good()) { //to avoid user input letters or words
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please try again." << endl;
			cin >> input;
		}
		cin.ignore(10000, '\n');
		system("cls");
		s = input - 1;
		if (drop && board[rows - 1][s] == cur) { //Remove Mode on
			for (int n = 1; n <= columns; n++)
				cout << ' ' << n;
			cout << endl;
			for (int i = 0; i < rows; i++) {
				cout << '|';
				for (int j = 0; j < columns; j++)
					cout << board[i][j] << '|';
				cout << endl;
			}
			cout << "If you want to insert a piece on the top, type 'A'." << endl;
			cout << "If you want to remove a piece from the bottom, type 'B'." << endl;
			char select;
			bool keepAsk = false;
			do {
				cin >> select;
				system("cls");
				keepAsk = false;
				if (select == 'A' || select == 'a') { //insert a piece on the top of that column
					if (s >= 0 && s < columns && !columnFull[s]) {
						for (int n = 1; n <= columns; n++)
							cout << ' ' << n;
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						top[s] += 1;
						if (top[s] == rows)
							columnFull[s] = true;
						stopSelect = true;
					}
					else if (s >= 0 && s <= columns && columnFull[s]) {
						for (int n = 1; n <= columns; n++)
							cout << ' ' << n;
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						cout << "No." << input << " line is already full." << endl;
						cout << "Please select another number from 1 to " << rows << "." << endl;
					}
					else {
						for (int n = 1; n <= columns; n++)
							cout << ' ' << n;
						cout << endl;
						for (int i = 0; i < rows; i++) {
							cout << '|';
							for (int j = 0; j < columns; j++) {
								if (i == rows - 1 - top[s] && j == s) {
									if (isPlayerOne)
										board[i][j] = 'X';
									else
										board[i][j] = 'O';
									cout << board[i][j] << '|';
									newx = j;
									newy = i;
								}
								else
									cout << board[i][j] << '|';
							}
							cout << endl;
						}
						cout << "Please select a number between 1 to " << rows << "." << endl;
					}
				}
				else if (select == 'B' || select == 'b') { //remove a piece from the bottom of that column
					for (int n = 1; n <= columns; n++) {
						cout << ' ' << n;
					}
					cout << endl;
					for (int i = rows - 1; i >= 0; i--) { //that column drops down
						if (i == 0)
							board[i][s] = '.';
						else
							board[i][s] = board[i - 1][s];
					}
					for (int i = 0; i < rows; i++) {
						cout << '|';
						for (int j = 0; j < columns; j++)
							cout << board[i][j] << '|';
						cout << endl;
					}
					newx = s;
					newy = rows - 1;
					top[s] -= 1;
					columnFull[s] = false;
					stopSelect = true;
				}
				else {
					keepAsk = true;
					cout << "Please type A or B." << endl;
				}
			} while (keepAsk);
		}
		else { //Remove Mode Off
			if (s >= 0 && s < columns && !columnFull[s]) {
				for (int n = 1; n <= columns; n++) {
					cout << ' ' << n;
				}
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				top[s] += 1;
				if (top[s] == rows)
					columnFull[s] = true;
				stopSelect = true;
			}
			else if (s >= 0 && s < columns && columnFull[s] == true) { //that column already full
				for (int n = 1; n <= columns; n++)
					cout << ' ' << n;
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne == true)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				cout << "No." << input << " line is already full." << endl;
				cout << "Please select a number between 1 to " << rows << "." << endl;
			}
			else { //input a number that out range
				for (int n = 1; n <= columns; n++)
					cout << ' ' << n;
				cout << endl;
				for (int i = 0; i < rows; i++) {
					cout << '|';
					for (int j = 0; j < columns; j++) {
						if (i == rows - 1 - top[s] && j == s) {
							if (isPlayerOne == true)
								board[i][j] = 'X';
							else
								board[i][j] = 'O';
							cout << board[i][j] << '|';
							newx = j;
							newy = i;
						}
						else
							cout << board[i][j] << '|';
					}
					cout << endl;
				}
				cout << "Please select a number between 1 to " << rows << "." << endl;
			}
		}
	} while (stopSelect == false);
	IsTie();
	if (drop == true) {//Remove Mode On
		for (int i = 1; i <= top[s]; i++) {
			if (newy >= rows - top[s]) {
				if (wrap == false)//Wrap Around Mode On/Off
					IsWon();
				else
					IsWonWrap();
				newy--;
				WonRecord();
			}
		}
	}
	else { //remove mode off
		if (wrap == false)
			IsWon();
		else
			IsWonWrap();
		WonRecord();
	}
}

void IsTie() { //if all columns are full, the game ends with tie
	int fullLine = 0;
	for (int i = 0; i < columns; i++) {
		if (top[i] == rows)
			fullLine += 1;
	}
	if (fullLine == columns)
		isTie = true;
}

void IsWon() { //check if any player won when Wrap Around Mode is off
	int count = 0, winflag = 1, i, j;
	char cur = board[newy][newx] == 'X' ? 'X' : 'O';
	for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--){ //check left
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx + 1, j = newy; i < rows && count++ < num; i++) { //check right
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWon = true;
	else
		winflag = 1;
	for (i = newx, j = newy + 1; j < columns && count++ < num; j++) { //check down
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx, j = newy - 1; j >= 0 && count++ < num; j--) { //check up
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWon = true;
	else
		winflag = 1;
	for (i = newx + 1, j = newy + 1; i < rows && j < columns && count++ < num; i++, j++) { //check down-right
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx - 1, j = newy - 1; i >= 0 && j >= 0 && count++ < num; i--, j--) { //check up-left
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWon = true;
	else
		winflag = 1;
	for (i = newx - 1, j = newy + 1; i >= 0 && j < columns && count++ < num; i--, j++) { //check down-left
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx + 1, j = newy - 1; i < rows && newy >= 0 && count++ < num; i++, j--) { //check up-right
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWon = true;
	else
		winflag = 1;
}

void IsWonWrap() {
	int count = 0, winflag = 1, i, j, m, n;
	char cur = board[newy][newx] == 'X' ? 'X' : 'O';
	if (newx == 0) { //check left
		for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy; i >= 0 && count++ < num; i--)
		{
			if (i == 0 && board[j][i] == cur) {
				winflag++;
				for (m = columns - 1, n = newy; m > newx && count++ < num; m--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (newx == columns - 1) { //check right
		for (m = 0, n = newy; m < newx && count++ < num; m++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy; i < columns && count++ < num; i++) {
			if (i == columns - 1 && board[j][i] == cur) {
				winflag++;
				for (m = 0, n = newy; m < newx && count++ < num; m++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
	for (i = newx, j = newy + 1; j < rows && count++ < num; j++) { //check down
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	for (i = newx, j = newy - 1; j >= 0 && count++ < num; j--) { //check up
		if (board[j][i] == cur)
			winflag++;
		else
			break;
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
	if (newx == columns - 1 && newy != rows - 1) { //check down-right
		for (m = 0, n = newy + 1; m < newx && n < rows && count++ < num; m++, n++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy + 1; i < columns && j < rows && count++ < num; i++, j++) {
			if (i == columns - 1 && board[j][i] == cur && j != rows - 1) {
				winflag++;
				for (m = 0, n = j + 1; m < newx && n < rows && count++ < num; m++, n++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (newx == 0 && newy != 0) { //check up-left
		for (m = columns - 1, n = newy - 1; m > newx && n >= 0 && count++ < num; m--, n--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy - 1; i >= 0 && j >= 0 && count++ < num; i--, j--)
		{
			if (i == 0 && board[j][i] == cur && j != 0) {
				winflag++;
				for (m = columns - 1, n = j - 1; m > newx && n >= 0 && count++ < num; m--, n--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
	if (newx == 0 && newy != rows - 1) { //check down-left
		for (m = columns - 1, n = newy + 1; m > newx && n < rows && count++ < num; m--, n++) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx - 1, j = newy + 1; i >= 0 && j < rows && count++ < num; i--, j++)
		{
			if (i == 0 && board[j][i] == cur && j != rows - 1) {
				winflag++;
				for (m = columns - 1, n = j + 1; m > newx && n < rows && count++ < num; m--, n++) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != 0 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (newx == columns - 1 && newy != 0) { //check up-right
		for (m = 0, n = newy - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
			if (board[n][m] == cur)
				winflag++;
			else
				break;
		}
	}
	else {
		for (i = newx + 1, j = newy - 1; i < columns && newy >= 0 && count++ < num; i++, j--) {
			if (i == columns - 1 && board[j][i] == cur && j != 0) {
				winflag++;
				for (m = 0, n = j - 1; m < newx && n >= 0 && count++ < num; m++, n--) {
					if (board[n][m] == cur)
						winflag++;
					else
						break;
				}
			}
			else if (i != columns - 1 && board[j][i] == cur)
				winflag++;
			else
				break;
		}
	}
	count = 0;
	if (winflag >= num)
		isWonWrap = true;
	else
		winflag = 1;
}

void WonRecord() {
	if (isWon || isWonWrap) {
		if (board[newy][newx] == 'X')
			xWon++;
		else
			oWon++;
	}
}

void SwitchPlayer() {
	if (isPlayerOne)
		isPlayerOne = false;
	else
		isPlayerOne = true;
}

void StopGame() {
	stopGame = true;
	if (xWon > 0 && oWon > 0) {
		cout << "The game ended in a draw." << endl;
	}
	else if (xWon > 0 && oWon == 0) {
		cout << "Player X won!" << endl;
	}
	else if (oWon > 0 && xWon == 0) {
		cout << "Player O won!" << endl;
	}
	else if (isWon == false && isWonWrap == false && isTie == true) {
		cout << "The game ended in a draw." << endl;
	}
	else
		stopGame = false;
}

void RestartGame() {
	cout << "Do you want to play Connect Four again?" << endl;
	cout << "If yes press 'Y'," << endl;
	cout << "If no press 'N'." << endl;
	char choose;
	bool keepAsk = true;
	do {
		cin >> choose;
		if (choose == 'Y' || choose == 'y') {
			restartGame = true;
			system("cls");
			keepAsk = false;
		}
		else if (choose == 'N' || choose == 'n') {
			system("cls");
			cout << "See you next time!" << endl;
			restartGame = false;
			keepAsk = false;
		}
		else {
			cout << "Please choose yes or no." << endl;
			keepAsk = true;
		}
	} while (keepAsk == true);
}