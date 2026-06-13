#include"StudentManager.h"
#include<set>
#include<fstream>
#include<sstream>
#include "utils.h"
#include<vector>
#include<algorithm>
void StudentManager::addStudent(){
    int id;
    std::string name;
    std::cout<<"请输入学号：";
    id=readInt();
    if(students.find(id)!=students.end()){
        std::cout<<"学号已存在!"<<std::endl;
        return ;
    }
    std::cout<<"请输入姓名:";
    std::cin>>name;
    std::map<std::string, double> scores;
    std::string course;
    double score;
    while(true){
        std::cout<<"请输入课程名(输入0结束):";
        std::cin>>course;
        if(course=="0") break;
        
        if(scores.find(course)!=scores.end()){
            std::cout<<"该课程已存在,请输入其他课程。";
            continue;
        }
        std::cout<<"请输入成绩:";
        score=readDouble();
        scores[course]=score;
    }
    Student stu(id,name,scores);
    students[id]=stu;
}
void StudentManager::removeStudent(int _id){
    if(students.find(_id)==students.end()){
        std::cout<<"学号未存在"<<std::endl;
        return ;
    }
    students.erase(_id);
}
void StudentManager::modifyStudent(int _id){
    auto it=students.find(_id);
    if(it==students.end()){
        std::cout<<"学号未存在"<<std::endl;
        return ;
    }
    std::string course;
    double newScores;
    while(true){
        std::cout<<"请输入要修改的课程(输入0结束):";
        std::cin>>course;
        if(course=="0") break;
        auto& stuScores=it->second.scores;
        if(stuScores.find(course)==stuScores.end()){
            std::cout<<"该学生没有该门课的成绩:"<<std::endl;
            continue;
        }
        std::cout<<"请输入新成绩:";
        std::cin>>newScores;
        stuScores[course]=newScores;
        std::cout<<"修改成功！"<<std::endl;
    }
}
void StudentManager::queryStudent(int _id){
    auto it=students.find(_id);
    if(it==students.end()){
        std::cout<<"学号未存在"<<std::endl;
        return ;
    }
    it->second.getid();
    it->second.getname();
    it->second.getscores();
    return ;
}
void StudentManager::displayStudent()const{
    if(students.empty()) {
        std::cout<<"当前管理系统未录入学生信息"<<std::endl;
        return ;
    }
    for(auto it=students.begin();it!=students.end();++it){
    it->second.getid();
    it->second.getname();
    it->second.getscores();
    }
}
void StudentManager::clcStatistics(){
    std::set<std::string> exist_course;
    for(auto it=students.begin();it!=students.end();++it){
        for( auto _scores=it->second.scores.begin();_scores!=it->second.scores.end();++_scores){
            exist_course.insert(_scores->first);
        }
    }
    if(exist_course.empty()){
        std::cout<<"当前系统无可课程信息"<<std::endl;
        return ;
    }
    std::cout<<"系统中有以下课程：";
    for(auto val:exist_course){
        std::cout<<val<<" ";
    }
    std::string course;
    double sum;
    int count;
    double max;
    double min;
    while(true){
        sum=0.0;
        count=0;
        max=0;
        min=1000;
        std::cout<<"请输入一个要统计的课程名(输入0结束):";
        std::cin>>course;
        if(course=="0") break;
        for(auto it=students.begin();it!=students.end();++it){
            for(auto it2=it->second.scores.begin();it2!=it->second.scores.end();++it2){
                if(it2->first==course) {
                    sum+=it2->second;
                    ++count;
                    if(it2->second>max){
                        max=it2->second;
                    }
                    if(it2->second<min){
                        min=it2->second;
                    }
                }       
            }
        }
        if(count==0){
            std::cout<<"没有学生选修该课"<<std::endl;
            continue;
        }
        std::cout<<course<<"课"<<std::endl;
        std::cout<<"平均分:"<<sum/count<<std::endl;
        std::cout<<"最高分:"<<max<<std::endl;
        std::cout<<"最低分："<<min<<std::endl;
    }
}
void StudentManager::saveToFile(){
    std::ofstream fout("save.txt");
    if(!fout.is_open()){
        std::cout<<"文件打开失败!!!\n";
        return ;
    }
    for(auto it=students.begin();it!=students.end();++it){
        fout<<it->first<<" "<<it->second.name<<" ";
        for(auto it2=it->second.scores.begin();it2!=it->second.scores.end();++it2){
            fout<<it2->first<<":"<<it2->second<<" ";
        }
        fout<<std::endl;
    }
    fout.close();
    std::cout<<"保存成功！"<<std::endl;
    return ;
}
void StudentManager::loadFromFile(){
    std::ifstream fin("save.txt");
    if(!fin.is_open()){
        std::cout<<"文件打开失败!!!\n";
        return ;
    }
    students.clear();
    std::string line;
    while(std::getline(fin,line)){
        if(line.empty()) continue;
        std::istringstream ss(line);
        int id;
        std::string name;
        ss>>id>>name;
        if(ss.fail()) continue;
        std::map<std::string,double> scores;
        std::string token;
        while(ss>>token){
            auto pos=token.find(':');
            if(pos==std::string::npos)continue;
            std::string course =token.substr(0,pos);
            double score=std::stod(token.substr(pos+1));
            scores[course]=score;
        }
        students[id]=Student(id,name,scores);

    }
    fin.close();
    std::cout<<"加载成功!共"<<students.size()<<"条记录。"<<std::endl;
 }
