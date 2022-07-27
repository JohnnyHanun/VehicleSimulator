#include "Sim_Obj.h"
#ifndef HW03_WAREHOUSE_H
#define HW03_WAREHOUSE_H


class Warehouse : public Sim_Obj {
private:
int inventory;
public:
    explicit Warehouse(const string& name,const Point& location,int Inventory);
    Warehouse(const Warehouse&rhs)=default;
    ~Warehouse() override =default;
    Warehouse& operator=(const Warehouse&rhs)=default;
    int getInventory() const;
    void setInventory(int inventory);
    void broadcastCurrentState() override;
};


#endif //HW03_WAREHOUSE_H
