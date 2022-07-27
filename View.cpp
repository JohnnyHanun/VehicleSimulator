#include <iostream>
#include <string>
using namespace std;

#include "View.h"
#include "Model.h"

View::View():zoom{DEFAULT_ZOOM}, displaySize{DEFAULT_DISPLAY_SIZE}, origin{START_COORDINATES, START_COORDINATES}{}
int GetNumOfDigits(const int &x) {
    return (int) to_string(x).size();
}

void PrintCxTimes(const char &c, const int &times) {
    for (int i = 0; i < times; ++i) {
        cout << c;
    }
}
void View::setDefault()
{
    zoom = DEFAULT_ZOOM;
    displaySize = DEFAULT_DISPLAY_SIZE;
    origin.setX(START_COORDINATES);
    origin.setY(START_COORDINATES);
}

void View::setSize(int newSize)
{
    displaySize = newSize;
}

void View::setZoom(float newZoom)
{
    zoom = newZoom;
}

void View::pan(float x, float y)
{
    origin.setX(x);
    origin.setY(y);
}

shared_ptr<Sim_Obj> View::getObjByPoint(const Point &pnt) {
    for(const auto & war : Model::getInstance().getWarhouses())
        if(war->getLocation() == pnt) return war;

    float epsilon = 0.5;

    for(const auto & truck : Model::getInstance().getTrucks())
        if(std::abs(truck->getTrackBase()->getPosition().getX()-pnt.getX()) <= epsilon&&
        std::abs(truck->getTrackBase()->getPosition().getY()-pnt.getY()) <= epsilon)
            return truck;

    for(const auto & chopper : Model::getInstance().getChoppers())
        if(std::abs(chopper->getTrackBase()->getPosition().getX()-pnt.getX()) <= epsilon
        && std::abs(chopper->getTrackBase()->getPosition().getY()-pnt.getY()) <= epsilon)
            return chopper;

    for(const auto & statetrooper : Model::getInstance().getStateTroppers())
        if(std::abs(statetrooper->getTrackBase()->getPosition().getX()-pnt.getX()) <= epsilon
        && std::abs(statetrooper->getTrackBase()->getPosition().getY()-pnt.getY())<= epsilon)
            return statetrooper;

    return nullptr;
}
string genNumStr(int length,int number)
{
    string ret;
    for(int i=0;i<length;i++)
        ret+=" ";
    string num = to_string(number);
    auto it_ret = ret.rbegin();
    for(auto it = num.rbegin();it != num.rend();it++)
    {
        *it_ret=*it;
        it_ret++;
    }
    return ret+" ";
}

void View::show() {
    cout << "Display size: " << displaySize << ", scale: " <<zoom<< ", origin: " << origin << endl;
    vector<string> map(displaySize);
    int yScale = int(origin.getY() + displaySize * zoom - zoom);
    for(int i=0;i<displaySize;i++)
    {
        string newRow;
        for(int j=0;j<displaySize;j++)
        {
            bool flag=false;
            for(int k=0;k<(int)zoom;k++)
            {
                for(int m=0;m<(int)zoom;m++)
                {
                    Point location(origin.getX()+float(j*zoom+k),yScale-m);
                    shared_ptr<Sim_Obj> obj = getObjByPoint(location);
                    if(obj != nullptr)
                    {
                        newRow+=obj->getName().substr(0, 2);
                        flag=true;
                        break;
                    }
                }


            }
            if(!flag)
                newRow+=". ";
        }
        map[i]=std::move(newRow);
        yScale-=(int)zoom;
    }
//    for(int i=0;i<displaySize;i++)
//    {
//        string newRow;
//        for(int j=0;j<displaySize;j++)
//        {
//            Point location(origin.getX()+float(j*zoom),yScale);
//            shared_ptr<Sim_Obj> obj = getObjByPoint(location);
//            if(obj != nullptr)
//                newRow+=obj->getName().substr(0, 2);
//            else
//                newRow+=". ";
//        }
//        map[i]=std::move(newRow);
//        yScale-=(int)zoom;
//    }
    yScale=int(origin.getY() + displaySize * zoom - zoom);
    int max_length = 0;
    while(yScale >= int(origin.getY()))
    {
        string tmp = to_string(yScale);
        if(max_length < tmp.size()) max_length = tmp.size();
        yScale-=(int)zoom;
    }
    yScale=int(origin.getY() + displaySize * zoom - zoom);
    int mod=0;
    for(auto & row : map)
    {
        if(mod%3==0)
        {
          row=genNumStr(max_length,yScale)+row;
          cout<<row<<endl;
        }
        else{
            int i=0;
            while(i<max_length) {
                cout<<" ";
                i++;
            }
            cout<<" "<<row<<endl;
        }
        mod++;
        yScale-=int(zoom);
    }
    int digits = max(GetNumOfDigits(yScale), (int) to_string((int) origin.getY()).size());;
    int x = (int) origin.getX();
    const int space = 6;

    PrintCxTimes(' ', (digits + 2) - GetNumOfDigits(x));
    cout << x;
    for (int i = 1; i < displaySize; i += 3) {
        x += (int) zoom * 3;
        int len = GetNumOfDigits(x);
        PrintCxTimes(' ', space - len);
        cout << x;
    }
    cout << endl;
}