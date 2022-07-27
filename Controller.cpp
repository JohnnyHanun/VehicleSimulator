//
// Created by Gonen Salner on 17/06/2022.
//
#include <iostream>
#include "Model.h"
#include <fstream>
#include "Utils.h"
#include "VehicleFactory.h"
using namespace std;

#include "Controller.h"

void Controller::parseWarehouseFile(const string &fileName) {
    ifstream file(fileName);

    if (!file) throw ControllerException("File not found " + fileName);
    string line;

    while (getline(file,line)){
        vector<string> lineVect = split(line, ',');

        if (lineVect.size() != 4) {
            throw ControllerException("Line is to short " + line);

        }
        if (!isLegalName(lineVect[0])) {
            throw ControllerException("Warehouse name is to long " + lineVect[0]);
        }
        float x;
        float y;
        int inventory;
        unsigned int s1 = lineVect[1].size();
        unsigned int s2 = lineVect[2].size() - 1;
        if (!strToInt(lineVect[3],inventory) || !strToFloat(slice(lineVect[1],1,s1),x) || !strToFloat(slice(lineVect[2],0,s2),y))
            throw ControllerException("Bad input");
        if(Model::getInstance().getWarehouse(lineVect[0]) != nullptr)
            throw ControllerException("Warehouse: " +  lineVect[0] + " already has been created .");
        Model::getInstance().add(make_shared<Warehouse>(lineVect[0], Point(x, y), inventory));
    }
}

void Controller::parseTruckFile(const string& fileName) {

        Model::getInstance().add(VehicleFactory<Truck>::instance().create("Truck",fileName));
}

void Controller::init(int argc, char **argv) {
    try {
        if (argc < 5) {
            throw ControllerException(
                    "Usages must be -w warehouse init file -t <truckfile1> [<truckfile2> <truckfile3> ...]  ");
        }
        if (string(argv[1]) != "-w") {
            throw ControllerException("Usages must be -w warehouse init file -t <truckfile1> [<truckfile2> <truckfile3> ...]  ");
        }
        parseWarehouseFile(argv[2]);
        if (string(argv[3]) != "-t"){
            throw ControllerException("Usages must be -w warehouse init file -t <truckfile1> [<truckfile2> <truckfile3> ...]  ");
        }
        for (int i = 4; i < argc; ++i) {
            parseTruckFile(argv[i]);
        }
    } catch (ControllerException& e){
        cerr << e.what() << endl;
        exit(1);
    }

}

Controller::Controller(int argc, char **argv) :view_ptr{make_shared<View>()}
{
    init(argc,argv);
}

