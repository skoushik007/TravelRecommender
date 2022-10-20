
#ifndef __FLIGHT__
#define __FLIGHT__

#include "AliasType.hpp"
#include<string>

using namespace std;
class Flight{
public:
    string Ori;
    string Dest;
    TimeType DepTime;
    TimeType ArrTime;
    int Cost;
    Flight(string Ori,string Dest,TimeType DepT,TimeType ArrT,int Cost);
};

#endif // __FLIGHT__





