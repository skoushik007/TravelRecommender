#include "Constraints.hpp"
#include"AliasType.hpp"
#include"Macros.hpp"
#include "FindRecommendationFromOrigin.hpp"
#include "Time.hpp"
#include<algorithm>

Route::Route(TimeType Arr):LastFlightId(NOT_FLIGHT_ID),Cost(0),ArrTime(Arr){}
Route::Route(string d,LastFlightIdType id,TravelCostType c,TimeType t):Dest(d),LastFlightId(id),Cost(c),ArrTime(t){}
Route::Route(){
            Cost = 0;
            LastFlightId = NOT_FLIGHT_ID;
}


bool FindRecommendationFromOrigin::FindCheapRouteTo(string ToDest,ArrTimeType  TillArrTime,Route &CheapRoute){
        set<Route> &BestRouteForDest = BestTravelRoutes[ToDest];
        if(BestRouteForDest.size() == 0){
            return false;
        }
        set<Route>::iterator Iter = BestRouteForDest.upper_bound(Route(TillArrTime));
        if(Iter->ArrTime == TillArrTime){
            CheapRoute = *Iter;
            return true;
        }
        if(Iter == BestRouteForDest.begin()){
            return false;
        }
        auto PrevIter = prev(Iter,1);
        CheapRoute = *PrevIter;
        return true;
}

void FindRecommendationFromOrigin::BuildRecommendation(const Route& R, Recommend &NewRecommend){
        NewRecommend.cost = R.Cost;
        NewRecommend.Dest = R.Dest;
        NewRecommend.Ori = Ori;
        NewRecommend.TravelDuration = R.ArrTime - DepTime;
        NewRecommend.DepDay = GetTimeInDay(DepTime);
        NewRecommend.DepTime = DepTime;
        int IterFlight = R.LastFlightId;

        while(IterFlight != NOT_FLIGHT_ID){
            NewRecommend.ListFlight.push_back(IterFlight);
            IterFlight = PrevFlightIdInBestRoute[IterFlight];
        }
        reverse(NewRecommend.ListFlight.begin(),NewRecommend.ListFlight.end());
}

void FindRecommendationFromOrigin::BuildRecommendations(vector<Recommend> &AllRecommends){
        for(pair<const DestCityType, set<Route>> &pr:BestTravelRoutes){
            set<Route> &BestRouteForDest = pr.second;
            for(const Route &r:BestRouteForDest){
                AllRecommends.push_back(Recommend());
                BuildRecommendation(r,AllRecommends[AllRecommends.size()-1]);
            }
        }
}

 void FindRecommendationFromOrigin::InsertNewRoute(const Route &NewRoute){
        set<Route> &BestRouteForDest = BestTravelRoutes[NewRoute.Dest];
        if(BestRouteForDest.size()==0){
            BestRouteForDest.insert(NewRoute);
        }
        else{
            Route CurrLastRoute = *prev(BestRouteForDest.end(),1);
            if(CurrLastRoute.Cost > NewRoute.Cost){
                if(CurrLastRoute.ArrTime == NewRoute.ArrTime){
                    BestRouteForDest.erase(CurrLastRoute);
                }
                BestRouteForDest.insert(NewRoute);
            }
        }
}

 void FindRecommendationFromOrigin::LinkNewRoutePrevRoute(int NewRouteLastFlightId,int PrevRouteLastFlightId){
        PrevFlightIdInBestRoute[NewRouteLastFlightId] = PrevRouteLastFlightId;
}

void FindRecommendationFromOrigin::FindCheapRouteTo(const Flight &EndFlight, FlightIdType EndFlightId){
        if(EndFlight.DepTime < this->DepTime)
            return;
        else if(EndFlight.DepTime == this->DepTime){
            //this flight cannot be a connecting flight
            if(EndFlight.Ori == this->Ori){
                //first flight has to be starting from Ori, as this Object only finds routes starting from Ori
                Route NewRoute(EndFlight.Dest, EndFlightId,EndFlight.Cost, EndFlight.ArrTime);
                InsertNewRoute(NewRoute);
                LinkNewRoutePrevRoute(NewRoute.LastFlightId, NOT_FLIGHT_ID);
            }
        }
        else{
            if(EndFlight.Ori == this->Ori){
                //connecting Flight will not be allowed to start from Ori
                return;
            }
            TimeType MaxLastFlightArrTime = EndFlight.DepTime - MIN_FLIGHT_GAP;
            Route PrevCheapRoute;
            bool res = FindCheapRouteTo(EndFlight.Ori,MaxLastFlightArrTime,PrevCheapRoute);
            if(res){
                Route NewRoute(EndFlight.Dest, EndFlightId,PrevCheapRoute.Cost + EndFlight.Cost, EndFlight.ArrTime);
                InsertNewRoute(NewRoute);
                LinkNewRoutePrevRoute(NewRoute.LastFlightId,PrevCheapRoute.LastFlightId);
            }
        }
}

FindRecommendationFromOrigin::FindRecommendationFromOrigin(DepTimeType DepTime, string Ori):DepTime(DepTime), Ori(Ori){}
