#ifndef STUDENTMANAGER_H_INCLUDED
#define STUDENTMANAGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

#include "student.h"
#include "public.h"

struct studentManager {
    int idUserNow;
    map<string, string> stEmailPass;
    map<string, int> stEmailId;
    vector <student> allStudents {vector<student>(100)};
    int countStudents = 0;

    //////////////////////////////READ FSTREAM/////////////////////////////////////////////////
    studentManager() {

        //
        fstream emailPassInput("fstream//students fstream//emailWithPass.txt",ios::in | ios::out);
        testOpenFile(emailPassInput.fail());
        if (emailPassInput.peek()!=emailPassInput.eof()) {
            string email;
            while(emailPassInput >> email >> stEmailPass[email]) {
            }
        }
        emailPassInput.close();

        fstream emailIdInput("fstream//students fstream//emailWithId.txt",ios::in | ios::out);
        testOpenFile(emailIdInput.fail());
        if (emailIdInput.peek()!=emailIdInput.eof()) {
            string email;
            while(emailIdInput >> email >> stEmailId[email]) {
            }
        }
        emailIdInput.close();
        //

        fstream stInfInput("fstream//students fstream//stInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(stInfInput.fail());
        if (stInfInput.peek()!=stInfInput.eof()) {
            int Id;
            while(stInfInput >> Id >> allStudents[Id].name >> allStudents[Id].email >> allStudents[Id].password) {
                allStudents[Id].id = Id;
            }
        }
        stInfInput.close();
        //
        fstream stIdCoInput("fstream//students fstream//stIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(stIdCoInput.fail());
        if (stIdCoInput.peek()!=stIdCoInput.eof()) {
            int idD, x;
            while(stIdCoInput >> idD >> x) {
                allStudents[idD].idCourses.push_back(x);
            }
        }
        stIdCoInput.close();
        //
        fstream stHomeWorkInfInput("fstream//students fstream//studentHomeWorkInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(stHomeWorkInfInput.fail());
        if (stHomeWorkInfInput.peek()!=stHomeWorkInfInput.eof()) {
            homeWork testHomeWork;
            while(stHomeWorkInfInput >> testHomeWork.id >> testHomeWork.idCource >> testHomeWork.idStudent) {
                 allStudents[testHomeWork.idStudent].homeWorks.push_back(testHomeWork);
            }
        }
        stHomeWorkInfInput.close();
        //
        fstream stHomeWorkRepairInput("fstream//students fstream//studentHomeWorkRepair.txt",ios::in | ios::out | ios::app);
        testOpenFile(stHomeWorkRepairInput.fail());
        if (stHomeWorkRepairInput.peek()!=stHomeWorkRepairInput.eof()) {
            int idStudent, idHomeWork;
            while(stHomeWorkRepairInput >> idStudent >> idHomeWork) {
                 for (int i = 0; i < allStudents[idStudent].homeWorks.size(); i++) {
                    if (allStudents[idStudent].homeWorks[i].id == idHomeWork) {
                        stHomeWorkRepairInput >> allStudents[idStudent].homeWorks[i].grade
                                              >> allStudents[idStudent].homeWorks[i].comment;
                        break;
                    }
                }
            }
        }
        stHomeWorkRepairInput.close();
        //
        fstream stHomeWorkSolutionInput("fstream//students fstream//studentHomeWorkSolution.txt",ios::in | ios::out | ios::app);
        testOpenFile(stHomeWorkSolutionInput.fail());
        if (stHomeWorkSolutionInput.peek()!=stHomeWorkSolutionInput.eof()) {
            int idStudent, idHomeWork;
            while(stHomeWorkSolutionInput >> idStudent >> idHomeWork) {
                 for (int i = 0; i < allStudents[idStudent].homeWorks.size(); i++) {
                    if (allStudents[idStudent].homeWorks[i].id == idHomeWork) {
                        stHomeWorkSolutionInput >> allStudents[idStudent].homeWorks[i].solution;
                        break;
                    }
                 }
            }
        }
        stHomeWorkSolutionInput.close();
        //
        fstream studentMessageToStudentInput("fstream//students fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(studentMessageToStudentInput.fail());
        if (studentMessageToStudentInput.peek()!=studentMessageToStudentInput.eof()) {
            int idDoctor;
            string email, letter;
            while(studentMessageToStudentInput >> idDoctor >> email >> letter) {
                allStudents[idDoctor].messageToMe.push_back({email, letter});
            }
        }
        studentMessageToStudentInput.close();

        fstream studentMessageFromMeInput("fstream//students fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(studentMessageFromMeInput.fail());
        if (studentMessageFromMeInput.peek()!=studentMessageFromMeInput.eof()) {
            int idDoctor;
            string email, letter;
            while(studentMessageFromMeInput >> idDoctor >> email >> letter) {
                allStudents[idDoctor].messageFromMe.push_back({email, letter});
            }
        }
        studentMessageFromMeInput.close();

    }

    ///////////////////////////////////////////////////////////////////////////////////////////

homeWork* addHomeWorkToStudent(int idHomeWork,int idCourse,int idStudent) {
    homeWork newHomeWork;
    newHomeWork.id = idHomeWork;
    newHomeWork.idCource = idCourse;
    newHomeWork.idStudent = idStudent;
    allStudents[idStudent].homeWorks.push_back(newHomeWork);

    fstream stHomeWorkInfInput("fstream//students fstream//studentHomeWorkInformation.txt",ios::in | ios::out | ios::app);
    testOpenFile(stHomeWorkInfInput.fail());
    stHomeWorkInfInput << idHomeWork << " " << idCourse << " " << idStudent << "\n";
    stHomeWorkInfInput.close();

    int e = allStudents[idStudent].homeWorks.size()-1;
    homeWork* testHomeWork = &allStudents[idStudent].homeWorks[e];
    return testHomeWork;
}

void repairStudentHomeWork(int idStudent, int idHomeWork) {
    for (int i = 0; i < allStudents[idStudent].homeWorks.size(); i++) {
        if (allStudents[idStudent].homeWorks[i].id == idHomeWork) {
            allStudents[idStudent].homeWorks[i].grade = readInteger("grade");

            string comment;
            cout << "plz enter your comment : \n";
            cin.ignore();
            getline(cin, comment);

            allStudents[idStudent].homeWorks[i].comment = comment;

            fstream stHomeWorkRepairInput("fstream//students fstream//studentHomeWorkRepair.txt",ios::in | ios::out | ios::app);
            testOpenFile(stHomeWorkRepairInput.fail());
            int grade = allStudents[idStudent].homeWorks[i].grade;
            stHomeWorkRepairInput << idStudent << " " << idHomeWork << " " << grade << " " << comment << "\n";
            stHomeWorkRepairInput.close();

            break;
        }
    }
}

///

bool checkEmailData(string email, string password, int id) {
        return ((stEmailPass[email]==password) && (stEmailId[email]==id));
    }

    void updateEmailData(string email, string password, int id) {
        stEmailId[email] = id;
        stEmailPass[email] = password;

       fstream emailPassInput("fstream//students fstream//emailWithPass.txt",ios::in | ios::out | ios::app);
        testOpenFile(emailPassInput.fail());
        emailPassInput << email << " " << password << "\n";
        emailPassInput.close();

        fstream emailIdInput("fstream//students fstream//emailWithId.txt",ios::in | ios::out | ios::app);
        testOpenFile(emailIdInput.fail());
        emailIdInput << email << " " << id << "\n";
        emailIdInput.close();
    }

    void SignUp(string email, string name, string password) {
        student newStudent;
        newStudent.id = countStudents;
        newStudent.name = name;
        newStudent.password = password;
        newStudent.email = email;
        allStudents[countStudents] = newStudent;
        countStudents++;
        updateEmailData(newStudent.email, newStudent.password, newStudent.id);

        fstream stInfInput("fstream//students fstream//stInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(stInfInput.fail());
        stInfInput << newStudent.id << " " << newStudent.name << " " << newStudent.email << " " << newStudent.password << "\n";
        stInfInput.close();
    }

    bool checkEmailPass(string email, string password) {
        return (stEmailPass[email]==password);
    }

    int signIn(string email, string password) {
        if (!checkEmailPass(email, password)) return false;
        idUserNow = stEmailId[email];
        return true;
    }

    void solveHomeWork(int idHomeWork, string solution) {
        for (int i = 0; i < allStudents[idUserNow].homeWorks.size(); i++) {
            if (allStudents[idUserNow].homeWorks[i].id == idHomeWork) {
                allStudents[idUserNow].homeWorks[i].solution = solution;

                fstream stHomeWorkSolutionInput("fstream//students fstream//studentHomeWorkSolution.txt",ios::in | ios::out | ios::app);
                testOpenFile(stHomeWorkSolutionInput.fail());
                stHomeWorkSolutionInput << idUserNow << " " << idHomeWork << " " << solution << "\n";
                stHomeWorkSolutionInput.close();

                break;
            }
        }
    }

    int studentJoinCourse(int idCourse) {
        allStudents[idUserNow].idCourses.push_back(idCourse);

        fstream stIdCoInput("fstream//students fstream//stIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(stIdCoInput.fail());
        stIdCoInput << idUserNow << " " << idCourse << "\n";
        stIdCoInput.close();

        fstream coursesStudentsInput("fstream//courses fstream//coursesStudents.txt",ios::in | ios::out | ios::app);
        testOpenFile(coursesStudentsInput.fail());
        coursesStudentsInput << idCourse << " " << idUserNow << "\n";
        coursesStudentsInput.close();

        return idUserNow;
    }

    vector<homeWork*> addHomeWorksCourseToStudent(int idCourse, vector<int> allHomeWorkCourses) {
        vector<homeWork*> homeWorks;
        for (int i = 0; i < allHomeWorkCourses.size(); i++) {
            homeWork newhomework;
            newhomework.idCource = idCourse;
            newhomework.idStudent = idUserNow;
            newhomework.id = allHomeWorkCourses[i];

            allStudents[idUserNow].homeWorks.push_back(newhomework);

            int e = allStudents[idUserNow].homeWorks.size()-1;
            homeWorks.push_back(&allStudents[idUserNow].homeWorks[e]);

            fstream stHomeWorkInfInput("fstream//students fstream//studentHomeWorkInformation.txt",ios::in | ios::out | ios::app);
            testOpenFile(stHomeWorkInfInput.fail());
            stHomeWorkInfInput << newhomework.id << " " << newhomework.idCource << " " << newhomework.idStudent << "\n";
            stHomeWorkInfInput.close();
        }
        return homeWorks;
    }

    vector<int> myCoursesId(){
        return allStudents[idUserNow].idCourses;
    }

    void printMyHomeWorks() {
        if (!allStudents[idUserNow].homeWorks.size()) {
            cout << "there are no homeWorks\n";
            return;
        }
        for (int i = 0; i < allStudents[idUserNow].homeWorks.size(); i++) {
            allStudents[idUserNow].homeWorks[i].print_Id_IdCourse_IdStudent();
            allStudents[idUserNow].homeWorks[i].printRepair();
        }
    }

    vector < pair<int, homeWork*> > allHomeWorksStudents() {
        vector < pair<int, homeWork*> > allHomeWorks;
        for (int i = 0; i < allStudents.size(); i++) {
            for (int j = 0; j < allStudents[i].homeWorks.size(); j++) {
                allHomeWorks.push_back({allStudents[i].homeWorks[j].idCource, &allStudents[i].homeWorks[j]});
            }
        }
        return allHomeWorks;
    }

    bool testIsTheEmailIsAvailable(string email) {
        for (int i = 0; i < countStudents; i++) {
            if (allStudents[i].email == email) return true;
        }
        return false;
    }

    bool testIfHomeWorkSolutionByMe(int idHomeWork) {
        for (int i = 0; i < allStudents[idUserNow].homeWorks.size(); i++) {
            if (allStudents[idUserNow].homeWorks[i].id == idHomeWork) {
                return (allStudents[idUserNow].homeWorks[i].solution != "");
            }
        }
        return false;
    }

    bool testIfHomeWorkIsRepaired(int idStudent, int idHomeWork) {
        for (int i = 0; i < allStudents[idStudent].homeWorks.size(); i++) {
            if (allStudents[idStudent].homeWorks[i].id == idHomeWork) {
                return (allStudents[idStudent].homeWorks[i].grade != -1);
            }
        }
        return false;
    }

    bool testIfStudentJoinedToCourseAlready(int idCourse) {
        for (int i = 0; i < allStudents[idUserNow].idCourses.size(); i++) {
            if (allStudents[idUserNow].idCourses[i] == idCourse) return true;
        }
        return false;
    }

    bool testIfStudentHaveCourse(int idStudent, int idCourse) {
        for (int i = 0; i < allStudents[idStudent].idCourses.size(); i++) {
            if (allStudents[idStudent].idCourses[i] == idCourse) return true;
        }
        return false;
    }

    bool testIfJoinedPreCourseBeforeThisCourse(vector<int> preCourse) {
        if (preCourse.size() > allStudents[idUserNow].idCourses.size()) return false;

        for (int i = 0; i < allStudents[idUserNow].idCourses.size(); i++) {
            bool found = false;
            for (int j = 0; j < preCourse.size(); j++) {
                if (allStudents[idUserNow].idCourses[i] == preCourse[j]) found = true;
            }
            if (!found) return false;
        }
        return true;
    }

    void pushMessageToStudent(string email, string letter, string emailStudent) {
        int idStudent = stEmailId[emailStudent];
        allStudents[idStudent].messageToMe.push_back({email, letter});

        fstream studentMessageToStudentInput("fstream//students fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(studentMessageToStudentInput.fail());
        studentMessageToStudentInput << idStudent << " " << email << " " << letter << "\n";
        studentMessageToStudentInput.close();
    }

    void pushMessageFromMe(string email, string letter) {
        allStudents[idUserNow].messageFromMe.push_back({email, letter});

        fstream studentMessageFromMeInput("fstream//students fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(studentMessageFromMeInput.fail());
        studentMessageFromMeInput << idUserNow << " " << email << " " << letter << "\n";
        studentMessageFromMeInput.close();
    }

    void printMyMessageFromMe() {
        if (!allStudents[idUserNow].messageFromMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allStudents[idUserNow].messageFromMe.size(); i++) {
            cout << "to : " << allStudents[idUserNow].messageFromMe[i].first << "\n";
            cout << "message : " << allStudents[idUserNow].messageFromMe[i].second << "\n \n";
        }
    }

    void printMyMessageToMe() {
        if (!allStudents[idUserNow].messageToMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allStudents[idUserNow].messageToMe.size(); i++) {
            cout << "from : " << allStudents[idUserNow].messageToMe[i].first << "\n";
            cout << "message : " << allStudents[idUserNow].messageToMe[i].second << "\n \n";
        }
    }

    string sendEmail() {
        return allStudents[idUserNow].email;
    }

    bool testHomeWorkIsSolve(int idStudent, int idHomeWork) {
        return (allStudents[idStudent].homeWorks[idHomeWork].solution != "");
    }





};


#endif // STUDENTMANAGER_H_INCLUDED
