// Created by oliviervh on 01.03.18.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "gtest/gtest.h"

#include "AirplaneClass.h"
#include "AirportClass.h"
#include "AirportHandler.h"
#include "MessageSystem.h"
#include "RunwayClass.h"

namespace {

    class AirplaneTest : public ::testing::Test {
    protected:
        // You should make the members protected s.t. they can be
        // accessed from sub-classes.

        AirplaneTest() {
            Airplane plane;

        }

        // virtual void SetUp() will be called before each test is run.  You
        // should define it if you need to initialize the variables.
        // Otherwise, this can be skipped.
        virtual void SetUp() {


        }

        // virtual void TearDown() will be called after each test is run.
        // You should define it if there is cleanup work to do.  Otherwise,
        // you don't have to provide it.
        virtual void TearDown() {
        }

        // Declares the variables your tests want to use.
        Airport *airport;
        Airplane *plane;
        Runway *runway;
        AirportHandler *D;
    };


    TEST_F(AirplaneTest, AirplaneConstructor) {
        plane = new Airplane();

        EXPECT_EQ(-1, plane->getGate());
        EXPECT_EQ(NULL, plane->getRunway());
        EXPECT_EQ(125, plane->getPassengers());
        EXPECT_EQ(125, plane->getPassengerCapacity());
    }

    TEST_F(AirplaneTest, AirplaneFunctions) {
        plane = new Airplane();

        //get & set planeNumber
        plane->setNumber("5");
        EXPECT_EQ("5", plane->getNumber());

        //get & set planeCallsign
        plane->setCallsign("callTest");
        EXPECT_EQ("callTest", plane->getCallsign());

        //get & set planeModel
        plane->setModel("Boeing 747");
        EXPECT_EQ("Boeing 747", plane->getModel());

        //get & set planeState
        plane->setState("Standing at gate");
        EXPECT_EQ("Standing at gate", plane->getState());

        //get & set planeAirport

        plane->setAirport(airport);
        EXPECT_EQ(airport, plane->getAirport());

        //get & set planeRunway
        plane->setRunway(runway);
        EXPECT_EQ(runway, plane->getRunway());

        //get & set planeFuel
        plane->setFuel(5);
        EXPECT_EQ(5, plane->getFuel());

        //get & set planePassengers
        plane->setPassengers(5);
        EXPECT_EQ(5, plane->getPassengers());

        //get & set planePassengerCapacity
        plane->setPassengerCapacity(5);
        EXPECT_EQ(5, plane->getPassengerCapacity());

        //get & set planeVars
        EXPECT_DEATH(plane->setVar("foutief type", "9ab"), "Assertion.*failed");
        plane->setVar("number", "7");
        plane->setVar("model", "TufTuf");
        plane->setVar("callsign", "J420");
        plane->setVar("status", "in brand");
        EXPECT_EQ("7", plane->getNumber());
        EXPECT_EQ("TufTuf", plane->getModel());
        EXPECT_EQ("J420", plane->getCallsign());
        EXPECT_EQ("in brand", plane->getState());

        //getInfo
        string str = "\nAirplane:\t";
        str += "J420";
        str += " (";
        str += "7";
        str += ")\n";
        str += "->model:\t";
        str += "TufTuf";
        str += "\n";
        str += "->type:\t\n->engine:\t\n->size:\t\n";
        EXPECT_EQ(str, plane->getInfo());


        D = new AirportHandler();
        D->addXmlData("LuchthavenV1.xml");
        airport = D->getAirports()[0];
        airport->setGates(2);

        //plane lands in airport
        plane->land(airport);

        //plane->isReadyForDeparture == false
        EXPECT_DEATH(plane->takeOff(), "Assertion.*failed");
        Airplane* newplane = new Airplane();
        Airplane* newplane0 = new Airplane();
        newplane->setCallsign("65A5B");
        newplane0->setCallsign("H4L0");
        newplane->setAirport(airport);
        newplane0->setAirport(airport);
        D->addAirplane(newplane);
        D->addAirplane(newplane0);
        D->addAirplane(plane);

        unsigned int free_gates = airport->getFreeGates().size();

        // plane tries to go to gate which doesn't exist
        EXPECT_DEATH(plane->toGate(10), "Assertion.*failed");
        // plane tries to go to gate 1
        plane->toGate(1);
        EXPECT_EQ(1, plane->getGate());

        // newplane tries to go to occupied gate
        EXPECT_DEATH(newplane->toGate(1), "Assertion.*failed");
        plane->toGate();
        // newplane tries to go to first open gate
        newplane->toGate();
        // newplane tries to go to first open gate, but no free gates
        EXPECT_DEATH(newplane0->toGate(), "Assertion.*failed");

        EXPECT_EQ("Standing at gate", plane->getState());

        //plane & newplane are in correct gates
        EXPECT_EQ(0, plane->getGate());
        EXPECT_EQ(1, newplane->getGate());

        //amount of free gates reduces
        EXPECT_EQ(free_gates-2, airport->getFreeGates().size());

        //has no valid gate
        EXPECT_FALSE(newplane0->isReadyForDeparture());
        EXPECT_DEATH(newplane0->prepareForDeparture(), "Assertion.*failed");
        EXPECT_FALSE(newplane0->isReadyForDeparture());

        //plane not ready for departure
        EXPECT_DEATH(plane->takeOff(), "Assertion.*failed");

        //has a valid gate
        EXPECT_FALSE(plane->isReadyForDeparture());
        plane->prepareForDeparture();
        EXPECT_TRUE(plane->isReadyForDeparture());

        EXPECT_EQ("Standing at gate", plane->getState());

        //plane not on a runway
        EXPECT_DEATH(plane->takeOff(), "Assertion.*failed");

        runway = new Runway;
        runway->setAirport(airport);
        runway->setName("tweede");
        airport->addRunway(runway);

        //toRunway
        //er zijn 2 runways
        plane->toRunway(runway);
        EXPECT_EQ("At runway", plane->getState());

        //runway is bezet
        Airplane* plane3 = new Airplane;
        plane3->setAirport(airport);
        EXPECT_DEATH(plane3->toRunway(runway), "Assertion.*failed");
        plane->toRunway();

        Airplane* plane4 = new Airplane;
        plane4->setAirport(airport);
        plane4->toRunway();
        //no free runways
        EXPECT_DEATH(plane3->toRunway(), "Assertion.*failed");

        //plane is on a runway
        plane->takeOff();

        //plane does no longer belong to an airport
        EXPECT_EQ(NULL, plane->getAirport());


        //LAND
        airport = new Airport;

         // airport heeft geen runways
        EXPECT_DEATH(plane->land(airport), "Assertion.*failed");

        //airport heeft 1 (vrije) runway ////PROBLEEM: AANTAL VRIJE RUNWAYS DAALT NIET
        runway = new Runway;
        runway->setName("eersterunway");
        airport->addRunway(runway);
        //EXPECT_TRUE(runway->setAirport(airport));

        EXPECT_EQ((unsigned)1, airport->getFreeRunways().size());
        EXPECT_NO_FATAL_FAILURE(plane->land(airport, runway));
        EXPECT_EQ((unsigned)0, airport->getFreeRunways().size());

        //airport heeft 1 bezette runway /////PROBLEEM: DIT GEEFT GEEN FALSE
        Airplane* plane2 = new Airplane;
        plane2->setCallsign("460AB");
        EXPECT_DEATH(plane2->land(airport, runway), "Assertion.*failed");



        //prints info
        plane->printInfo();

        delete D;

    }

