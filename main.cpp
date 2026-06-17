#include "StudentManager.h"
#include "utils.h"
#include <windows.h>

enum MenuChoice {
    EXIT = 0,
    ADD_STUDENT,
    REMOVE_STUDENT,
    MODIFY_STUDENT,
    QUERY_STUDENT,
    DISPLAY_ALL,
    STATISTICS,
    SAVE_TO_FILE,
    LOAD_FROM_FILE,
    SORT_BY_SCORE,
    LIST_FAILED,
    RANK_STUDENTS
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    StudentManager manager;
    manager.loadFromFile();

    int choice, id;
    while (true) {
        std::cout << "\n=== 学生成绩管理系统 ===\n";
        std::cout << "1. 添加学生\n";
        std::cout << "2. 删除学生\n";
        std::cout << "3. 修改学生成绩\n";
        std::cout << "4. 查询学生\n";
        std::cout << "5. 显示所有学生\n";
        std::cout << "6. 课程统计\n";
        std::cout << "7. 保存到文件\n";
        std::cout << "8. 从文件加载\n";
        std::cout << "9. 按课程成绩排序\n";
        std::cout << "10. 不及格学生名单\n";
        std::cout << "11. 成绩排名\n";
        std::cout << "0. 退出\n";
        std::cout << "请选择：";
        choice = readInt();

        switch (choice) {
        case ADD_STUDENT:
            manager.addStudent();
            break;
        case REMOVE_STUDENT:
            std::cout << "请输入学号：";
            id = readInt();
            manager.removeStudent(id);
            break;
        case MODIFY_STUDENT:
            std::cout << "请输入学号：";
            id = readInt();
            manager.modifyStudent(id);
            break;
        case QUERY_STUDENT:
            std::cout << "请输入学号：";
            id = readInt();
            manager.queryStudent(id);
            break;
        case DISPLAY_ALL:
            manager.displayStudent();
            break;
        case STATISTICS:
            manager.clcStatistics();
            break;
        case SAVE_TO_FILE:
            manager.saveToFile();
            break;
        case LOAD_FROM_FILE:
            manager.loadFromFile();
            break;
        case SORT_BY_SCORE:
            manager.sortByScore();
            break;
        case LIST_FAILED:
            manager.listFailedStudents();
            break;
        case RANK_STUDENTS:
            manager.rankStudents();
            break;
        case EXIT:
            manager.saveToFile();
            std::cout << "已保存，再见！\n";
            return 0;
        default:
            std::cout << "无效选项，请重新输入！\n";
            break;
        }
    }
}