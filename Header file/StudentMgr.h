#ifndef STUDENTMGR_H
#define STUDENTMGR_H

#include "common.h"

void addStudent();
void editStudent();
void deleteStudent();
void listStudents();
bool stuIdExists(const string& id);
string generateStuId();

#endif