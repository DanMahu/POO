#include <iostream>
#include <vector>
#include <string>
using namespace std;

//clasa abstracta de baza
class Figure {
public:
    virtual double perimetru() = 0; //functie virtuala pura
    virtual string getType() = 0; //functie virtuala pura pentru a returna tipul figurii
    virtual ~Figure() {} //destructor virtual
};

//clasele derivate
class Rectangle : public Figure {
    double lungime, latime;
    public:
    //constructor parametrizat
    Rectangle(double lungime = 1.0, double latime = 1.0) : lungime(lungime), latime(latime) {}
    
    string getType() { return "Dreptunghi"; }

    ~Rectangle() {} //destructor

    //functie de calculare a perimetrului dreptunghiului
    double perimetru() { return 2 * (lungime + latime); }
};

class Circle : public Figure {
    double R;
    public:
    //constructor parametrizat
    Circle(double R = 1.0) : R(R) {}

    string getType() { return "Cerc"; }

    ~Circle() {}

    //functie de calculare a perimetrului cercului
    double perimetru() { return 2 * 3.14 * R; }
};

class Triangle : public Figure {
    double l1, l2, l3;
    public:
    //constructor parametrizat
    Triangle(double l1 = 1.0, double l2 = 1.0, double l3 = 1.0) : l1(l1), l2(l2), l3(l3) {}

    string getType() { return "Triunghi"; }

    ~Triangle() {}

    //functie de calculare a perimetrului triunghiului
    double perimetru() { return l1 + l2 + l3; }
};

class Rhomb : public Figure {
    double l;
    public:
    //constructor parametrizat
    Rhomb(double l = 1.0) : l(l) {}

    string getType() { return "Romb"; }

    ~Rhomb() {}

    //functie de calculare a perimetrului rombului
    double perimetru() { return 4 * l; }
};

int main() {
    //vector de pointeri catre clasa abstracta Figure
    vector<Figure*> figuri;

    Rectangle dreptunghi(3.5, 6.9);
    Circle cerc(5.5);
    Triangle triunghi(2.5, 4.0, 6.6);
    Rhomb romb(7.0);
    Triangle triunghi1;
    Rectangle dreptunghi1;

    //adaugarea adreselor obiectelor in vectorul de pointeri
    figuri.push_back(&dreptunghi);
    figuri.push_back(&cerc);
    figuri.push_back(&triunghi);
    figuri.push_back(&romb);
    figuri.push_back(&triunghi1);
    figuri.push_back(&dreptunghi1);


    //calcularea perimetrelor pentru fiecare obiect prin pointerii din vector
    for (auto& figura : figuri) {
        cout << "Perimetru " << figura->getType() << ": " << figura->perimetru() << endl;
    }
    return 0;
}
