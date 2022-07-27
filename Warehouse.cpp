#include "Warehouse.h"

int Warehouse::getInventory() const {
    return inventory;
}
void Warehouse::setInventory(int Inventory) {
    Warehouse::inventory +=Inventory;
}
Warehouse::Warehouse(const string& name,const Point& location,int Inventory)
: Sim_Obj(name,location),inventory{Inventory}{}

void Warehouse::broadcastCurrentState() {
    cout << "Warehouse " << getName() << " at position " << getLocation() << ", Inventory: " << getInventory() << endl;
}