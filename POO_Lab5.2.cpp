#include <iostream>
#include <string>
using namespace std;

class Mobila
{
	string material;
	double lungime;
	double latime;
	protected:
		//constructor parametrizat
		Mobila(string material, double lungime, double latime) : material(material), lungime(lungime), latime(latime) {}

		//destructor
		~Mobila() {}
	public:
		//functii de setare si de returnare
		void setMaterial(string newMaterial) { material = newMaterial; }

		string getMaterial() { return material; }
		
		void setDimensiuni(double lung, double lat) { lungime = lung, latime = lat; }

		double getLungime() { return lungime; }
		double getLatime() { return latime; }
};

class Divan: public Mobila
{
	string calitate;
	protected:
		//constructor parametrizat
		Divan(string material, double lungime, double latime, string calitate) : Mobila(material, lungime, latime), calitate(calitate) {}

		//destructor
		~Divan() {}
	public:
		//functii de setare si de returnare
		void setCalitate(string newQuality) { calitate = newQuality; }

		string getCalitate() { return calitate; }
};

class Pat: public Mobila
{
	int nrLocuri;
	protected:
		//constructor parametrizat
		Pat(string material, double lungime, double latime, int nrLocuri) : Mobila(material, lungime, latime), nrLocuri(nrLocuri) {}

		//destructor
		~Pat() {}
	public:
		//functii de setare si de returnare
		void setLocuri(int locuri) { nrLocuri = locuri; }
		int getLocuri() { return nrLocuri; }
};

class Divan_Pat : public Divan, public Pat
{
	public:
		//constructor parametrizat
		Divan_Pat(string material = "-", double lungime = 0.0, double latime = 0.0, string calitate = "-", int nrLocuri = 0) : Divan(material, lungime, latime, calitate),
			Pat(material, lungime, latime, nrLocuri) {}

		//destructor
		~Divan_Pat() {}

		string getMaterial() { return Mobila::getMaterial(); }

		//supraincarcarea operatorului de afisare ca functie prietena
		friend ostream& operator<<(ostream& out, Divan_Pat& obj);
};

ostream& operator<<(ostream& out, Divan_Pat& obj)
{
	return out <<"\nMaterial: " << obj.Mobila::getMaterial()
		<< "\nLungime: " << obj.Mobila::getLungime()
		<< "\nLatime: " << obj.Mobila::getLatime()
		<< "\nCalitate: " << obj.getCalitate()
		<< "\nNr. Locuri: " << obj.getLocuri() << endl;
}

int main() {
	Divan_Pat obiect("Piele", 2.5, 1.3, "foarte buna", 3);
	cout << obiect;
	cout << "\nModificarea materialului si dimensiunilor:" << endl;
	obiect.Mobila::setMaterial("Stofa");
	obiect.Mobila::setDimensiuni(2.2, 1.1);
	cout << obiect;
	
	cout << "\nReturnarea unor detalii despre canapea:" << endl;
	Divan_Pat Canapea("Catifea", 2.0, 1.0, "inalta", 2);
	cout << "Calitate: " << Canapea.getCalitate() << endl;
	cout << "Nr. de locuri: " << Canapea.getLocuri() << endl;
	cout << "Dimensiuni: " << Canapea.Mobila::getLungime() << " m lungime si " << Canapea.Mobila::getLatime() << " m latime." << endl;
	return 0;
}