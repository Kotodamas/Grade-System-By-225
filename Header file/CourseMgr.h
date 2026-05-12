#ifndef COURSEMGR_H
#define COURSEMGR_H

#include "common.h"

void addCourse();
void editCourse();
void deleteCourse();
void listCourses();
bool courseCodeExists(const string& code);
string generateCourseCode();

#endif