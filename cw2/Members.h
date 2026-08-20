#ifndef MEMBERS_H_
#define MEMBERS_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;


struct Staff {
    string id;
    int load;
    int remaining;
    vector<int> projects;
    unordered_set<string> students;
    unordered_set<string> subjects;
};

struct Project {
    int id;
    string proposerId;
    int multiplicity;
    int remaining;
    string subjectArea;
    string title;
};

struct Student {
    string id;
    vector<int> choices;
    int allocatedProject = -1;
    string allocatedSupervisor = "";
};

#endif