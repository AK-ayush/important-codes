#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
    int id;
    string name;
public:
    Player(int, string);
    int getId();
    string getName();
};

class Game{
    vector<int> row;
    vector<int> col;
    int diagonal;
    int antiDiagonal;
    vector<vector<char>> board;
    int numberOfMoves = 0;
    Player* winner;
    bool isDraw;
    inline bool isValid(int, int);
public:
    Game(int);
    void printBoard();
    bool move(int, int, Player&);
    Player* getWinner();
};


Player::Player(int id, string name){
    this->id = id;
    this->name = name;
}

int Player::getId(){
    return this->id;
}

string Player::getName() {
    return this->name;
}

Game::Game(int n){
    row.resize(n, 0);
    col.resize(n, 0);
    board.resize(n, vector<char>(n));
    diagonal = antiDiagonal = 0;
    winner = nullptr;
    isDraw = false;
}

void Game::printBoard(){
    int n = board.size();
    for(int i = 0; i < n ; ++i){
        for(int j = 0; j < n; ++j){
            cout<<board[i][j]<<" ";
        }
        cout<<"\n";
    }
}

inline bool Game::isValid(int r, int c){
    return r >= 0 && r < board.size() && c >= 0 && c < board[0].size();
}

bool Game::move(int r, int c, Player& p){
    int num = p.getId() == 0 ? 1 : -1;
    char ch = p.getId() == 0 ? 'O' : 'X';
    if(!isValid(r, c) || board[r][c] == 'O' || board[r][c] == 'X'){
        cout<<"position is not valid\n";
        return false;
    }
    if(winner || isDraw){
        cout<<"Game has ended!\n";
        return false;
    }
    int n = board.size();
    board[r][c] = ch;
    row[r] += num;
    col[c] += num;
    if(row == col)
        diagonal += num;
    if(c == (n - c - 1))
        antiDiagonal += num;
    
    if( abs(row[c]) == n || 
        abs(col[c]) == n || 
        abs(diagonal) == n || 
        abs(antiDiagonal) == n){
        winner = &p;
    }
    ++numberOfMoves;
    if(numberOfMoves == n*n)
        isDraw = true;
    return true;
}

Player* Game::getWinner(){
    if(isDraw) {
        cout<<"Game is declared as Draw!\n";
    }
    return winner;
}

int main() {
    cout<<"Tik Tac Toe!\n";
    return 0;
}