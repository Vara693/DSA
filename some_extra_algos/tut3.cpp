#include <iostream>
using namespace std;

class student{
    private:
    string name;
    int age;

    public:
    student(string name, int age){
        this->name = name;
        this->age = age;
    }

    void detail(){
        cout << "Name: " << this->name << ", Age: " << this-> age << endl;
    }
};
int main() {
    student s1("Nalayak", 19);
    s1.detail();

    return 0;
}