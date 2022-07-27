#ifndef HW03_TRACKBASE_H
#define HW03_TRACKBASE_H
#include "Geometry.h"

class TrackBase {
private:
    float course{};
    float speed{};
    Point position, destination;
public:
    TrackBase()=default;
    ~TrackBase()=default;
    TrackBase(float course,float speed,Point  position, Point destination);
    TrackBase(const TrackBase & rhs)=default;
    TrackBase & operator=(const TrackBase & rhs)=default;
    float getCourse() const;
    void setCourse(float course);
    float getSpeed() const;
    void setSpeed(float speed);
    const Point &getPosition() const;
    const Point &getDestination() const;
    void setDestination(const Point &destination);
    void setPosition(const Point &position);
};


#endif //HW03_TRACKBASE_H
