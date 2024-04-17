#ifndef HOMEWORKMANAGER_H_INCLUDED
#define HOMEWORKMANAGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

#include "homework.h"
#include "public.h"

struct homeWorksManager {

    vector < vector<homeWork*> > allHomeWorks  {vector< vector<homeWork*> > (100)};
    int countHomeWorks = 0;

    void addToAllHomeWorks(int idCourse, homeWork* testHomeWork) {
        allHomeWorks[idCourse].push_back(testHomeWork);
    }

    void printHomeWorkCourse(int idCourse) {

        if (!allHomeWorks[idCourse].size()) {
            cout << "there are no homeWorks \n";
            return;
        }

        cout << "_________cours HomeWork_________\n \n";
        for (int i = 0; i < allHomeWorks[idCourse].size(); i++) {
            (*allHomeWorks[idCourse][i]).print_Id_IdCourse_IdStudent();
            (*allHomeWorks[idCourse][i]).printRepair();
            cout << "____________\n";
        }
    }


};


#endif // HOMEWORKMANAGER_H_INCLUDED
