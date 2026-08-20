#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Members.h"
#include "Allocation.h"
using namespace std;

void phase1(unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students) {
    //process each student
    for (auto& [stid, st] : students) {
        //go to next student if already allocated
        if (st.allocatedProject != -1) continue;

        //give student most preferred project still available
        //go to next student if no available preferred project
        for (int choice : st.choices) {
            Project& p = projects[choice];
            if (p.remaining > 0) {
                st.allocatedProject = p.id;
                p.remaining--;
                break;
            }
        }   
    }
}

void phase2_1(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students) {
    //process each staff
    for (auto& [sid, s] : staff) {
        //go to next staff if load is full
        if (s.remaining <= 0) continue;

        //process each project proposed by staff
        for (int pid : s.projects) {
            Project& p = projects[pid];

            //assign students allocated to project to staff
            for (auto& [stid, st] : students) {
                if (st.allocatedProject == p.id && st.allocatedSupervisor.empty() && s.remaining > 0) {
                    st.allocatedSupervisor = s.id;
                    s.remaining--;
                }
            }

            //assign unallocated students to project and to staff if free space
            if (p.remaining && s.remaining > 0) {
                for (auto& [stid, st]: students) {
                    if (st.allocatedProject == -1 && s.remaining > 0 && p.remaining > 0) {
                        st.allocatedProject = p.id;
                        st.allocatedSupervisor = s.id;
                        p.remaining--;
                        s.remaining--;
                    }
                }
            }
            //next staff when full
            if (s.remaining == 0) break;
        }        
    }
}

void phase2_2(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students) {
    for (auto& [sid, s] : staff) {
        if (s.remaining <= 0) continue;

        for (auto& [pid, p] : projects) {
            if (s.remaining <= 0) continue;
            
            //go to next project if proposed by staff
            if (p.proposerId == s.id) continue;

            //go to next project if not area of expertise
            if (s.subjects.find(p.subjectArea) == s.subjects.end()) continue;

            for (auto& [stid, st] : students) {
                if (s.remaining <= 0) break; 

                //assign student to staff if allocated to project and no supervisor
                if (st.allocatedProject == p.id && st.allocatedSupervisor.empty()) {
                    st.allocatedSupervisor = s.id;
                    s.remaining--;
                }
            }

            //if any space for project and staff, assign leftover students if unallocated
            if (p.remaining > 0 && s.remaining > 0) {
                for (auto& [stid, st] : students) {
                    if (s.remaining <= 0 || p.remaining <= 0) break;

                    if (st.allocatedProject == -1) {
                        st.allocatedSupervisor = s.id;
                        st.allocatedProject = p.id;
                        s.remaining--;
                        p.remaining--;                    
                    }
                }
            }
        }
    }
}

void phase2_3(unordered_map<string, Staff>& staff,
    unordered_map<int, Project>& projects,
     unordered_map<string, Student>& students) {
    for (auto& [sid, s] : staff) {
    if (s.remaining <= 0) continue;

        for (auto& [pid, p] : projects) {
            if (s.remaining <= 0) break;

            //assign allocated student to supervisor if there is free space
            for (auto& [stid, st] : students) {
                if (s.remaining <= 0) break; 

                if (st.allocatedProject == p.id && st.allocatedSupervisor.empty()) {
                    st.allocatedSupervisor = s.id;
                    s.remaining--;
                }
            }

            //assign unallocated student to project and supervisor with free space
            if (p.remaining > 0 && s.remaining > 0) {
                for (auto& [stid, st] : students) {
                    if (s.remaining <= 0 || p.remaining <= 0) break;

                    if (st.allocatedProject == -1) {
                        st.allocatedSupervisor = s.id;
                        st.allocatedProject = p.id;
                        s.remaining--;
                        p.remaining--;                    
                    }
                }
            }
        
        }
    }   
}