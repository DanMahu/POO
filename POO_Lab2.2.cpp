#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

class Complex
{
	float re; //partea reala a numarului
	float im; //partea imaginara a numarului
	public:
		//constructor implicit
		Complex() : re(0.0), im(0.0) {}

		//constructor parametrizat pentru initializarea re si im
		Complex(float real, float imag) : re(real), im(imag) {}
		float getReal() { return re; } //functie de returnare a partii reale
		float getImag() { return im; } //functie de returnare a partii imaginare
		
		Complex operator+(const Complex& otherMx) //supraincarcarea operatorului +
		{
			return Complex(re + otherMx.re, im + otherMx.im);
		}

		Complex operator-(const Complex& otherMx) //supraincarcarea operatorului -
		{
			return Complex(re - otherMx.re, im - otherMx.im);
		}

		Complex operator*(const Complex& otherMx) //supraincarcarea operatorului *
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

		//constructor de copiere
		Matrix(const Matrix& otherMx) : randuri(otherMx.randuri), coloane(otherMx.coloane), codEroare(otherMx.codEroare)
		{
			alocareMemorie(randuri, coloane);

			for (int i = 0; i < randuri; i++)
				for (int j = 0; j < coloane; j++)
				{
					C[i][j] = otherMx.C[i][j];
				}
		}

		//destructor
		~Matrix()
		{
			if (C != nullptr)
			{
				for (int i = 0; i < randuri; i++)
				{
					delete[] C[i];
				}
				delete[] C;
				C = nullptr;
			}
			//cout << "Destructor: Obiect distrus!\n";
		}

		//functie de alocare de memorie pentru ambele matrici
		void alocareMemorie(int r_size, int c_size)
		{
			if (r_size < 0 && c_size < 0)
			{
				codEroare = 1; //cod de eroare pentru dimensiuni invalide
				return;
			}
			C = new Complex * [r_size]; //aloca memorie pentru un array de pointeri
			for (int i = 0; i < r_size; i++)
				C[i] = new Complex[c_size]; //aloca memorie de c_size coloane pentru fiecare linie
			//cout << "Memorie alocata!\n";
		}

