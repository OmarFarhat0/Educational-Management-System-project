#ifndef DOCTOR_H_INCLUDED
#define DOCTOR_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "public.h"


struct doctor{
    int id;
    string name, email, password;
    vector<int> idCorces;
    vector<pair<string, string>> messageFromMe;
    vector<pair<string, string>> messageToMe;

    void printIdCorces() {
        for (int i = 0; i < idCorces.size(); i++) cout << idCorces[i] << " ";
        cout << "\n \n";
    }
};


#endif // DOCTOR_H_INCLUDED
