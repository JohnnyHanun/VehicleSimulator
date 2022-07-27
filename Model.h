#include <iostream>
#include "Truck.h"
#include "Chopper.h"
#include "stateTrooper.h"
#include "Warehouse.h"


using namespace std;

#ifndef HW03_MODEL_H
#define HW03_MODEL_H


class Model {
private:
    static unique_ptr<Model> model;
    vector<shared_ptr<Truck>> trucks;
    vector<shared_ptr<stateTrooper>> stateTroopers;
    vector<shared_ptr<Chopper>> choppers;
    vector<shared_ptr<Warehouse>> warehouses;
    u_int time;
    //View * view;
    Model();
public:
    Model(const Model&)=delete;
    Model& operator=(const Model&)=delete;
    Model(Model&&) = delete;
    Model& operator=(Model&&)=delete;
    static Model& getInstance();
    const vector<shared_ptr<Truck>> &  getTrucks();
    const vector<shared_ptr<stateTrooper>> &  getStateTroppers();
    const vector<shared_ptr<Chopper>> &  getChoppers();
    const vector<shared_ptr<Warehouse>> &  getWarhouses();
    void add(shared_ptr<Truck>);
    void add(shared_ptr<Warehouse>);
    void add(shared_ptr<Chopper>);
    void add(shared_ptr<stateTrooper>);
    shared_ptr<Warehouse> getWarehouse(const string& warehouseName);
    shared_ptr<Truck> getTruck(const string& TruckName);
    shared_ptr<Chopper> getChopper(const string& ChooperName);
    shared_ptr<stateTrooper> getStateTrooper(const string& StateTrooperName);
    const u_int& getTime() const;
    void update();
    void broadcast();
    bool isExist(const string& name);

};


#endif //HW03_MODEL_H
