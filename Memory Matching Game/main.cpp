
#include <iostream>
#include<vector>
#include<algorithm>
#include <ctime>
#include <cstdlib>
#include<windows.h>

using namespace std;

const int board_size = 4;
const int total_pairs = (board_size * board_size) / 2;




//  GENERATING BOARD
vector <vector<int>> generateBoard() {
    // creating number of pairs
    vector<int> pairs;
    for (int i = 1; i <= total_pairs; ++i) {
        pairs.push_back(i);
        pairs.push_back(i);
    }
    

    // suffle the vector
    srand(time(0));
    random_shuffle(pairs.begin(), pairs.end());


    vector<vector<int>> board(board_size, vector<int>(board_size));
    int k = 0;
    // create a board
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j] = pairs[k++];
        }
    }
    return board;
}


//      DISPLAY THE BOARD

void displayBoard(vector<vector<int>>& board, vector<vector<bool>>& revealedCard) {
    
    cout << "       ";
    for (int i = 0; i < board_size; i++) {
        cout << i << "    ";
    }
    cout <<"\n      -----------------" << endl;

    for (int i = 0; i < board_size; ++i) {
        cout << i << "  =>  ";
        for (int j = 0; j < board_size; ++j) {
            if (revealedCard[i][j]) {
                cout << board[i][j] << "    ";
            }
            else {
                cout << "❌    ";
            }
        }
        
        cout <<endl<< endl;
    }
}



// function to check the match between cards
bool isMatch(vector<vector<int>>& board, vector<pair<int, int>>& picks) {
    int x1 = picks[0].first;
    int y1 = picks[0].second;
    int x2 = picks[1].first;
    int y2 = picks[1].second;

    return board[x1][y1] == board[x2][y2];
}



// user inputs
void getPlayerInput(int& x, int& y) {
    cout << "\nEnter the Row and Column: ";
    cin >> x >> y;
    cout << endl;
}






// GAME LOGIC

void playGame(vector<vector<int>> &board) {
    vector<vector<bool>> revealedCard(board_size, vector<bool>(board_size, false));
    int matchPairs = 0;

    while (matchPairs < total_pairs) {
        displayBoard(board, revealedCard);
        
        vector<pair<int, int>> picks;

        for (int i = 0; i < 2; ++i) {
            int x, y;
            bool validPick = false;

            while (!validPick) {
                getPlayerInput(x, y);
                // Check if the input is within the board and not already revealed
                if (x >= 0 && x < board_size && y >= 0 && y < board_size && !revealedCard[x][y]) {
                    validPick = true;
                }
                else {
                    cout << "Invalid input or card already revealed. Please try again." << endl;
                }
            }
            
            picks.push_back({ x, y });
            revealedCard[x][y] = true;
            displayBoard(board, revealedCard);
            
        }

        
        if (isMatch(board, picks)) {
                cout << "\nIt's A Match!\n" << endl;
                ++matchPairs;
                Sleep(2000);
                system("cls");
        }
        else {
                cout << "\nNot A Match!\n" << endl;
                revealedCard[picks[0].first][picks[0].second] = false;
                revealedCard[picks[1].first][picks[1].second] = false;
                Sleep(2000);
                system("cls");
        }
        
    }
    cout << "\nCongratulation You've Matched all the Pairs!🎉🎉!" << endl;
}



int main() {
    vector<vector<int>> board = generateBoard();
    playGame(board);
    return 0;
}





