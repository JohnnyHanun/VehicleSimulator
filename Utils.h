#ifndef HW03_UTILS_H
#define HW03_UTILS_H
#include <iostream>
#include <vector>
#include <sstream>
#define pi 3.14159265
using namespace std;
vector<string> split(const string & g,char delim=':');
string slice(const string & slc , unsigned int i,unsigned int j);
float to_radians(float theta_d);
float to_degrees(float theta_r);
bool strToInt(const string& str, int& num);
bool strToFloat(const string& str, float & num);
float calculateTime(string & time);
bool isPoint(const string& point);
bool isLegalName(const string& name);
#endif //HW03_UTILS_H
