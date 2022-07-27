#include <iostream>
using namespace std;
#include "Truck.h"
#include "Utils.h"
#include "VehicleFactory.h"
#include "Model.h"
#include "fstream"
#include "Controller.h"
registerInFactory<Vehicle, Truck> rt("Truck");

Truck::Truck(const int &cases, const deque<Destinations> &dests, const TrackBase &trackB, const string &name,const State &status)
: Vehicle(trackB,name,status),destinations{dests},Alive{true},Attacked{false},cases{cases}
{
}

int Truck::getCases() const {
    return cases;
}

void Truck::setCases(int Cases) {
    Truck::cases = Cases;
}

bool Truck::isAlive() const {
    return Alive;
}

void Truck::setAlive(bool alive) {
    Alive = alive;
}

bool Truck::isAttacked() const {
    return Attacked;
}

void Truck::setAttacked(bool attacked) {
    Attacked = attacked;
}
void Truck::moveTo()
{
    TrackBase & tb = *getTrackBase();
    double distance = tb.getPosition().Distance(tb.getDestination());
    // the case that we should do the all move
    // in one time step
    if (distance <= tb.getSpeed())
    {
        tb.setPosition(tb.getDestination());
        return;
    }
    if (tb.getPosition().getX() == tb.getDestination().getX()) // 90 degrees
    {
        float factor = (tb.getPosition().getY() - tb.getDestination().getY()) < 0 ? 1 : -1;
        float x=tb.getPosition().getX();
        float y=tb.getPosition().getY()+factor*tb.getSpeed();
        tb.setPosition(Point(x,y));
        return;
    }
    if (tb.getPosition().getY() == tb.getDestination().getY()) // 0 degrees
    {
        float factor = (tb.getPosition().getX() - tb.getDestination().getX()) < 0 ? 1 : -1;
        float x=tb.getPosition().getX()+factor*tb.getSpeed();
        float y=tb.getPosition().getY();
        tb.setPosition(Point(x,y));
        return;
    }
    // the angle to move
    float alpha = atan2(tb.getDestination().getY()-tb.getPosition().getY(),tb.getDestination().getX()-tb.getPosition().getX());
   //double alpha = atan2((p2.y - p1.y),(p2.x - p1.x) );
    if(alpha<0)
        alpha=(float)(2.*pi+alpha);
    // according to the location, destination and the speed
    float x=tb.getPosition().getX()+(tb.getSpeed())*cos(alpha);
    float y=tb.getPosition().getY()+(tb.getSpeed())*sin(alpha);
    tb.setPosition(Point(x,y));

}
void Truck::update()
{
    if(!destinations.empty() && (getState() != Stopped && getState() != OffRoad) )
    {
     Destinations & dest = destinations[0];
    if(isAlive())
    {
        if(getTrackBase()->getPosition()==dest.warehouse->getLocation())
        {
            if(destinations.size() == 1)
            {
                if(dest.unload!=0)
                {
                    dest.warehouse->setInventory(dest.unload);
                    cases-=dest.unload;
                    dest.unload=0;
                    setState(Parked);
                }
            }

            float leavingTime = calculateTime(dest.leavingTime);
            if((u_int)leavingTime <= Model::getInstance().getTime()) {
                float arrivingTime = calculateTime(dest.arrivingTime);
                destinations.pop_front();
                if (destinations.empty())
                {
                    setAlive(false);
                    setState(Parked);
                    return;
                }
                Destinations & dest1 = destinations[0];
                float distance = getTrackBase()->getPosition().Distance(dest1.warehouse->getLocation());
                float time = calculateTime(dest1.arrivingTime)-leavingTime;
                getTrackBase()->setSpeed(distance/time);
                getTrackBase()->setDestination(dest1.warehouse->getLocation());
                moveTo();
                setState(Moving);
            }

        }
        else
        {
            setState(Moving);
            moveTo();
            if(getTrackBase()->getPosition()==dest.warehouse->getLocation())
            {
                if(dest.unload!=0)
                {
                    dest.warehouse->setInventory(dest.unload);
                    cases-=dest.unload;
                    dest.unload=0;
                    setState(Parked);
                }
            }
        }
    }

    }
}

