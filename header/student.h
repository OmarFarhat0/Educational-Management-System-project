#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "homework.h"
#include "public.h"

struct student{
    int id;
    string name, email, password;
    vector<int> idCourses;
    vector<pair<string, string>> messageFromMe;
    vector<pair<string, string>> messageToMe;
    vector<homeWork> homeWorks;

    void read(int Id) {
        name = readString("name");
        email = readValidEmail();
        cout << "enter your password \n";
        cin >> password;
        id = Id;
    }


};


#endif // STUDENT_H_INCLUDED
