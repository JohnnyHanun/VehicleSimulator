#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <queue>
#include <memory>
#include <cmath>
#include <ctgmath>
#include <algorithm>
#include <sstream>
#ifndef HW03_GEOMETRY_H
#define HW03_GEOMETRY_H
#define pi 3.14159265

typedef enum{Stopped,Parked,OffRoad,Moving} State;
using u_int = unsigned int;
using namespace std;
class Point{
private:

public:
    float x;
    float y;
    Point();
    ~Point()=default;
    Point(float x,float y);
    Point(const Point & rhs)=default;
    Point(const string & pnt);
    Point(Point && rhs) noexcept ;
    Point& operator=(const Point & rhs)=default;
    Point& operator=(Point && rhs)=default;
    float getX() const;
    void setX(float x);
    float getY() const;
    float getAngle(const Point & rhs) const;
    void setY(float y);
    bool operator==(const Point & rhs) const;
    float Distance(const Point & rhs) const;
    friend ostream& operator<<(ostream& out, const Point &me);

};
#endif //HW03_GEOMETRY_H
