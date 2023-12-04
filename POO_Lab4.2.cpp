#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vaca
{
    int id; 
    static int count;
    double cantMedLapte;
    int varsta;
    string *nume;
    string *rasa;

    public:
        //constructor parametrizat
        Vaca(const string& nume, const string& rasa, int varsta, double cantMedLapte) :
            varsta(varsta), cantMedLapte(cantMedLapte)
        {
            id = ++count; //incrementarea si atribuirea id-ului unic
            //alocarea dinamica pentru nume si rasa
            this->nume = new string(nume);
            this->rasa = new string(rasa);
        }
        
        //constructor de copiere
        Vaca(const Vaca& other)
        {
            id = other.id;
            cantMedLapte = other.cantMedLapte;
            varsta = other.varsta;
            nume = new string(*other.nume);
            rasa = new string(*other.rasa);
        }

        //destructor
        ~Vaca()
        {
            delete nume;
            delete rasa;
        }
        
        //supraincarcarea operatorului de atribuire
        Vaca& operator=(const Vaca& other)
        {
            if (this != &other)
            {
                //elibereaza memoria existenta si dupa copie datele noi
                delete nume;
                delete rasa;
                id = other.id;
                cantMedLapte = other.cantMedLapte;
                varsta = other.varsta;
                nume = new string(*other.nume);
                rasa = new string(*other.rasa);
            }
            return *this;
        }

        //functie pentru obtinerea cantitatii de lapte
        double getCantMedLapte() { return cantMedLapte; }

        //functie de obtinere a numarului total de vaci
        int getCount() { return count; }
        
        //functie de resetare a numarului total de vaci
        void resetCount() { count = 0; }

        //functie pentru obtinerea id-ului unic al vacii
        int getId() { return id; }
};

int Vaca::count = 0; //initializarea variabilei statice

class Cireada
{
    vector<Vaca> vaci; //vector de obiecte

    public:
        //functie pentru adaugarea unei vaci in cireada
        void adaugaVaca(const Vaca& vaca) { vaci.push_back(vaca); }
        
        //functie pentru eliminarea unei vaci din cireada
        void eliminaVaca(int id)
        {
            for (int i = 0; i < vaci.size(); i++)
            {
                if (vaci[i].getId() == id)
                {
                    vaci.erase(vaci.begin() + i);
                    break;
                }
            }
        }

        //functie pentru calcularea cantitatii totale de lapte
        void cantMedTotala()
        {
            double total = 0.0;
            for (auto &vaca : vaci)
            {
                total += vaca.getCantMedLapte();
            }
            cout << "Cantitatea medie totala de lapte: " << total << endl;
        }

        //functie de afisare a numarului total de vaci
        void numarVaci()
        {
            cout << "Numarul total de vaci: " << vaci.size() << endl;
        }
};

int main()
{
    Vaca Florita("Florita", "Holstein", 2, 9.2);
    Vaca Daisy("Daisy", "Simmental", 3, 7.5);
    Vaca Bella("Bella", "Holstein", 4, 10.3);
    Vaca Felicia("Felicia", "Hereford", 3, 8.6);
    cout << "Cantitatea medie de lapte a vacutei Daisy: " << Daisy.getCantMedLapte() << "\n\n";
    Cireada cireada;
    cireada.adaugaVaca(Florita);
    cireada.adaugaVaca(Daisy);
    cireada.adaugaVaca(Bella);
    cireada.adaugaVaca(Felicia);

    cireada.numarVaci();
    cireada.cantMedTotala();

    cireada.eliminaVaca(1);

    cireada.numarVaci();
    cireada.cantMedTotala();
    return 0;
}