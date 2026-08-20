#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Members.h"
#include "FileParser.h"
#include "Allocation.h"
#include <algorithm>
using namespace std;

int computeScore(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students) {
    int total = 0;
    
    //add student scores to total
    for (auto& [stid, st] : students) {
        
        //Score of 4 for most preferred
        //-1 for every position below, 0 for outside choice
        int studentScore = 0;
        for (int i = 0; i < st.choices.size(); i++) {
            if (st.choices[i] == st.allocatedProject) {
                studentScore = 4 - i;
                break;
            }
        }
        total += studentScore;
    }

    //add staff scores to total
    for (auto& [stid, st] : students) {
        Project p = projects[st.allocatedProject];
        Staff s = staff[st.allocatedSupervisor];
        int staffScore = 0;
        //4 for proposed project, 2 for in subject area, 0 for outside
        if (p.proposerId == s.id) staffScore = 4;
        else if (s.subjects.count(p.subjectArea)) staffScore = 2;
        total += staffScore;
    }

    return total;
}

int main() {
    //initialise maps
    unordered_map<string, Staff> staff;
    unordered_map<int, Project> projects;
    unordered_map<string, Student> students;

    //read input and extract filenames
    string input;
    cin >> input;
    string tmp; 
    string staffFile; string projectFile; string stringFile; 
    string outputFile;

    stringstream ss(input);
    ss >> tmp >> staffFile >> projectFile >> stringFile >> outputFile;

    //parse files and add to maps
    parseStaff(staffFile, staff);
    parseProject(projectFile, projects, staff);
    parseStudent(stringFile, students);

    //allocation methods
    phase1(projects, students);
    phase2_1(staff, projects, students);
    phase2_2(staff, projects, students);
    phase2_3(staff, projects, students);

    int score = computeScore(staff, projects, students);

    //output to file, takes last commandline argument as name
    ofstream MyFile(outputFile);

    //create list of student ids
    vector<string> stids;
    for (auto& [stid, student] : students) stids.push_back(stid);
    sort(stids.begin(), stids.end());

    //output student id + project + supervisor per line
    for (string& stid : stids) {
        Student st = students[stid];
        MyFile << st.id << " " << st.allocatedProject 
            << " " << st.allocatedSupervisor << "\n";
    }
    
    //score at bottom
    MyFile << score << "\n";
}
