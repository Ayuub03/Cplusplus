#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include <string>
#include <unordered_map>
#include "Members.h"
using namespace std;

void phase1(unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students); 

void phase2_1(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students);

void phase2_2(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students);

void phase2_3(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students); 

#endif