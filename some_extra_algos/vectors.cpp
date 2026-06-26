#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<string> cars = {"BMW", "Lambo", "Cheron", "Ford"};
    for(string i : cars){
        cout << i << endl;
    }

    cout << endl << cars[1] << endl;
    cout << endl << cars.at(1) << endl; // often preferred over []
    // cout << endl << cars.at(6) << endl;

    // Operations not valid in c
    cars.at(3) = "Tesla";
    cars.push_back("Buggatti");

    for(string i : cars){
        cout << i << endl;
    }

    cars.pop_back(); // delete element from back
    for(string i : cars){
        cout << endl << i << endl;
    }

    cout << cars.size();

    
    return 0;
}