#include <iostream>
#include <cstring>
using namespace std;

class Om
{
    protected:
    char* nume;
    int varsta;
    float greutate;
    public:
    //constructor implicit
    Om() : nume(NULL), varsta(0), greutate(0.0) {}

    //constructor parametrizat
    Om(const char* nume, int varsta, float greutate) : varsta(varsta), greutate(greutate)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
    }

    //destructor
    ~Om()
    {
        if (nume != NULL)
        {
            delete[] nume;
            nume = NULL;
        }
    }

    //supraincarcarea operatorului de atribuire
    Om& operator=(const Om &om)
    {
        if (this != &om)
        {
            delete[] nume;
            nume = new char[strlen(om.nume) + 1];
            strcpy_s(nume, strlen(om.nume) + 1, om.nume);
            varsta = om.varsta;
            greutate = om.greutate;
        }
        return *this;
    }

    //functie pentru resetarea varstei
    void reseteazaVarsta(int varstaNoua) { varsta = varstaNoua; }

    //afisarea datelor
    friend ostream& operator<<(ostream& out, const Om& om)
    {
        return out << "\nNume: " << om.nume << "\nVarsta: " << om.varsta << "\nGreutate: " << om.greutate << endl;
        //return out;
    }
};

class Matur : public Om
{
    string nr_pasaport;
    public:
        //constructor implicit
        Matur() : nr_pasaport() {}

        //constructor parametrizat
        Matur(const char* nume, int varsta, float greutate, string nr_pasaport) : Om(nume, varsta, greutate), nr_pasaport(nr_pasaport) {}

        //destructor
        ~Matur() {}

        //functie pentru resetarea numarului de pasaport
        void resetareNr_Pasaport(string numarNou) { nr_pasaport = numarNou; }

        //afisarea datelor
        friend ostream& operator<<(ostream& out, const Matur& omMatur)
        {
            return out << "\nNume: " << omMatur.nume << "\nVarsta: " << omMatur.varsta << "\nGreutate: " << omMatur.greutate << "\nNumar pasaport: " << omMatur.nr_pasaport << endl;
        }
};

int main()
{
    Om persoana("Ion", 20, 75.5);
    cout << persoana;
    Om persoana2;
    persoana2 = persoana;
    cout << persoana2;

    Matur persoanaM("Valeriu", 28, 80.5, "AD123456");
    cout << persoanaM;

    persoana.reseteazaVarsta(43);
    cout << persoana;

    persoanaM.reseteazaVarsta(30);
    persoanaM.resetareNr_Pasaport("AB432533");
    cout << persoanaM;

    return 0;
}