    TEST_F(AirplaneTest, AirportConstructor) {
        airport = new Airport("naam", "hallo", "A750", 5);

        EXPECT_EQ("naam", airport->getName());
        EXPECT_EQ("hallo", airport->getIata());
        EXPECT_EQ("A750", airport->getCallsign());
        EXPECT_EQ(5, airport->getGates());
    }

    TEST_F(AirplaneTest, AirportFunctions) {
        D = new AirportHandler();
        D->addXmlData("LuchthavenV1.xml");

        airport = D->getAirports()[0];

        plane = new Airplane();
        plane->setCallsign("original");

        D->addAirplane(plane);
        plane->setAirport(airport);
        EXPECT_EQ(airport, plane->getAirport());

        //get & set airportName
        airport->setName("privejet");
        EXPECT_EQ("privejet", airport->getName());

        //get & set airportName
        airport->setIata("dierentuin");
        EXPECT_EQ("dierentuin", airport->getIata());

        //get & set airportName
        airport->setCallsign("dier4U");
        EXPECT_EQ("dier4U", airport->getCallsign());

        //get & set airportGates
        airport->setGates(3);
        EXPECT_EQ("dier4U", airport->getCallsign());

        //get & set planeVars

        EXPECT_DEATH(airport->setVar("foutief type", "9ab"),  "Assertion.*failed");
        airport->setVar("name", "7");
        airport->setVar("iata", "TufTuf");
        airport->setVar("callsign", "J420");
        airport->setVar("gates", "5");
        EXPECT_EQ("7", airport->getName());
        EXPECT_EQ("TufTuf", airport->getIata());
        EXPECT_EQ("J420", airport->getCallsign());
        EXPECT_EQ(5, airport->getGates());

        //getInfo
        string s = "\nAirport:\t";
        s += "7 (TufTuf)\n->callsign:\tJ420\n->gates:\t";
        s += intToString(airport->getGates()) + "\n";
        s += "->runways:\t";
        s += intToString((int)airport->getRunways().size());
        s += "\n";
        EXPECT_EQ(s, airport->getInfo());

        //getFreeGates decreased by 1 because plane occupying one space
        EXPECT_EQ((unsigned)5, airport->getFreeGates().size());
        EXPECT_DEATH(plane->toGate(5), "Assertion.*failed");
        plane->toGate(1);
        EXPECT_EQ((unsigned)4, airport->getFreeGates().size());

        //get & set airportRunways
        //runways0 has no name
        runway = new Runway();
        runway->setName("11R");
        Runway* runway0 = new Runway();

        vector<Runway*> allrunways;
        allrunways.push_back(runway);
        allrunways.push_back(runway0);
        const vector<Runway*> final = allrunways;
        airport->setRunways(final);
        EXPECT_EQ(final, airport->getRunways());

        //runways have same name
        runway->setName("11R");
        runway0->setName("11R");

        allrunways.clear();
        allrunways.push_back(runway);
        allrunways.push_back(runway0);
        const vector<Runway*> final1 = allrunways;
        airport->setRunways(final1);
        EXPECT_EQ(final1, airport->getRunways());


        //runways have different name
        runway->setName("11R");
        runway0->setName("12R");

        allrunways.clear();
        allrunways.push_back(runway);
        allrunways.push_back(runway0);
        const vector<Runway*> final0 = allrunways;
        airport->setRunways(final);
        EXPECT_EQ((unsigned)2,  airport->getRunways().size());
        //EXPECT_EQ(final, airport->getRunways());

        //add & removeRunway
        Runway* runway1 = new Runway();
        runway1->setName("13R");

        Runway* runway2 = new Runway();
        runway2->setName("13R");


        airport->removeRunway("11R");
        EXPECT_EQ((unsigned)1,  airport->getRunways().size());
        EXPECT_DEATH(airport->removeRunway("11R"), "Assertion.*failed");
        EXPECT_EQ((unsigned)1,  airport->getRunways().size());

        airport->addRunway(runway1);
        EXPECT_DEATH(airport->addRunway(runway2), "Assertion.*failed");

        //getFreeRunways
        plane->toRunway(runway1);
        EXPECT_EQ((unsigned)1, airport->getFreeRunways().size());

        //check gate occupied
        plane->toGate(1);
        EXPECT_TRUE(airport->getGateOccupied(1));
        EXPECT_FALSE(airport->getGateOccupied(0));
        plane->toGate(0);

        EXPECT_TRUE(airport->getGateOccupied(0));
        EXPECT_FALSE(airport->getGateOccupied(1));

        Airplane* plane1 = new Airplane;
        plane1->setAirport(airport);
        plane1->toGate(1);
        EXPECT_EQ(unsigned(3), airport->getFreeGates().size());
        plane1->toRunway();


        EXPECT_DEATH(airport->getGateOccupied(6), "Assertion.*failed");
        EXPECT_FALSE(airport->getGateOccupied(1));
        EXPECT_TRUE(airport->getGateOccupied(0));

        airport->setGateOccupied(0, false);
        EXPECT_FALSE(airport->getGateOccupied(0));
        airport->setGateOccupied(0, true);

        vector<bool> boolvector;
        boolvector.push_back(true);
        boolvector.push_back(false);
        const vector<bool> finalevector = boolvector;

        airport->setGatesOccupied(finalevector);
        EXPECT_EQ(finalevector, airport->getGatesOccupied());


        //EXPECT_EQ(finalevector, airport->getGatesOccupied());

        airport->printInfo();
    }

