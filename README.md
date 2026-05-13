# 学生成绩管理系统

基于 C++ 命令行界面的学生成绩管理系统，采用链表数据结构实现数据的增删改查、查询统计与文件持久化。

---

## 项目结构

```
学生成绩管理系统/
├── main.cpp                 # 主入口：菜单界面、全局变量、程序主循环
├── Header file/             # 头文件目录（函数声明与数据结构定义）
│   ├── common.h             #   公共数据结构（Student/Course/Score）、全局声明、工具函数声明
│   ├── StudentMgr.h         #   学生管理模块声明
│   ├── CourseMgr.h          #   课程管理模块声明
│   ├── ScoreMgr.h           #   成绩管理模块声明
│   ├── Query.h              #   查询模块声明
│   ├── Stat.h               #   统计模块声明
│   └── FileIO.h             #   文件读写模块声明
├── Source file/             # 源文件目录（函数实现）
│   ├── common.cpp           #   工具函数实现（isNumber、toLower）
│   ├── StudentMgr.cpp       #   学生增删改查实现
│   ├── CourseMgr.cpp        #   课程增删改查实现
│   ├── ScoreMgr.cpp         #   成绩增删改查实现
│   ├── Query.cpp            #   多条件查询实现
│   ├── Stat.cpp             #   统计功能实现
│   └── FileIO.cpp           #   文件加载、保存、内存释放
├── students.txt             # 学生数据文件（程序运行时自动生成）
├── courses.txt              # 课程数据文件
├── scores.txt               # 成绩数据文件
├── grade_system.exe         # 编译产物（可执行文件）
└── .vscode/
    ├── tasks.json            # VS Code 构建/清理任务
    ├── launch.json           # 调试配置
    └── c_cpp_properties.json # C++ IntelliSense 配置
```

---

## 数据结构设计

系统核心是三个**链表**，每个节点通过 `next` 指针串联：

```
stuHead ──→ [学号|姓名|性别|专业|班级|next] ──→ [学号|姓名|性别|专业|班级|next] ──→ ... → nullptr
                   Student 节点 ①                       Student 节点 ②

courseHead ──→ [课程编号|课程名称|学分|next] ──→ [课程编号|课程名称|学分|next] ──→ ... → nullptr
                     Course 节点 ①                          Course 节点 ②

scoreHead ──→ [学号|课程编号|分数|next] ──→ [学号|课程编号|分数|next] ──→ ... → nullptr
                    Score 节点 ①                       Score 节点 ②
```

三种节点定义在 `common.h` 中：

```cpp
struct Student { string stuId, name, gender, major, className; Student* next; };
struct Course  { string courseCode, courseName; double credit; Course* next; };
struct Score   { string stuId, courseCode; int score; Score* next; };
```

---

## 程序运行流程

```
┌─────────────────────────────────────────────┐
│                  main()                      │
│  1. system("chcp 65001 > nul")  设置UTF-8   │
│  2. loadData()     从3个txt文件加载数据      │
│  3. 进入主循环：                              │
│     ┌──────────────────────────────────┐     │
│     │      showMainMenu() 显示菜单      │     │
│     │  1 → studentManageMenu() 学生管理 │     │
│     │  2 → courseManageMenu()  课程管理 │     │
│     │  3 → scoreManageMenu()   成绩管理 │     │
│     │  4 → queryMenu()         信息查询 │     │
│     │  5 → statMenu()          统计功能 │     │
│     │  6 → saveData() 退出              │     │
│     └──────────────────────────────────┘     │
│  4. saveData()     将链表数据写回3个txt文件   │
│  5. freeMemory()   释放所有链表节点内存       │
└─────────────────────────────────────────────┘
```

---

## 功能模块详解

### 1. 学生信息管理 (`StudentMgr.cpp`)

| 功能     | 函数              | 说明                                  |
| -------- | ----------------- | ------------------------------------- |
| 添加学生 | `addStudent()`    | 输入姓名/性别/专业/班级，自动生成学号 |
| 编辑学生 | `editStudent()`   | 按学号查找并修改任意字段              |
| 删除学生 | `deleteStudent()` | 按学号删除学生及其关联成绩            |
| 查看全部 | `listStudents()`  | 遍历并打印学生链表                    |
| 学号查重 | `stuIdExists()`   | 检查学号是否已存在                    |
| 生成学号 | `generateStuId()` | 自动生成格式为 `STU-001` 的唯一学号   |

### 2. 课程信息管理 (`CourseMgr.cpp`)

