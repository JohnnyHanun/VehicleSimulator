#include <iostream>
#include "Vehicle.h"

using namespace std;

#ifndef HW03_STATETROOPER_H
#define HW03_STATETROOPER_H


class stateTrooper: public Vehicle{
private:
    queue<string> commands;
    deque<Destinations> dests;
    string source_wh;
    string ahead;
    void initalize_dests();
    void parse(const string & cmd);
    void moveTo();
public:
    stateTrooper()=default;
    stateTrooper(const string  &name , string source);
    ~stateTrooper() override = default;
    stateTrooper(const stateTrooper & rhs)=default;
    stateTrooper & operator=(const stateTrooper & rhs)=default;
    void course(float crs);
    void destination(const string & wh);
    void position(float x,float y);
    void update() override;
    void broadcastCurrentState() override;
    static stateTrooper * createInstance(const string & params);
    void insertCommand(const string &command);
};


#endif //HW03_STATETROOPER_H
