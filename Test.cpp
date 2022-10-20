

#include"Flight.hpp"
#include"FlightProcessor.hpp"
#include"Recommend.hpp"
#include<iostream>

void case1(){
    vector<Flight> InFlights;


    Flight f1("BLR","DEL",0,3,1);
    InFlights.push_back(f1);

    Flight f2("DEL","ABC",38,42,3);
    InFlights.push_back(f2);

    Flight f3("DEL","ABC",40,42,2);
    InFlights.push_back(f3);


    FlightProcessor FP(InFlights);
    FP.process();
    const vector<Recommend> &OutRecommends = FP.GetRecommends();
    for(const Recommend &r:OutRecommends){
        r.print();
        cout << endl;
    }
}


void case2(){
    vector<Flight> InFlights;


    Flight f1("BLR","DEL",0,3,1);
    InFlights.push_back(f1);

    Flight f5("ABC","DEL",0,4,2);
    InFlights.push_back(f5);

    Flight f2("DEL","ABC",38,42,3);
    InFlights.push_back(f2);

    Flight f3("DEL","ABC",40,42,2);
    InFlights.push_back(f3);

    Flight f4("DEL","ABC",33,35,2);
    InFlights.push_back(f4);


    FlightProcessor FP(InFlights);
    FP.process();
    const vector<Recommend> &OutRecommends = FP.GetRecommends();
    for(const Recommend &r:OutRecommends){
        r.print();
        cout << endl;
    }
}


#include<set>
#include<iostream>
int main(){
    //case1();
    case2();
    return 0;
}
