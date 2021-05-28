#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <cstdlib>
#include <ctime>



using namespace std;

typedef pair<int, int> Point ;

class Ship{
    string id;
    int size;
    Point location;
public:
    Ship(string, int, int, Point);
    const string getId();
    int getSize();
    Point getLocation();
    bool canHit(Point);
};

class Game{
    vector<vector<string>> board;
    unordered_map<int, vector<Ship>> battleShips;
    int size;
    int winner;
    void updateBoard(string, int, Point);
public:
    Game(int); // init winner as -1,
    int getWinner();
    void addShip(string, int, int, int, int, int);
    void launchMissile(int id, int x, int y);
    void viewBattleFiled(); 
};


class Driver{
    int size;
    Game game;
    set<Point> visited;
public:
    Driver(int, Game&);
    void addShip(string, int, int, int, int, int);
    void startGame();
    int getWinner();
    Point genPoint(int);
    void viewBattleFiled();
};

Ship::Ship(string id, int playerId, int size, Point point) : location(point){
    string ch = playerId == 0 ? "A" : "B";
    this->id = ch + "-"+ id; 
    this->size = size;
}

const string Ship::getId(){
    return this->id;
}

int Ship::getSize(){
    return this->size;
}

Point Ship::getLocation(){
    return this->location;
}

bool Ship::canHit(Point point){
    return (point.first < location.first + size && point.first >= location.first && 
            point.second < location.second + size && point.second >= location.second);
}

Game::Game(int N){
    this->size = N;
    this->board.resize(N, vector<string>(N, "..."));
    winner = -1;
    cout<<"Game is initialised\n";
}

int Game::getWinner(){
    return this->winner;
}

void Game::updateBoard(string shipId, int size, Point p){
    for(int i = p.first; i < p.first+size; i++){
        for(int j = p.second; j < p.second+size; j++){
            if(i < this->size && j < this->size){
                board[i][j] = shipId;
            }
        }
    }
}

void Game::addShip(string id, int size, int xA, int yA, int xB, int yB){
    
    Point locA(xA, yA);
    bool canAdd = true;
    for(Ship& ship : battleShips[0]){
        if(ship.canHit(locA)){
            canAdd = false;
            break;
        }
    }
    if(canAdd && xA >= 0 && xA+size <= this->size && yA+size <= this->size/2 && yA >= 0){
        Ship shipA(id, 0, size, locA);
        battleShips[0].push_back(shipA);
        updateBoard(shipA.getId(), size, locA);
        cout<<"Added the ship for player 0 at "<<xA<<", "<<yA<<endl;
    }
    else{
        cout<<"Can't add the ship for player A at "<<xA<<", "<<yA<<endl;
    }
    
    canAdd = true;
    Point locB(xB, yB);
    
      for(Ship& ship : battleShips[1]){
        if(ship.canHit(locB)){
            canAdd = false;
            break;
        }
    }
    
    if(canAdd && xB >= 0 && xB +size <= this->size && yB >= 0 && yB >= this->size/2 && yB+size <= this->size){
        Ship shipB(id, 1, size, locB);
        battleShips[1].push_back(shipB);
        updateBoard(shipB.getId(), size, locB);
        cout<<"Added the ship for player 1 at "<<xB<<", "<<yB<<endl;
    }
    else{
        cout<<"Can't add the ship for player B at "<<xB<<", "<<yB<<endl;
    }
}

void Game::launchMissile(int targetPlayerId, int x, int y){ 
    Point target(x, y);
    int idx = 0;
    char ch = targetPlayerId == 0 ? 'A' : 'B';
    
    for(Ship& ship : battleShips[targetPlayerId]){
        if(ship.canHit(target)){ 
            cout<<"Hit! player"<<ch<<"'s ship with id '"<<ship.getId()<<"' destryoed. \n";
            updateBoard("...", ship.getSize(), ship.getLocation());
            battleShips[targetPlayerId].erase(battleShips[targetPlayerId].begin()+idx);
            if(battleShips[targetPlayerId].size() == 0){ // if all the ships are destryoed
                winner = targetPlayerId == 0 ? 1 : 0;
            }
            return ;  // there can be only one ship that is in the range of fire
        }
        ++idx;
    }
    cout<<"Miss.\n";
}

void Game::viewBattleFiled(){
    cout<<"\n\n";
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

Driver::Driver(int N, Game& game) : game(game){
    size = N;
}

void Driver::addShip(string id, int size, int xA, int yA, int xB, int yB){
    game.addShip(id, size, xA, yA, xB, yB);
}

int Driver::getWinner(){
    return game.getWinner();
}

Point Driver::genPoint(int playerId){
    int x, y;
    x = (rand() % size);  // x will be full 0..N-1
    y = (rand() % (size/2));
    y += playerId == 0 ? (size/2) : 0;  // divide by vertical line at size/2 [0..(size/2)-1] [size/2 .. size-1]
    Point p = make_pair(x,y);
    // cout<<p.first<<"  "<<p.second<<"vis"<<visited.count(p)<<endl;
    return p;
}

void Driver::startGame(){
    cout<<"\n\nStarting game...\n\n";
    int playerId = 0; // A
    int targetPlayerId;
    int x, y;
    Point p;
    char ch;
    while(game.getWinner() < 0){
        do {
            x = (rand() % size);  // x will be full 0..N-1
            y = (rand() % (size/2));
            y += playerId == 0 ? (size/2) : 0;  // divide by vertical line at size/2 [0..(size/2)-1] [size/2 .. size-1]
            p = make_pair(x,y);
            // p = genPoint(playerId); 
        } while(visited.count(p));
        visited.insert(p);
        ch = playerId == 0? 'A' : 'B';
        cout<<"Player"<<ch<<"'s turn: Missile fired at ("<<p.first<<","<<p.second<<").  ";
        
        targetPlayerId = playerId == 0 ? 1 : 0;
        game.launchMissile(targetPlayerId, p.first, p.second);
        game.viewBattleFiled();
        playerId = (playerId+1)%2;   // chaning the turn
    }
    cout<<"Game is ended\n";
}

void Driver::viewBattleFiled(){
    game.viewBattleFiled();
}

int main() {
    srand((unsigned) time(0));     // calling srand()
    int N;  // N is even always
    cin>>N;
    if(N&1 && N > 0) {
        cout<<"N must be even and greter than 0!\n";
        return 0;
    }
    
    Game game(N);
    Driver driver(N, game);
    
    driver.addShip("SH1", 2, 0,0, 0,4);
    driver.addShip("SH2", 2, 1,1, 5,4);
    cout<<"\n\nIntial Positions of ships:\n\n";
    driver.viewBattleFiled();
    cout<<"\n\n\n";
    driver.startGame();
    
    char winner = driver.getWinner() == 0 ? 'A' : 'B';
    cout<<"Winner is player"<<winner<<endl; 
  return 0;
}


/*

* Design: OOPS
• Overloading vs. Overriding.
• Encapsulation and inheritance.
• inheritance and polymorphism
• HLD (Component wise segregation)
• LLD (Class & sequence diagram)

I sincerely want to thank you for your posts. 
It happended several times, whenever I was a slightly off the track and saw your post while scrolling thourgh the linkedin, It suddenly stopped my mind's chattering and left me in a state of introspection. 



*/