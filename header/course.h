#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "public.h"

struct course{
    int id;
    string name, password;
    tm periodFrom, periodTo; //date
    vector<int> students, homeWorks, teAssistants, preCource;


    void printIdNamePassword() {
        cout << "course id : " << id << " | ";
        cout << "course name : " << name << " | ";
        cout << "course password : " << password << "\n \n";
    }

    void printIdStudents() {
        if (!students.size()) cout << "there are no students";
        else {
            cout << "IdStudents : \n";
            for (int i = 0; i < students.size(); i++) cout << students[i] << " ";
        }
        cout << "\n \n";
    }

    void printIdHomeWorks() {
        if (!homeWorks.size()) cout << "there are no homeWorks";
        else {
            cout << "IdHomeWorks : \n \n";
            for (int i = 0; i < homeWorks.size(); i++) cout << homeWorks[i] << " ";
        }
        cout << "\n \n";
    }

    void printIdTeAssistants() {
        if (!teAssistants.size()) cout << "there are no assistants";
        else {
            cout << "IdAssistants : \n";
            for (int i = 0; i < teAssistants.size(); i++) cout << teAssistants[i] << " ";
        }

        cout << "\n \n";
    }

    void printPreCourse() {
        if (!preCource.size()) cout << "there are not preCourse";
        else {
            cout << "preCourse id : \n";
            for (int i = 0; i < preCource.size(); i++) cout << preCource[i] << " ";
        }


        cout << "\n \n";
    }
};


#endif // COURSE_H_INCLUDED
