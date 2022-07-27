#VehicleSimulator
This project deals with a time-dependent simulation of vehicles, and it is designed to make use of the Controller-View-Model paradigm.
This is a simulation in which the time steps are controlled through single commands, when the world "freezes" at each time step, until the next time transition.
A transition of a time step occurs according to the user's command, represents one circular hour, and includes an update of all the objects in the simulation world.
The geographic space is defined using a two-dimensional Euclidean space; The unit of measure is one hundred kilometers (100km), and it is assumed that the space
is not finite (no enforcement of language conditions, beyond the storage limitations of the float type.) North is defined to be the positive direction of the y-axis (0
degrees, east is the positive direction of the x-axis (90 degrees), south is the negative direction of the y-axis (180 degrees), and west is the negative direction of
x-axis (270 degrees). A vehicle's location or destination will be defined using a pair of coordinates, but the direction of travel can be defined using an angle.

the participants in the simulation:
Warehouse - A warehouse is a simulation object with a permanent location and content of crates of goods (without a storage limit), and is responsible for unloading and loading trucks. Its existence is determined during the initialization phase of the simulation(with an input configuration file).

Truck - This vehicle transports crates of goods from warehouse to warehouse according to loading and unloading orders. Upon arrival at the warehouse designated for unloading, the truck will unload the number of boxes in the unloading order. The creation of the truck occurs during the initialization of the simulation, where its rotation between the warehouses is also determined. (each truck should have a configuration file, for example if we want to create 10 trucks that means we need  10 different configuration files).

State Trooper - This vehicle patrols between the various warehouses in the geographical space, and upon completing a route returns to the departure point.
The creation of the mobile takes place during The simulation, where her moves are also determined.(run time creation , client/player decision).

Chopper - This vehicle attacks and robs trucks; He is not allowed to park in warehouses. The creation of the motorcycle takes place during the simulation, where they are also determined his moves.(run time creation , client/player decision).





