
#ifndef __RECOMMEND__
#define __RECOMMEND__
#include "AliasType.hpp"
#include<string>
#include<vector>

class Recommend{
    public:
    string Ori;
    string Dest;
    TimeType DepDay;//days since epoch
    TimeType DepTime;//in minutes since epoch
    int cost;
    TimeType TravelDuration;//in minutes
    vector<FlightIdType> ListFlight;

    void print()const;
};

#endif // __RECOMMEND__



