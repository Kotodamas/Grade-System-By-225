#include "common.h"
#include "StudentMgr.h"
#include "CourseMgr.h"
#include "ScoreMgr.h"
#include "Query.h"
#include "Stat.h"
#include "FileIO.h"
#include <iostream>
using namespace std;

// 全局链表头指针定义（唯一实例）
Student* stuHead = nullptr;
Course* courseHead = nullptr;
Score* scoreHead = nullptr;

void showMainMenu() {
    cout << "\n=== 学生成绩管理系统 ===\n";
    cout << "1. 学生信息管理\n";
    cout << "2. 课程信息管理\n";
    cout << "3. 成绩信息管理\n";
    cout << "4. 信息查询\n";
    cout << "5. 统计功能\n";
    cout << "6. 保存数据并退出\n";
    cout << "请选择操作：";
}

void studentManageMenu() {
    int choice;
    do {
        cout << "\n--- 学生信息管理 ---\n";
        cout << "1. 添加学生\n2. 编辑学生\n3. 删除学生\n4. 查看所有学生\n5. 返回主菜单\n";
        cout << "请选择：";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: deleteStudent(); break;
            case 4: listStudents(); break;
            case 5: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 5);
}

void courseManageMenu() {
    int choice;
    do {
        cout << "\n--- 课程信息管理 ---\n";
        cout << "1. 添加课程\n2. 编辑课程\n3. 删除课程\n4. 查看所有课程\n5. 返回主菜单\n";
        cout << "请选择：";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: addCourse(); break;
            case 2: editCourse(); break;
            case 3: deleteCourse(); break;
            case 4: listCourses(); break;
            case 5: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 5);
}

void scoreManageMenu() {
    int choice;
    do {
        cout << "\n--- 成绩信息管理 ---\n";
        cout << "1. 添加/修改成绩\n2. 删除成绩\n3. 查看所有成绩\n4. 返回主菜单\n";
        cout << "请选择：";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: addOrUpdateScore(); break;
            case 2: deleteScore(); break;
            case 3: listScores(); break;
            case 4: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 4);
}

void queryMenu() {
    int choice;
    do {
        cout << "\n--- 信息查询 ---\n";
        cout << "1. 查询学生信息\n2. 查询课程信息\n3. 查询成绩信息\n";
        cout << "4. 按学生检索课程成绩\n5. 按课程检索学生信息\n6. 返回主菜单\n";
        cout << "请选择：";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: queryStudent(); break;
            case 2: queryCourse(); break;
            case 3: queryScore(); break;
            case 4: queryStudentCourses(); break;
            case 5: queryCourseStudents(); break;
            case 6: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 6);
}

void statMenu() {
    int choice;
    do {
        cout << "\n--- 统计功能 ---\n";
        cout << "1. 按学生统计（课程门数、平均成绩、总学分）\n";
        cout << "2. 按课程统计（人数、平均、最高、最低）\n";
        cout << "3. 统计平均成绩不及格的学生\n";
        cout << "4. 返回主菜单\n";
        cout << "请选择：";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: statByStudent(); break;
            case 2: statByCourse(); break;
            case 3: statFailingStudents(); break;
            case 4: break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 4);
}

int main() {
    loadData();
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: studentManageMenu(); break;
            case 2: courseManageMenu(); break;
            case 3: scoreManageMenu(); break;
            case 4: queryMenu(); break;
            case 5: statMenu(); break;
            case 6: saveData(); break;
            default: cout << "无效选择！" << endl;
        }
    } while (choice != 6);
    freeMemory();
    cout << "系统已退出。" << endl;
    return 0;
}