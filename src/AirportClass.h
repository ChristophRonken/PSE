//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AirportCLASS_H
#define PSE_V1_AirportCLASS_H

#include <iostream>
#include <sstream>
#include "AirplaneClass.h"
#include "RunwayClass.h"
#include "MessageSystem.h"
#include <vector>
#include <typeinfo>

using namespace std;

class Runway;

class Airplane;

class Airport {
    string name;
    string iata;
    string callsign;

    int gates;

    vector<Runway*> Runways;
    vector<bool> GatesOccupied;

public:

    Airport();

    /**
     * construct an Airport with parameters
     * @param name
     * @param iata
     * @param callsign
     * @param gates
     */
    Airport(const string &name, const string &iata, const string &callsign, int gates);

    virtual ~Airport();

    /**
     * get the name of the Airport
     * @return name
     */
    const string &getName() const;

    /**
     * set the name of the airport
     * @param name
     */
    void setName(const string &name);

    /**
     * get the iata of the airport
     * @return Iata
     */
    const string &getIata() const;

    /**
     * set the iata of the airport
     * @param iata
     */
    void setIata(const string &iata);

    /**
     * get the callsign of the airport
     * @return callsign
     */
    const string &getCallsign() const;

    /**
     * sets the callsign of the airport
     * @param callsign
     */
    void setCallsign(const string &callsign);

    /**
     * get the amount of gates in the airport
     * @return gates
     */
    int getGates() const;

    /**
     * set the amount of gates in the airport
     * @param gates
     */
    void setGates(int gates);

    /**
     * get the runways in the airport
     * @return Runways
     */
    const vector<Runway *> &getRunways() const;

    /**
     * set the runways in the airport
     * @param Runways
     */
    void setRunways(const vector<Runway *> &Runways);

    /**
     * get a vector with for each gate index a bool ti show if it's occupied
     * @return occuiped gates
     */
    const vector<bool> &getGatesOccupied() const;

    /**
     * set wich gates are occupied through a vector
     * @param GatesOccupied
     */
    void setGatesOccupied(const vector<bool> &GatesOccupied);

    /**
     * sets the var of the airport
     * @param Type of the var
     * @param Value of the var
     */
    void setVar(string Type, string Value);

    /**
     * adds a runway to the airport
     * Precondition: !runwayExists(string)
     * @param runway
     */
    void addRunway(Runway* runway);

    /**
     * removes a runway from the airport
     * Precontition: runwayExists(string)
     * @param name
     */
    void removeRunway(string name);

    /**
     * prints the airports info in the console
     */
    void printInfo();

    /**
     * gets the airports info as a string
     * @return
     */
    string getInfo();

    /**
     * set a certain gate to occ
     * Precondition: validGateIndex(int)
     * @param int i : index of the gate
     * @param bool occ : occupied or not
     */
    void setGateOccupied(int i, bool occ);

    /**
     * get if a certain gate is occupied
     * Precondition: validGateIndex(int)
     * @param int i
     * @return occupied
     */
    bool getGateOccupied(int i);

    /**
     * returns a vector with the indexes of all the free gates
     * @return FreeGates
     */
    vector<int> getFreeGates();

    /**
     * returns a vector with the indexes of all the free Runways
     * @return FreeRunways
     */
    vector<int> getFreeRunways();



    string graphicRepresentation();

    /** Input controle
     */
    bool validGateIndex(int i);
    bool runwayExists(string name);

};


#endif //PSE_V1_AirportCLASS_H
