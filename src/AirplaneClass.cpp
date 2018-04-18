//
// Created by oliviervh on 01.03.18.
//

#include "AirplaneClass.h"

Airplane::Airplane() {
    gate = -1;
    runway = NULL;
    passengers = 125;
    passengerCapacity = 125;

    Route = new FlightPlan();

}

const string &Airplane::getNumber() const {
    return number;
}

void Airplane::setNumber(const string &number) {
    Airplane::number = number;

}

const string &Airplane::getCallsign() const {
    return callsign;
}

void Airplane::setCallsign(const string &callsign) {
    Airplane::callsign = callsign;
}

const string &Airplane::getModel() const {
    return model;
}

void Airplane::setModel(const string &model) {
    Airplane::model = model;

}

const string &Airplane::getState() const {
    return state;
}

void Airplane::setState(const string &state) {
    Airplane::state = state;
}

int Airplane::getFuel() const {
    return fuel;
}

void Airplane::setFuel(int fuel) {
    Airplane::fuel = fuel;
}

int Airplane::getHeight() const {
    return height;
}

void Airplane::setHeight(int height) {
    Airplane::height = height;
}

int Airplane::getFuelCapacity() const {
    return fuelCapacity;
}

void Airplane::setFuelCapacity(int fuelCapacity) {
    Airplane::fuelCapacity = fuelCapacity;
}

int Airplane::getPassengers() const {
    return passengers;
}

void Airplane::setPassengers(int passengers) {
    Airplane::passengers = passengers;
}

int Airplane::getPassengerCapacity() const {
    return passengerCapacity;
}

void Airplane::setPassengerCapacity(int passengerCapacity) {
    Airplane::passengerCapacity = passengerCapacity;
}

Airport *Airplane::getAirport() const {
    return airPort;
}

void Airplane::setAirport(Airport *airPort){
    Airplane::airPort = airPort;

}

bool Airplane::isReadyForDeparture() const {
    return ReadyForDeparture;
}

void Airplane::setReadyForDeparture(bool ReadyForDeparture) {
    Airplane::ReadyForDeparture = ReadyForDeparture;
}

const string &Airplane::getType() const {
    return type;
}

void Airplane::setType(const string &type) {
    Airplane::type = type;
}

const string &Airplane::getEngine() const {
    return engine;
}

void Airplane::setEngine(const string &engine) {
    Airplane::engine = engine;
}

const string &Airplane::getSize() const {
    return size;
}

void Airplane::setSize(const string &size) {
    Airplane::size = size;
}

int Airplane::getOpperationTime() const {
    return opperationTime;
}

void Airplane::setOpperationTime(int opperationTime) {
    Airplane::opperationTime = opperationTime;
}

Runway *Airplane::getRunway() const {
    return runway;
}

void Airplane::setRunway(Runway *runway) {

    Airplane::runway = runway;

}

void Airplane::toRunway(Runway *runway ) {

    REQUIRE(atAirport(), "At airport" );
    REQUIRE(validRunway(runway), "Valid runway");


    if (runway == NULL){
        vector<int> runw = airPort->getFreeRunways();
        if (runw.size() > 0){
            runway = airPort->getRunways()[runw[0]];

        }
    }

    inputMessage("Sending airplane (" + getNumber() + ") to runway (" + runway->getName() + ")");

    Runway * PrevRunw = Airplane::runway;
    Airplane::runway = runway;

    if (gate != -1 || PrevRunw != NULL) {
        actionMessage("Arplane " + getNumber() + " is taxiing to " + runway->getName());
    }

    if (PrevRunw != NULL) {
        PrevRunw->setOccupied(false);
    }

    if (gate != -1) {
        airPort->setGateOccupied(gate, false);
        gate = -1;
    }

    notificationMessage("Airplane (" + number + ") is now at runway " + runway->getName() + "\n");
    Airplane::setState("At runway");
    runway->setOccupied(true);

}

