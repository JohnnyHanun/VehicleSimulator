#include "Utils.h"
#include <ctype.h>
#include <algorithm>
vector<string> split(const string & g,char delim)
{
    vector<string> s;
    string temp=g;
    temp.erase( std::remove(temp.begin(), temp.end(), '\r'), temp.end() );
    stringstream ss(temp);
    while(getline(ss,temp,delim))
    {
        temp.erase( std::remove(temp.begin(), temp.end(), ' '), temp.end() );
        s.push_back(temp);
    }

    return s;
}
string slice(const string & slc , unsigned int i,unsigned int j)
{
    return slc.substr(i,j);
}

float to_radians(float theta_d)
{
    return theta_d * pi / 180.0;
}

float to_degrees(float theta_r)
{
    return theta_r * 180.0 / pi;
}

bool strToInt(const string& str, int& num)
{
    try{
        for (auto c : str){

            if (!isdigit(c)){
                throw exception();
            }
        }
        num = stoi(str);
    } catch (...){
        return false;
    }
    return true;

}
bool strToFloat(const string& str, float & num)
{
    int c{};
    int numberOfDots{};
    if (str[0] == '-') {
        c++;
    } else if (!isdigit(str[0])) return false;
    try{
        for (; c<str.length(); c++){
            if (isalpha(str[c]) || !isdigit(str[c]) && numberOfDots > 1 || str[c] == '-'){
                throw exception();
            }
            if(str[c]=='.') numberOfDots++;
        }
        num = stof(str);
    } catch (...){
        return false;
    }
    return true;

}

bool isPoint(const string &point) {
    if (point[0] != '(' || point[point.length()-1] !=')'){
        return false;
    }
    float x{};
    for(auto & c: point){
        if (c == ',')
            x++;
    }
    if (x != 1){
        return false;
    }
    vector<string> v = split(point, ',');

    if (!strToFloat(slice(v[0], 1,v[0].size()), x) || !strToFloat(slice(v[1], 0,v[1].size()-1), x))
        return false;

    return true;
}

float calculateTime(string & time)
{
    vector<string> v = split(time);
    if (v[0].length() != 2 || v[1].length() != 2 || stoi(v[1]) > 59){
        throw exception();
    }

    for (string & s : v) {
        for (char i : s) {
            if (!isdigit(i)){
                throw exception();
            }
        }
    }
    return stof(v[0])+static_cast<float>((stof(v[1])/60.));
}

bool isLegalName(const string& name)
{
    if(name.size() > 12)
        return false;
    for(const auto & c : name)
        if(!isalpha(c)) return false;

    return true;

}