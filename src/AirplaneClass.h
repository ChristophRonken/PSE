//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirplaneCLASS_H
#define PSE_V1_AirplaneCLASS_H

#include <iostream>

#include "AirportClass.h"
#include "RunwayClass.h"
#include "FlightPlan.h"

#include "DesignByContract.h"


using namespace std;

class Airport;
class Runway;

class Airplane {

    string number;
    string callsign;
    string model;
    string state;
    string type;
    string engine;
    string size;

    string task;

    Airport* airPort;
    Runway* runway;

    int gate;
    int fuel;
    int fuelCapacity;
    int passengers;
    int passengerCapacity;
    int height;
    int opperationTime;

    bool ReadyForDeparture;

    FlightPlan* Route;

    /**
     * sets if the plane is ready for departure
     * Precondition: Plane must be at gate
     * @param ReadyForDeparture
     */
    void setReadyForDeparture(bool ReadyForDeparture);

public:
    Airplane();

    /**
     * get the ID number
     * @return
     */
    const string &getNumber() const;

    /**
     * Set ID number
     * @param number
     */
    void setNumber(const string &number);

    /**
     * returns the planes callsign
     * @return callsign
     */
    const string &getCallsign() const;

    /**
     * sets the planes callsign
     * @param callsign
     */
    void setCallsign(const string &callsign);

    /**
     * get plane model
     * @return model type
     */
    const string &getModel() const;

    /**
     * set planes model
     * @param model
     */
    void setModel(const string &model);

    /**
     * get current state of the plane
     * @return state
     */
    const string &getState() const;

    /**
     * sets the state of the plane
     * @param state
     */
    void setState(const string &state);

    /**
     *returns a pointer to the current airport
     * @return Airport *
     */
    Airport *getAirport() const;

    /**
     * sets the current airport
     * @param airPort
     */
    void setAirport(Airport *airPort);

    /**
     * returns a pointer to the current runway
     * @return Runway*
     */
    Runway *getRunway() const;

    /**
     * sets the current runway
     * @param runway
     */
    void setRunway(Runway *runway);

    /**
     * returns the current gate number
     * @return gate
     */
    int getGate() const;

    void setGate(int gate);

    /**
     * returns the amount of fuel
     * @return fuel
     */
    int getFuel() const;

    /**
     * sets the amount of fuel
     * @param fuel
     */
    void setFuel(int fuel);

    int getFuelCapacity() const;

    void setFuelCapacity(int fuelCapacity);


    /**
     * get the amount of passengers
     * @return passengers
     */
    int getPassengers() const;

    /**
     * sets the amount of passengers
     * @param passengers
     */
    void setPassengers(int passengers);

    /**
     * gets the max passenger capacity of the plane
     * @return passengerCapassity
     */
    int getPassengerCapacity() const;

    /**
     * sets the max passenger capacity
     * @param passengerCapacity
     */
    void setPassengerCapacity(int passengerCapacity);


    int getHeight() const;

    void setHeight(int height);

    const string &getType() const;

    void setType(const string &type);

    const string &getEngine() const;

    void setEngine(const string &engine);

    const string &getSize() const;

    void setSize(const string &size);

    int getOpperationTime() const;

    void setOpperationTime(int opperationTime);

    /**
     * set the variables of the plane
     * @param Type of the given variable
     * @param Value of the variable
     */
    void setVar(string Type, string Value);

    /**
     * prints the info of the plane in the console
     */
    void printInfo();

    /**
     * gets the info of the plane as a string
     * @return info
     */
    string getInfo();

    /**
     * retursn true if the plane is ready for departure
     * @return readyForDeparture
     */
    bool isReadyForDeparture() const;

    /**
     * prepares the plane for departure
     * Precondition: this->atGate()
     */
    void prepareForDeparture();

    /**
     * lands the plane in the given airport
     * A runway is optional
     * Precondition: this->validLandingSpot(Airport*, Runway* )
     * @param Port
     * @param R
     */
    void land(Airport* Port , Runway* R = NULL);


    /**
     * sends the plane to the given runway
     * if no runway was given, it will choose the first free runway
     * Precondition: this->atAirport() && validRunway(Runway* )
     * @param runway
     */
    void toRunway(Runway *runway = NULL);

    /**
     * send the plane to gate x
     * if no gate index is given, the first free gate is chosen
     * Precondition: this->validGate() && this->atAirport()
     * @param gate
     */
    void toGate(int gate = -1);

    /**
     * send the plane to exit the airport
     * Precondition: this->readyForTakeOff()
     */
    void takeOff();

    void useFuel();

    bool notFinished();
    int getTime();
    void execTask();
    void finishtask();
    void nextTask();
    string getCurrentTask();
    string getDestination();
    void setTaskDestination(Airport* Port);

    /**
     * Input Controle
     */
    bool validGate(int gate = -1);
    bool validRunway(Runway* Runw = NULL);
    bool validLandingSpot(Airport* Port, Runway* Runw = NULL );

    /**
     * State Controle
     */
    bool atAirport();
    bool atGate();
    bool readyForTakeOff();

};


#endif //PSE_V1_AirplaneCLASS_H
