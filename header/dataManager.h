#ifndef PROJECTSYSTEM_H_INCLUDED
#define PROJECTSYSTEM_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "studentManager.h"
#include "doctorManager.h"
#include "assistantManger.h"
#include "courseManger.h"
#include "homeworkManager.h"
#include "public.h"

struct dataManager {
    doctorManger doctorMangeR;
    studentManager studentManageR;
    assistantsManager assistantsManageR;
    coursesManager courseManageR;
    homeWorksManager homeWorksManageR;

    //////////////////////////////READ FSTREAM/////////////////////////////////////////////////

    dataManager() {

        //
        fstream countUsersInput("fstream//system//countUsers.txt",ios::in | ios::out | ios::app);
        testOpenFile(countUsersInput.fail());
        countUsersInput >> doctorMangeR.countDoctors >> studentManageR.countStudents
                        >> assistantsManageR.countAssistants >> courseManageR.countCourses
                        >> homeWorksManageR.countHomeWorks;
        countUsersInput.close();
        //

        vector < pair<int, homeWork*> > allHomeWorks = studentManageR.allHomeWorksStudents();
        for (int i = 0; i < allHomeWorks.size(); i++) {
            homeWorksManageR.addToAllHomeWorks(allHomeWorks[i].first, allHomeWorks[i].second);
        }

    }

    /////////////////////////////////////////////////////////////////////////////////////////////

    void systemUpdateCount() {
        fstream countUsersInput("fstream//system//countUsers.txt",ios::in | ios::out | ios::trunc);
        testOpenFile(countUsersInput.fail());

        countUsersInput << doctorMangeR.countDoctors << " ";
        countUsersInput << studentManageR.countStudents << " ";
        countUsersInput << assistantsManageR.countAssistants << " ";
        countUsersInput << courseManageR.countCourses << " ";
        countUsersInput <<  homeWorksManageR.countHomeWorks;

        countUsersInput.close();
    }

    //////////////////////////////DOCTORS/////////////////////////////////////////////////

    void systemDoctorSignUp() {
        string email = readValidEmail();

        if (doctorMangeR.testIfFindDotorSameEmail(email)||
            assistantsManageR.testIfFindAssistantSameEmail(email)||
            studentManageR.testIsTheEmailIsAvailable(email)
            ) {
            cout << "email is used \n";
            return;
        }

        string name = readString("name");
        string password;
        cout << "enter your password \n";
        cin >> password;

        doctorMangeR.SignUp(email, name, password);
        systemUpdateCount();
    }

    bool systemDoctoSignIn() {
        string email = readValidEmail(), password;
        cout << "enter your password \n";
        cin >> password;
        return (doctorMangeR.signIn(email, password));
    }

    void systemDoctorCreateCourse() {
        string name = readString("name");
        while(courseManageR.testIfFindCourseSameName(name)) {
            cout << "the name is used plz try again \n";
            name = readString("name");
        }
        string password;
        cout << "enter your password \n";
        cin >> password;

        int idCourse = courseManageR.createCourse(name, password);
        doctorMangeR.CreateCourse(idCourse);
        systemUpdateCount();
    }

    void systemDoctorCreareHomeWork() {
        int idCourse = doctorMangeR.createHomeWork();
        if ((idCourse<0)|(idCourse >= courseManageR.countCourses)) {
            cout << "course is not found \n";
            return;
        }
        if (!doctorMangeR.testIfDoctorHaveThisCourse(idCourse)) {
            cout << "you are not have this course \n";
            return;
        }

        int idHomeWork = homeWorksManageR.countHomeWorks;
        vector<int> studentJoinedCourse = courseManageR.addHomeWorkToCourse(idCourse, idHomeWork);
        for (int i = 0; i < studentJoinedCourse.size(); i++) {
            homeWork* ptrHomeWork = studentManageR.addHomeWorkToStudent(idHomeWork, idCourse, studentJoinedCourse[i]);
            homeWorksManageR.addToAllHomeWorks(idCourse, ptrHomeWork);
        }
        homeWorksManageR.countHomeWorks++;
        systemUpdateCount();
    }

