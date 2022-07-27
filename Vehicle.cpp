#include <iostream>
using namespace std;
#include "Vehicle.h"
Destinations::Destinations(const shared_ptr<Warehouse>& ware, string arrivingTime, string leavingTime, int unload)
        :warehouse{ware},arrivingTime{std::move(arrivingTime)},leavingTime{std::move(leavingTime)},unload{unload},visit{false},distance{0}
{

}

Destinations::Destinations(const shared_ptr<Warehouse> &ware, const float &distance)
:warehouse{ware},distance{distance},arrivingTime{""},leavingTime{""},unload{0},visit{false}
{

}


Vehicle::Vehicle(const string &name, const Point &location, Point destination, float course, float speed, const State& status)
: Sim_Obj{name,location}, trackBase{make_shared<TrackBase>(course, speed, location, destination)}, status{status} {}

const shared_ptr<TrackBase> &Vehicle::getTrackBase() const {
    return trackBase;
}

const State&  Vehicle::getState() const {
    return status;
}

void Vehicle::setState(const State& Status) {
    this->status = Status;
}

void Vehicle::stop() {
    setState(Stopped);
    getTrackBase()->setSpeed(0.);
}

void Vehicle::setDestination(const Point &newDestination) {
    this->getTrackBase()->setDestination(newDestination);
}

void Vehicle::setCourse(float course) {
    this->getTrackBase()->setCourse(course);

}

Vehicle::Vehicle(const TrackBase &trackB, const string &name, const State& status)
: Sim_Obj(name,trackB.getPosition()),trackBase{make_shared<TrackBase>(trackB)},status{status}
{

}