void Truck::broadcastCurrentState() {
    if(destinations.size() == 0 ) { cout<<"Truck "+getName()<<" Has finished her mission , and went out of the game."<<endl;return; }
    Destinations & dest = destinations[0];
    switch(getState())
    {
        case Parked:
            cout<<"Truck "+getName()<<" Parked at "<<dest.warehouse->getName()<<" ,Crates: "+to_string(getCases())<<" ."<<endl;
            break;
        case Stopped:
            cout<<"Truck "+getName()<<" Stopped at "<<getTrackBase()->getPosition()<<" ."<<endl;
            break;
        case OffRoad:
            cout<<"Truck "+getName()<<" Off road at "<<getTrackBase()->getPosition()<<" due to an Attack , Crates: "<< getCases() <<" ."<<endl;
            break;
        case Moving:
            cout<<"Truck "+getName()<<" at "<<getTrackBase()->getPosition()<<", Heading to "+dest.warehouse->getName()<<" ,Crates: "+to_string(getCases())<<" ."<<endl;
            break;
    }
}



Truck* parseTruckFile(const string& fileName) {
    try{
        ifstream file(fileName);
        deque<Destinations> destinations;
        if (!file) throw ControllerException("File not found " + fileName);
        string line;
        getline(file, line);
        vector<string> vectLine = split(line, ',');
        if (!vectLine.empty() && vectLine.size() != 2) throw ControllerException("Bad input");
        string destName = vectLine[0];
        shared_ptr<Warehouse> fwar = Model::getInstance().getWarehouse(destName);
        if (!fwar) throw ControllerException("Warehouse is not exist " + destName);
        string leavingTime = vectLine[1];
        calculateTime(leavingTime);
        destinations.push_back(std::move(Destinations(fwar, "00:00", leavingTime, 0)));
        int inventory = 0;
        while (getline(file, line)) {
            vectLine = split(line, ',');
            if (vectLine.size() != 4) throw ControllerException("Bad input");
            destName = vectLine[0];
            shared_ptr<Warehouse> war = Model::getInstance().getWarehouse(destName);
            if (!war) throw ControllerException("Warehouse is not exist " + destName);
            string arrivingTime = vectLine[1];
            if (arrivingTime == "00:00") throw ControllerException("Bad input");
            leavingTime = vectLine[3];
            int temp;
            if (!strToInt(vectLine[2], temp)) throw ControllerException("Bad input");
            inventory += temp;
            destinations.push_back(std::move(Destinations(war, arrivingTime, leavingTime, temp)));
        }
        fwar->setInventory(-inventory);
        if (fwar->getInventory() <= 0) {
            throw ControllerException("Warehouse inventory is empty you can't " + fwar->getName());
        }
        TrackBase trackBase(0., 0, fwar->getLocation(), fwar->getLocation());
        string truckName = split(fileName, '.')[0];
        float prev = 0.;
        for (auto &d: destinations) {
            float check1, check2;
            if (d.arrivingTime == "00:00")
                prev = calculateTime(d.leavingTime);
            else {
                check1 = calculateTime(d.arrivingTime);
                if (prev > check1)
                    throw ControllerException("Bad input");
                check2 = calculateTime(d.leavingTime);
                if (check1 > check2)
                    throw ControllerException("Bad input");
                prev = check2;
            }
        }
        if (Model::getInstance().getWarehouse(truckName) != nullptr)
            throw ControllerException("Truck: " + truckName + " already has been created .");
        return new Truck(inventory, destinations, trackBase, truckName);
    }catch (ControllerException & e){
        throw e;
    }
    catch (...){
        throw ControllerException("Bad input");
    }
}
Truck *Truck::createInstance(const string &params) {
        return parseTruckFile(params);


}







