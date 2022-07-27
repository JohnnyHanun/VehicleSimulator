
#include <iostream>
#include "Geometry.h"

using namespace std;

#ifndef HW03_SIM_OBJ_H
#define HW03_SIM_OBJ_H
class Sim_Obj {
private:
    string name;
    Point location;
public:
    Sim_Obj(const string& name,const Point& location);
    Sim_Obj(const Sim_Obj& rhs) = default;
    Sim_Obj(Sim_Obj&& rhs) = default;
    Sim_Obj& operator=(const Sim_Obj& rhs) = default;
    virtual ~Sim_Obj() = 0;
    virtual void broadcastCurrentState();
    virtual void update();
    const string &getName() const;
    const Point &getLocation() const;

};


#endif //HW03_SIM_OBJ_H