    void systemDoctorRepairHomeWork() {
        int idCourse = readInteger("course id");
        if ((idCourse<0)|(idCourse >= courseManageR.countCourses)) {
            cout << "course is not found \n";
            return;
        }
        if (!doctorMangeR.testIfDoctorHaveThisCourse(idCourse)) {
            cout << "you are not have this course \n";
            return;
        }
        /////
        int idHomeWork = readInteger("homeWork id");
        if ((idHomeWork<0)|(idHomeWork >= homeWorksManageR.countHomeWorks)) {
            cout << "homwWork is not found \n";
            return;
        }
        /////
        int idStudent = readInteger("student id");
        if ((idStudent<0)|(idStudent >= studentManageR.countStudents)) {
            cout << "student is not found \n";
            return;
        }
        if (!studentManageR.testIfStudentHaveCourse(idStudent,idCourse)) {
            cout << "student not have this course \n";
            return;
        }
        if (studentManageR.testIfHomeWorkIsRepaired(idStudent, idHomeWork)) {
            cout << "homeWork is already repaired \n";
            return;
        }
        if (!studentManageR.testHomeWorkIsSolve(idStudent, idHomeWork)) {
            cout << "homeWork is not solved by the student \n";
            return;
        }
        if (!courseManageR.testIfCourseHaveThisHomeWork(idCourse, idHomeWork)) {
            cout << "this course is not have this homeWork \n";
            return;
        }

        studentManageR.repairStudentHomeWork(idStudent, idHomeWork);
    }

    void systemDoctorPrintAllCoursesInfo() {
        vector<int> courses = doctorMangeR.returnMyCoursesId();

        if (!courses.size()) {
            cout << "there are no courses \n";
            return;
        }

        for (int i = 0; i < courses.size(); i++) {
            courseManageR.printCourseInformation(courses[i]);
            homeWorksManageR.printHomeWorkCourse(courses[i]);
            cout << "______________________________________________________________________________________________________\n";
        }
    }

    void systemDoctorInviteAssistantToCourse() {
        pair<int, int> idCourse_idAssistant = doctorMangeR.sendAssistantInviteToCourse();
        int idCourse = idCourse_idAssistant.first;
        int idAssistant = idCourse_idAssistant.second;

        if ((idCourse<0)|(idCourse >= courseManageR.countCourses)) {
            cout << "course is not found \n";
            return;
        }
        if ((idAssistant<0)|(idAssistant >= assistantsManageR.countAssistants)) {
            cout << "assistant is not found \n";
            return;
        }
        if (assistantsManageR.testIfAssistantHaveThisCourse(idCourse,idAssistant)) {
            cout << "assistant already have this course \n";
            return;
        }

        if (assistantsManageR.testIfAssistantHaveInviteThisCourse(idCourse,idAssistant)) {
            cout << "assistant already have invite to this course \n";
            return;
        }

        assistantsManageR.addInviteToCourse(idCourse, idAssistant);
    }

    void systemDoctoraddPreCourseToThisCourse() {
        int idCourse = readInteger("course id");
        if ((idCourse<0)|(idCourse >= courseManageR.countCourses)) {
            cout << "course is not found \n";
            return;
        }
        int idPre = readInteger("preCourse id");
        if ((idPre<0)|(idPre >= courseManageR.countCourses)) {
            cout << "idPre is not found \n";
            return;
        }

        if (courseManageR.testIfPreAddToCourse(idCourse,idPre)) {
            cout << "already added \n";
            return;
        }
        courseManageR.addPreCourseToThisCourse(idCourse, idPre);
    }

