//
// Created by oliviervh on 01.03.18.
//

#ifndef PSE_V1_MESSAGESYSTEM_H
#define PSE_V1_MESSAGESYSTEM_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "DesignByContract.h"

using namespace std;

/**
 * Prints an action message in the console
 * @param s
 */
void actionMessage(string s);

/**
 * Prints a notification message
 * @param s
 */
void notificationMessage(string s);

/**
 * Prints an error message in the console
 * @param s
 */
void errorMessage(string s);

/**
 * Prints a succes messade in the console
 * @param s
 */
void succesMessage(string s);

/**
 * Prints a notification of an input in the console
 * @param s
 */
void inputMessage(string s);

/**
 * Converts Ints to strings
 * @param int i
 * @return string
 */
string intToString(int i);

/**
 * Returns the ofstream object containing all the text send to the Message functions
 * @return text
 */
ofstream* getText();


#endif //PSE_V1_MESSAGESYSTEM_H
