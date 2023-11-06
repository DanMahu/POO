#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

class Complex
{
	float re; //partea reala a numarului
	float im; //partea imaginara a numarului
	public:
		//constructor implicit
		Complex() : re(0), im(0) {}

		//constructor cu doi parametri pentru initializarea re si im
		Complex(float real, float imag) : re(real), im(imag) {}

		float getReal() { return re; } //functie de returnare a partii reale
		float getImag() { return im; } //functie de returnare a partii imaginare

		Complex operator+(Complex& otherMx) //supraincarcarea operatorului + 
		{
			return Complex(re + otherMx.re, im + otherMx.im); //returneaza un obiect cu noul rezultat
		}

		Complex operator-(Complex& otherMx) //supraincarcarea operatorului -
		{
			return Complex(re - otherMx.re, im - otherMx.im);
		}

		Complex operator*(Complex& otherMx) //supraincarcarea operatorului *
		{
			return Complex(re * otherMx.re, im * otherMx.im);
		}
};

class Matrix
{
	Complex** C;
	int randuri;
	int coloane;
	int codEroare;
	public:
		//constructor implicit
		Matrix() : C(nullptr), randuri(0), coloane(0), codEroare(0) {}

		//constructor cu un parametru - matrice patrata
		Matrix(int size) : randuri(size), coloane(size), codEroare(0)
		{
			alocareMemorie(size, size);
		}

		//constructor cu doi parametri - matrice dreptunghiulara
		Matrix(int r_size, int c_size) : randuri(r_size), coloane(c_size), codEroare(0)
		{
			alocareMemorie(r_size, c_size);
		}

		//desctrutor
		~Matrix()
		{
			//cout << "Destructor: Obiect distrus!\n";
		}

		Matrix alocareMemorie(int r_size, int c_size) //functie de alocare a memoriei pentru matrice
		{
			if (r_size > 0 && c_size > 0)
			{
				C = new Complex * [r_size]; //aloca memorie pentru un array de pointeri
				for (int i = 0; i < r_size; i++)
					C[i] = new Complex[c_size]; //aloca memorie de c_size coloane pentru fiecare linie
			}
			else
			{
				codEroare = 1; //cod de eroare pentru dimensiuni invalide
				return Matrix(); //returneaza un obiect pentru a indica eroarea
			}
		}

		//functie de creare a matricelor patrate sau dreptunghiulare
		void creareMatrice(int r_size, int c_size)
		{
			int optiune;
			float re, im;
			cout << "\nAlege prin ce metoda sa introduci elementele: "
				<< "\n1. De la tastatura"
				<< "\n2. Random"
				<< "\nOptiunea aleasa: ";
			cin >> optiune;
			do
			{
				switch (optiune)
				{
				case 1:
					cout << "\nIntrodu partea reala si imaginara pentru fiecare element (r, i): \n";
					for (int i = 0; i < r_size; i++)
					{
						for (int j = 0; j < c_size; j++)
						{
							cout << "[" << i << "][" << j << "]: ";
							//printf("[%d][%d]: ", i, j);
							cin >> re >> im; //se citesc elementele de la tastatura (partea reala si imaginara)
							C[i][j] = Complex(re, im); //atribuie elementului corespunzator din matrice valoarea introdusa
						}
					}
					cout << "\nElementele au fost introduse.\n";
					break;
				case 2:
					srand(time(0)); //initializeaza generatorul de numere folosind ora actuala
					for (int i = 0; i < r_size; i++)
						for (int j = 0; j < c_size; j++)
						{
							re = static_cast<float>(1.0 + (rand() / (RAND_MAX / 15.0))); //genereaza numere aleatorii intre 1.0 si 15.0
							im = static_cast<float>(1.0 + (rand() / (RAND_MAX / 19.0)));
							C[i][j] = Complex(re, im); //atribuie elementului corespunzator din matrice valoarea generata
						}
					cout << "\nElementele au fost generate aleatoriu.\n";
					break;
				default: cout << "\nOptiune invalida! Incearca din nou.\n";
					break;
				}
			} while (optiune != 1 && optiune != 2);
		}

		//afisarea matricelor la ecran
		void afisareMatrice()
		{
			cout << endl;
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					//cout << fixed << setprecision(1); 
					cout.precision(2); //afisarea valorilor cu o singura zecimala dupa virgula
					cout << C[i][j].getReal() << " + " << C[i][j].getImag() << "i   "; //afiseaza partea reala si imaginara
				}
				cout << endl;
			}
		}

		void setElem(int i, int j, const Complex& newValue)
		{
			if (i >= 0 && i < randuri && j >= 0 && j < coloane) //verifica daca indicii nu sunt in afara limitelor
				C[i][j] = newValue; //seteaza noua valoarea pe randul i si coloana j
		}

		//functie de adunare a doua matrici
		Matrix adunare(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 2; //cod de eroare pentru dimensiuni incompatibile
				return Matrix();
			}
			else codEroare = 0; //daca dimensiuni sunt asemanatoare, codEroare este setat la 0 pentru a indica ca nu sunt erori
			Matrix suma(randuri, coloane); //se creeaza o matrice noua cu aceleasi dimensiuni
			for (int i = 0; i < randuri; i++)
				for (int j = 0; j < coloane; j++)
				{
					Complex sumaElem = C[i][j] + otherMx.C[i][j]; //se aduna elementele curente cu elementele din matricea 2
					suma.setElem(i, j, sumaElem); //seteaza elementul pe pozitia i j
				}
			return suma; //returneaza matricea
		}

		//scadere a doua matrici
		Matrix scadere(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 2; //cod de eroare pentru dimensiuni incompatibile
				return Matrix();
			}
			else codEroare = 0;
			Matrix diferenta(randuri, coloane);
			for (int i = 0; i < randuri; i++)
				for (int j = 0; j < coloane; j++)
				{
					Complex diferentaElem = C[i][j] - otherMx.C[i][j];
					diferenta.setElem(i, j, diferentaElem);
				}
			return diferenta;
		}

		//inmultire a doua matrici
		Matrix inmultire(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 2; //cod de eroare pentru dimensiuni incompatibile
				return Matrix();
			}
			else codEroare = 0;
			Matrix produs(randuri, coloane);
			for (int i = 0; i < randuri; i++)
				for (int j = 0; j < coloane; j++)
				{
					Complex produsElem = C[i][j] * otherMx.C[i][j];
					produs.setElem(i, j, produsElem);
				}
			return produs;
		}

		//inmultirea unei matrici cu un numar
		void inmultireCuNumar(int nr)
		{
			for (int i = 0; i < randuri; i++)
				for (int j = 0; j < coloane; j++)
				{
					C[i][j] = Complex(C[i][j].getReal() * nr, C[i][j].getImag() * nr); //actualizeaza fiecare element din matrice inmultit la numarul dorit
				}
		}

		int getCodEroare() //functie de returnare a codului de eroare
		{
			return codEroare;
		}

		bool notEmpty() //functie ajutatoare pentru verificare
		{
			return (C != nullptr);
		}
};

