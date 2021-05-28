/*

source -> dest, seats
amount = KM * Seats * 0.75 * Amount charged KM
amount = KM * Amount charges KM

*/
#include <vector>
#include <iostream>

using namespace std;

enum RideStatus {IDLE, CREATED, WITHDRAWN, COMPLETED};

class Ride{
private:
    int id;
    int source;
    int dest;
    int seats;
    RideStatus rideStatus;

public:
    static const int AMOUNT_PER_KM = 20;  //so that there is only one copy of this var
    Ride(){
        id = source = dest = seats = 0;
        rideStatus = RideStatus::IDLE;
    }
    
    int calculateFare(bool isPriorityRider){ // if rider is privilleged or not
        int dist = dest-source;
        if(seats < 2){
            return dist * AMOUNT_PER_KM * (isPriorityRider ? 0.75 : 1);
        }
        return dist * AMOUNT_PER_KM * seats * (isPriorityRider ? 0.5 : 0.75);
    } 

    void setRideStatus(RideStatus rideStatus){
        this->rideStatus = rideStatus;
    }

    RideStatus getRideStatus(){
        return this->rideStatus;
    }

    int getSeats()
    {
        return this->seats;
    }

    void setSeats(int seats)
    {
        this->seats = seats;
    }

    int getId()
    {
        return this->id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    int getSource()
    {
        return this->source;
    }

    void setSource(int source)
    {
        this->source = source;
    }

    int getDest()
    {
        return this->dest;
    }

    void setDest(int dest)
    {
        this->dest = dest;
    }
};


class Person {
public:
    string name;
};

 // -------------
class Rider : private Person{ //all public memebe of person is now private
    // Ride currentRide;
    // vector<Ride> completedRides;
    vector<Ride> allRides;
public:
    Rider(string name){
        this->name = name;
    }

    void createRide(int, int, int, int); // id, origin, dest, num of seats
    void updateRide(int, int, int, int);
    void withdrawRide(int);
    // int closeRide(); // return amount for multiple rides from riders need to add extra args
    int closeRide(int);
};

void Rider::createRide(int id, int source, int dest, int seats){
    if(source > dest){
        cout<<"Wrong values of source and dest are provided!\n";
        return ;
    }

    Ride currentRide; // for multiple rides from rider.
    // updating the current ride
    currentRide.setId(id);
    currentRide.setSource(source);
    currentRide.setDest(dest);
    currentRide.setSeats(seats);
    currentRide.setRideStatus(RideStatus::CREATED);
    allRides.push_back(currentRide);
}


void Rider::updateRide(int id, int source, int dest, int seats){
    /* if(currentRide.getRideStatus() == RideStatus::WITHDRAWN){
        cout<<"Can' t update the withdrawn ride!\n";
        return ;
    }

    if(currentRide.getRideStatus() == RideStatus::COMPLETED){
        cout<<"Can' t update the completed ride!\n";
        return ;
    }

    createRide(id, source, dest, seats); */
    auto iter = allRides.rbegin(); // since we are adding from back
    for(; iter != allRides.rend(); ++iter){
        if(iter->getId() == id)
            break;
    }
    if(iter == allRides.rend() || iter->getRideStatus() != RideStatus::CREATED){
        cout<<"Can't update the rides, ride not found!\n";
        return;
    }

    iter->setSource(source);
    iter->setDest(dest);
    iter->setSeats(seats);

}


void Rider::withdrawRide(int id){
    /*if(currentRide.getId() != id){
        cout<<"Wrong run id as input. Can't withdraw the ride\n";
        return ;
    }

    if(currentRide.getRideStatus() != RideStatus::CREATED){
        cout<<"can't update the ride!. Ride is not created\n";
        return ;
    }

    currentRide.setRideStatus(RideStatus::WITHDRAWN); */

    auto iter = allRides.rbegin();
    for(; iter != allRides.rend(); ++iter){
        if(iter->getId() == id)
            break;
    }
    if(iter == allRides.rend()){
        cout<<"ride not found!\n"<<endl;
        return ;
    }
    
    if(iter->getRideStatus() != RideStatus::CREATED){
        cout<<"Can't withdraw the ride. Ride is not created.\n"<<endl;
    }

    iter->setRideStatus(RideStatus::WITHDRAWN);
    /*optional*/
    allRides.erase((iter+1).base()); // distance from base of allRides. withdrawn ride is as good as never happened.
}

int Rider::closeRide(int id){
    /*if(currentRide.getRideStatus() != RideStatus::CREATED){
        cout<<"Ride wasn't in progress!. can't upadte the ride\n";
        return 0;
    }
    currentRide.setRideStatus(RideStatus::COMPLETED);
    completedRides.push_back(currentRide);
    return currentRide.calculateFare(completedRides.size() >= 10); */

    auto iter = allRides.rbegin();
    for(; iter != allRides.rend(); ++iter){
        if(iter->getId() == id)
            break;
    }
    if(iter == allRides.rend() || iter->getRideStatus() != RideStatus::CREATED){
        cout<<"Ride is not created yet!"<<endl;
        return 0;
    }

    iter->setRideStatus(RideStatus::COMPLETED);
    return iter->calculateFare(allRides.size() >= 10);
        
}

// ----------------------------

class Driver : private Person{
public:
    Driver(string name) {
        this->name = name;
    }
};


// --------------------------------

int main() {
    // cout<<"hello world!\n";
    Driver driver("Ramesh");
    Rider rider("RCL");

    rider.createRide(1, 50, 60, 1);
    cout<<rider.closeRide(1) << endl;

    rider.updateRide(1, 50, 60, 2);
    cout<<rider.closeRide(1) << endl;

    cout<<"**************************************\n";

    rider.createRide(1, 50, 60, 1);
    rider.withdrawRide(1);

    rider.updateRide(1, 50, 60, 2);
    cout<<rider.closeRide(1) << endl;

    cout<<"**************************************\n";

    rider.createRide(1, 50, 60, 1);
    rider.updateRide(1, 50, 60, 2);
    cout<<rider.closeRide(1) << endl;

    return 0;
}
