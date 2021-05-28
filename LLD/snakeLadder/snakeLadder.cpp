#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class Snake{
    int start, end;
public:
    Snake(int, int);
};

class Ladder{
    int start, end;
public:
    Ladder(int, int);
};

class Player {
    int id;
    string name;
    int currentPosition;
    int getUniqueId();
public:
    Player(string);
    int getId();
    int getCurrentPosition();
    const string& getName() const;
    bool setCurrentPosition(int);
};

class Game {
    vector<Player> players;
    int currentTurn; //keep the player id in a round robin fashion
    Player* winner;
    unordered_map<int, int> snakeAndLadderMap;
public:
    Game(vector<Player>&, unordered_map<int, int>&);
    bool roll(Player&, int);
    void declareWinner();
};

Snake::Snake(int start, int end){
    this->start = start;
    this->end = end;
}

Ladder::Ladder(int start, int end){
    this->start = start;
    this->end = end;
}

int Player::getUniqueId(){
    static int playerId = 0;
    return playerId++;
}

Player::Player(string name) {
    this->id = getUniqueId();
    this->name = name;
    this->currentPosition = 0;
}

int Player::getId(){
    return this->id;
}

int Player::getCurrentPosition(){
    return this->currentPosition;
}

const string& Player::getName() const{
    return this->name;
}

bool Player::setCurrentPosition(int pos){
    if(pos > 0 && pos <= 100){
       currentPosition = pos;
       return true;
    }
    return false;
}

Game::Game(vector<Player>& players, unordered_map<int, int>& snakeAndLadderMap){
    currentTurn = 0;
    winner = nullptr;
    this->players = players;
    this->snakeAndLadderMap = snakeAndLadderMap;
}

bool Game::roll(Player& player, int value){
    if(currentTurn != player.getId()){
        cout<<"Not your turn!\n";
        return false;
    }
    if(winner){
        cout<<"Game has ended Already!\n";
        return false;
    }
    if(value < 1 && value > 6){
        cout<<"dice value is not valid!\n";
        return false;
    }
    currentTurn = (1+currentTurn)%players.size();

    int newPos = player.getCurrentPosition() + value;
    if(newPos > 100) {
        cout<<"New position is going out of board!\n";
        //skip the chance
    }
    else if(newPos == 100){
        winner = &player;
        player.setCurrentPosition(newPos);
        cout<<"Winner Found!\n";
    }
    else if(snakeAndLadderMap.count(newPos)){
       newPos = snakeAndLadderMap[newPos];
       player.setCurrentPosition(newPos); 
    }
    return true;
}

void Game::declareWinner(){
    if(!winner){
        cout<<"Game is not ended yet!\n";
        return ;
    }
    cout<<"Winner is: "<<winner->getName()<<" with id: "<<winner->getId()<<endl;
}
int main() {
    cout<<"Snake and Ladder!\n";
    
    return 0;
}