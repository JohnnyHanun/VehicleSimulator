//
// Created by Gonen Salner on 17/06/2022.
//
#include <iostream>
#include "Truck.h"
#include "Chopper.h"
#include "stateTrooper.h"
#include "Warehouse.h"
#include "View.h"
using namespace std;

#ifndef HW03_CONTROLLER_H
#define HW03_CONTROLLER_H
class ControllerException : public exception{
public:
    explicit ControllerException(const char* message): msg(message) {}
    ControllerException(const ControllerException& e) noexcept{msg=e.msg;}
    explicit ControllerException(string message): msg(move(message)) {}
    const char* what() const noexcept override {return msg.c_str();}
protected:
    string msg;
};

class Controller {
private:
    void init(int argc, char* argv[]);
    shared_ptr<View> view_ptr;
public:
    void parseWarehouseFile(const string& fileName);
    void parseTruckFile(const string& fileName);
    Controller(int argc, char* argv[]);
    Controller()=default;
    ~Controller()=default;
    Controller(const Controller& rhs)=delete;
    Controller& operator=(const Controller& rhs)=delete;
    void run();


};


#endif //HW03_CONTROLLER_H
