#ifndef CLASS_H
#define CLASS_H
#include<iostream>
#include<string>
#include<map>
class Student{
private:
    int id;
    std::string name;
    std::map<std::string,double> scores;
public:
    Student()=default;
    Student(int _id,std::string _name,const std::map<std::string,double>& _scores);
    void getid()const;
    void getname()const;
    void getscores()const;
    void display()const;
    void setid(int new_id);
    void setname(std::string new_name);
    void setscores(std::map<std::string,double> new_scores);
    friend class StudentManager;
};

#endif