    void systemDoctorSendMessage() {
        string emailSender = doctorMangeR.sendEmail();
        string emailRecipient = readString("email recipient");

        if (emailSender == emailRecipient) {
            cout << "you are the same person \n";
            return;
        }

        string letter;
        cout << "plz enter letter \n";
        cin.ignore();
        getline(cin, letter);

        int opetion;
        cout << "1: recipient is doctor | 2: recipient is assistant | 3: recipient is student \n";
        opetion = readInteger("opetion between 1-3");

        while (!numberInLimit(opetion,1,3)) {
            opetion = readInteger("opetion between 1-3");
        }


        if (opetion == 1) {
            if (!doctorMangeR.testIfFindDotorSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            doctorMangeR.pushMessageToDoctor(emailSender,letter,emailRecipient);
        }
        else if (opetion == 2) {
            if (!assistantsManageR.testIfFindAssistantSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
           assistantsManageR.pushMessageToAssistant(emailSender,letter,emailRecipient);
        }
        else if (opetion == 3) {
            if (!studentManageR.testIsTheEmailIsAvailable(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            studentManageR.pushMessageToStudent(emailSender,letter,emailRecipient);
        }

        doctorMangeR.pushMessageFromMe(emailRecipient, letter);
    }

    void systemDoctorPrintMessageFromMe() {
        doctorMangeR.printMyMessageFromMe();
    }

    void systemDoctorPrintMessageToMe() {
        doctorMangeR.printMyMessageToMe();
    }

    //////////////////////////////STUDENTS/////////////////////////////////////////////////

    void systemStudentSignUp() {
        string email = readValidEmail();

        if (doctorMangeR.testIfFindDotorSameEmail(email)||
            assistantsManageR.testIfFindAssistantSameEmail(email)||
            studentManageR.testIsTheEmailIsAvailable(email)
            ) {
            cout << "email is used \n";
            return;
        }

        string name = readString("name");
        string password;
        cout << "enter your password \n";
        cin >> password;

        studentManageR.SignUp(email, name, password);
        systemUpdateCount();
    }

    bool systemStudentSignIn() {
        string email = readValidEmail(), password;
        cout << "enter your password \n";
        cin >> password;
        return studentManageR.signIn(email, password);
    }

    void systemStudentSolveHomeWork() {
        int idHomeWork = readInteger("homeWork id");

        if(studentManageR.testIfHomeWorkSolutionByMe(idHomeWork)) {
            cout << "the homeWork is already solved \n";
            return;
        }

        while ((idHomeWork<0)||(idHomeWork>homeWorksManageR.countHomeWorks)) {
            cout << "the homeWork id is not found plz try again \n";
            readInteger("homeWork id");
        }

        string solution;
        cout << "plz enter solution \n";
        cin.ignore();
        getline(cin, solution);

        studentManageR.solveHomeWork(idHomeWork,solution);
    }

    void systemStudentJoinCourse() {
        int idCourse = readInteger("id course");

        if ((idCourse<0)||(idCourse>doctorMangeR.countDoctors)) {
            cout << "the course id is not found \n";
            return;
        }
        if (studentManageR.testIfStudentJoinedToCourseAlready(idCourse)) {
            cout << "you are already joined \n";
            return;
        }

        string password;
        cout << "plz enter course password \n";
        cin >> password;

        if (!courseManageR.testPasswordCourse(idCourse, password)) {
            cout << "the password is not true \n";
            return;
        }

        vector<int> preCourse = courseManageR.returnPreCourseToThisCourse(idCourse);
        if (!studentManageR.testIfJoinedPreCourseBeforeThisCourse(preCourse)) {
            cout << "plz join to preCourses before this course \n";
            return;
        }

        int idStudent = studentManageR.studentJoinCourse(idCourse);
        courseManageR.addStudentToCourse(idCourse, idStudent);
        vector<int> homeWorkCourse = courseManageR.returnHomeWorkCourse(idCourse);
        vector<homeWork*> homWorkCoursePtr = studentManageR.addHomeWorksCourseToStudent(idCourse, homeWorkCourse);
        for (int i = 0; i < homWorkCoursePtr.size(); i++) homeWorksManageR.addToAllHomeWorks(idCourse, homWorkCoursePtr[i]);
    }

    void systemStudentPrintHisCourse() {
        vector<int> myCoursesId = studentManageR.myCoursesId();

        if (!myCoursesId.size()) {
            cout << "there are no courses joined \n";
            return;
        }

        for (int i = 0; i < myCoursesId.size(); i++) {
            int idCourse = myCoursesId[i];
            string nameCourse = courseManageR.returnNameCourse(idCourse);
            cout << "name course : " << nameCourse << " | id course : " << idCourse << "\n";
        }
    }

    void systemStudentPrintMyHomeWork() {
        studentManageR.printMyHomeWorks();
    }

    void systemStudentPrintMessageFromMe() {
        studentManageR.printMyMessageFromMe();
    }

    void systemStudentPrintMessageToMe() {
        studentManageR.printMyMessageToMe();
    }

    void systemStudentSendMessage() {
        string emailSender = studentManageR.sendEmail();
        string emailRecipient = readString("email recipient");

        string letter;
        cout << "plz enter letter \n";
        cin.ignore();
        getline(cin, letter);


        int opetion;
        cout << "1: recipient is doctor | 2: recipient is assistant | 3: recipient is student \n";
        opetion = readInteger("opetion between 1-3");

        while (!numberInLimit(opetion,1,3)) {
            opetion = readInteger("opetion between 1-3");
        }

        if (opetion == 1) {
            if (!doctorMangeR.testIfFindDotorSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            doctorMangeR.pushMessageToDoctor(emailSender,letter,emailRecipient);
        }
        else if (opetion == 2) {
            if (!assistantsManageR.testIfFindAssistantSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
           assistantsManageR.pushMessageToAssistant(emailSender,letter,emailRecipient);
        }
        else if (opetion == 3) {
            if (!studentManageR.testIsTheEmailIsAvailable(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            studentManageR.pushMessageToStudent(emailSender,letter,emailRecipient);
        }

        studentManageR.pushMessageFromMe(emailRecipient, letter);
    }

    //////////////////////////////ASSISTANTS/////////////////////////////////////////////////

    void assistantSignUp() {

        string email = readValidEmail();
        if (doctorMangeR.testIfFindDotorSameEmail(email)||
            assistantsManageR.testIfFindAssistantSameEmail(email)||
            studentManageR.testIsTheEmailIsAvailable(email)
            ) {
            cout << "email is used \n";
            return;
        }
        string name = readString("name");
        string password;
        cout << "enter your password \n";
        cin >> password;

        assistantsManageR.SignUp(email, name, password);
        systemUpdateCount();
    }

    bool assistantSignIn() {
        string email = readValidEmail(), password;
        cout << "enter your password \n";
        cin >> password;
        return assistantsManageR.signIn(email , password);
    }

    void systemAssistantAcceptanceInvite() {;

        vector< pair<int, int> > idCourse_idAssistant = assistantsManageR.acceptanceInvite();
        for (int i = 0; i < idCourse_idAssistant.size(); i++) {
            int idCourse = idCourse_idAssistant[i].first;
            int idAssistant = idCourse_idAssistant[i].second;
            courseManageR.addAssistantToCourse(idCourse, idAssistant);
        }
    }

    void systemAssistantRepairHomeWork() {
        int idCourse = readInteger("course id");
        if ((idCourse<0)|(idCourse >= courseManageR.countCourses)) {
            cout << "course is not found \n";
            return;
        }
        if (!assistantsManageR.testIfIHaveThisCourse(idCourse)) {
            cout << "you are not have this course \n";
            return;
        }
        /////
        int idHomeWork = readInteger("homeWork id");
        if ((idHomeWork<0)|(idHomeWork >= homeWorksManageR.countHomeWorks)) {
            cout << "homwWork is not found \n";
            return;
        }
        /////
        int idStudent = readInteger("student id");
        if ((idStudent<0)|(idStudent >= studentManageR.countStudents)) {
            cout << "student is not found \n";
            return;
        }
        if (!studentManageR.testIfStudentHaveCourse(idStudent,idCourse)) {
            cout << "student not have this course \n";
            return;
        }
        if (studentManageR.testIfHomeWorkIsRepaired(idStudent, idHomeWork)) {
            cout << "homeWork is already repaired \n";
            return;
        }

        studentManageR.repairStudentHomeWork(idStudent, idHomeWork);
    }

    void systemAssistantPrintAllCoursesInfo() {
        vector<int> courses = assistantsManageR.returnAllCoursesId();
        if (!courses.size()) {
            cout << "there are no courses \n";
            return;
        }
        for (int i = 0; i < courses.size(); i++) {
            courseManageR.printCourseInformation(courses[i]);
            homeWorksManageR.printHomeWorkCourse(courses[i]);
            cout << "______________________________________________________________________________________________________\n";
        }
    }

    void systemAssistantMessageFromMe() {
        assistantsManageR.printMyMessageFromMe();
    }

    void systemAssistantMessageToMe() {
        assistantsManageR.printMyMessageToMe();
    }

    void systemAssistantSendMessage() {
        string emailSender = assistantsManageR.sendEmail();
        string emailRecipient = readString("email recipient");

        string letter;
        cout << "plz enter letter \n";
        cin.ignore();
        getline(cin, letter);

        int opetion;
        cout << "1: recipient is doctor | 2: recipient is assistant | 3: recipient is student \n";
        opetion = readInteger("opetion between 1-3");

        while (!numberInLimit(opetion,1,3)) {
            opetion = readInteger("opetion between 1-3");
        }

        if (opetion == 1) {
            if (!doctorMangeR.testIfFindDotorSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            doctorMangeR.pushMessageToDoctor(emailSender,letter,emailRecipient);
        }
        else if (opetion == 2) {
            if (!assistantsManageR.testIfFindAssistantSameEmail(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
           assistantsManageR.pushMessageToAssistant(emailSender,letter,emailRecipient);
        }
        else if (opetion == 3) {
            if (!studentManageR.testIsTheEmailIsAvailable(emailRecipient)) {
                cout << "email is not found \n";
                return;
            }
            studentManageR.pushMessageToStudent(emailSender,letter,emailRecipient);
        }

        assistantsManageR.pushMessageFromMe(emailRecipient, letter);

    }

};

#endif // PROJECTSYSTEM_H_INCLUDED