    TEST_F(AirplaneTest, RunwayConstructor) {
        plane = new Airplane();
        D = new AirportHandler();
        D->addXmlData("LuchthavenV1.xml");

        airport = D->getAirports()[0];

        runway = new Runway("Freddy", airport);
        EXPECT_EQ("Freddy", runway->getName());
        EXPECT_EQ(airport, runway->getAirport());
        EXPECT_FALSE(runway->isOccupied());
    }

    TEST_F(AirplaneTest, RunwayFunctions) {
        D = new AirportHandler();
        D->addXmlData("LuchthavenV1.xml");

        airport = D->getAirports()[0];

        plane = new Airplane();

        runway = new Runway();

        //get & set runwayName
        EXPECT_NE("Primair", runway->getName());
        EXPECT_NE(airport, runway->getAirport());
        runway->setName("Primair");
        runway->setAirport(airport);
        EXPECT_EQ("Primair", runway->getName());
        EXPECT_EQ(airport, runway->getAirport());

        EXPECT_FALSE(runway->isOccupied());
        runway->setOccupied(true);
        EXPECT_TRUE(runway->isOccupied());
        runway->setOccupied(false);
        EXPECT_FALSE(runway->isOccupied());
    }

    TEST_F(AirplaneTest, AirportHandlerFunctions) {
        D = new AirportHandler();
        EXPECT_DEATH(D->addXmlData("foutiefbestand.xml"), "Assertion.*failed");
        D->addXmlData("LuchthavenV1.xml");

        airport = D->getAirports()[0];

        //addAirplane
        plane = new Airplane();
        //plane has no callsign
        EXPECT_DEATH(D->addAirplane(plane), "Assertion.*failed");

        //plane has a callsign
        plane->setCallsign("original");
        D->addAirplane(plane);

        //plane's callsign is a duplicate
        EXPECT_DEATH(D->addAirplane(plane), "Assertion.*failed");

        //plane's callsign is no duplicate
        plane->setCallsign("different");
        EXPECT_DEATH(D->addAirplane(plane), "Assertion.*failed");

        //removeplane
        unsigned int i = D->getAirplanes().size();
        D->removeAirplane("different");
        EXPECT_DEATH(D->removeAirplane("different"), "Assertion.*failed");
        EXPECT_EQ(i-1, D->getAirplanes().size());

        //addAirport
        airport = new Airport();
        //plane has no callsign
        EXPECT_DEATH(D->addAirport(airport), "Assertion.*failed");

        //plane has a callsign
        airport->setCallsign("original");
        D->addAirport(airport);

        //plane's callsign is a duplicate
        EXPECT_DEATH(D->addAirport(airport), "Assertion.*failed");

        //plane's callsign is no duplicate
        airport->setCallsign("different");
        EXPECT_DEATH(D->addAirport(airport), "Assertion.*failed");

        //removeAirport
        i = D->getAirports().size();
        D->removeAirport("different");
        EXPECT_DEATH(D->removeAirport("different"), "Assertion.*failed");
        EXPECT_EQ(i-1, D->getAirports().size());


        //airport1 has no callsign
        Airport* airport0 = new Airport();
        Airport* airport1 = new Airport();
        airport0->setCallsign("original");
        EXPECT_EQ((unsigned)1, D->getAirports().size());
        vector<Airport *> airports;
        airports.push_back(airport0);
        airports.push_back(airport1);
        const vector<Airport *> myairportvector = airports;
        EXPECT_DEATH(D->setAirports(myairportvector), "Assertion.*failed");

        EXPECT_NE( myairportvector, D->getAirports());


        //duplicate callsign
        airports.clear();
        airport1->setCallsign("original");
        airports.push_back(airport0);
        airports.push_back(airport1);
        const vector<Airport *> final = airports;
        EXPECT_DEATH(D->setAirports(final), "Assertion.*failed");
        EXPECT_NE(final, D->getAirports());

        //valid callsigns
        airports.clear();
        airport1->setCallsign("New");
        airports.push_back(airport0);
        airports.push_back(airport1);
        const vector<Airport *> finalvec = airports;
        D->setAirports(final);
        EXPECT_EQ((unsigned)2, D->getAirports().size());
        EXPECT_EQ(finalvec, D->getAirports());

        runway = new Runway();

        // different callsigns Airplanes
        Airplane* airplane0 = new Airplane();
        Airplane* airplane1 = new Airplane();
        airplane0->setCallsign("0");
        airplane1->setCallsign("1");

        vector<Airplane*> Planes;
        Planes.push_back(airplane0);
        Planes.push_back(airplane1);

        D->setAirplanes(Planes);
        EXPECT_EQ(Planes, D->getAirplanes());

        // Duplicate callsign airplanes
        airplane1->setCallsign("0");
        EXPECT_DEATH(D->setAirplanes(Planes), "Assertion.*failed");

        // No callsign airplanes
        airplane1->setCallsign("");
        EXPECT_DEATH(D->setAirplanes(Planes), "Assertion.*failed");

        //getInfo
        string teststring;
        for (unsigned int i = 0; i< D->getAirports().size(); i++ ){
            teststring+= D->getAirports()[i]->getInfo();
        }

        for (unsigned int i = 0; i< D->getAirplanes().size(); i++ ){
            teststring+= D->getAirplanes()[i]->getInfo();
        }
        EXPECT_EQ(teststring, D->getInfo());

        //FileOutput
        D->fileOutput();

        //printInfo
        D->printInfo();

        ofstream *OutputTxt = getText();

        *OutputTxt << "End";

        OutputTxt->close();

        EXPECT_FALSE(OutputTxt->is_open());

        delete D;

    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
