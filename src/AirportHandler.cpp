//
// Created by oliviervh on 01.03.18.
//

#include "AirportHandler.h"
#include <algorithm>

void AirportHandler::addXmlData(string fileName) {

    REQUIRE(validFileName(fileName), "Valid file name");

    // Open XML
    const char *cstr = fileName.c_str();
    TiXmlDocument doc(cstr);
    doc.LoadFile();

    TiXmlElement* root = doc.FirstChildElement();

    // If Xml isn't empty
    if (root != NULL){

        // Loop over elements
        for ( TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement() ){

            // Print Element Name
            string elemName = elem->Value();
            //cout << elemName << endl;

            // Element creation

            // Airport
            if (elemName == "AIRPORT"){
                Airport* Port = new Airport();
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();
                    string AttValue = elemAtt->GetText();

                    Port->setVar(AttName, string(AttValue));
                }

                Airports.push_back(Port);
                succesMessage("Airport added (" + Port->getName() + ")");
                //Port->printValues();
                continue;
            }

            // Runway
            if (elemName == "RUNWAY"){
                Runway* Runw = new Runway();

                // Loop over Variables
                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){

                    string AttName = elemAtt->Value();
                    string AttValue = elemAtt->GetText();

                    // Set Name
                    if (AttName == "name"){
                        Runw->setName(AttValue);
                        continue;
                    }

                    // Set Airport
                    if (AttName == "airport"){
                        for (unsigned int i = 0; i < Airports.size(); i++){

                            if (Airports[i]->getIata() == AttValue){
                                Airports[i]->addRunway(Runw);

                                break;
                            }

                        }

                        if (Runw->getAirport() == NULL){
                            errorMessage("Failed to add runway, no such airport.");
                            delete Runw;
                        }
                        continue;
                    }

                    if (AttName == "type"){
                        if (AttValue == "gras" || AttValue == "verhard"){
                            Runw->setType(AttValue);

                        }

                    }

                    if (AttName == "length"){
                        int i;
                        istringstream(AttValue) >> i;
                        Runw->setLength(i);

                    }

                    if (AttName == "TAXIROUTE"){


                    }
                }

                continue;
            }

            // Airplane
            if (elemName == "AIRPLANE") {
                Airplane *Plane = new Airplane();

                for (TiXmlElement* elemAtt = elem->FirstChildElement(); elemAtt!= NULL; elemAtt = elemAtt->NextSiblingElement()){
                    string AttName = elemAtt->Value();
                    string AttValue = elemAtt->GetText();

                    Plane->setVar(AttName, string(AttValue));
                }

                Airplanes.push_back(Plane);

                succesMessage("Plane added (" + Plane->getCallsign() + ")");

                continue;
            }
        }
    }
}

AirportHandler::AirportHandler() {}

AirportHandler::~AirportHandler() {

    for (unsigned int i = 0; i < Airplanes.size(); i++){
        delete Airplanes[i];

    }

    for (unsigned int i = 0; i < Airports.size(); i++) {
        delete Airports[i];

    }
}

const vector<Airport *> &AirportHandler::getAirports() const {
    return Airports;
}

void AirportHandler::setAirports(const vector<Airport *> &Airports) {

    REQUIRE(validAirports(Airports), "Valid airports");

    AirportHandler::Airports = Airports;
    ENSURE(Airports == AirportHandler::Airports, "Set Airports");

}

const vector<Airplane *> &AirportHandler::getAirplanes() const {
    return Airplanes;
}

void AirportHandler::setAirplanes(const vector<Airplane *> &Airplanes) {

    REQUIRE(validAirplanes(Airplanes), "Valid airplanes");

    AirportHandler::Airplanes = Airplanes;

}

void AirportHandler::printInfo() {

    for (unsigned int i = 0; i < Airports.size() ; i++) {
        Airports[i]->printInfo();

    }

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        Airplanes[i]->printInfo();

    }

}

string AirportHandler::getInfo() {

    string s;

    for (unsigned int i = 0; i< Airports.size(); i++ ){
        s+= Airports[i]->getInfo();

    }

    for (unsigned int i = 0; i< Airplanes.size(); i++ ){
        s+= Airplanes[i]->getInfo();

    }

    return s;

}

