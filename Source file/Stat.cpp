//负责人 吴子恒

#include "Stat.h"
#include "StudentMgr.h"
#include "CourseMgr.h"
#include "ScoreMgr.h"
#include <iostream>
#include <vector>
using namespace std;

extern Student* stuHead;
extern Course* courseHead;
extern Score* scoreHead;

void statByStudent() {
    cout << "请输入学生学号或姓名：";
    string input; cin >> input; cin.ignore();
    Student* stu = nullptr;
    Student* p = stuHead;
    while (p && p->stuId != input) p = p->next;
    if (p) stu = p;
    else {
        p = stuHead;
        while (p && p->name != input) p = p->next;
        if (p) stu = p;
    }
    if (!stu) {
        cout << "未找到该学生。" << endl;
        return;
    }
    int courseCount = 0;
    double totalScore = 0;
    double totalCredits = 0;
    Score* s = scoreHead;
    while (s) {
        if (s->stuId == stu->stuId) {
            courseCount++;
            totalScore += s->score;
            Course* c = courseHead;
            while (c && c->courseCode != s->courseCode) c = c->next;
            if (c) totalCredits += c->credit;
        }
        s = s->next;
    }
    if (courseCount == 0) {
        cout << "该学生尚无成绩记录。" << endl;
        return;
    }
    double avgScore = totalScore / courseCount;
    cout << "学生 " << stu->name << " (" << stu->stuId << ")" << endl;
    cout << "选修课程门数：" << courseCount << endl;
    cout << "平均成绩：" << avgScore << endl;
    cout << "总学分数：" << totalCredits << endl;
}

void statByCourse() {
    cout << "请输入课程代码或课程名称：";
    string input; cin >> input; cin.ignore();
    Course* course = nullptr;
    Course* p = courseHead;
    while (p && p->courseCode != input) p = p->next;
    if (p) course = p;
    else {
        p = courseHead;
        while (p && p->courseName != input) p = p->next;
        if (p) course = p;
    }
    if (!course) {
        cout << "未找到该课程。" << endl;
        return;
    }
    int stuCount = 0;
    double totalScore = 0;
    int maxScore = -1, minScore = 101;
    Score* s = scoreHead;
    while (s) {
        if (s->courseCode == course->courseCode) {
            stuCount++;
            totalScore += s->score;
            if (s->score > maxScore) maxScore = s->score;
            if (s->score < minScore) minScore = s->score;
        }
        s = s->next;
    }
    if (stuCount == 0) {
        cout << "该课程尚无成绩记录。" << endl;
        return;
    }
    double avgScore = totalScore / stuCount;
    cout << "课程 " << course->courseName << " (" << course->courseCode << ")" << endl;
    cout << "选修学生人数：" << stuCount << endl;
    cout << "平均成绩：" << avgScore << endl;
    cout << "最高成绩：" << maxScore << endl;
    cout << "最低成绩：" << minScore << endl;
}

void statFailingStudents() {
    vector<pair<string, pair<double, int>>> statVec; // <stuId, <totalScore, count>>
    for (Score* s = scoreHead; s; s = s->next) {
        bool found = false;
        for (auto& item : statVec) {
            if (item.first == s->stuId) {
                item.second.first += s->score;
                item.second.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            statVec.push_back({s->stuId, {static_cast<double>(s->score), 1}});
        }
    }
    bool anyFail = false;
    cout << left << setw(12) << "学号" << setw(12) << "姓名" << setw(16) << "专业" << setw(12) << "班级" << setw(10) << "平均成绩" << endl;
    for (auto& item : statVec) {
        double avg = item.second.first / item.second.second;
        if (avg < 60) {
            anyFail = true;
            Student* stu = stuHead;
            while (stu && stu->stuId != item.first) stu = stu->next;
            if (stu) {
                cout << left << setw(12) << stu->stuId << setw(12) << stu->name << setw(16) << stu->major << setw(12) << stu->className << setw(10) << avg << endl;
            } else {
                cout << left << setw(12) << item.first << setw(12) << "未知" << setw(16) << "-" << setw(12) << "-" << setw(10) << avg << endl;
            }
        }
    }
    if (!anyFail) cout << "没有平均成绩不及格的学生。" << endl;
}