#include "ugyfel.hpp"

using namespace std;

int main(){
    fstream ugyfelek;
    ugyfelek.open("ugyfelek.csv", ios::in | ios::out | ios::app);
    Ugyfel u;
    u.generateNumber(ugyfelek);
    cout << u.getTelefon() << endl;
    u.generateNumber(ugyfelek);
    cout << u.getTelefon() << endl;
    ugyfelek.close();
    u.generateNumber(ugyfelek);
    cout << u.getTelefon() << endl;
    return 0;
}
