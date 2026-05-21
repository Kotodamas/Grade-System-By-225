#include "ScoreMgr.h"
#include "StudentMgr.h"
#include "CourseMgr.h"
#include <iostream>
using namespace std;

extern Student* stuHead;
extern Course* courseHead;
extern Score* scoreHead;

bool checkStuExist(const string& stuId) {
    Student* p = stuHead;
    while (p) {
        if (p->stuId == stuId) return true;
        p = p->next;
    }
    return false;
}

bool checkCourseExist(const string& courseCode) {
    Course* p = courseHead;
    while (p) {
        if (p->courseCode == courseCode) return true;
        p = p->next;
    }
    return false;
}

Score* findScore(const string& stuId, const string& courseCode) {
    Score* p = scoreHead;
    while (p) {
        if (p->stuId == stuId && p->courseCode == courseCode) return p;
        p = p->next;
    }
    return nullptr;
}

void addOrUpdateScore() {
    string stuId, courseCode;
    int score;
    cout << "请输入学号："; cin >> stuId;
    if (!checkStuExist(stuId)) {
        cout << "学号不存在！请先添加学生信息。" << endl;
        return;
    }
    cout << "请输入课程代码："; cin >> courseCode;
    if (!checkCourseExist(courseCode)) {
        cout << "课程代码不存在！请先添加课程信息。" << endl;
        return;
    }

    Score* exist = findScore(stuId, courseCode);
    if (exist) {
        cout << "该生已有该课程成绩（原成绩：" << exist->score << "）。是否修改？（y/n）: ";
        char ch; cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            cout << "请输入新成绩："; cin >> exist->score;
            cout << "成绩已更新（重修覆盖）！" << endl;
        } else {
            cout << "未修改。" << endl;
        }
    } else {
        cout << "请输入成绩："; cin >> score;
        Score* newScore = new Score;
        newScore->stuId = stuId;
        newScore->courseCode = courseCode;
        newScore->score = score;
        newScore->next = scoreHead;
        scoreHead = newScore;
        cout << "成绩添加成功！" << endl;
    }
}

void deleteScore() {
    if (!scoreHead) {
        cout << "暂无成绩记录！" << endl;
        return;
    }
    string stuId, courseCode;
    cout << "请输入学号："; cin >> stuId;
    cout << "请输入课程代码："; cin >> courseCode;

    Score *prev = nullptr, *curr = scoreHead;
    while (curr && (curr->stuId != stuId || curr->courseCode != courseCode)) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "未找到该生该课程的成绩记录！" << endl;
        return;
    }
    if (prev) prev->next = curr->next;
    else scoreHead = curr->next;
    delete curr;
    cout << "成绩记录已删除！" << endl;
}

void listScores() {
    if (!scoreHead) {
        cout << "暂无成绩记录！" << endl;
        return;
    }
    cout << left << setw(12) << "学号" << setw(12) << "课程代码" << setw(6) << "成绩" << endl;
    Score* p = scoreHead;
    while (p) {
        cout << left << setw(12) << p->stuId << setw(12) << p->courseCode << setw(6) << p->score << endl;
        p = p->next;
    }
}