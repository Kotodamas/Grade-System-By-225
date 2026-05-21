#include "Query.h"
#include "StudentMgr.h"
#include "CourseMgr.h"
#include "ScoreMgr.h"
#include <iostream>
using namespace std;

extern Student* stuHead;
extern Course* courseHead;
extern Score* scoreHead;

void queryStudent() {
    if (!stuHead) {
        cout << "暂无学生信息！" << endl;
        return;
    }
    cout << "查询方式：\n1. 学号\n2. 姓名\n3. 性别\n4. 专业\n5. 班级\n请选择：";
    int type; cin >> type; cin.ignore();
    string keyword; bool exact;
    cout << "查询类型：\n1. 精确匹配\n2. 模糊匹配\n请选择：";
    int exactChoice; cin >> exactChoice; cin.ignore();
    exact = (exactChoice == 1);
    cout << "请输入查询关键字："; getline(cin, keyword);

    Student* p = stuHead;
    bool found = false;
    while (p) {
        bool match = false;
        switch(type) {
            case 1: match = exact ? (p->stuId == keyword) : (p->stuId.find(keyword) != string::npos); break;
            case 2: match = exact ? (p->name == keyword) : (p->name.find(keyword) != string::npos); break;
            case 3: match = exact ? (p->gender == keyword) : (p->gender.find(keyword) != string::npos); break;
            case 4: match = exact ? (p->major == keyword) : (p->major.find(keyword) != string::npos); break;
            case 5: match = exact ? (p->className == keyword) : (p->className.find(keyword) != string::npos); break;
        }
        if (match) {
            if (!found) {
                cout << left << setw(12) << "学号" << setw(12) << "姓名" << setw(6) << "性别" << setw(16) << "专业" << setw(12) << "班级" << endl;
                found = true;
            }
            cout << left << setw(12) << p->stuId << setw(12) << p->name << setw(6) << p->gender << setw(16) << p->major << setw(12) << p->className << endl;
        }
        p = p->next;
    }
    if (!found) cout << "未找到匹配的学生信息。" << endl;
}

void queryCourse() {
    if (!courseHead) {
        cout << "暂无课程信息！" << endl;
        return;
    }
    cout << "查询方式：\n1. 课程代码\n2. 课程名称\n3. 学分\n请选择：";
    int type; cin >> type; cin.ignore();
    string keyword; bool exact;
    cout << "查询类型：\n1. 精确匹配\n2. 模糊匹配\n请选择：";
    int exactChoice; cin >> exactChoice; cin.ignore();
    exact = (exactChoice == 1);
    cout << "请输入查询关键字："; getline(cin, keyword);

    Course* p = courseHead;
    bool found = false;
    while (p) {
        bool match = false;
        switch(type) {
            case 1: match = exact ? (p->courseCode == keyword) : (p->courseCode.find(keyword) != string::npos); break;
            case 2: match = exact ? (p->courseName == keyword) : (p->courseName.find(keyword) != string::npos); break;
            case 3: {
                double cred = stod(keyword);
                match = (p->credit == cred);
                if (!exact && p->credit > cred-0.5 && p->credit < cred+0.5) match = true;
                break;
            }
        }
        if (match) {
            if (!found) cout << left << setw(12) << "课程代码" << setw(20) << "课程名称" << setw(6) << "学分" << endl;
            cout << left << setw(12) << p->courseCode << setw(20) << p->courseName << setw(6) << p->credit << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) cout << "未找到匹配的课程信息。" << endl;
}

void queryScore() {
    if (!scoreHead) {
        cout << "暂无成绩记录！" << endl;
        return;
    }
    cout << "查询方式：\n1. 学号\n2. 课程代码\n3. 姓名（仅精确）\n4. 课程名称（仅精确）\n请选择：";
    int type; cin >> type; cin.ignore();
    if (type == 1 || type == 2) {
        string key;
        cout << "请输入关键字："; getline(cin, key);
        Score* p = scoreHead;
        bool found = false;
        while (p) {
            if ((type == 1 && p->stuId == key) || (type == 2 && p->courseCode == key)) {
                if (!found) cout << left << setw(12) << "学号" << setw(12) << "课程代码" << setw(6) << "成绩" << endl;
                cout << left << setw(12) << p->stuId << setw(12) << p->courseCode << setw(6) << p->score << endl;
                found = true;
            }
            p = p->next;
        }
        if (!found) cout << "未找到匹配的成绩记录。" << endl;
    } else if (type == 3) {
        string name; cout << "请输入学生姓名："; getline(cin, name);
        Student* stu = stuHead;
        while (stu && stu->name != name) stu = stu->next;
        if (!stu) {
            cout << "未找到该姓名的学生。" << endl;
            return;
        }
        string stuId = stu->stuId;
        Score* p = scoreHead;
        bool found = false;
        while (p) {
            if (p->stuId == stuId) {
                if (!found) cout << left << setw(12) << "学号" << setw(12) << "课程代码" << setw(6) << "成绩" << endl;
                cout << left << setw(12) << p->stuId << setw(12) << p->courseCode << setw(6) << p->score << endl;
                found = true;
            }
            p = p->next;
        }
        if (!found) cout << "该学生暂无成绩记录。" << endl;
    } else if (type == 4) {
        string cname; cout << "请输入课程名称："; getline(cin, cname);
        Course* c = courseHead;
        while (c && c->courseName != cname) c = c->next;
        if (!c) {
            cout << "未找到该名称的课程。" << endl;
            return;
        }
        string code = c->courseCode;
        Score* p = scoreHead;
        bool found = false;
        while (p) {
            if (p->courseCode == code) {
                if (!found) cout << left << setw(12) << "学号" << setw(12) << "课程代码" << setw(6) << "成绩" << endl;
                cout << left << setw(12) << p->stuId << setw(12) << p->courseCode << setw(6) << p->score << endl;
                found = true;
            }
            p = p->next;
        }
        if (!found) cout << "该课程暂无成绩记录。" << endl;
    } else {
        cout << "无效选择。" << endl;
    }
}

void queryStudentCourses() {
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
    cout << left << setw(12) << "学号" << setw(12) << "姓名" << setw(20) << "课程名称" << setw(6) << "成绩" << endl;
    Score* s = scoreHead;
    bool hasScore = false;
    while (s) {
        if (s->stuId == stu->stuId) {
            Course* c = courseHead;
            while (c && c->courseCode != s->courseCode) c = c->next;
            string cname = c ? c->courseName : "未知课程";
            cout << left << setw(12) << stu->stuId << setw(12) << stu->name << setw(20) << cname << setw(6) << s->score << endl;
            hasScore = true;
        }
        s = s->next;
    }
    if (!hasScore) cout << "该学生尚无成绩记录。" << endl;
}

void queryCourseStudents() {
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
    cout << left << setw(12) << "学号" << setw(12) << "姓名" << setw(16) << "专业" << setw(12) << "班级" << setw(6) << "成绩" << endl;
    Score* s = scoreHead;
    bool hasScore = false;
    while (s) {
        if (s->courseCode == course->courseCode) {
            Student* stu = stuHead;
            while (stu && stu->stuId != s->stuId) stu = stu->next;
            if (stu) {
                cout << left << setw(12) << stu->stuId << setw(12) << stu->name << setw(16) << stu->major << setw(12) << stu->className << setw(6) << s->score << endl;
                hasScore = true;
            }
        }
        s = s->next;
    }
    if (!hasScore) cout << "该课程尚无成绩记录。" << endl;
}