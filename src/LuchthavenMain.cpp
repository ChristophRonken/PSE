//
// Created by oliviervh on 01.03.18.
//

#include <vector>

#include "AirportHandler.h"

using namespace std;


int main(int argc, char **argv){

    AirportHandler* D = new AirportHandler();
    D->addXmlData("LuchthavenV1.xml");
    Airplane* a = D->getAirplanes()[0];
    a->land(D->getAirports()[0]);

    //a->liftoff();

    a->toGate();

    //a->toGate(99);
    a->toGate(9);
    a->prepareForDeparture();

    a->toRunway();

    a->takeOff();

    D->getAirports()[0]->removeRunway("11R");
    //D->getAirports()[0]->removeRunway("11R");

    D->fileOutput();

    delete D;


    return 0;
}