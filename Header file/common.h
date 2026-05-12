#ifndef COMMON_H
#define COMMON_H
//lxzmjj
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstdlib>

using namespace std;

// 数据结构定义
struct Student {
    string stuId;
    string name;
    string gender;
    string major;
    string className;
    Student* next;
};

struct Course {
    string courseCode;
    string courseName;
    double credit;
    Course* next;
};

struct Score {
    string stuId;
    string courseCode;
    int score;
    Score* next;
};

// 全局链表头指针（声明，定义在 main.cpp）
extern Student* stuHead;
extern Course* courseHead;
extern Score* scoreHead;

// 通用辅助函数
bool isNumber(const string& s);
string toLower(string s);

#endif