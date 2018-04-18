//
// Created by oliviervh on 01.03.18.
//



#include "MessageSystem.h"

std::ofstream OutputStream("Log.txt");

void actionMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[;m--Action:\t\033[0m\033[0;m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");

}

void notificationMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;34m--Note:\t\t\033[0m\033[1;34m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

void errorMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;31m--Error:\t\033[0m\033[1;31m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");

};

void succesMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;33m--Succes:\t\033[0m\033[1;33m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

void inputMessage(string s){
    REQUIRE(OutputStream != NULL, "Outputstream exists?");
    //cout << "\033[1;4;32m--Input:\t\033[0m\033[1;32m " << s << "\033[0m" << endl;
    OutputStream << s << "\n";

    ENSURE(true, "No postconditions");
}

string intToString(int i){

    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;

};

ofstream * getText(){

    return &OutputStream;
};