void Controller::run() {
    string cmd;
    vector<string> commands;
    const u_int &time = Model::getInstance().getTime();
    cout << "Time " << time << ": Enter command: ";
    while (getline(cin, cmd)) {
    try{
        if (cmd == "exit") return;
        if (cmd == "go") {
            Model::getInstance().update();
            cout << "Time " << time << ": Enter command: ";
            continue;
        }
        commands = split(cmd, ' ');
        if (commands.empty())
            throw ControllerException("Illegal Command , Please Try Again.");
        if (commands[0] == "create") {
            if (commands.size() < 4 || commands.size() > 5)
                throw ControllerException("Illegal Command , Please Try Again.");
            if (commands[2] == "Chopper") {
                if (commands.size() == 5) {
                    if (!Model::getInstance().isExist(commands[1]))
                        throw ControllerException("Illegal Command , this name already hes been used!");
                    if (!isPoint(commands[3] + commands[4]))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    if (!isLegalName(commands[1]))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    Model::getInstance().add(VehicleFactory<Chopper>::instance().create(commands[2], commands[1] + " " +commands[3]+commands[4]));
                } else
                    throw ControllerException("Illegal Command , Please Try Again.");
            } else if (commands[2] == "State_trooper") {
                if (commands.size() == 4) {
                    if (!Model::getInstance().isExist(commands[1]))
                        throw ControllerException("Illegal Command , this name already hes been used!");
                    if (Model::getInstance().getWarehouse(commands[3]) == nullptr)
                        throw ControllerException("Illegal Command , this Warehouse does not exist.");
                    if (!isLegalName(commands[1]))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    Model::getInstance().add(VehicleFactory<stateTrooper>::instance().create(commands[2], commands[1]+" "+commands[3]));
                } else
                    throw ControllerException("Illegal Command , Please Try Again.");
            } else
                throw ControllerException("Illegal Command , Please Try Again.");
        } else if (commands[0] == "default") {
            if(commands.size() != 1)
                throw ControllerException("Illegal Command , Please Try Again.");
            view_ptr->setDefault();
        } else if (commands[0] == "size") {
            if(commands.size() != 2)
                throw ControllerException("Illegal Command , Please Try Again.");
            int size;
            if(!strToInt(commands[1],size))
                throw ControllerException("Illegal Command , Please Try Again.");
            if(size < 6 || size > 30)
                throw ControllerException("Illegal Command , size should be between 30>= size > 6 .");
            view_ptr->setSize(size);
        } else if (commands[0] == "zoom") {
            if(commands.size() != 2)
                throw ControllerException("Illegal Command , Please Try Again.");
            float zoom;
            if(!strToFloat(commands[1],zoom))
                throw ControllerException("Illegal Command , Please Try Again.");
            if(zoom<=0)
                throw ControllerException("Illegal Command , Zoom should be positive real number.");
            view_ptr->setZoom(zoom);
        } else if (commands[0] == "pan") {
            if(commands.size() != 3)
                throw ControllerException("Illegal Command , Please Try Again.");
            float x,y;
            if(!strToFloat(commands[1],x) || !strToFloat(commands[2],y) )
                throw ControllerException("Illegal Command , Please Try Again.");
            view_ptr->pan(x,y);
        }else if(commands[0]=="show") {
            if(commands.size() != 1)
                throw ControllerException("Illegal Command , Please Try Again.");
            view_ptr->show();
        }else if (commands[0] == "status") {
                if(commands.size() != 1)
                    throw ControllerException("Illegal Command , Please Try Again.");
                Model::getInstance().broadcast();
            }
        else {
            shared_ptr<Truck> truck = Model::getInstance().getTruck(commands[0]);
            shared_ptr<Chopper> chopper = Model::getInstance().getChopper(commands[0]);
            shared_ptr<stateTrooper> strooper = Model::getInstance().getStateTrooper(commands[0]);
            if (truck != nullptr) {
                if (commands.size() != 2 || commands[1] != "stop")
                    throw ControllerException("Illegal Command , Please Try Again.");
                truck->stop();
            } else if (chopper != nullptr) {
                if (commands.size() < 2 || commands.size() > 5)
                    throw ControllerException("Illegal Command , Please Try Again.");
                if (commands[1] == "position") {
                    if (commands.size() != 5)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    float x, y, v;
                    if (!strToFloat(commands[2], x) || !strToFloat(commands[3], y) || !strToFloat(commands[4], v))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    chopper->insertCommand(commands[1] + " " + commands[2] + " " + commands[3] + " " + commands[4]);
                } else if (commands[1] == "course") {
                    if (commands.size() != 4)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    float course, speed;
                    if (!strToFloat(commands[2], course) || !strToFloat(commands[3], speed))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    if (speed < 0 || speed > 170)
                        throw ControllerException(
                                "Illegal Command , Please Try Again. Speed should be between 0-170 km/h.");
                    chopper->insertCommand(commands[1] + " " + commands[2] + " " + commands[3]);
                } else if (commands[1] == "stop") {
                    if (commands.size() > 2)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    chopper->insertCommand(commands[1]);
                } else if (commands[1] == "attack") {
                    if (commands.size() != 3)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    truck = Model::getInstance().getTruck(commands[2]);
                    if (truck != nullptr)
                        chopper->insertCommand(commands[1] + " " + commands[2]);
                    else
                        throw ControllerException("Illegal Command , Please Try Again.");
                } else //None of the commands are LEGAL
                    throw ControllerException("Illegal Command , Please Try Again.");
            } else if (strooper != nullptr) {
                if (commands.size() < 2 || commands.size() > 4)
                    throw ControllerException("Illegal Command , Please Try Again.");
                if (commands[1] == "position") {
                    if (commands.size() != 4)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    float x, y;
                    if (!strToFloat(commands[2], x) || !strToFloat(commands[3], y))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    strooper->insertCommand(commands[1] + " " + commands[2] + " " + commands[3]);
                } else if (commands[1] == "course") {
                    if (commands.size() != 3)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    float course;
                    if (!strToFloat(commands[2], course))
                        throw ControllerException("Illegal Command , Please Try Again.");
                    strooper->insertCommand(commands[1] + " " + commands[2]);
                } else if (commands[1] == "stop") {
                    if (commands.size() > 2)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    strooper->insertCommand(commands[1]);
                } else if (commands[1] == "destination") {
                    if (commands.size() != 3)
                        throw ControllerException("Illegal Command , Please Try Again.");
                    shared_ptr<Warehouse> war = Model::getInstance().getWarehouse(commands[2]);
                    if (war != nullptr)
                        strooper->insertCommand(commands[1] + " " + commands[2]);
                    else
                        throw ControllerException("Illegal Command , Please Try Again.");
                } else //None of the commands are LEGAL
                    throw ControllerException("Illegal Command , Please Try Again.");
            } else {
                throw ControllerException("Illegal Command , Please Try Again.");
            }
        }
    }catch(ControllerException & e)
    {
     cerr<<e.what()<<endl;
    }
    cout << "Time " << time << ": Enter command: ";
}
}



