#ifndef CLASS_CPP
#define CLASS_CPP
#include"class.h"
#include<iomanip>
#include<sstream>
Student::Student(int _id,std::string _name,const std::map<std::string,double>& _scores)
:id(_id),name(_name),scores(_scores){}
void Student::getid()const{
    std::cout<<"学生id:"<<id<<std::endl;
}
void Student::getname()const{
    std::cout<<"学生姓名:"<<name<<std::endl;
}
void Student::getscores()const{
    for(auto it=scores.begin();it!=scores.end();++it){
        std::cout<<"课程："<<it->first<<" 成绩："<<it->second<<std::endl;
    }
}
void Student::display()const{
    std::cout<<std::left<<std::setw(8)<<id
             <<std::setw(12)<<name;
    for(const auto& it:scores){
        std::ostringstream oss;
        oss<<std::fixed<<std::setprecision(1)<<it.second;
        std::cout<<std::setw(16)<<(it.first+":"+oss.str());
    }
    std::cout<<std::right<<std::endl;
}
void Student::setid(int new_id){
    this->id=new_id;
}
void Student::setname(std::string new_name){
    this->name=new_name;
}
void Student::setscores(std::map<std::string,double> new_scores){
    this->scores=new_scores;
}
#endif