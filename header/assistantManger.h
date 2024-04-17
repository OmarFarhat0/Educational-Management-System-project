#ifndef ASSISTANTMANGER_H_INCLUDED
#define ASSISTANTMANGER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
#define all(v) v.begin(), v.end()

#include "assistant.h"
#include "public.h"

struct assistantsManager {
    int idUserNow;
    map<string, string> assistantEmailPass;
    map<string, int> assistantEmailId;
    vector <Assistant> allAssistants {vector<Assistant>(100)};
    int countAssistants = 0;

    ////////////////ASSISTANT FSREAM////////////////////////////////////////////////////

    assistantsManager() {

        fstream emailPassInput("fstream//assistants fstream//assistantsEmailWithPass.txt",ios::in | ios::out);
        testOpenFile(emailPassInput.fail());
        if (emailPassInput.peek()!=emailPassInput.eof()) {
            string email;
            while(emailPassInput >> email >> assistantEmailPass[email]) {
            }
        }
        emailPassInput.close();

        fstream emailIdInput("fstream//assistants fstream//assistantsEmailWithId.txt",ios::in | ios::out);
        testOpenFile(emailIdInput.fail());
        if (emailIdInput.peek()!=emailIdInput.eof()) {
            string email;
            while(emailIdInput >> email >> assistantEmailId[email]) {
            }
        }
        emailIdInput.close();

        //

        fstream assistantInfInput("fstream//assistants fstream//assistantInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantInfInput.fail());
        if (assistantInfInput.peek()!=assistantInfInput.eof()) {
            int Id;
            while(assistantInfInput >> Id >> allAssistants[Id].name >> allAssistants[Id].email >> allAssistants[Id].password) {
                allAssistants[Id].id = Id;
            }
        }
        assistantInfInput.close();
        //

        fstream assistantIdCourseInput("fstream//assistants fstream//assistantIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantIdCourseInput.fail());
        if (assistantIdCourseInput.peek()!=assistantIdCourseInput.eof()) {
            int idAssistant, idCourse;
            while(assistantIdCourseInput >> idAssistant >> idCourse) {
                allAssistants[idAssistant].idCourses.push_back(idCourse);
            }
        }
        assistantIdCourseInput.close();
        //
        fstream assistantInviteIdCourseInput("fstream//assistants fstream//assistantInviteIdCourse.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantInviteIdCourseInput.fail());
        if (assistantInviteIdCourseInput.peek()!=assistantInviteIdCourseInput.eof()) {
            int idAssistant, idCourse;
            while(assistantIdCourseInput >> idAssistant >> idCourse) {
                allAssistants[idAssistant].inviteIdCorces.push_back(idCourse);
            }
        }
        assistantInviteIdCourseInput.close();
        //
        fstream assistantMessageToStudentInput("fstream//assistants fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantMessageToStudentInput.fail());
        if (assistantMessageToStudentInput.peek()!=assistantMessageToStudentInput.eof()) {
            int idDoctor;
            string email, letter;
            while(assistantMessageToStudentInput >> idDoctor >> email >> letter) {
                allAssistants[idDoctor].messageToMe.push_back({email, letter});
            }
        }
        assistantMessageToStudentInput.close();

        fstream assistantMessageFromMeInput("fstream//assistants fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantMessageFromMeInput.fail());
        if (assistantMessageFromMeInput.peek()!=assistantMessageFromMeInput.eof()) {
            int idDoctor;
            string email, letter;
            while(assistantMessageFromMeInput >> idDoctor >> email >> letter) {
                allAssistants[idDoctor].messageFromMe.push_back({email, letter});
            }
        }
        assistantMessageFromMeInput.close();

    }


    /////////////////////////////////////////////////////////////////////

    void addInviteToCourse(int idCourse, int idAssistant) {
        allAssistants[idAssistant].inviteIdCorces.push_back(idCourse);
    }

    ///

    void updateEmailData(string email, string password, int id) {
        assistantEmailId[email] = id;
        assistantEmailPass[email] = password;

        fstream emailPassInput("fstream//assistants fstream//assistantsEmailWithPass.txt",ios::in | ios::out | ios::app);
        testOpenFile(emailPassInput.fail());
        emailPassInput << email << " " << password << "\n";
        emailPassInput.close();

        fstream emailIdInput("fstream//assistants fstream//assistantsEmailWithId.txt",ios::in | ios::out | ios::app);
        testOpenFile(emailIdInput.fail());
        emailIdInput << email << " " << id << "\n";
        emailIdInput.close();
    }

    void SignUp(string email, string name, string password) {
        Assistant newAssistant;
        newAssistant.email = email;
        newAssistant.name = name;
        newAssistant.password = password;
        newAssistant.id = countAssistants;

        allAssistants[countAssistants] = newAssistant;
        countAssistants++;
        updateEmailData(newAssistant.email, newAssistant.password, newAssistant.id);

        fstream assistantInfInput("fstream//assistants fstream//assistantInformation.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantInfInput.fail());
        assistantInfInput << newAssistant.id << " " << newAssistant.name << " " << newAssistant.email << " "
        << newAssistant.password << "\n";
        assistantInfInput.close();
    }

    bool checkEmailPass(string email, string password) {
        return (assistantEmailPass[email]==password);
    }

    int signIn(string email, string password) {
        if (!checkEmailPass(email, password)) return false;
        idUserNow = assistantEmailId[email];
        return true;
    }

    vector< pair<int,int> > acceptanceInvite() {
        vector< pair<int,int> > idCourse_idAssistant;
        if (!allAssistants[idUserNow].inviteIdCorces.size()) {
            cout << "there are no invite \n";
            return idCourse_idAssistant;
        }
        for (int i = 0; i < allAssistants[idUserNow].inviteIdCorces.size(); i++) {
            //cout << 5;
            int idCourse = allAssistants[idUserNow].inviteIdCorces[i];
            cout << "you have invite to teach in course : " << idCourse;
            cout << " enter one to acceptance and zero to ignore" << endl;
            bool acc;
            cin >> acc;

            if (acc) {
                allAssistants[idUserNow].idCourses.push_back(idCourse);
                allAssistants[idUserNow].inviteIdCorces.erase(
                            find(all(allAssistants[idUserNow].inviteIdCorces), idCourse)
                        );

                idCourse_idAssistant.push_back({idCourse,idUserNow});

                fstream coursesAssistants("fstream//courses fstream//coursesAssistants.txt",ios::in | ios::out | ios::app);
                testOpenFile(coursesAssistants.fail());
                coursesAssistants << idCourse << " " << idUserNow << "\n";
                coursesAssistants.close();

                fstream assistantIdCourseInput("fstream//assistants fstream//assistantIdCourse.txt",ios::in | ios::out | ios::app);
                testOpenFile(assistantIdCourseInput.fail());
                assistantIdCourseInput << idUserNow << " " << idCourse << "\n";
                assistantIdCourseInput.close();
            }
            cout << "\n";
        }
        updateFstreamInviteAssistant();
        return idCourse_idAssistant;
    }

    vector<int> returnAllCoursesId() {
        return allAssistants[idUserNow].idCourses;
    }

    void updateFstreamInviteAssistant() {
        fstream assistantInviteIdCourseInput("fstream//assistants fstream//assistantInviteIdCourse.txt",ios::in | ios::out | ios::trunc);
        testOpenFile(assistantInviteIdCourseInput.fail());
        for (int i = 0; i < countAssistants; i++) {
            for (int j = 0; j < allAssistants[i].inviteIdCorces.size(); j++) {
                int idAssistant =  i, idCourse = allAssistants[i].inviteIdCorces[j];
                assistantInviteIdCourseInput << idAssistant << " " << idCourse << "\n";
            }
        }
        assistantInviteIdCourseInput.close();
    }

    bool testIfFindAssistantSameEmail(string email) {
        for (int i = 0; i < countAssistants; i++) {
            if (allAssistants[i].email == email) return true;
        }
        return false;
    }

    bool testIfIHaveThisCourse(int idCourse) {
        for (int i = 0; i < allAssistants[idUserNow].idCourses.size(); i++) {
            if (allAssistants[idUserNow].idCourses[i] == idCourse) return true;
        }
        return false;
    }

    bool testIfAssistantHaveThisCourse(int idCourse, int idAssistant) {
        for (int i = 0; i < allAssistants[idAssistant].idCourses.size(); i++) {
            if (allAssistants[idAssistant].idCourses[i] == idCourse) return true;
        }
        return false;
    }

    bool testIfAssistantHaveInviteThisCourse(int idCourse, int idAssistant) {
        for (int i = 0; i < allAssistants[idAssistant].inviteIdCorces.size(); i++) {
            if (allAssistants[idAssistant].inviteIdCorces[i] == idCourse) return true;
        }
        return false;
    }

    void pushMessageToAssistant(string email, string letter, string emailStudent) {
        int idAssistantRecipient = assistantEmailId[emailStudent];
        allAssistants[idAssistantRecipient].messageToMe.push_back({email, letter});

        fstream assistantMessageToStudentInput("fstream//assistants fstream//messageToMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantMessageToStudentInput.fail());
        assistantMessageToStudentInput << idAssistantRecipient << " " << email << " " << letter << "\n";
        assistantMessageToStudentInput.close();
    }

    void pushMessageFromMe(string email, string letter) {
        allAssistants[idUserNow].messageFromMe.push_back({email, letter});

        fstream assistantMessageFromMeInput("fstream//assistants fstream//messageFromMe.txt",ios::in | ios::out | ios::app);
        testOpenFile(assistantMessageFromMeInput.fail());
        assistantMessageFromMeInput << idUserNow << " " << email << " " << letter << "\n";
        assistantMessageFromMeInput.close();
    }

    void printMyMessageFromMe() {
        if (!allAssistants[idUserNow].messageFromMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allAssistants[idUserNow].messageFromMe.size(); i++) {
            cout << "to : " << allAssistants[idUserNow].messageFromMe[i].first << "\n";
            cout << "message : " << allAssistants[idUserNow].messageFromMe[i].second << "\n \n";
        }
    }

    void printMyMessageToMe() {
        if (!allAssistants[idUserNow].messageToMe.size()) {
            cout << "no message \n";
            return;
        }
        for (int i = 0; i < allAssistants[idUserNow].messageToMe.size(); i++) {
            cout << "from : " << allAssistants[idUserNow].messageToMe[i].first << "\n";
            cout << "message : " << allAssistants[idUserNow].messageToMe[i].second << "\n \n";
        }
    }

    string sendEmail() {
        return allAssistants[idUserNow].email;
    }

};

#endif // ASSISTANTMANGER_H_INCLUDED
