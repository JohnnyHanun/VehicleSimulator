#include <iostream>
#include "Sim_Obj.h"
#include "Warehouse.h"
#include "TrackBase.h"
using namespace std;

#ifndef HW03_VEHICLE_H
#define HW03_VEHICLE_H
typedef struct Destinations{
    shared_ptr<Warehouse> warehouse;
    string arrivingTime, leavingTime;
    int unload;
    bool visit;
    float distance;
    Destinations(const shared_ptr<Warehouse>& ware, string arrivingTime, string leavingTime, int unload);
    Destinations(const shared_ptr<Warehouse>& ware,const float & distance=0);
}Destinations;


class Vehicle: public Sim_Obj{
private:
    shared_ptr<TrackBase> trackBase;
    State status;
public:
    Vehicle(const string& name,const Point& location, Point destination, float course,float speed, const State& status=Stopped);
    Vehicle(const TrackBase & trackB,const string& name,const State& status=Stopped);

    Vehicle();

    ~Vehicle() override = default;

    const shared_ptr<TrackBase> &getTrackBase() const;

    const State& getState() const;

    void setState(const State&);

    virtual void stop();

    virtual void setDestination(const Point &newDestination);

    virtual void setCourse(float  course);

};


#endif //HW03_VEHICLE_H
