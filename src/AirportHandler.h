//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_AIRPORTHANDLER_H
#define PSE_V1_AIRPORTHANDLER_H

#include <fstream>
#include "AirportClass.h"
#include "AirplaneClass.h"
#include "RunwayClass.h"
#include "../xml/tinyxml.h"

class AirportHandler {

    vector<Airport*> Airports;
    vector<Airplane*> Airplanes;

public:
    AirportHandler();

    virtual ~AirportHandler();

    /**
     * Removes an airplane from the saved Airplanes
     * Preconditions: airplaneExists(string)
     * @param callsign
     */
    void removeAirplane(string callsign);

    /**
     * Adds an airport to the saved airports
     * Preconditions: validAirport(Airport*)
     * @param Airport
     */
    void addAirport(Airport *Airport);

    /**
     * Removes an airport from the saved airports
     * Preconditions: airportExists(string)
     * @param callsign
     */
    void removeAirport(string callsign);

    /**
     * Add airplanes, airports and runways from an given xml file.
     * Preconditions: validFileName(string)
     * @param fileName
     */
    void addXmlData(string fileName);

    /**
     * Returns a vector with the saved airports
     * @return Airports
     */
    const vector<Airport *> &getAirports() const;

    /**
     * Sets the saved airports to the given vector of airports.
     * Note that if you already had other airports saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airports.
     * Precondition: validAirports(vector<Airport*>)
     * @param Airports
     */
    void setAirports(const vector<Airport *> &Airports);

    /**
     * Returns a vector with all the saved airplanes
     * @return Airplanes
     */
    const vector<Airplane *> &getAirplanes() const;

    /**
     * Dets the saved planes to the given vector of planes.
     * Note that if you already had other airplanes saved,
     * they will dissapear from this handler
     * and might cause memory leaks if not deleted properly.
     * It is adviced to only use this function to initialize the vector of airplanes.
     * Precondition: validAirplanes(vector<Airplane*>);
     * @param Airplanes
     */
    void setAirplanes(const vector<Airplane *> &Airplanes);

    /**
     * Adds an airplane to the list of planes
     * Precondition: validAiplane(Airplane*)
     * @param Plane
     */
    void addAirplane(Airplane* Plane);

    /**
     * Get a string with the info of all planes and airports
     * @return info
     */
    string getInfo();

    /**
     * Prints info of the planes and airports in the console
     */
    void printInfo();

    /**
     * Outputs a file, with the info of the airplanes and airports, to the working directory
     */
    void fileOutput();;


    void runSimulation();

    Airport* getAirport(string name);



    /** Input controle
     */
    bool airplaneExists(string callsign);
    bool airportExists(string callsign);

    bool validFileName(string name);
    bool validAirplanes(vector<Airplane*> Planes);
    bool validAirports(vector<Airport*> Ports);
    bool validAiplane(Airplane* Plane);
    bool validAirport(Airport* Port);


};


#endif //PSE_V1_AIRPORTHANDLER_H
