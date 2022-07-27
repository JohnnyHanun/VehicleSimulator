using namespace std;
#include "Model.h"
unique_ptr<Model> Model::model = nullptr;

const u_int& Model::getTime() const {
    return time;
}

Model & Model::getInstance() {
    if(model==nullptr)
        model = unique_ptr<Model>(new Model());
    return *model;
}

const vector<shared_ptr<Truck>> &Model::getTrucks() {
    return trucks;
}

const vector<shared_ptr<stateTrooper>> &Model::getStateTroppers() {
    return stateTroopers;
}

const vector<shared_ptr<Chopper>> &Model::getChoppers() {
    return choppers;
}

const vector<shared_ptr<Warehouse>> &Model::getWarhouses() {
    return warehouses;
}

void Model::add(shared_ptr<Truck> truck) {
    if (truck != nullptr)
        trucks.push_back(std::move(truck));
}

void Model::add(shared_ptr<Warehouse> warehouse) {
    if (warehouse != nullptr)
        warehouses.push_back(std::move(warehouse));
}

void Model::add(shared_ptr<Chopper> chopper) {
    if (chopper != nullptr)
        choppers.push_back(std::move(chopper));
}

void Model::add(shared_ptr<stateTrooper> stateTrooper) {
    if (stateTrooper != nullptr)
        stateTroopers.push_back(std::move(stateTrooper));
}

shared_ptr<Warehouse> Model::getWarehouse(const string &warehouseName) {
    for(const auto& war: warehouses)
        if (war->getName() == warehouseName)
            return shared_ptr<Warehouse>{war};
    return nullptr;

}

shared_ptr<Truck> Model::getTruck(const string &TruckName) {
    for(const auto& truck: trucks)
        if (truck->getName() == TruckName)
            return shared_ptr<Truck>{truck};

    return nullptr;
}

Model::Model()
:trucks{},stateTroopers{},warehouses{},time{},choppers{}
{
    add(make_shared<Warehouse>("Frankfurt",Point(40,10),100000));
}

void Model::update() {
    for (auto & truck : trucks){
        truck->update();
    }
    for (auto & stateTrooper : stateTroopers){
        stateTrooper->update();
    }
    for (auto & chopper : choppers){
        chopper->update();
    }
    time++;
}

shared_ptr<stateTrooper> Model::getStateTrooper(const string &StateTrooperName) {
    for(const auto& state: stateTroopers)
        if (state->getName() == StateTrooperName)
            return shared_ptr<stateTrooper>{state};
    return nullptr;
}


shared_ptr<Chopper> Model::getChopper(const string &ChooperName) {
        for(const auto& chopper: choppers)
        if (chopper->getName() == ChooperName)
            return shared_ptr<Chopper>{chopper};
    return nullptr;
}

bool Model::isExist(const string &name) {
    return (!getChopper(name) && !getTruck(name)
    && !getStateTrooper(name)
    && !getWarehouse(name));
}

void Model::broadcast()
{
    for(auto & war : warehouses)
        war->broadcastCurrentState();
    for (auto & truck : trucks)
        truck->broadcastCurrentState();
    for (auto & stateTrooper : stateTroopers)
        stateTrooper->broadcastCurrentState();
    for (auto & chopper : choppers)
        chopper->broadcastCurrentState();
}
