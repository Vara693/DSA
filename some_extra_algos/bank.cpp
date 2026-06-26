#include <iostream>
using namespace std;

class customer{
    private:
    string name;
    int customer_id;
    public:
    customer(string n, int id){
        name = n;
        customer_id = id;
    }
    void display_customer(){
        cout << "Name: " << name << endl;
        cout << "Customer ID: " << customer_id << endl;
    }
    int get_id(){
        return customer_id;
    }

};

class account{
    private:
    int acc_no;
    double bakance;
    customer cust;

    public:
    account(int accno, double bal, customer crust):cust(crust){

    }
    
};
int main() {

    return 0;
}