int Airplane::getGate() const {
    return gate;
}

void Airplane::setGate(int gate) {
    Airplane::gate = gate;
}

void Airplane::toGate(int gate ) {

    REQUIRE(validGate(gate), "valid gate index");
    REQUIRE(atAirport(), "At airport");

    if (gate == -1){
        vector<int> t = airPort->getFreeGates();
        gate = t[0];
    }

    inputMessage("Sending airplane (" + getNumber() + ") to gate (" + intToString(gate) + ")");
    actionMessage("Airplane (" + number + ") is taxiing to gate " + intToString(gate));

    if (Airplane::gate != -1){  // if the plane was at another gate...
        airPort->setGateOccupied(Airplane::gate, false);

    }

    // Set new gate
    Airplane::gate = gate;
    Airplane::airPort->setGateOccupied(Airplane::gate, true);

    if (runway != NULL) {   // if the plane was at a runway...
        runway->setOccupied(false);
        runway = NULL;
    }

    Airplane::setState("Standing at gate");
    notificationMessage("Airplane (" + number + ") is now at gate " + intToString(gate) + "\n");
}

void Airplane::setVar(string Type, string Value) {

    if (Type == "number"){
        Airplane::setNumber(Value);
        return ;
    }

    else if (Type == "model"){
        Airplane::setModel(Value);
        return ;
    }

    else if (Type == "callsign"){
        Airplane::setCallsign(Value);
        return;
    }

    else if (Type == "status"){
        Airplane::setState(Value);
        return;
    }

    else if (Type == "type"){
        Airplane::setType(Value);
        return;
    }

    else if (Type == "engine"){
        Airplane::setEngine(Value);
        return;
    }

    else if (Type == "size"){
        Airplane::setSize(Value);
        return;
    }

    else if (Type == "passengers"){
        int i;
        istringstream(Value) >> i;
        Airplane::setPassengers(i);
        return;
    }

    else if (Type == "passengerCap"){
        int i;
        istringstream(Value) >> i;
        Airplane::setPassengerCapacity(i);
        return;
    }

    else if (Type == "height"){
        int i;
        istringstream(Value) >> i;
        Airplane::setHeight(i);
        return;
    }

    else if (Type == "fuel"){
        int i;
        istringstream(Value) >> i;
        Airplane::setFuel(i);
        return;
    }

    else if (Type == "fuelCap"){
        int i;
        istringstream(Value) >> i;
        Airplane::setFuelCapacity(i);
        return;
    }

    else if (Type == "gate"){
        int i;
        istringstream(Value) >> i;
        Airplane::setGate(i);
        return;
    }

    else {
        REQUIRE(false, "Valid Type");
    }

}

void Airplane::printInfo() {
   cout << Airplane::getInfo() << endl;

}

string Airplane::getInfo() {
    string str;
    str = "\nAirplane:\t" + callsign + " (" + number +  ")\n"
          + "->model:\t" + model +"\n"
          + "->type:\t" + type + "\n"
          + "->engine:\t" + engine + "\n"
          + "->size:\t" + size + "\n";

    return str;
}

void Airplane::prepareForDeparture() {

    REQUIRE(atGate(), "Standing at gate");

    inputMessage("Preparing airplane (" + getNumber() + ") for departure.");


    notificationMessage(intToString(passengers) + " exited airplane " + getNumber() + " at gate " + intToString(gate) + " of " + airPort->getName() );
    notificationMessage(getNumber() + " has been checked for technical malfunction");
    notificationMessage(getNumber() + " has been refueled");
    notificationMessage(intToString(passengers) + " boarded airplane " + getNumber() + " at gate " + intToString(gate) + " of " + airPort->getName() + "\n" );

    setReadyForDeparture(true);

}