| 功能     | 函数             | 说明                                |
| -------- | ---------------- | ----------------------------------- |
| 添加课程 | `addCourse()`    | 输入课程名称/学分，自动生成课程编号 |
| 编辑课程 | `editCourse()`   | 按课程编号查找并修改                |
| 删除课程 | `deleteCourse()` | 按课程编号删除课程及其关联成绩      |
| 查看全部 | `listCourses()`  | 遍历并打印课程链表                  |

### 3. 成绩信息管理 (`ScoreMgr.cpp`)

| 功能      | 函数                 | 说明                         |
| --------- | -------------------- | ---------------------------- |
| 添加/修改 | `addOrUpdateScore()` | 存在则更新分数，否则新增记录 |
| 删除成绩  | `deleteScore()`      | 按学号+课程编号删除单条记录  |
| 查看全部  | `listScores()`       | 遍历并打印成绩链表           |
| 查找      | `findScore()`        | 按学号+课程编号查找成绩节点  |

### 4. 信息查询 (`Query.cpp`)

支持对三种实体进行**精确匹配**或**模糊匹配**查询：

| 查询对象 | 可检索字段                         |
| -------- | ---------------------------------- |
| 学生     | 学号、姓名、性别、专业、班级       |
| 课程     | 课程编号、课程名称                 |
| 成绩     | 学号、课程编号                     |
| 关联查询 | 按学生查课程成绩、按课程查选课学生 |

### 5. 统计功能 (`Stat.cpp`)

| 统计类型   | 输出内容                         |
| ---------- | -------------------------------- |
| 按学生统计 | 选修课程门数、平均成绩、总学分   |
| 按课程统计 | 选课人数、平均分、最高分、最低分 |
| 不及格统计 | 列出平均成绩 < 60 的所有学生     |

### 6. 文件读写 (`FileIO.cpp`)

| 函数           | 说明                                                                      |
| -------------- | ------------------------------------------------------------------------- |
| `loadData()`   | 程序启动时从 `students.txt` / `courses.txt` / `scores.txt` 读取数据到链表 |
| `saveData()`   | 选择退出时将链表数据写回三个 txt 文件                                     |
| `freeMemory()` | 释放三个链表的所有动态分配节点                                            |

**数据文件格式：**

- `students.txt`：`学号 姓名 性别 专业 班级`（每行一个学生）
- `courses.txt`：`课程编号 课程名称 学分`（每行一门课）
- `scores.txt`：`学号 课程编号 分数`（每行一条成绩）

---

## 构建与运行

### 环境要求

- **编译器**：GCC / MinGW-w64（支持 C++11 或更高版本）
- **操作系统**：Windows（程序使用了 `system("chcp 65001")` 处理控制台中文编码）
- **编辑器**：VS Code（已配置 `tasks.json`）

### 编译

在 VS Code 中按 `Ctrl+Shift+B`（或菜单 Terminal → Run Build Task）即可编译。

手动编译命令：

```bash
g++.exe -g -I "Header file" main.cpp "Source file/common.cpp" "Source file/StudentMgr.cpp" "Source file/CourseMgr.cpp" "Source file/ScoreMgr.cpp" "Source file/Query.cpp" "Source file/Stat.cpp" "Source file/FileIO.cpp" -o grade_system.exe
```

### 运行

```bash
.\grade_system.exe
```

### 清理

在 VS Code 中 `Ctrl+Shift+P` → "Run Task" → "clean"，或手动：

```bash
del grade_system.exe
```

---

## 模块依赖关系

```
main.cpp ──────┬──→ StudentMgr ────→ common.h
               ├──→ CourseMgr  ────→ common.h
               ├──→ ScoreMgr   ────→ common.h
               ├──→ Query      ────→ StudentMgr, CourseMgr, ScoreMgr
               ├──→ Stat       ────→ StudentMgr, CourseMgr, ScoreMgr
               └──→ FileIO     ────→ common.h
```

所有模块共享 `common.h` 中定义的 `Student`、`Course`、`Score` 结构体，以及三个全局链表头指针 `stuHead`、`courseHead`、`scoreHead`。

---

## 设计要点

1. **链表存储**：所有数据在内存中以单向链表组织，插入在头部完成（O(1)），查找需遍历（O(n)）
2. **文件持久化**：启动时加载、退出时保存，数据不会因程序关闭而丢失
3. **关联一致性**：删除学生时自动删除其所有成绩；删除课程时自动删除相关成绩
4. **中文支持**：程序启动时自动将控制台切换为 UTF-8 编码（`chcp 65001`），确保中文菜单和数据正常显示
5. **生成式 ID**：学生学号（`STU-001` 格式）和课程编号（`C-001` 格式）根据已有数据自动递增生成

---

