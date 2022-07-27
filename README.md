#VehicleSimulator
This project deals with a time-dependent simulation of vehicles, and it is designed to make use of the Controller-View-Model paradigm.
This is a simulation in which the time steps are controlled through single commands, when the world "freezes" at each time step, until the next time transition.
A transition of a time step occurs according to the user's command, represents one circular hour, and includes an update of all the objects in the simulation world.
The geographic space is defined using a two-dimensional Euclidean space; The unit of measure is one hundred kilometers (100km), and it is assumed that the space
is not finite (no enforcement of language conditions, beyond the storage limitations of the float type.) North is defined to be the positive direction of the y-axis (0
degrees, east is the positive direction of the x-axis (90 degrees), south is the negative direction of the y-axis (180 degrees), and west is the negative direction of
x-axis (270 degrees). A vehicle's location or destination will be defined using a pair of coordinates, but the direction of travel can be defined using an angle.


