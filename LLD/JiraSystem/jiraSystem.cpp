#include <iostream>
#include <vector>
#include <string>
using namespace std;


enum TaskType {STORY, FEATURE, BUG};
enum TaskStatus {OPEN, IN_PROGRESS, RESOLVED, DELAYED, COMPLETED};

class Task;

class Sprint {
    int begin, end;
    string name;
    vector<Task> tasks;
public:
    Sprint(int, int, string);
    const vector<Task>& getTasks() const;
    void addTask(Task&);
    void printDetails();
    bool operator==(Sprint&);
    void eraseTask(int taskIndex);
};


class User {
    vector<Task> taskList;   // task created
    vector<Sprint> sprintList;  // associated with
public:
    Task createTask(TaskType);  
    Task createTask(string);  // for story
    Sprint createSprint(int, int, string);
    bool addToSprint(Sprint&, Task&);
    bool removeFromSprint(Sprint&, Task&);
    bool changeStatus(Task&, TaskStatus);
    void printAllTasks();
};


class Task {
    int id;  // auto increment id
    string subtract;
    User user;
    TaskType taskType;
    TaskStatus taskStatus;
    int getUniqueId();
public:
    Task();
    int getId();
    void setTaskType(TaskType);
    void setTaskStatus(TaskStatus);
    void setSubtract(const string);
    void setUser(User);
    bool operator==(Task&);
};

Sprint::Sprint(int begin, int end, string name){
    this->begin = begin;
    this->end = end;
    this->name = name;
}

void Sprint::addTask(Task& task){
    this->tasks.push_back(task);
}

const vector<Task>& Sprint::getTasks() const {
    return this->tasks;
}

void Sprint::printDetails(){
    cout<<"Sprint Name: "<<this->name <<"\nSprint Begins: "<<this->begin<<"\nSprint Ends: "<<this->end<<endl;
}

inline bool Sprint::operator==(Sprint& sprint){
    return (this->begin == sprint.begin) && (this->end == sprint.end) && (this->name == sprint.name);
}

void Sprint::eraseTask(int taskIndex){
    tasks.erase(tasks.begin()+taskIndex);
}

Task User::createTask(TaskType taskType){
    if(taskType != TaskType::STORY){
        cout<<"Warning! Task of type STORY is being created with no subtract.\n";
    }
    Task task;
    task.setTaskType(taskType);
    task.setUser(*this);  // IMP
    this->taskList.push_back(task);
    return task;
}
// overloaded function for handling the story type
Task User::createTask(string subtract){
    Task task;
    task.setTaskType(TaskType::STORY);
    task.setSubtract(subtract);
    task.setUser(*this);
    this->taskList.push_back(task);
    return task;
}

Sprint User::createSprint(int begin, int end, string name){
    Sprint sprint(begin, end, name);
    this->sprintList.push_back(sprint);
    return sprint;
}

// first check if user has created the given sprint only then can add task.
bool User::addToSprint(Sprint& sprint, Task& task) { 
    for(Sprint& spr : sprintList){
        if(spr == sprint){   // operator implemenation
            sprint.addTask(task);
            return true;
        }
    }
    return false;
}

bool User::removeFromSprint(Sprint& sprint, Task& task) {
    int i = 0;
    for(Sprint& spr : sprintList) {
        if(spr == sprint){
            i = 0;
            for(Task t: sprint.getTasks()){
                if(t == task){  // IMP check for the errors
                    sprint.eraseTask(i);
                    return true;
                }
                ++i;
            }
        }
    }
    return false;
}

bool User::changeStatus(Task& task, TaskStatus taskStatus){
    for(Task &t : taskList){
        if(t == task){
            task.setTaskStatus(taskStatus);
            return true;
        }
    }
    return false;
}

void User::printAllTasks() {
    for(Task& task : this->taskList){
        cout<<"Task id: "<<task.getId()<<" ";
    }
    cout<<endl;
}

int Task::getUniqueId() {   // auto increment id 
    static int taskId = 1;
    return taskId++;
}

Task::Task() {
    this->id = getUniqueId();
    this->taskStatus = TaskStatus::OPEN;
}

int Task::getId(){
    return this->id;
}

void Task::setUser(User user){
    this->user = user;
}

void Task::setSubtract(const string subtract){
    this->subtract = subtract;
}

void Task::setTaskType(TaskType taskType){
    this->taskType = taskType;
}

void Task::setTaskStatus(TaskStatus taskStatus){
    this->taskStatus = taskStatus;
}

bool Task::operator==(Task& task){
    return this->getId() == task.getId();
}

int main(){
    cout<<"Jira Tracker!\n";
    
    return 0;
}