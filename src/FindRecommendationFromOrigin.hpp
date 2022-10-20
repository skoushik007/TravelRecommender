
#ifndef __FINDRECOMMENDATIONFROMORIGIN__
#define __FINDRECOMMENDATIONFROMORIGIN__
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include"Recommend.hpp"
#include"Flight.hpp"

class Route{
    public:
        string Dest;
        LastFlightIdType LastFlightId;
        TravelCostType Cost;
        TimeType ArrTime;
        Route(TimeType Arr);
        Route(string d,LastFlightIdType id,TravelCostType c,TimeType t);
        Route();

        bool operator<(const Route &r)const{
            if(ArrTime < r.ArrTime)
                return true;
            else
                return false;
        }
        bool operator>(const Route &r)const{
            if(ArrTime > r.ArrTime)
                return true;
            else
                return false;
        }
        bool operator==(const Route &r)const{
            if(ArrTime == r.ArrTime)
                return true;
            else
                return false;
        }

};

class FindRecommendationFromOrigin{
    DepTimeType DepTime;
    string Ori;
    unordered_map<FlightIdType,FlightIdType> PrevFlightIdInBestRoute;
    map<DestCityType, set<Route>> BestTravelRoutes;

    bool FindCheapRouteTo(string ToDest,ArrTimeType  TillArrTime,Route &CheapRoute);
    void BuildRecommendation(const Route& R,Recommend &NewRecommend);
    void InsertNewRoute(const Route &NewRoute);
    void LinkNewRoutePrevRoute(int NewRouteLastFlightId,int prevRouteLastFlightId);

public:
    FindRecommendationFromOrigin(DepTimeType DepTime, string Ori);
    void BuildRecommendations(vector<Recommend> &AllRecommends);
    void FindCheapRouteTo(const Flight &EndFlight,FlightIdType EndFlightId);
};

#endif
