#ifndef ASSISTANT_H_INCLUDED
#define ASSISTANT_H_INCLUDED

#include <iostream>
#include <vector>
using namespace std;

#include "public.h"

struct Assistant{
    int id;
    string name, email, password;
    vector<int> idCourses;
    vector<int> inviteIdCorces;
    vector<pair<string, string>> messageFromMe;
    vector<pair<string, string>> messageToMe;
};

#endif // ASSISTANT_H_INCLUDED
