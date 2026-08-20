#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Members.h"
#include "FileParser.h"
using namespace std;

//parse each line into staff object then add to map
void parseStaff(string& filename, unordered_map<string, Staff>& staff) {
    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        Staff s;
        ss >> s.id >> s.load;
        s.remaining = s.load;

        string subject;
        while (ss >> subject) s.subjects.insert(subject);

        staff[s.id] = s;
    }
}

//parse each line into project object then add to map
void parseProject(string& filename, unordered_map<int, Project>& projects, 
    unordered_map<string, Staff>& staff) {
    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        Project p;
        ss >> p.id >> p.proposerId >> p.multiplicity >> p.subjectArea;
        p.remaining = p.multiplicity;

        string word;
        //read rest of line and add to title
        while (ss >> word) p.title += " " + word;
        //remove empty space
        if (!p.title.empty() && p.title[0] == ' ') p.title.erase(0, 1);

        projects[p.id] = p;
        //add project to staff's proposed project
        staff[p.proposerId].projects.push_back(p.id);
    }
}

//parse each line into student object then add to map
void parseStudent(string& filename, unordered_map<string, Student>& students) {
    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        Student st;
        ss >> st.id;

        int choice;
        while (ss >> choice) st.choices.push_back(choice);

        students[st.id] = st;
    }
}