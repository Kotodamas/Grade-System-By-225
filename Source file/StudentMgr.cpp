// 负责人 崔景皓

#include "StudentMgr.h"
#include "ScoreMgr.h"   // 为了同步成绩表中的学号
#include <iostream>
#include <fstream>
using namespace std;

extern Student* stuHead;
extern Score* scoreHead;

void addStudent() {
    Student* newStu = new Student;
    newStu->next = nullptr;

    cout << "是否自动生成学号？(y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    if (choice == 'y' || choice == 'Y') {
        newStu->stuId = generateStuId();
        cout << "自动生成学号：" << newStu->stuId << endl;
    } else {
        cout << "请输入学号：";
        getline(cin, newStu->stuId);
        if (stuIdExists(newStu->stuId)) {
            cout << "学号已存在，添加失败！" << endl;
            delete newStu;
            return;
        }
    }

    cout << "请输入姓名："; getline(cin, newStu->name);
    cout << "请输入性别："; getline(cin, newStu->gender);
    cout << "请输入专业："; getline(cin, newStu->major);
    cout << "请输入班级："; getline(cin, newStu->className);

    newStu->next = stuHead;
    stuHead = newStu;
    cout << "学生信息添加成功！" << endl;
}

void editStudent() {
    if (!stuHead) {
        cout << "暂无学生信息！" << endl;
        return;
    }
    string id;
    cout << "请输入要编辑的学生学号：";
    cin >> id;
    cin.ignore();

    Student* p = stuHead;
    while (p && p->stuId != id) p = p->next;
    if (!p) {
        cout << "未找到该学号的学生！" << endl;
        return;
    }

    cout << "原信息：" << p->stuId << " " << p->name << " " << p->gender << " " << p->major << " " << p->className << endl;
    cout << "请输入新的姓名（直接回车保留原值）：";
    string input;
    getline(cin, input); if (!input.empty()) p->name = input;
    cout << "请输入新的性别（直接回车保留原值）：";
    getline(cin, input); if (!input.empty()) p->gender = input;
    cout << "请输入新的专业（直接回车保留原值）：";
    getline(cin, input); if (!input.empty()) p->major = input;
    cout << "请输入新的班级（直接回车保留原值）：";
    getline(cin, input); if (!input.empty()) p->className = input;

    cout << "是否要修改学号？(y/n)：";
    char ch;
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        string newId;
        cout << "请输入新学号：";
        getline(cin, newId);
        if (stuIdExists(newId)) {
            cout << "新学号已存在，学号修改失败！" << endl;
        } else {
            string oldId = p->stuId;
            p->stuId = newId;
            // 同步成绩表学号
            Score* s = scoreHead;
            while (s) {
                if (s->stuId == oldId) s->stuId = newId;
                s = s->next;
            }
            cout << "学号修改成功，已同步更新成绩表中的对应学号。" << endl;
        }
    }
    cout << "学生信息更新完成！" << endl;
}

void deleteStudent() {
    if (!stuHead) {
        cout << "暂无学生信息！" << endl;
        return;
    }
    string id;
    cout << "请输入要删除的学生学号：";
    cin >> id;

    Student *prev = nullptr, *curr = stuHead;
    while (curr && curr->stuId != id) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) {
        cout << "未找到该学号的学生！" << endl;
        return;
    }

    // 删除该生的所有成绩记录
    Score *sPrev = nullptr, *sCurr = scoreHead;
    while (sCurr) {
        if (sCurr->stuId == id) {
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
    else stuHead = curr->next;
    delete curr;
    cout << "学生信息及其所有成绩记录已删除！" << endl;
}

void listStudents() {
    if (!stuHead) {
        cout << "暂无学生信息！" << endl;
        return;
    }
    cout << left << setw(12) << "学号" << setw(12) << "姓名" << setw(6) << "性别" << setw(16) << "专业" << setw(12) << "班级" << endl;
    Student* p = stuHead;
    while (p) {
        cout << left << setw(12) << p->stuId << setw(12) << p->name << setw(6) << p->gender << setw(16) << p->major << setw(12) << p->className << endl;
        p = p->next;
    }
}

bool stuIdExists(const string& id) {
    Student* p = stuHead;
    while (p) {
        if (p->stuId == id) return true;
        p = p->next;
    }
    return false;
}

string generateStuId() {
    int maxNum = 0;
    Student* p = stuHead;
    while (p) {
        string id = p->stuId;
        if (id.length() > 1 && id[0] == 'S') {
            string numStr = id.substr(1);
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
    return "S" + numStr;
}