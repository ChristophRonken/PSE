//
// Created by oliviervh on 01.03.18.
//

#include "RunwayClass.h"

const string &Runway::getName() const {
    return name;
}

void Runway::setName(const string &name) {
    Runway::name = name;

}

Airport *Runway::getAirport() const {
    return airPort;
}

void Runway::setAirport(Airport *Port) {
    Runway::airPort = Port;

}

bool Runway::isOccupied() const {
    return occupied;
}

void Runway::setOccupied(bool occupied) {
    Runway::occupied = occupied;
    if (!occupied){
        notificationMessage("Runway ("  + getName() + ") is now unoccupied");

    }

}

Runway::Runway(const string &name, Airport *airPort) : name(name), airPort(airPort) {
    occupied = false;
}

Runway::Runway() {
    occupied = false;

}

const string &Runway::getType() const {
    return type;
}

void Runway::setType(const string &type) {
    Runway::type = type;
}

int Runway::getLength() const {
    return length;
}

void Runway::setLength(int length) {
    Runway::length = length;
}





