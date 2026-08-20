#ifndef FILEPARSER_H_
#define FILEPARSER_H_

#include <string>
#include <unordered_map>
#include "Members.h"
using namespace std;

void parseStaff(string& filename, unordered_map<string, Staff>& staff);

void parseProject(string& filename, unordered_map<int, Project>& projects,
    unordered_map<string, Staff>& staff);

void parseStudent(string& filename, unordered_map<string, Student>& students);

#endif