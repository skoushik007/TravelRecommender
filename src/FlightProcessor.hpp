


#ifndef __FLIGHTPROCESSOR__
#define __FLIGHTPROCESSOR__

#include"Flight.hpp"
#include"AliasType.hpp"
#include<vector>
#include<map>
#include "Recommend.hpp"
using namespace std;

class FlightProcessor{
    vector<Flight> AllFlights;
    vector<Recommend> AllRecommends;
    map<TimeType, vector<FlightIdType>> FlightDepTimeLine;
    map<TimeType, vector<FlightIdType>> FlightArrTimeLine;

    void FillDepTimeLine(map<TimeType, vector<FlightIdType>> &dest);
    void FillArrTimeLine(map<TimeType, vector<FlightIdType>>  &dest);
    void FillTimeLine();

    public:
    FlightProcessor(vector<Flight> &AllFlights);
    void process();
    const Flight &getFlight(int id)const;
    const vector<Recommend> &GetRecommends();
};

#endif // __FLIGHTPROCESSOR__

