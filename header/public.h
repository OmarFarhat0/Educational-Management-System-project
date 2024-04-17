#ifndef PUBLIC_H_INCLUDED
#define PUBLIC_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <fstream>
using namespace std;

#include "public.h"

void testOpenFile(bool fail) {
    if (fail) {
        cout << "error in open file";
        exit(1);
    }
}

string readString(string input) {
    cout << "Plz enter the " << input << " : " << endl;
    string a;
    bool error = 0;
    while (true) {
        if (error == 1) cout << "Plz enter string : " << endl;
        cin >> a;
        bool isInteger = true;
        for (int i = 0; i < a.size(); i++) {
            if (!isdigit(a[i])) {
                isInteger = false;
                break;
            }
        }
        if (!isInteger) break;
        else error = 1;
    }
    return a;
}

int readInteger(string input) {
    cout << "Plz enter the " << input << " : " << endl;
    string a;
    bool error = 0;
    while (true) {
        if (error == 1) cout << "Plz enter integer number : " << endl;
        cin >> a;
        bool isInteger = true;
        for (int i = 0; i < a.size(); i++) {
            if (!isdigit(a[i])) {
                isInteger = false;
                break;
            }
        }
        if (isInteger) break;
        else error = 1;
    }
    int num;
    istringstream iss(a);
    iss >> num;
    return num;
}

string readValidEmail() {
    while(true) {
        cout << "enter your email : \n";
        string email;
        cin >> email;
        regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        if(!regex_match(email, pattern)) cout << "error \n";
        else {
            return email;
        }
    }
}

bool numberInLimit (int num, int mn, int mx) {
    if ((num<mn)||(num>mx)) return false;
    return true;
}

#endif // PUBLIC_H_INCLUDED
