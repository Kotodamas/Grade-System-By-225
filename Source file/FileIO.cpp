// 负责人 吴子恒

#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

extern Student* stuHead;
extern Course* courseHead;
extern Score* scoreHead;

void loadData() {
    ifstream stuFile("students.txt");
    if (stuFile.is_open()) {
        string line;
        while (getline(stuFile, line)) {
            stringstream ss(line);
            Student* s = new Student;
            ss >> s->stuId >> s->name >> s->gender >> s->major >> s->className;
            s->next = stuHead;
            stuHead = s;
        }
        stuFile.close();
    }
    ifstream courseFile("courses.txt");
    if (courseFile.is_open()) {
        string line;
        while (getline(courseFile, line)) {
            stringstream ss(line);
            Course* c = new Course;
            ss >> c->courseCode >> c->courseName >> c->credit;
            c->next = courseHead;
            courseHead = c;
        }
        courseFile.close();
    }
    ifstream scoreFile("scores.txt");
    if (scoreFile.is_open()) {
        string line;
        while (getline(scoreFile, line)) {
            stringstream ss(line);
            Score* s = new Score;
            ss >> s->stuId >> s->courseCode >> s->score;
            s->next = scoreHead;
            scoreHead = s;
        }
        scoreFile.close();
    }
    cout << "数据加载完成。" << endl;
}

void saveData() {
    ofstream stuFile("students.txt");
    Student* p = stuHead;
    while (p) {
        stuFile << p->stuId << " " << p->name << " " << p->gender << " " << p->major << " " << p->className << endl;
        p = p->next;
    }
    stuFile.close();

    ofstream courseFile("courses.txt");
    Course* c = courseHead;
    while (c) {
        courseFile << c->courseCode << " " << c->courseName << " " << c->credit << endl;
        c = c->next;
    }
    courseFile.close();

    ofstream scoreFile("scores.txt");
    Score* s = scoreHead;
    while (s) {
        scoreFile << s->stuId << " " << s->courseCode << " " << s->score << endl;
        s = s->next;
    }
    scoreFile.close();
    cout << "数据保存完成。" << endl;
}

void freeMemory() {
    while (stuHead) {
        Student* t = stuHead;
        stuHead = stuHead->next;
        delete t;
    }
    while (courseHead) {
        Course* t = courseHead;
        courseHead = courseHead->next;
        delete t;
    }
    while (scoreHead) {
        Score* t = scoreHead;
        scoreHead = scoreHead->next;
        delete t;
    }
}