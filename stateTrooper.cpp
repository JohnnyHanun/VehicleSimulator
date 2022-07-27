#include "Utils.h"
using namespace std;

#include "stateTrooper.h"
#include "VehicleFactory.h"
#include "Model.h"
registerInFactory<Vehicle, stateTrooper> rst("State_trooper");

void stateTrooper::initalize_dests() {

    const auto & warhouses = Model::getInstance().getWarhouses();
    dests.clear();
    for(const auto & wh : warhouses)
    {
        if(wh->getName() == source_wh) {
            getTrackBase()->setDestination(wh->getLocation());
            ahead = wh->getName();
            continue;
        }
        dests.push_back(Destinations(wh));
    }
    getTrackBase()->setCourse(0);
}

stateTrooper::stateTrooper(const string& name, string source)
: Vehicle(TrackBase(),name),source_wh{std::move(source)},commands{},dests{},ahead{}
{
    getTrackBase()->setSpeed(90.);
    getTrackBase()->setPosition(Model::getInstance().getWarehouse(source_wh)->getLocation());
    getTrackBase()->setCourse(0.);
    initalize_dests();
}

void stateTrooper::course(float crs)
{
    getTrackBase()->setCourse(crs);
}

void stateTrooper::destination(const string & wh)
{
    source_wh = wh;
    initalize_dests();
}

void stateTrooper::position(float x, float y)
{
    getTrackBase()->setPosition(Point(x,y));
}

void stateTrooper::parse(const string &cmd)
{
    vector<string> prs = split(cmd,' ');
    if(prs[0]=="stop")
    {
        setState(Stopped);
        dests.clear();
    }
    else {
        if (prs[0] == "destination")
            destination(prs[1]);
        else if (prs[0] == "course")
            course(atof(prs[1].c_str()));
        else if (prs[0] == "position")
            position(atof(prs[1].c_str()), atof(prs[2].c_str()));
        setState(Moving);
    }
}

void stateTrooper::moveTo()
{
    TrackBase & tb = *getTrackBase();
    double distance = tb.getPosition().Distance(tb.getDestination());
    // the case that we should do the all move
    // in one time step
    if (distance <= (tb.getSpeed()/100.))
    {
        tb.setPosition(tb.getDestination());
        return;
    }
    if (tb.getPosition().getX() == tb.getDestination().getX()) // 90 degrees
    {
        float factor = (tb.getPosition().getY() - tb.getDestination().getY()) < 0 ? 1 : -1;
        float x=tb.getPosition().getX();
        float y=tb.getPosition().getY()+factor*(tb.getSpeed()/100.);
        tb.setPosition(Point(x,y));
        return;
    }
    if (tb.getPosition().getY() == tb.getDestination().getY()) // 0 degrees
    {
        float factor = (tb.getPosition().getX() - tb.getDestination().getX()) < 0 ? 1 : -1;
        float x=tb.getPosition().getX()+factor*(tb.getSpeed()/100.);
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
    auto x=float(tb.getPosition().getX()+((tb.getSpeed()/100.))*cos(alpha));
    auto y=float(tb.getPosition().getY()+((tb.getSpeed()/100.))*sin(alpha));
    tb.setPosition(Point(x,y));
}
void stateTrooper::update() {
    while (!commands.empty()) {
        parse(commands.front());
        commands.pop();
    }
    if (getState() != Stopped && getState() != Parked) {
        TrackBase &tb = *getTrackBase();
        if (tb.getCourse() == 0)
            moveTo();
        else {
            auto x = float(tb.getPosition().getX() + sin(tb.getCourse() * pi / 180.) * (tb.getSpeed() / 100.));
            auto y = float(tb.getPosition().getY() + cos(tb.getCourse() * pi / 180.) * (tb.getSpeed() / 100.));
            tb.setPosition(Point(x, y));
        }
        if (tb.getPosition() == tb.getDestination()) {
            if(dests.empty() && tb.getDestination()==Model::getInstance().getWarehouse(source_wh)->getLocation() )
            {
                setState(Parked);
            }
            else if(dests.empty())
            {
                if(!(tb.getDestination() == Model::getInstance().getWarehouse(source_wh)->getLocation()))
                     tb.setDestination(Model::getInstance().getWarehouse(source_wh)->getLocation());
            }
            else
            {
              for(auto & dst : dests)
                  dst.distance=getTrackBase()->getPosition().Distance(dst.warehouse->getLocation());
              auto functor = [](const Destinations & a , const Destinations & b)->bool{
                    if(a.distance == b.distance)
                        return a.warehouse->getName() < b.warehouse->getName();
                    return a.distance < b.distance;
                };
              sort(dests.begin(),dests.end(),functor);
              tb.setDestination(dests[0].warehouse->getLocation());
              ahead = dests[0].warehouse->getName();
              dests.pop_front();
              setState(Moving);
            }
        }
    }
}

void stateTrooper::broadcastCurrentState() {
        switch(getState())
        {
            case Parked:
                cout<<"State Trooper "+getName()<<" Parked at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case Stopped:
                cout<<"State Trooper "+getName()<<" Stopped at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case OffRoad:
                cout<<"State Trooper "+getName()<<" Off road at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case Moving:
                cout<<setprecision(4)<<"State Trooper "+getName()<<" at "<<getTrackBase()->getPosition()<<", Heading to "+ahead+", speed : "<<getTrackBase()->getSpeed()<<" km/h."<<endl;
                break;
        }
}

stateTrooper *stateTrooper::createInstance(const string &params) {
        vector<string> prs = split(params,' ');
        return new stateTrooper(prs[0],prs[1]);
}

void stateTrooper::insertCommand(const string &command) {
    commands.push(command);
}







