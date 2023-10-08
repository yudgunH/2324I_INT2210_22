#include <iostream>
#include <map>
using namespace std;

struct Student {
     string name;
     string class_name;
};

map<int, Student> students;

void Insert(int ID,  string Name,  string Class) {
    students[ID] = {Name, Class};
}

void Delete(int ID) {
    students.erase(ID);
}

void Infor(int ID) {
    if (students.find(ID) != students.end()) {
        cout << students[ID].name + "," + students[ID].class_name << endl;
    } else {
        cout << "NA,NA" << endl;
    }
}

int main() {
    // Test the functions
    Insert(1,"Tuan","K61CS");
    Insert(2,"Vinh","K43C");
    Infor(3);
    Infor(2);
    Delete(2);
    Infor(2);
    return 0;
}
