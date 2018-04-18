//
// Created by oliviervh on 01.03.18.
//

#include "AirportClass.h"
#include <algorithm>

Airport::Airport() {}

Airport::Airport(const string &name, const string &iata, const string &callsign, int gates){
    Airport::name = name;
    Airport::iata = iata;
    Airport::callsign = callsign;
    Airport::gates = gates;

    GatesOccupied.resize(gates);
};

Airport::~Airport() {

    for (unsigned int i = 0; i < Runways.size(); i++){

        delete Runways[i];

    }
}

const string &Airport::getName() const {
    return name;
}

void Airport::setName(const string &name) {
    Airport::name = name;
    ENSURE(Airport::name == name, "Airport name set");

}

const string &Airport::getIata() const {
    return iata;
}

void Airport::setIata(const string &iata) {
    Airport::iata = iata;
    ENSURE(Airport::iata == iata, "Airport iata set");

}

const string &Airport::getCallsign() const {
    return callsign;
}

void Airport::setCallsign(const string &callsign) {
    Airport::callsign = callsign;
    ENSURE(Airport::name == name, "Airport name set");

}

int Airport::getGates() const {
    return gates;
}

void Airport::setGates(int gates) {
    Airport::gates = gates;
    GatesOccupied.resize(gates, false);
    ENSURE(Airport::gates == gates, "Gates set");
    ENSURE(GatesOccupied.size() == unsigned(gates), "Added new gates");

}

const vector<Runway *> &Airport::getRunways() const {
    return Runways;
}

void Airport::setRunways(const vector<Runway *> &Runways) {
    Airport::Runways = Runways;
    ENSURE(Airport::Runways == Runways, "Set Runways");

}

const vector<bool> &Airport::getGatesOccupied() const {
    return GatesOccupied;
}

void Airport::setGatesOccupied(const vector<bool> &GatesOccupied) {
    Airport::GatesOccupied = GatesOccupied;
    ENSURE(GatesOccupied == GatesOccupied, "Set GatesOccupied");

}

void Airport::setVar(string Type, string Value) {
    if (Type == "name"){
        Airport::setName(Value);
        return;
    }

    else if (Type == "iata"){
        Airport::setIata(Value);
        return;
    }

    else if (Type == "callsign"){
        Airport::setCallsign(Value);
        return;
    }

    else if (Type == "gates"){
        int i;
        istringstream(Value) >> i;
        Airport::setGates(i);
        return;
    }

    else{
        ENSURE(false, "Invalid input Type");

    }

}

void Airport::addRunway(Runway *runway) {

    REQUIRE(!runwayExists(runway->getName()), "Runway doesn't exist yet");

    runway->setAirport(this);
    Runways.push_back(runway);

    string s;
    s = "Runway added (" + runway->getName() + ") to airport (" + this->getName() + ")";
    succesMessage(s);

}

void Airport::removeRunway(string name) {

    REQUIRE(runwayExists(name), "Runway exists");

    for (unsigned int i = 0; i < Runways.size(); i++){
        if (Runways[i]->getName() == name){
            Runways[i]->setAirport(NULL);
            string t = Runways[i]->getName();
            delete Runways[i];
            Runways[i] = Runways[Runways.size()-1];
            Runways.resize(Runways.size()-1);

            succesMessage("Runway Deleted (" + t + ")" );
            return;
        }
    }
}

void Airport::printInfo() {

    cout << getInfo();

}

string Airport::getInfo() {

    string s;
    s += "\nAirport:\t" + name + " (" + iata + ")\n"
         + "->callsign:\t" + callsign + "\n"
         + "->gates:\t" + intToString(gates) + "\n"
         + "->runways:\t" + intToString(static_cast<int>(Runways.size())) + "\n";

    return s;
}

void Airport::setGateOccupied(int i, bool occ) {
    REQUIRE(validGateIndex(i), "Valid gate index");

    GatesOccupied[i] = occ;
    if (!occ){
        notificationMessage("Gate ("  + intToString(i) + ") is now unoccupied");

    }

}

vector<int> Airport::getFreeGates() {
    vector<int> Gates;

    for (unsigned int i = 0; i < GatesOccupied.size(); i++){
        if (!GatesOccupied[i]){
            Gates.push_back(i);
        }
    }

    ENSURE(&Gates != NULL, "Gates exists");

    return Gates;
}

vector<int> Airport::getFreeRunways() {
    vector<int> RW;

    for (unsigned int i = 0; i < Runways.size(); i++){
        if (!Runways[i]->isOccupied()){
            RW.push_back(i);

        }

    }

    ENSURE(&RW != NULL, "RW exists");

    return RW;
}

bool Airport::getGateOccupied(int i) {

    REQUIRE(validGateIndex(i), "Valid gate index");

    return GatesOccupied[i];

}

bool Airport::validGateIndex(int i) {
    return getGates() > i && i >= 0;
}

bool Airport::runwayExists(string name) {
    for (unsigned int i = 0; i < Runways.size(); i++){
        if (Runways[i]->getName() == name){
            return true;
        }
    }

   return false;
}

string Airport::graphicRepresentation() {


    for (unsigned  int i = 0; i< Runways.size(); i++ ){



    }

    return std::__cxx11::string();
}





