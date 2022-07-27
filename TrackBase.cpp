#include "TrackBase.h"

float TrackBase::getCourse() const {
    return course;
}

void TrackBase::setCourse(float Course) {
    TrackBase::course = Course;
}

float TrackBase::getSpeed() const {
    return speed;
}

void TrackBase::setSpeed(float Speed) {
    TrackBase::speed = Speed;
}

const Point &TrackBase::getPosition() const  {
    return position;
}

void TrackBase::setPosition(const Point &Position) {
    TrackBase::position = Position;
}

TrackBase::TrackBase(float course, float speed, Point  position, Point  destination)
:course{course}, speed{speed}, position{std::move(position)}, destination{std::move(destination)} {}

const Point &TrackBase::getDestination() const {
    return destination;
}

void TrackBase::setDestination(const Point &Destination) {
    this->destination = Destination;
}
