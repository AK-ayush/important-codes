#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Meeting;  // forward declaration of meeting class for the Calendar.

typedef vector<Meeting> Calendar;

class Room {
    string name;
    // Calendar calendar; //meetings so far
    unordered_map<int, Calendar> calendar;
public:
    Room(string);
    const string& getName() const;
    // bool book(int, int); // start and end
    bool book(int, int, int); // day, start, end
};

class Meeting {
    int start, end;
    Room room;
public:
    Meeting(int, int, Room);
    int getStart();
    int getEnd();
};

class Scheduler {
    vector<Room> rooms;
public:
    Scheduler(vector<Room>);
    // string book(int, int);
    string book(int, int, int);
};

const string& Room::getName() const {
    return this->name;
}

Room::Room(string name) {
    this->name = name;
}

bool Room::book(int day, int start, int end){
    if(calendar.count(day)){
        for(Meeting &m : calendar[day]){
            // TODO : check for the clashes
            if(m.getStart() < end && m.getEnd() > start) 
                return false; // clashing with existing meeting
        }
    }
    Meeting meeting(start, end, *this);  // IMP : *this
    calendar[day].push_back(meeting);

    return true;
}

Meeting::Meeting(int start, int end, Room room) : room(room){  // IMP: member initialization for room:  
    this->start = start;
    this->end = end;
}

int Meeting::getStart(){
    return this->start;
}

int Meeting::getEnd(){
    return this->end;
}

Scheduler::Scheduler(vector<Room> rooms){
    this->rooms = rooms;
}

string Scheduler::book(int day, int start, int end){
    for(Room &room : rooms){ // this & is IMP : w/o room will be a local copy and it will cease to exist once it goes out of scope.
        bool flag = room.book(day, start, end);
        if(flag) return room.getName();
    }
    cout<<"No rooms available for given time slot!\n";
    return "";
}

int main(){
    cout<<"Meeting Scheduler\n";

    Room room1("Ganga");
    Room room2("Hemavati");
    Room room3("Kali");

    vector<Room> rooms;
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);

    Scheduler scheduler(rooms);
    cout<<scheduler.book(1, 2, 5)<<endl;
    cout<<scheduler.book(1, 5, 8)<<endl;
    cout<<scheduler.book(1, 4, 8)<<endl;
    cout<<scheduler.book(1, 3, 6)<<endl;
    cout<<scheduler.book(1, 7, 8)<<endl;
    cout<<scheduler.book(2, 6, 9)<<endl;
    return 0;
}