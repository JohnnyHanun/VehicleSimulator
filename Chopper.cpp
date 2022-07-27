#include "Utils.h"
#include "Chopper.h"
#include "VehicleFactory.h"
#include "Model.h"
registerInFactory<Vehicle, Chopper> rc("Chopper");

Chopper::Chopper(const string & name, const string &pos)
:Vehicle(TrackBase(),name),range{2.},attacking{}
{
    getTrackBase()->setSpeed(0);
    getTrackBase()->setCourse(0);
    getTrackBase()->setPosition(Point(pos));

}

Chopper::Chopper(const string &name , float x, float y)
:Vehicle(TrackBase(),name),range{2.},attacking{}
{
    getTrackBase()->setSpeed(0);
    getTrackBase()->setCourse(0);
    getTrackBase()->setPosition(Point(x,y));
}

void Chopper::course(float angle, float speed)
{
    getTrackBase()->setSpeed(speed);
    getTrackBase()->setCourse(angle);
    setState(Moving);
}

void Chopper::position(float x, float y, float speed)
{
    getTrackBase()->setPosition(Point(x,y));
    getTrackBase()->setCourse(speed);
    setState(Moving);
}

void Chopper::attack(const string &truck_name)
{
   const auto & stateTroopers = Model::getInstance().getStateTroppers();
   auto truck = Model::getInstance().getTruck(truck_name);
   TrackBase & tb = *truck->getTrackBase();
   float dst;
   for(const auto & stp : stateTroopers)
   {
       dst = stp->getTrackBase()->getPosition().Distance(tb.getPosition()) / 100.;
      if(dst <= 10)
      {
          fail(*truck);
          return;
      }
   }
   dst = float(getTrackBase()->getPosition().Distance(tb.getPosition()) / 100.);
   if(dst <= range && truck->getState() != Parked && truck->getState() != OffRoad )
   {
       succeed(*truck);
       return;
   }
   fail(*truck);
}


void Chopper::parse(const string &cmd)
{
    vector<string> prs = split(cmd,' ');
    if(prs[0]=="stop")
        setState(Stopped);
    else {
        if (prs[0] == "course")
            course(atof(prs[1].c_str()),atof(prs[2].c_str()));
        else if (prs[0] == "position")
            position(atof(prs[1].c_str()), atof(prs[2].c_str()),atof(prs[3].c_str()));
        else if(prs[0]=="attack")
            set_attacking(true,prs[1]);
        setState(Moving);
    }
}

void Chopper::set_attacking(bool flag, const string &truck_name)
{
    attacking.flag = flag;
    attacking.truck_name = truck_name;
}
void Chopper::update()
{
    while (!commands.empty()) {
        parse(commands.front());
        commands.pop();
    }
    if(attacking.flag)
        attack(attacking.truck_name);
    else if(getState()!=Stopped)
    {
        TrackBase & tb = *getTrackBase();
        auto x = float(tb.getPosition().getX() + sin(tb.getCourse() * pi / 180.) * (tb.getSpeed() / 100.));
        auto y = float(tb.getPosition().getY() + cos(tb.getCourse() * pi / 180.) * (tb.getSpeed() / 100.));
        tb.setPosition(Point(x, y));
    }
}

void Chopper::succeed(Truck & truck)
{
    attacking.flag=false;
    attacking.truck_name="";
    if(range <= 20) range++;
    truck.setState(OffRoad);
    truck.setAlive(false);
    truck.setCases(0);
    setState(Stopped);
    cout<<getName()<<" Tried to attack Truck: "<<truck.getName()<<" and Succeeded .. at "<<truck.getTrackBase()->getPosition()<<"."<<endl;
}

void Chopper::fail(Truck & truck)
{
    attacking.flag=false;
    attacking.truck_name="";
    if(range != 0) range--;
    setState(Stopped);
    cout<<getName()<<" Tried to attack Truck: "<<truck.getName()<<" But Failed .. at "<<truck.getTrackBase()->getPosition()<<"."<<endl;
}

float Chopper::getRange() const {
    return range;
}

void Chopper::setRange(float Range) {
    Chopper::range = Range;
}

void Chopper::broadcastCurrentState() {
        switch(getState())
        {
            case Parked:
                cout<<"Chopper "+getName()<<" Parked at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case Stopped:
                cout<<"Chopper "+getName()<<" Stopped at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case OffRoad:
                cout<<"Chopper "+getName()<<" Off road at "<<getTrackBase()->getPosition()<<" ."<<endl;
                break;
            case Moving:
                cout<<setprecision(4)<<"Chopper "+getName()<<" at "<<getTrackBase()->getPosition()<<", Heading on course: "<<getTrackBase()->getCourse()<<+" deg, speed : "<<getTrackBase()->getSpeed()<<" km/h."<<endl;
                break;
        }
}

Chopper *Chopper::createInstance(const string &params)
{
    vector<string> prs = split(params,' ');
    return new Chopper(prs[0],prs[1]);
}

void Chopper::insertCommand(const string &command) {
        commands.push(command);
}


