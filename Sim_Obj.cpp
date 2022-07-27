//
// Created by Gonen Salner on 06/06/2022.
//
#include <iostream>

using namespace std;

#include "Sim_Obj.h"

Sim_Obj::Sim_Obj(const string& name,const Point& location): name{name}, location{location}{}

const string &Sim_Obj::getName() const {
    return name;
}

const Point &Sim_Obj::getLocation() const {
    return location;
}

void Sim_Obj::broadcastCurrentState() {}

void Sim_Obj::update() {}

Sim_Obj::~Sim_Obj() = default;
