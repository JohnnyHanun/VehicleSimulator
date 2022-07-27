#include "Vehicle.h"
#include "Truck.h"
using namespace std;

#ifndef HW03_CHOPPER_H
#define HW03_CHOPPER_H


class Chopper: public Vehicle
{
private:
    float range{};
    queue<string> commands;
    struct{bool flag;string truck_name;}  attacking;
    void set_attacking(bool flag,const string & truck_name);
    void parse(const string &cmd);
    void succeed(Truck & truck );
    void fail(Truck & truck );
public:
    Chopper()=default;
    Chopper(const string &name, const string & pos );
    Chopper(const string &name , float x,float y);
    ~Chopper() override =default;
    Chopper(const Chopper& rhs)=default;
    Chopper& operator=(const Chopper & rhs)=default;
    void course(float angle, float speed);
    void position(float x,float y,float speed);
    void attack(const string & truck_name);
    void update() override;
    float getRange() const;
    void setRange(float range);
    void broadcastCurrentState() override;
    static Chopper * createInstance(const string & params);
    void insertCommand(const string& command);
};

#endif //HW03_CHOPPER_H
