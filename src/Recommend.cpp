#include"Recommend.hpp"
#include"bits/stdc++.h"

using namespace std;

void Recommend::print()const{
    cout << "DepDay(day since epoch) " << DepDay << endl;
    cout << "DepMinute(minute since epoch)" << DepTime << endl;
    cout << "Cost " << cost << endl;
    cout << "Travel Duration "  << TravelDuration << endl;
    cout << "Flight List ";
    for(auto id:ListFlight){
        cout << id << " ";
    }
    cout << endl;
    cout << "Ori " << Ori << endl;
    cout << "Dest " << Dest << endl;
}
