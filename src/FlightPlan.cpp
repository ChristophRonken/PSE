//
// Created by oliviervh on 12.04.18.
//

#include "FlightPlan.h"


FlightPlan::FlightPlan() {

}

const string &FlightPlan::getDestination() const {
    return destination;
}

void FlightPlan::setDestination(const string &destination) {
    FlightPlan::destination = destination;
}

int FlightPlan::getDeparture() const {
    return departure;
}

void FlightPlan::setDeparture(int departure) {
    FlightPlan::departure = departure;
}

int FlightPlan::getInterval() const {
    return interval;
}

void FlightPlan::setInterval(int interval) {
    FlightPlan::interval = interval;
}
