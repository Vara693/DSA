#include <iostream>
using namespace std;

class complex{
    private:
    float real;
    float imag;

    public:
    complex(float r=0, float i=0){
        real = r;
        imag = i;
    }

    friend complex operator+(complex c1, complex c2);
    friend complex operator-(complex c1, complex c2);

    void display() {
        cout << real << "+" << imag << "i" << endl;
    }
};

complex operator+(complex c1, complex c2){
    return complex(c1.real + c2.real, c1.imag + c2.imag);
}

complex operator-(complex c1, complex c2){
    return complex(c1.real - c2.real, c1.imag - c2.imag);
}

int main() {

    return 0;
}