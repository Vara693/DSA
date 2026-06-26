#include <iostream>
using namespace std;

class rectangle{
    private:
        float length;
        float width;

    public:
        //constrator
        rectangle(float l, float w){
            length = l;
            width = w;
        }



    float area(){
        return length*width;
    }
    float perimeter(){
        return 2*(length + width);
    }
};

int main() {
    float l, w;
    cout << "Enter length: ";
    cin >> l;
    cout << "Enter width: ";
    cin >> w;

    rectangle r1(l,w);


    cout << "Area: " << r1.area() << endl;
    cout << "Perimeter: " << r1.perimeter() << endl; 

    
    return 0;
}