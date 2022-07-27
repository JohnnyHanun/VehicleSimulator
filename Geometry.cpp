#include "Geometry.h"
#include "Utils.h"

Point::Point(float x, float y) : x{x}, y{y}
{
}

Point::Point()
:x{0},y{0}{}

float Point::getX() const {
    return x;
}

void Point::setX(float X) {
    Point::x = X;
}

float Point::getY() const {
    return y;
}

void Point::setY(float Y) {
    Point::y = Y;
}

ostream& operator<<(ostream& out, const Point &me)
{
    out.setf(std::ios_base::fixed, std::ios_base::floatfield);
    cout << setprecision(2)<<"(" << me.x << ", " << me.y << ")";
    return out;
}

bool Point::operator==(const Point & rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}

float Point::Distance(const Point &rhs) const {
    return static_cast<float>(sqrt(pow(rhs.getX() - getX(),2)+pow(rhs.getY()-getY(),2)));;
}

Point::Point(Point &&rhs) noexcept
:x{rhs.x},y{rhs.y}
{
rhs.x=0;
rhs.y=0;
}

Point::Point(const string &pnt)
{
    vector<string> point = split(pnt,',');
    x=stof(slice(point[0],1,point[0].size()));
    y=stof(slice(point[1],0,point[1].size()-1));
}

float Point::getAngle(const Point &rhs) const
{
        float dot = x * rhs.x + y*rhs.y;
        auto norm_a = (float)sqrt(pow(x,2)+pow(y,2)) ;
        auto norm_b = (float)sqrt(pow(rhs.x,2)+pow(rhs.y,2));
        return to_degrees(acos(dot/(norm_a*norm_b)));
    }


