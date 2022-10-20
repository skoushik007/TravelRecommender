
#include"FlightProcessor.hpp"
#include"FindRecomendationFromDepTime.hpp"


    FlightProcessor::FlightProcessor(vector<Flight> &AllFlights):AllFlights(AllFlights){
        FillTimeLine();
    }

    const vector<Recommend> & FlightProcessor::GetRecommends(){
        return  AllRecommends;
    }
    void FlightProcessor::FillDepTimeLine(map<DepTimeType, vector<FlightIdType>> &dest){
        for(unsigned int i=0;i<AllFlights.size();i++){
            auto &f = AllFlights[i];
            auto DepTime = f.DepTime;
            dest[DepTime].push_back(i);
        }
    }

    void FlightProcessor::FillArrTimeLine(map<ArrTimeType, vector<FlightIdType>>  &dest){
        for(unsigned int i=0;i<AllFlights.size();i++){
            auto &f = AllFlights[i];
            auto ArrTime = f.ArrTime;
            dest[ArrTime].push_back(i);
        }
    }

    void FlightProcessor::FillTimeLine(){
        FillArrTimeLine(FlightArrTimeLine);
        FillDepTimeLine(FlightDepTimeLine);
    }



    void FlightProcessor::process(){
        map<ArrTimeType, vector<FlightIdType>>::iterator PtrNextArrTime = FlightArrTimeLine.begin();
        map<ArrTimeType, vector<FlightIdType>>::iterator PtrEndArrTime = FlightArrTimeLine.end();

        for(auto &CurrDepTime:FlightDepTimeLine){
            long long int DepTime = CurrDepTime.first;
            while(PtrNextArrTime != PtrEndArrTime && PtrNextArrTime->first <= DepTime){
                PtrNextArrTime++;
            }
            if(PtrNextArrTime == PtrEndArrTime){
                break;
            }
            auto &BegFlightIds = CurrDepTime.second;
            FindRecomendationFromDepTime RecommendFinderFromDepTime(*this,AllRecommends,PtrNextArrTime,PtrEndArrTime,BegFlightIds,DepTime);
        }
    }

    const Flight &FlightProcessor::getFlight(int id)const{
        return AllFlights[id];
    }
