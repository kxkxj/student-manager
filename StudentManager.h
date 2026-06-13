#include"class.h"
class StudentManager{
private:
    std::map<int,Student> students;
public:
    void addStudent();
    void removeStudent(int _id);
    void modifyStudent(int _id);
    void queryStudent(int _id);
    void displayStudent()const;
    void clcStatistics();
    void saveToFile(); 
    void loadFromFile();
    void sortByScore();
    void listFailedStudents();
    void rankStudents();
};