//
// Created by Gonen Salner on 07/06/2022.
//
#include <iostream>
#include "Vehicle.h"
using namespace std;

#ifndef HW03_TRUCK_H
#define HW03_TRUCK_H


class Truck: public Vehicle{
private:
    int cases;
    bool Alive;
    bool Attacked;
    void moveTo();
public:
    deque<Destinations> destinations;
    Truck(const int &cases,const deque<Destinations>& dests,const TrackBase& trackB,const string & name, const State & status=Parked);
    ~Truck() override =default;
    Truck & operator=(const Truck& rhs)=default;
    int getCases() const;
    void setCases(int cases);
    void update() override;
    bool isAlive() const;
    void broadcastCurrentState() override;
    void setAlive(bool alive);
    bool isAttacked() const;
    void setAttacked(bool attacked);
    static Truck * createInstance(const string & params);
};


#endif //HW03_TRUCK_H
