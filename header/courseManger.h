#ifndef COURSEMANGER_H_INCLUDED
#define COURSEMANGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

#include "course.h"
#include "public.h"

struct coursesManager {

    vector <course> allCourses {vector<course>(100)};
    int countCourses = 0;

    //////////READ FSTREAM//////////////////////////////////////////


    coursesManager() {

        fstream courseInfInput("fstream//courses fstream//coursesInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(courseInfInput.fail());
        if (courseInfInput.peek()!=courseInfInput.eof()) {
            int idCourse;
            while(courseInfInput >> idCourse >> allCourses[idCourse].name >> allCourses[idCourse].password) {
                 allCourses[idCourse].id = idCourse;
            }
        }
        courseInfInput.close();
        //
        fstream coursesHomeWorkInput("fstream//courses fstream//coursesHomeWorks.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursesHomeWorkInput.fail());
        if (coursesHomeWorkInput.peek()!=coursesHomeWorkInput.eof()) {
            int idCourse,x ;
            while(coursesHomeWorkInput >> idCourse >> x) {
                 allCourses[idCourse].homeWorks.push_back(x);
            }
        }
        coursesHomeWorkInput.close();
        //
        fstream coursesAssistants("fstream//courses fstream//coursesAssistants.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursesAssistants.fail());
        if (coursesAssistants.peek()!=coursesAssistants.eof()) {
            int idCourse,x ;
            while(coursesAssistants >> idCourse >> x) {
                 allCourses[idCourse].teAssistants.push_back(x);
            }
        }
        coursesAssistants.close();
        //
        fstream coursesStudentsInput("fstream//courses fstream//coursesStudents.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursesStudentsInput.fail());
        if (coursesStudentsInput.peek()!=coursesStudentsInput.eof()) {
            int idCourse,x ;
            while(coursesStudentsInput >> idCourse >> x) {
                 allCourses[idCourse].students.push_back(x);
            }
        }
        coursesStudentsInput.close();
        //

        fstream coursePreCourseInput("fstream//courses fstream//preCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursePreCourseInput.fail());
        if (coursePreCourseInput.peek()!=coursePreCourseInput.eof()) {
            int idCourse, idPre ;
            while(coursePreCourseInput >> idCourse >> idPre) {
                 allCourses[idCourse].preCource.push_back(idPre);
            }
        }
        coursePreCourseInput.close();


    }


    ////////////////////////////////////////////////////////////////

    int createCourse(string name, string password) {
        course newCourse;
        newCourse.id = countCourses;
        newCourse.name = name;
        newCourse.password = password;

        allCourses[countCourses] = newCourse;
        countCourses++;

        fstream courseInfInput("fstream//courses fstream//coursesInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(courseInfInput.fail());
        courseInfInput << newCourse.id << " " << newCourse.name << " " << newCourse.password << "\n";
        courseInfInput.close();

        return newCourse.id;
    }

    vector<int> addHomeWorkToCourse(int idCourse, int idHomeWork) {
        allCourses[idCourse].homeWorks.push_back(idHomeWork);

        fstream coursesHomeWorkInput("fstream//courses fstream//coursesHomeWorks.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursesHomeWorkInput.fail());
        coursesHomeWorkInput << idCourse << " " << idHomeWork << "\n";
        coursesHomeWorkInput.close();

        return allCourses[idCourse].students;
    }

    void printCourseInformation(int idCourse) { //without homework
        allCourses[idCourse].printIdNamePassword();
        allCourses[idCourse].printIdStudents();
        allCourses[idCourse].printIdTeAssistants();
        allCourses[idCourse].printPreCourse();
    }

    void addStudentToCourse(int idCourse, int idStudent) {
        allCourses[idCourse].students.push_back(idStudent);
    }

    vector<int> returnHomeWorkCourse(int idCourse) {
            return allCourses[idCourse].homeWorks;
    }

    string returnNameCourse(int idCourse) {
        return (allCourses[idCourse].name);
    }

    void addAssistantToCourse(int idCourse, int idAssistant) {
        cout << "hi";
        allCourses[idCourse].teAssistants.push_back(idAssistant);
    }

    bool testIfFindCourseSameName(string name) {
        for (int i = 0; i < countCourses; i++) {
            if (allCourses[i].name == name) return true;
        }
        return false;
    }

    bool testPasswordCourse(int idCourse, string password) {
        return (allCourses[idCourse].password == password);
    }

    void addPreCourseToThisCourse(int idCourse, int idPre) {
        allCourses[idCourse].preCource.push_back(idPre);

        fstream coursePreCourseInput("fstream//courses fstream//preCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursePreCourseInput.fail());
        coursePreCourseInput << idCourse << " " << idPre << "\n";
        coursePreCourseInput.close();

    }

    vector<int> returnPreCourseToThisCourse (int idCourse) {
        return (allCourses[idCourse].preCource);
    }

    bool testIfPreAddToCourse(int idCourse, int idPre) {
        for (int i = 0; i < allCourses[idCourse].preCource.size(); i++) {
            if (allCourses[idCourse].preCource[i] == idPre) return true;
        }
        return false;
    }

    bool testIfCourseHaveThisHomeWork(int idCourse, int idHomeWork) {
        for (int i = 0; i < allCourses[idCourse].homeWorks.size(); i++) {
            if (allCourses[idCourse].homeWorks[i] == idHomeWork) return true;
        }
        return false;
    }

};


#endif // COURSEMANGER_H_INCLUDED
