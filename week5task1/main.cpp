#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<ctime>

using namespace std;
bool checkWin(char**& board, char sign, int x, int y) {
    if ((board[x][y] == sign && board[x][y + 1] == sign && board[x][y + 2] == sign &&
        board[x][y + 3] == sign && board[x][y + 4] == sign) ||
        (board[x][y - 1] == sign && board[x][y] == sign && board[x][y + 1] == sign &&
            board[x][y + 2] == sign && board[x][y + 3] == sign) ||
        (board[x][y - 2] == sign && board[x][y - 1] == sign && board[x][y] == sign &&
            board[x][y + 1] == sign && board[x][y + 2] == sign) ||
        (board[x][y - 3] == sign && board[x][y - 2] == sign && board[x][y - 1] == sign &&
            board[x][y] == sign && board[x][y + 1] == sign) ||
        (board[x][y - 4] == sign && board[x][y - 3] == sign && board[x][y - 2] == sign &&
            board[x][y - 1] == sign && board[x][y] == sign)) {
        cout << "Congratulations! You won!" << endl;
        return true;
    }
    return false;
}
bool checkDraw(char**& board, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}
int isNumber(char number[]) { // returning -1 in case there is an invalid input
    //checking for negative numbers
    if (number[0] == '-')
        return -1;

    for (int i = 0; number[i] != 0; i++) {
        if (number[i] > '9' || number[i] < '0')
            return -1;
    }
    int x = atoi(number);
    return x;
}
char getSign() {
    char player_sign[100];
    cout << "Press 1 to choose a cross or 2 to choose a nought" << endl;
    cin >> player_sign;
    int validated_player_sign = isNumber(player_sign);
    if (validated_player_sign == 1) {
        return 'X';
    }
    if (validated_player_sign == 2) {
        return 'O';
    }
    else {
        cout << "Invalid input! Try once again!" << endl;
        getSign();
    }
}
void getMove(char**& baord, char player_sign);
void printBoard(char**& board, char player_sign, int rows, int columns);
void initialiseBoard(char**& baord, char player_sign, int rows, int columns);
void computerMove(char**& board, char computer_sign, char player_sign, int rows, int columns);

int main()
{
    cout << "Hello! Specify the first dimension of the board:" << endl;
    int rows;
    cin >> rows;
    cout << "Specify the second dimension of the board:" << endl;
    int columns;
    cin >> columns;
    char** board = new char* [rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns];
    }
    char player_sign = getSign();
    char computer_sign;
    if (player_sign == 'X') {
        computer_sign = 'O';
    }
    else {
        computer_sign = 'X';
    }
    initialiseBoard(board, player_sign, rows, columns);
    while (true) {
        system("CLS");
        printBoard(board, player_sign, rows, columns);
        getMove(board, player_sign);
        computerMove(board, computer_sign, player_sign, rows, columns);
        printBoard(board, player_sign, rows, columns);
        cout << "Type anything to go to the next move" << endl;
        _getch();
    }



    //deleting the board array
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;


    return 0;
}
void getMove(char**& board, char player_sign) {
    cout << "It's time to make a move! Specify the row:" << endl;
    char row[100];
    cin >> row;
    int validated_row = isNumber(row);
    cout << "Specify the column:" << endl;
    char column[100];
    cin >> column;
    int validated_column = isNumber(column);
    validated_row--;
    validated_column--;
    if (board[validated_row][validated_column] == '-') {
        board[validated_row][validated_column] = player_sign;
    }
    else {
        cout << "You entered an already occupied spot! Try once again!" << endl;
        getMove(board, player_sign);
    }
    if (checkWin(board, player_sign, validated_row, validated_column)) {
        exit(0);
    }
    /*if (checkDraw(board, validated_row, validated_column)) {
        cout << "So close! It is a draw!";
        exit(0);
    }*/
}
void initialiseBoard(char**& board, char player_sign, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = '-';
        }
    }
}
void printBoard(char**& board, char player_sign, int rows, int columns) {
    cout << "   ";
    for (int x = 1; x <= columns; x++) {
        cout << x;
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        i++;
        cout << i << ": ";
        i--;
        for (int j = 0; j < columns; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}
void computerMove(char**& board, char computer_sign, char player_sign, int rows, int columns) {
    srand(time(0));
    int row = rand() % rows;
    int column = rand() % columns;
    if (board[row][column] == '-') {
        board[row][column] = computer_sign;
    }
    else {
        computerMove(board, computer_sign, player_sign, rows, columns);
    }
    if (checkWin(board, player_sign, row, column)) {
        exit(0);
    }
}