#include <iostream>
#include <string>
using namespace std;

class Divan
{
	protected:
		string stare;
		double lungime;
		//constructor parametrizat
		Divan(string stare = "", double lungime = 0.0) : stare(stare), lungime(lungime) {}
		
		//destructor
		~Divan() {}
	public:
		void afisareStare()
		{
			cout << "Divanul este intr-o stare " << stare << "." << endl;
		}

		void afisareLungime()
		{
			cout << "Divanul are o lungime de " << lungime << " m." << endl;
		}
};

class Pat
{
	protected:
		string culoare;
		//constructor parametrizat
		Pat(string culoare = "") : culoare(culoare) {}

		//destructor
		~Pat() {}
	public:
		void afisareCuloare()
		{
			cout << "Patul are culoarea " << culoare << "." << endl;
		}

		void asezare()
		{
			cout << "Asezare pe pat!" << endl;
		}
};

class Divan_Pat: public Divan, public Pat
{
	public:
		//constructor parametrizat
		Divan_Pat(string stare, double lungime, string culoare) : Divan(stare, lungime), Pat(culoare) {}
		
		//destructor
		~Divan_Pat() {}

		void relaxare()
		{
			cout << "Relaxare pe Divan-Pat!" << endl;
		}
};

int main() {
	Divan_Pat ex("deplorabila", 2.5, "maro");
	ex.afisareStare();
	ex.afisareLungime();
	ex.afisareCuloare();
	ex.asezare();
	ex.relaxare();
	return 0;
}