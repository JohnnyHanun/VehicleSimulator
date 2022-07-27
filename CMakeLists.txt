cmake_minimum_required(VERSION 3.17)
project(HW03)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW03 main.cpp Geometry.h Geometry.cpp Sim_Obj.h Sim_Obj.cpp TrackBase.h TrackBase.cpp Vehicle.h Vehicle.cpp Truck.cpp Truck.h Warehouse.h Warehouse.cpp stateTrooper.cpp stateTrooper.h Chopper.cpp Chopper.h Model.cpp Model.h Utils.cpp Utils.h VehicleFactory.cpp VehicleFactory.h Controller.cpp Controller.h View.cpp View.h)