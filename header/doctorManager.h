#ifndef DOCTORMANAGER_H_INCLUDED
#define DOCTORMANAGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

#include "doctor.h"
#include "public.h"

struct doctorManger {
    int idUserNow;
    map<string, string> drEmailPass;
    map<string, int> drEmailId;
    vector <doctor> allDoctors {vector<doctor>(100)};
    int countDoctors = 0;

    ////////////READ FSTREAM/////////////////////////////////////////////////


    doctorManger() {

        fstream emailPassInput("fstream//doctors fstream//doctorsEmailWithPass.txt",ios::in | ios::out);
        testOpenFile(emailPassInput.fail());
        if (emailPassInput.peek()!=emailPassInput.eof()) {
            string email;
            while(emailPassInput >> email >> drEmailPass[email]) {
            }
        }
        emailPassInput.close();

        fstream emailIdInput("fstream//doctors fstream//doctorsEmailWithId.txt",ios::in | ios::out);
        testOpenFile(emailIdInput.fail());
        if (emailIdInput.peek()!=emailIdInput.eof()) {
            string email;
            while(emailIdInput >> email >> drEmailId[email]) {
            }
        }
        emailIdInput.close();

        //

        fstream drInfInput("fstream//doctors fstream//drInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(drInfInput.fail());
        if (drInfInput.peek()!=drInfInput.eof()) {
            int Id;
            while(drInfInput >> Id >> allDoctors[Id].name >> allDoctors[Id].email >> allDoctors[Id].password) {
                allDoctors[Id].id = Id;
            }
        }
        drInfInput.close();
        //
        fstream drIdCoInput("fstream//doctors fstream//drIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(drIdCoInput.fail());
        if (drIdCoInput.peek()!=drIdCoInput.eof()) {
            int idD, x;
            while(drIdCoInput >> idD >> x) {
                allDoctors[idD].idCorces.push_back(x);
            }
        }
        drIdCoInput.close();
        //

        fstream DoctorMessageToDoctorInput("fstream//doctors fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(DoctorMessageToDoctorInput.fail());
        if (DoctorMessageToDoctorInput.peek()!=DoctorMessageToDoctorInput.eof()) {
            int idDoctor;
            string email, letter;
            while(DoctorMessageToDoctorInput >> idDoctor >> email >> letter) {
                allDoctors[idDoctor].messageToMe.push_back({email, letter});
            }
        }
        DoctorMessageToDoctorInput.close();

        fstream DoctorMessageFromMe("fstream//doctors fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(DoctorMessageFromMe.fail());
        if (DoctorMessageFromMe.peek()!=DoctorMessageFromMe.eof()) {
            int idDoctor;
            string email, letter;
            while(DoctorMessageFromMe >> idDoctor >> email >> letter) {
                allDoctors[idDoctor].messageFromMe.push_back({email, letter});
            }
        }
        DoctorMessageFromMe.close();


    }


    /////////////////////////////////////////////////////////////////////////

    bool checkEmailPass(string email, string password) {
        return (drEmailPass[email]==password);
    }

    int signIn(string email, string password) {
        if (!checkEmailPass(email, password)) return false;
        idUserNow = drEmailId[email];
        return true;

    }

    void updateEmailData(string email, string password, int id) {
        drEmailId[email] = id;
        drEmailPass[email] = password;

        fstream drEmailPassInput("fstream//doctors fstream//doctorsEmailWithPass.txt",ios::in | ios::out | ios::app);
        testOpenFile(drEmailPassInput.fail());
        drEmailPassInput << email << " " << password << "\n";
        drEmailPassInput.close();

        fstream drEmailIdInput("fstream//doctors fstream//doctorsEmailWithId.txt",ios::in | ios::out | ios::app);
        testOpenFile(drEmailIdInput.fail());
        drEmailIdInput << email << " " << id << "\n";
        drEmailIdInput.close();
    }

    void SignUp(string email, string name, string password) {
        //email
        doctor newDoctor;
        newDoctor.id = countDoctors;
        newDoctor.email = email;
        newDoctor.name = name;
        newDoctor.password = password;
        allDoctors[countDoctors] = newDoctor;
        countDoctors++;
        updateEmailData(newDoctor.email, newDoctor.password, newDoctor.id);

        fstream drInfInput("fstream//doctors fstream//drInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(drInfInput.fail());
        drInfInput << newDoctor.id << " " << newDoctor.name << " " << newDoctor.email << " " << newDoctor.password << "\n";
        drInfInput.close();
    }

    void CreateCourse(int idCourse) {
        allDoctors[idUserNow].idCorces.push_back(idCourse);

        fstream drIdCoInput("fstream//doctors fstream//drIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(drIdCoInput.fail());
        drIdCoInput << idUserNow << " " << idCourse << "\n";
        drIdCoInput.close();
    }

    int createHomeWork() {
        int idCourse = readInteger("id course");
        return idCourse;
    }

    vector<int> returnMyCoursesId() {
        return allDoctors[idUserNow].idCorces;
    }

    pair<int, int> sendAssistantInviteToCourse() { //invite
        pair<int, int> id_Course_Assistant = {readInteger("course id"), readInteger("assistants id")};

        fstream assistantInviteIdCourseInput("fstream//assistants fstream//assistantInviteIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantInviteIdCourseInput.fail());
        assistantInviteIdCourseInput << id_Course_Assistant.second << " " << id_Course_Assistant.first << "\n";
        assistantInviteIdCourseInput.close();

        return id_Course_Assistant;
    }

    bool testIfFindDotorSameEmail(string email) {
        for (int i = 0; i < countDoctors; i++) {
            if (allDoctors[i].email == email) return true;
        }
        return false;
    }

    bool testIfDoctorHaveThisCourse(int idCourse) {
        for (int i = 0; i < allDoctors[idUserNow].idCorces.size(); i++) {
            if (allDoctors[idUserNow].idCorces[i] == idCourse) return true;
        }
        return false;
    }

    string sendEmail() {
        return allDoctors[idUserNow].email;
    }

    void pushMessageToDoctor(string email, string letter, string emailDoctor) {
        int idDoctorRecipient = drEmailId[emailDoctor];
        allDoctors[idDoctorRecipient].messageToMe.push_back({email, letter});

        fstream DoctorMessageToDoctorInput("fstream//doctors fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(DoctorMessageToDoctorInput.fail());
        DoctorMessageToDoctorInput << idDoctorRecipient << " " << email << " " << letter << "\n";
        DoctorMessageToDoctorInput.close();
    }

    void pushMessageFromMe(string email, string letter) {
        allDoctors[idUserNow].messageFromMe.push_back({email, letter});

        fstream studentMessageFromMeInput("fstream//doctors fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(studentMessageFromMeInput.fail());
        studentMessageFromMeInput << idUserNow << " " << email << " " << letter << "\n";
        studentMessageFromMeInput.close();
    }


    void printMyMessageFromMe() {
        if (!allDoctors[idUserNow].messageFromMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allDoctors[idUserNow].messageFromMe.size(); i++) {
            cout << "to : " << allDoctors[idUserNow].messageFromMe[i].first << "\n";
            cout << "message : " << allDoctors[idUserNow].messageFromMe[i].second << "\n \n";
        }
    }

    void printMyMessageToMe() {
        if (!allDoctors[idUserNow].messageToMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allDoctors[idUserNow].messageToMe.size(); i++) {
            cout << "from : " << allDoctors[idUserNow].messageToMe[i].first << "\n";
            cout << "message : " << allDoctors[idUserNow].messageToMe[i].second << "\n \n";
        }
    }


};


#endif // DOCTORMANAGER_H_INCLUDED
