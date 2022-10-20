#include "Constraints.hpp"
#include"AliasType.hpp"
#include"Macros.hpp"
#include "FindRecomendationFromDepTime.hpp"
#include "Time.hpp"



void FindRecomendationFromDepTime::StartProcess(){
    while(CurrArrTime != EndArrTime && CurrArrTime->first - DepTime <= MAX_TRAVEL_TIME){
        auto &EndFlightIds = CurrArrTime->second;
        for(auto id:EndFlightIds){
            for(auto &r: RecommendFinderFromAllOrigin){
                FindRecommendationFromOrigin &RecommendFinderFromOrigin = r.second;
                RecommendFinderFromOrigin.FindCheapRouteTo(Processor.getFlight(id),id);
            }
        }
        CurrArrTime++;
    }
}


    FindRecomendationFromDepTime::FindRecomendationFromDepTime(FlightProcessor &fp,vector<Recommend> &AllRecommends, map<ArrTimeType,
                                 vector<FlightIdType>>::iterator CurrArrTime,
                                 map<ArrTimeType, vector<FlightIdType>>::iterator  EndArrTime,
                                 const vector<FlightIdType> &FlightDepartingAtDepTime, DepTimeType DepTime):Processor(fp),AllRecommends(AllRecommends),CurrArrTime(CurrArrTime),
                                                                                                             EndArrTime(EndArrTime),FlightDepartingAtDepTime(FlightDepartingAtDepTime),DepTime(DepTime)
    {
        for(auto fId: FlightDepartingAtDepTime){
            const Flight &flight = fp.getFlight(fId);
            if(RecommendFinderFromAllOrigin.find(flight.Ori) == RecommendFinderFromAllOrigin.end()){
                RecommendFinderFromAllOrigin.insert({flight.Ori, FindRecommendationFromOrigin(DepTime,flight.Ori)});
            }
        }
        StartProcess();
        for(auto &r: RecommendFinderFromAllOrigin){
                FindRecommendationFromOrigin &RecommendFinderFromOrigin = r.second;
                RecommendFinderFromOrigin.BuildRecommendations(AllRecommends);
        }
    }

