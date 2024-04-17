#ifndef HOMEWORK_H_INCLUDED
#define HOMEWORK_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "public.h"

struct homeWork{
    int id, grade = -1, idCource, idStudent;
    string solution = "", comment = "";

    void print_Id_IdCourse_IdStudent() {
        cout << "id : " << id << " | " << "idCourse : " << idCource << " | " << "idStudent : " << idStudent << "\n";
    }

    void printRepair() {
        if (grade==(-1)) cout << "the homeWork is not repaired \n";
        else cout << "grade : " << grade << " | " << "comment : " << comment << "\n";

        if (solution == "") cout << "the homeWork is not solved \n";
        else cout << "solution : " << solution << "\n";
    }

};

#endif // HOMEWORK_H_INCLUDED