void AirportHandler::fileOutput() {

    string str = AirportHandler::getInfo();

    fstream file;
    file.open("test.txt", fstream::out);
    file << str;
    file.close();

}

void AirportHandler::addAirplane(Airplane *Plane) {

    REQUIRE(validAiplane(Plane), "Valid airplane");

    Airplanes.push_back(Plane);
    ENSURE(Airplanes[Airplanes.size()-1] == Plane, "Plane added");

}

void AirportHandler::removeAirplane(string callsign){

    REQUIRE(airplaneExists(callsign), "Airplane exists");

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getCallsign() == callsign) {
            Airplanes[i]->setAirport(NULL);
            delete Airplanes[i];
            Airplanes[i] = Airplanes[Airplanes.size()-1];
            Airplanes.resize(Airplanes.size()-1);

            succesMessage("Airplane Deleted (" + callsign + ")" );
            return;
        }
    }

}

Airport *AirportHandler::getAirport(string name) {
    return NULL;
}

void AirportHandler::addAirport(Airport *Port) {

    REQUIRE(validAirport(Port), "Valid airport");

    Airports.push_back(Port);
    ENSURE(Airports[Airports.size()-1] == Port, "Airport added");

}

void AirportHandler::removeAirport(string callsign){

    REQUIRE(airportExists(callsign), "Airport exists");

    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getCallsign() == callsign) {

            const vector<Runway *> Runways;
            Airports[i]->setRunways(Runways);

            const vector<bool> occup;
            Airports[i]->setGatesOccupied(occup);

            delete Airports[i];
            Airports[i] = Airports[Airports.size()-1];
            Airports.resize(Airports.size()-1);

            succesMessage("Airplane Deleted (" + callsign + ")" );
            return;

        }
    }

}

bool AirportHandler::airplaneExists(string callsign) {

    for (unsigned int i = 0; i< Airplanes.size(); i++){
        if (Airplanes[i]->getCallsign() == callsign){
            return true;
        }
    }
    return false;

}

bool AirportHandler::airportExists(string callsign) {
    for (unsigned int i = 0; i< Airports.size(); i++){
        if (Airports[i]->getCallsign() == callsign){
            return true;
        }
    }
    return false;
}

bool AirportHandler::validFileName(string name) {
    const char *cstr = name.c_str();
    TiXmlDocument doc(cstr);

    return doc.LoadFile();

}

bool AirportHandler::validAirplanes(vector<Airplane *> Planes) {

    vector<string> names;
    for (unsigned int i = 0; i< Planes.size(); i++){
        string name = Planes[i]->getCallsign();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

   return true;
}

bool AirportHandler::validAirports(vector<Airport *> Ports) {

    vector<string> names;
    for (unsigned int i = 0; i< Ports.size(); i++){
        string name = Ports[i]->getCallsign();
        if (!(find(names.begin(), names.end(), name) == names.end() && name != "")){
            return false;
        }
        names.push_back(name);
    }

    return true;

}

bool AirportHandler::validAiplane(Airplane *Plane) {

    if (Plane->getCallsign() == ""){
        return false;

    }

    for (unsigned int i = 0; i < Airplanes.size(); i++) {
        if (Airplanes[i]->getCallsign() == Plane->getCallsign()){
            return false;
        }
    }

    return true;

}

bool AirportHandler::validAirport(Airport* Port) {

    if (Port->getCallsign() == ""){
        return false;

    }
    for (unsigned int i = 0; i < Airports.size(); i++) {
        if (Airports[i]->getCallsign() == Port->getCallsign()){
            return false;

        }
    }

    return true;
}

void AirportHandler::runSimulation() {

    for (unsigned int i = 0; i< Airplanes.size(); i++){
        Airplane* Plane = Airplanes[i];
        if (Plane->notFinished()) {
            if (Plane->getTime() > 0) {

                if (Plane->getCurrentTask() == "land"){
                    Plane->setTaskDestination(AirportHandler::getAirport(Plane->getDestination()));

                }

                Plane->execTask();
                

            } else {
                Plane->finishtask();
                Plane->nextTask();

            }
        }
    }

}




