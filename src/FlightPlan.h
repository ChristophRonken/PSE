//
// Created by oliviervh on 12.04.18.
//

#ifndef PSE_V1_AIRPLANEROUTE_H
#define PSE_V1_AIRPLANEROUTE_H

#include <iostream>
#include <vector>


using namespace std;


class FlightPlan {

    string destination;
    int departure;
    int interval;

public:

    FlightPlan();

    const string &getDestination() const;

    void setDestination(const string &destination);

    int getDeparture() const;

    void setDeparture(int departure);

    int getInterval() const;

    void setInterval(int interval);


};



#endif //PSE_V1_AIRPLANEROUTE_H
