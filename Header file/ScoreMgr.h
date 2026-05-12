#ifndef SCOREMGR_H
#define SCOREMGR_H

#include "common.h"

void addOrUpdateScore();
void deleteScore();
void listScores();
Score* findScore(const string& stuId, const string& courseCode);
bool checkStuExist(const string& stuId);
bool checkCourseExist(const string& courseCode);

#endif