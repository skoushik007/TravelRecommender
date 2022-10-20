#ifndef __FINDRECOMMENDATIONFROMFLIGHT__
#define __FINDRECOMMENDATIONFROMFLIGHT__



#include"FlightProcessor.hpp"
#include"Recommend.hpp"
#include"FindRecommendationFromOrigin.hpp"

class FindRecomendationFromDepTime{
    const  FlightProcessor &Processor;
    vector<Recommend> &AllRecommends;
    map<ArrTimeType, vector<FlightIdType>>::iterator CurrArrTime;
    map<ArrTimeType, vector<FlightIdType>>::iterator EndArrTime;
    const vector<FlightIdType> &FlightDepartingAtDepTime;
    const DepTimeType DepTime;
    unordered_map<OriCityType, FindRecommendationFromOrigin> RecommendFinderFromAllOrigin;


    void StartProcess();
public:
    FindRecomendationFromDepTime(FlightProcessor &fp,vector<Recommend> &AllRecommends, map<ArrTimeType,
                                 vector<FlightIdType>>::iterator CurrArrTime,
                                 map<ArrTimeType, vector<FlightIdType>>::iterator  EndArrTime,
                                 const vector<FlightIdType> &FlightDepartingAtDepTime, DepTimeType DepTime);
};
#endif // __FINDRECOMMENDATIONFROMFLIGHT__