void StudentManager::sortByScore(){
    std::string course;
    std::cout<<"请输入要排序的课程名:";
    std::cin>>course;
    struct ScoreEntry
    {   int id;
        std::string name;
        double score;
    };
    std::vector<ScoreEntry> entries;
    for(auto & kv:students){
        auto it=kv.second.scores.find(course);
        if(it!=kv.second.scores.end()){
            entries.push_back({kv.second.id,kv.second.name,it->second});
        }
    }
    if(entries.empty()){
        std::cout<<"没有学生选修"<<course<<std::endl;
        return ;
    }
    std::sort(entries.begin(),entries.end(),
    [](const ScoreEntry& a,const ScoreEntry &b){
        return a.score>b.score;
    });
    std::cout<<course<<"成绩排名："<<std::endl;
    for(size_t i=0;i<entries.size();++i){
        std::cout<<"第"<<i+1<<"名：";
        std::cout<<"学生id:"<<entries[i].id<<" ";
        std::cout<<"学生姓名："<<entries[i].name<<" ";
        std::cout<<"学生成绩："<<entries[i].score<<std::endl;
    }
}
void StudentManager::listFailedStudents(){
    std::cout<<"请输入课程名：";
    std::string course;
    std::cin>>course;
    bool hasFailed=false;
    for(auto &it:students){
        auto it2=it.second.scores.find(course); 
        if(it2!=it.second.scores.end()&&it2->second<60){
            if(!hasFailed){
                std::cout<<"不及格学生名单："<<std::endl;
                hasFailed=true;
            }
            std::cout<<it.second.name<<"("<<it.first<<"):"<<it2->second<<"分"<<std::endl;
        }
    }
    if(!hasFailed){
        std::cout<<course<<"没有不及格学生"<<std::endl;
    }
}
void StudentManager::rankStudents(){
    struct rankEntry{
        int id;
        std::string name;
        double total;
        double avg;
        std::vector<std::string> missing;
    };
    int max=0;
    std::set<std::string> allCourses;
    auto maxStudent=students.end();
    for(auto it=students.begin();it!=students.end();++it){  
        if(max<it->second.scores.size()){
            max=it->second.scores.size();
            maxStudent=it;
        }
    }
    if(students.empty()||max==0){
        std::cout<<"没有学生数据"<<std::endl;
        return ;
    }
    std::vector<rankEntry> entries;
    for(auto &kv :students){
        double  total=0;
        for(auto& sc:kv.second.scores) total+=sc.second;
        double avg=total/kv.second.scores.size();
        std::vector<std::string> missing;
        for(auto &mc:maxStudent->second.scores){
            if(kv.second.scores.find(mc.first)==kv.second.scores.end()){
                missing.push_back(mc.first);
            }

        }
        entries.push_back({kv.first,kv.second.name,total,avg,missing});
    }
    std::cout<<"按平均分排名请输入1,按总分排名请输入2:";
    int mode=readInt();
    std::sort(entries.begin(),entries.end(),
    [mode](const rankEntry &a,const rankEntry& b){
        return mode==1?a.avg>b.avg:a.total>b.total;
    });
    for (size_t i = 0; i < entries.size(); ++i) {
        std::cout << i + 1 << ". " << entries[i].name
                << "(" << entries[i].id << ")"
              << " 总分:" << entries[i].total
              << " 平均分:" << entries[i].avg;
    if (!entries[i].missing.empty()) {
        std::cout << " 少修:";
        for (auto &m : entries[i].missing) std::cout << m << " ";
    }
    std::cout << std::endl;
}

}