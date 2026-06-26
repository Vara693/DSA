#include <iostream>
#include <string>
using namespace std;

class teacher{ //Encapsulation: Wrapping data and member functions in a single unit called class
    //properties/attributes
    private:
        double salary; //data hiding
    public:
        string name;
        string iden;
        int age;
        string depart;

        //Constructor
        teacher(){
            cout<< "This is a Unviversity"<<endl;

        }

    //methods
    void pri(){
        cout << iden << name << " is the head of " << depart << " department.\nProbably " << age << " years old." << endl;
    }
    void chan( string newdept){
        depart = newdept;
    }
    //setter
    void setsalary(double s){
        salary = s;
    }
    //getter
    double getsalary(){
        return salary;
    }
};

int main(){
    teacher t1;
    t1.name = "Varadraj";
    t1.age  =19;
    t1.depart = "Computer sci";
    t1.iden = "Proff.";
    

    cout << "\nName: " << t1.name << endl;
    // t1.pri();

    teacher t2;
    t2.name = "Swara";
    t2.age  =19;
    t2.depart = "IT";
    t2.iden = "Proff.";

    cout << "Name: " << t2.name << endl;
    t1.chan(t2.depart);
    t1.pri();
    t2.pri();

    //getter and setter
    t1.setsalary(25000);
    cout << t1.getsalary() << endl;
    return 0;
}