void Airplane::land(Airport *Port, Runway* Runw) {

    REQUIRE(validLandingSpot(Port, Runw), "Valid landing spot");

    Airplane::setState("Approaching");

    if (Runw == NULL) {
        inputMessage("Preparing airplane (" + Airplane::getNumber() + ") for landing in " + Port->getName());

        vector<Runway *> runw = Port->getRunways();

        for (unsigned int i = 0; i < runw.size(); i++) {
            if (!runw[i]->isOccupied()) {
                Runw =  runw[i];

                break;
            }

        }

    }

    notificationMessage(Airplane::getNumber() + " is approaching " + Port->getName() + " at 10.000 ft.");

    while (height > 1000) {
        height -= 1000;
        actionMessage(Airplane::getNumber() + " descents to a height of " + intToString(height));

    }

    height = 0;

    actionMessage(Airplane::getNumber() + " is landing at Runway" + Runw->getName());

    Airplane::setAirport(Port);
    notificationMessage("Airplane (" + Airplane::getNumber() + ") landed in " + Port->getName());

    Airplane::setRunway(Runw);
    notificationMessage("Airplane (" + Airplane::number + ") is now at runway " + Runw->getName() + "\n");

    Runw->setOccupied(true);

    Airplane::setState("At runway");

    ENSURE(Runw == Airplane::getRunway(), "Landed" );

}

void Airplane::takeOff() {

    REQUIRE(readyForTakeOff(), "Ready for take off");

    inputMessage("Sending airplane " + Airplane::getNumber() + " for departure");

    notificationMessage("Airplane (" + Airplane::getNumber() + ") is taking off at " + Airplane::getAirport()->getName());

    while (height < 5000) {

        actionMessage("Airplane (" + Airplane::getNumber() + ") ascended to " + intToString(height) + "ft");
        height += 1000;

    }

    notificationMessage("Airplane (" + Airplane::getNumber() + ") has left " + Airplane::getAirport()->getName() + "\n");

    Airplane::setAirport(NULL);
    Airplane::setRunway(NULL);

    Airplane::setState("Airborne");

    ENSURE(runway == NULL && state == "Airborne" && airPort == NULL && height >= 5000, "Airborne");

}

bool Airplane::validLandingSpot(Airport *Port, Runway *Runw) {

    if (Port == NULL){
        return false;

    }

    if (Runw == NULL) {
        vector<Runway *> runw = Port->getRunways();

        for (unsigned int i = 0; i < runw.size(); i++) {
            if (!runw[i]->isOccupied()) {
                return true;
            }

        }

        return false;

    }

    return !Runw->isOccupied();
}

bool Airplane::validGate(int gate) {

    if (gate == -1){
        vector<int> t = airPort->getFreeGates();
        if (t.size() == 0){
            return false;
        }
        gate = t[0];
    }

    if (!(gate >= 0 && gate < airPort->getGates())){
        return false;
    }
    if (airPort->getGateOccupied(gate)){
        return false;
    }

    return true;

}

bool Airplane::validRunway(Runway* Runw) {

    if (Runw == NULL){
        vector<int> runw = airPort->getFreeRunways();
        if (runw.size() > 0){
            return true;

        }

        return false;
    }

    return !Runw->isOccupied();

}

bool Airplane::atAirport() {

    if (airPort == NULL){
        return false;
    }



    return true;

}

bool Airplane::atGate() {

    return state == "Standing at gate" && gate >= 0;


}

bool Airplane::readyForTakeOff() {
    return (Airplane::isReadyForDeparture() && airPort != NULL && Airplane::runway != NULL && Airplane::state == "At runway");
}

bool Airplane::notFinished() {
    return false;
}

void Airplane::useFuel() {

}

int Airplane::getTime() {
    return 0;
}

void Airplane::execTask() {

}

void Airplane::finishtask() {
    
}

string Airplane::getCurrentTask() {

    return task;

}

string Airplane::getDestination() {
    return Route->getDestination();
}

void Airplane::nextTask() {

}

void Airplane::setTaskDestination(Airport *Port) {

}