		//functie de creare a ambelor matrici
		void creareMatrice(int r_size, int c_size)
		{
			int optiune = 0;
			float re, im;
			do
			{
				cout << "\nAlege prin ce metoda sa introduci elementele: "
					<< "\n1. De la tastatura"
					<< "\n2. Random"
					<< "\n3. Iesire"
					<< "\nOptiunea aleasa: ";
				cin >> optiune;
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
				case 3: cout << "\nIesire din functie!\n";
					break;
				default: cout << "\nOptiune invalida! Incearca din nou.\n";
					break;
				}
			} while (optiune != 1 && optiune != 2 && optiune != 3);
		}

		//functie de afisare a matricelor la ecran
		void afisareMatrice()
		{
			cout << endl;
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					cout << fixed << setprecision(1); 
					//cout.precision(2); //afisarea valorilor cu o singura zecimala dupa virgula
					cout << C[i][j].getReal() << " + " << C[i][j].getImag() << "i   "; //afiseaza partea reala si imaginara
				}
				cout << endl;
			}
		}
		
		//functie de setare a valorilor
		void setElem(int i, int j, const Complex& newValue)
		{
			if (i >= 0 && i < randuri && j >= 0 && j < coloane) C[i][j] = newValue;
			else codEroare = 2; //cod de eroare pentru coordonate in afara limitei matricei
		}

		Matrix operator+(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 3; //cod de eroare pentru dimensiuni incompatibile
				return Matrix(); //returneaza un obiect gol
			}
			else codEroare = 0; //reseteaza cod de eroare

			Matrix suma(randuri, coloane); //obiect de tip Matrix cu randuri x coloane
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					//suma.C[i][j] = C[i][j] + otherMx.C[i][j];
					Complex sumaElem = C[i][j] + otherMx.C[i][j];
					suma.setElem(i, j, sumaElem);
				}
			}
			return suma;
		}

		Matrix operator-(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 3;
				return Matrix();
			}
			else codEroare = 0;

			Matrix diferenta(randuri, coloane);
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					//diferenta.C[i][j] = C[i][j] - otherMx.C[i][j];
					Complex difElem = C[i][j] - otherMx.C[i][j];
					diferenta.setElem(i, j, difElem);
				}
			}
			return diferenta;
		}

		Matrix operator*(const Matrix& otherMx)
		{
			if (randuri != otherMx.randuri || coloane != otherMx.coloane)
			{
				codEroare = 3;
				return Matrix();
			}
			else codEroare = 0;

			Matrix produs(randuri, coloane);
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					//produs.C[i][j] = C[i][j] * otherMx.C[i][j];
					Complex prodElem = C[i][j] * otherMx.C[i][j];
					produs.setElem(i, j, prodElem);
				}
			}
			return produs;
		}

		//functie de inmultire a unui numar cu fiecare element dintr-o matrice
		void inmultireCuNumar(int nr)
		{
			for (int i = 0; i < randuri; i++)
			{
				for (int j = 0; j < coloane; j++)
				{
					C[i][j] = Complex(C[i][j].getReal() * nr, C[i][j].getImag() * nr);
				}
			}
		}

		//supraincarcarea operatorului = 
		Matrix& operator=(const Matrix& otherMx)
		{
			if (this != &otherMx) //evita autoatribuirea
			{
				//elibereaza memoria existenta
				if (C != nullptr)
				{
					for (int i = 0; i < randuri; i++)
					{
						delete[] C[i];
					}
					delete[] C;
					C = nullptr;
				}

				//copiaza datele din cealalta matrice
				randuri = otherMx.randuri;
				coloane = otherMx.coloane;
				codEroare = otherMx.codEroare;

				//aloca memorie pentru matricea curenta
				alocareMemorie(randuri, coloane);

				//copiaza elementele din cealalta matrice
				for (int i = 0; i < randuri; i++)
				{
					for (int j = 0; j < coloane; j++)
					{
						C[i][j] = otherMx.C[i][j];
					}
				}
			}
			return *this; //returneaza o referinta la obiectul curent
		}

		int getCodEroare() { return codEroare; } //functie de returnare a codului de eroare

		bool notEmpty() { return (C != nullptr); } //functie de returnare true/false in dependenta de pointer

		void setNullptr() { C = nullptr; } //functie de setare a unui pointer ca nullptr
};

//functie ajutatoare pentru verificare inainte de afisare pentru a evita afisarea matricelor goale/inexistente
void verificarePtAfisare(Matrix& matrix, const string& numeMatrice)
{
	if (matrix.notEmpty())
	{
		cout << "\n" << numeMatrice << ":";
		matrix.afisareMatrice();
	}
}

int main() {
	Matrix p, d, suma, diferenta, produs;
	int optiune = 0;
	do {
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
			suma = p + d;
			if (p.getCodEroare() == 3)
			{
				suma.setNullptr();
				cout << "\nEroare: Dimensiuni incompatibile!\n";
			}
			else
			{
				cout << "\nRezultatul matricelor adunate:";
				suma.afisareMatrice();
			}
			break;
		case 5:
			diferenta = p - d;
			if (p.getCodEroare() == 3)
			{
				diferenta.setNullptr();
				cout << "\nEroare: Dimensiuni incompatibile!\n";
			}
			else
			{
				cout << "\nRezultatul diferentei matricelor:";
				diferenta.afisareMatrice();
			}
			break;
		case 6:
			produs = p * d;
			if (p.getCodEroare() == 3)
			{
				produs.setNullptr();
				cout << "\nEroare: Dimensiuni incompatibile!\n";
			}
			else
			{
				cout << "\nRezultatul produsului matricelor:";
				produs.afisareMatrice();
			}
			break;
		case 7:
			int option7;
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