#ifndef EDUCATIONALMANAGEMENTSYSTEM_H_INCLUDED
#define EDUCATIONALMANAGEMENTSYSTEM_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "dataManager.h"
#include "public.h"

struct EducationalManagementSystem {

    dataManager dataManageR;

    void doctorDisplay(){
        while(true) {
            cout << "1: create course \n";
            cout << "2: create homeWork \n";
            cout << "3: repair homeWork \n";
            cout << "4: send assistant invite to course \n";
            cout << "5: print all My courses information \n";
            cout << "6: add preCourse to course \n";
            cout << "7: send message \n";
            cout << "8: print message from me \n";
            cout << "9: print message to me \n";
            cout << "10: log out \n";

            int opetion;
            opetion = readInteger("opetion between 1-10");

            while(!numberInLimit(opetion,1,10)) {
                opetion = readInteger("opetion between 1-10");
            }

            if      (opetion == 1) dataManageR.systemDoctorCreateCourse();
            else if (opetion == 2) dataManageR.systemDoctorCreareHomeWork();
            else if (opetion == 3) dataManageR.systemDoctorRepairHomeWork();
            else if (opetion == 4) dataManageR.systemDoctorInviteAssistantToCourse();
            else if (opetion == 5) dataManageR.systemDoctorPrintAllCoursesInfo();
            else if (opetion == 6) dataManageR.systemDoctoraddPreCourseToThisCourse();
            else if (opetion == 7) dataManageR.systemDoctorSendMessage();
            else if (opetion == 8) dataManageR.systemDoctorPrintMessageFromMe();
            else if (opetion == 9) dataManageR.systemDoctorPrintMessageToMe();
            else if (opetion == 10) break;
        }
    }

    void studentDisplay() {
        while(true) {
            cout << "1: join course \n";
            cout << "2: solve homeWork \n";
            cout << "3: print my courses \n";
            cout << "4: print my HomeWorks \n";
            cout << "5: send message \n";
            cout << "6: print message from me \n";
            cout << "7: print message to me \n";
            cout << "8: log out \n";

            int opetion;
            opetion = readInteger("opetion between 1-8");

            while(!numberInLimit(opetion,1,8)) {
                opetion = readInteger("opetion between 1-8");
            }

            if (opetion == 1) dataManageR.systemStudentJoinCourse();
            else if (opetion == 2) dataManageR.systemStudentSolveHomeWork();
            else if (opetion == 3) dataManageR.systemStudentPrintHisCourse();
            else if (opetion == 4) dataManageR.systemStudentPrintMyHomeWork();
            else if (opetion == 5) dataManageR.systemStudentSendMessage();
            else if (opetion == 6) dataManageR.systemStudentPrintMessageFromMe();
            else if (opetion == 7) dataManageR.systemStudentPrintMessageToMe();
            else if (opetion == 8) break;
        }
    }

    void assistantDisplay() {
        while(true) {
            cout << "1: acceptance invite to course \n";
            cout << "2: repair homeWork \n";
            cout << "3: print all My courses information \n";
            cout << "4: send message \n";
            cout << "5: print message from me \n";
            cout << "6: print message to me \n";
            cout << "7: log out \n";

            int opetion;
            opetion = readInteger("opetion between 1-7");

            while(!numberInLimit(opetion,1,7)) {
                opetion = readInteger("opetion between 1-7");
            }

            if      (opetion == 1) dataManageR.systemAssistantAcceptanceInvite();
            else if (opetion == 2) dataManageR.systemAssistantRepairHomeWork();
            else if (opetion == 3) dataManageR.systemAssistantPrintAllCoursesInfo();
            else if (opetion == 4) dataManageR.systemAssistantSendMessage();
            else if (opetion == 5) dataManageR.systemAssistantMessageFromMe();
            else if (opetion == 6) dataManageR.systemAssistantMessageToMe();
            else if (opetion == 7) break;
        }
    }

        void signUp() {
        cout << "1: doctor \n";
        cout << "2: student \n";
        cout << "3: assistant \n";
        int opetion;
        opetion = readInteger("opetion between 1-3");

        while(!numberInLimit(opetion,1,3)) {
            opetion = readInteger("opetion between 1-3");
        }

        if (opetion==1) dataManageR.systemDoctorSignUp();
        else if (opetion==2) dataManageR.systemStudentSignUp();
        else if (opetion==3) dataManageR.assistantSignUp();
    }

    void signIn() {
        cout << "1: doctor \n";
        cout << "2: student \n";
        cout << "3: assistant \n";
        int opetion;
        opetion = readInteger("opetion between 1-3");

        while(!numberInLimit(opetion,1,3)) {
            opetion = readInteger("opetion between 1-3");
        }

        if (opetion==1) {
            while(true) {
                if (dataManageR.systemDoctoSignIn()) {
                    doctorDisplay();
                    break;
                }
                else cout << "The email or password is incorrect \n";
            }

        }
        else if (opetion==2) {
            while(true) {
                if (dataManageR.systemStudentSignIn()) {
                    studentDisplay();
                    break;
                }
                else cout << "The email or password is incorrect \n";
            }
        }
        else if (opetion==3) {
            while(true) {
                if (dataManageR.assistantSignIn()) {
                    assistantDisplay();
                    break;
                }
                else cout << "The email or password is incorrect \n";
            }
        }
    }

    void homeDisplay() {
        while(true) {
            cout << "1: sign up \n";
            cout << "2: sign in \n";
            cout << "3: exit \n";

            int opetion;
            opetion = readInteger("opetion between 1-3");

            while(!numberInLimit(opetion,1,3)) {
                opetion = readInteger("opetion between 1-3");
            }

            if (opetion == 1) signUp();
            else if (opetion == 2) signIn();
            else if (opetion == 3) break;
        }
    }
};


#endif // EDUCATIONALMANAGEMENTSYSTEM_H_INCLUDED
