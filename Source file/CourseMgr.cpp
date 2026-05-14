// 负责人 潘沛启

#include "CourseMgr.h"
#include "ScoreMgr.h"
#include <iostream>
#include <fstream>
using namespace std;

extern Course* courseHead;
extern Score* scoreHead;

void addCourse() {
    Course* newCourse = new Course;
    newCourse->next = nullptr;

    cout << "是否自动生成课程代码？(y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    if (choice == 'y' || choice == 'Y') {
        newCourse->courseCode = generateCourseCode();
        cout << "自动生成课程代码：" << newCourse->courseCode << endl;
    } else {
        cout << "请输入课程代码：";
        getline(cin, newCourse->courseCode);
        if (courseCodeExists(newCourse->courseCode)) {
            cout << "课程代码已存在，添加失败！" << endl;
            delete newCourse;
            return;
        }
    }
    cout << "请输入课程名称："; getline(cin, newCourse->courseName);
    cout << "请输入学分："; cin >> newCourse->credit; cin.ignore();

    newCourse->next = courseHead;
    courseHead = newCourse;
    cout << "课程信息添加成功！" << endl;
}

void editCourse() {
    if (!courseHead) {
        cout << "暂无课程信息！" << endl;
        return;
    }
    string code;
    cout << "请输入要编辑的课程代码：";
    cin >> code;
    cin.ignore();

    Course* p = courseHead;
    while (p && p->courseCode != code) p = p->next;
    if (!p) {
        cout << "未找到该课程！" << endl;
        return;
    }

    cout << "原信息：" << p->courseCode << " " << p->courseName << " " << p->credit << endl;
    cout << "请输入新的课程名称（直接回车保留原值）：";
    string input;
    getline(cin, input); if (!input.empty()) p->courseName = input;
    cout << "请输入新的学分（直接输入负数保留原值）：";
    double cred; cin >> cred; if (cred >= 0) p->credit = cred; cin.ignore();

    cout << "是否要修改课程代码？(y/n)：";
    char ch;
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        string newCode;
        cout << "请输入新课程代码：";
        getline(cin, newCode);
        if (courseCodeExists(newCode)) {
            cout << "新课程代码已存在，修改失败！" << endl;
        } else {
            string oldCode = p->courseCode;
            p->courseCode = newCode;
            Score* s = scoreHead;
            while (s) {
                if (s->courseCode == oldCode) s->courseCode = newCode;
                s = s->next;
            }
            cout << "课程代码修改成功，已同步更新成绩表中的对应课程代码。" << endl;
        }
    }
    cout << "课程信息更新完成！" << endl;
}

void deleteCourse() {
    if (!courseHead) {
        cout << "暂无课程信息！" << endl;
        return;
    }
    string code;
    cout << "请输入要删除的课程代码：";
    cin >> code;

    Course *prev = nullptr, *curr = courseHead;
    while (curr && curr->courseCode != code) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "未找到该课程！" << endl;
        return;
    }

    Score *sPrev = nullptr, *sCurr = scoreHead;
    while (sCurr) {
        if (sCurr->courseCode == code) {
            if (sPrev) sPrev->next = sCurr->next;
            else scoreHead = sCurr->next;
            Score* toDel = sCurr;
            sCurr = sCurr->next;
            delete toDel;
        } else {
            sPrev = sCurr;
            sCurr = sCurr->next;
        }
    }

    if (prev) prev->next = curr->next;
    else courseHead = curr->next;
    delete curr;
    cout << "课程信息及其所有成绩记录已删除！" << endl;
}

void listCourses() {
    if (!courseHead) {
        cout << "暂无课程信息！" << endl;
        return;
    }
    cout << left << setw(12) << "课程代码" << setw(20) << "课程名称" << setw(6) << "学分" << endl;
    Course* p = courseHead;
    while (p) {
        cout << left << setw(12) << p->courseCode << setw(20) << p->courseName << setw(6) << p->credit << endl;
        p = p->next;
    }
}

bool courseCodeExists(const string& code) {
    Course* p = courseHead;
    while (p) {
        if (p->courseCode == code) return true;
        p = p->next;
    }
    return false;
}

string generateCourseCode() {
    int maxNum = 0;
    Course* p = courseHead;
    while (p) {
        string code = p->courseCode;
        if (code.length() > 1 && code[0] == 'C') {
            string numStr = code.substr(1);
            if (isNumber(numStr)) {
                int num = stoi(numStr);
                if (num > maxNum) maxNum = num;
            }
        }
        p = p->next;
    }
    maxNum++;
    string numStr = to_string(maxNum);
    while (numStr.length() < 3) numStr = "0" + numStr;
    return "C" + numStr;
}