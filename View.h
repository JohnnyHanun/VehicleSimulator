
#include <iostream>
#include "Sim_Obj.h"
#include "Geometry.h"
using namespace std;

#ifndef HW03_VIEW_H
#define HW03_VIEW_H
#define DEFAULT_DISPLAY_SIZE 25
#define DEFAULT_ZOOM 2.0
#define START_COORDINATES -10
using namespace std;
class View
{
private:
    float zoom ;
    Point origin;
    int displaySize;
    shared_ptr<Sim_Obj> getObjByPoint(const Point & pnt);
public:
    View();
    // set back to the default values
    void setDefault();
    // set the size
    void setSize(int newSize);
    // set the zoom factor
    void setZoom(float newZoom);
    // set the pan
    void pan(float x, float y);
    // show the view
    void show();

};

#endif