//functie ajutatoare pentru verificare inainte de afisare pentru a evita afisarea matricelor goale/inexistente
void verificarePtAfisare(Matrix& m, const string& numeMatrice)
{
	if (m.notEmpty()) //verifica daca matricea nu este goala
	{
		cout << "\n" << numeMatrice << ":";
		m.afisareMatrice();
	}
}

int main()
{
	Matrix p, d, suma, diferenta, produs; //obiecte de tip Matrix
	int optiune;
	do
	{
		cout << "\n<<----------Meniu---------->>"
			<< "\n1. Creeaza o matrice patrata"
			<< "\n2. Creeaza o matrice dreptunghiulara"
			<< "\n3. Afisarea matricelor"
			<< "\n4. Adunarea matricelor"
			<< "\n5. Scaderea matricelor"
			<< "\n6. Inmultirea matricelor"
			<< "\n7. Inmultirea matricei cu un numar"
			<< "\n8. Iesire din program"
			<< "\nOptiunea aleasa: ";
		cin >> optiune;
		switch (optiune)
		{
		case 1:
				int size;
				cout << "\nIntrodu dimensiunea matricei patratice: ";
				cin >> size;
				p = Matrix(size);
				if (p.getCodEroare() == 1) cout << "\nEroare: Dimensiune invalida!\n";
				else p.creareMatrice(size, size);
			break;
		case 2:
				int r_size, c_size;
				cout << "\nIntrodu dimensiunile matricei dreptunghiulare:\nNr. Randuri: ";
				cin >> r_size;
				cout << "Nr. Coloane: ";
				cin >> c_size;
				d = Matrix(r_size, c_size);
				if (d.getCodEroare() == 1) cout << "\nEroare: Dimensiuni invalide!\n";
				else d.creareMatrice(r_size, c_size);
			break;
		case 3: 
				if (p.notEmpty() || d.notEmpty())
				{
					verificarePtAfisare(p, "Matricea patrata");
					verificarePtAfisare(d, "Matricea dreptunghiulara");
					verificarePtAfisare(suma, "Suma matricelor");
					verificarePtAfisare(diferenta, "Diferenta matricelor");
					verificarePtAfisare(produs, "Produsul matricelor");
				}
				else cout << "\nMatricile nu au fost create!\n";
			break;
		case 4:
				suma = p.adunare(d);
				if (p.getCodEroare() == 2) cout << "\nEroare: Dimensiuni incompatibile!\n";
				else
				{
					cout << "\nRezultatul matricelor adunate:";
					suma.afisareMatrice();
				}
			break;
		case 5: diferenta = p.scadere(d);
				if (p.getCodEroare() == 2) cout << "\nEroare: Dimensiuni incompatibile!\n";
				else
				{
					cout << "\nRezultatul diferentei matricelor:";
					diferenta.afisareMatrice();
				}
			break;
		case 6: produs = p.inmultire(d);
				if (p.getCodEroare() == 2) cout << "\nEroare: Dimensiuni incompatibile!\n";
				else
				{
					cout << "\nRezultatul produsului matricelor:";
					produs.afisareMatrice();
				}
			break;
		case 7: int option7;
				int nr;
				cout << "\nIntrodu numarul dorit pentru a inmulti matricea: ";
				cin >> nr;
				do
				{
					cout << "\nAlege care matrice o inmultesti:"
						<< "\n1. Patrata"
						<< "\n2. Dreptunghiulara"
						<< "\nOptiunea aleasa: ";
					cin >> option7;
					switch (option7)
					{
					case 1:
						cout << "\nMatricea patrata inainte:\n";
						p.afisareMatrice();
						p.inmultireCuNumar(nr);
						cout << "\nMatricea dupa:\n";
						p.afisareMatrice();
						break;
					case 2:
						cout << "\nMatricea dreptunghiulara inainte:\n";
						d.afisareMatrice();
						d.inmultireCuNumar(nr);
						cout << "\nMatricea dupa:\n";
						d.afisareMatrice();
						break;
					default: cout << "\nOptiune invalida! Incearca din nou.\n";
						break;
					}
				} while (option7 != 1 && option7 != 2);
			break;
		case 8: cout << "\nIesire din program...\n";
			break;
		default: cout << "\nOptiune invalida! Incearca din nou.\n";
			break;
		}
	} while (optiune != 8);

	return 0;
}
