#include <iostream>

using namespace std;

struct Vector
{
	float* p = nullptr;
	int nrElem;
	bool isEmpty; //indicator: true - nu sunt elemente in vector, false - sunt elemente in vector
};

void meniu(Vector& V);
void initializareVector(Vector& V);
void introduceElementeVector(Vector& V);
void afisareElementeVector(Vector& V);
void accesareElementeVector(Vector& V);
void verificarePtModificare(Vector& V, int& newSize);
void modificareDimensiuneVector(Vector& V);
void normaVector(Vector& V);
void eliminareVector(Vector& V);
void iesireDinProgram(Vector& V);

int main() {
	Vector V;
	meniu(V);
	return 0;
}

void meniu(Vector &V)
{
	int option;
	cout << "1. Initializare vector;"
		<< "\n2. Introdu elemente in vector;"
		<< "\n3. Afiseaza elementele vectorului;"
		<< "\n4. Acceseaza elemente din vector;"
		<< "\n5. Modifica dimensiunea vectorului;"
		<< "\n6. Calculeaza norma vectorului;"
		<< "\n7. Eliminare vector;"
		<< "\n8. Iesire din program."
		<< "\nOptiunea aleasa: ";
	cin >> option;
	switch (option)
	{
		case 1: initializareVector(V);
			meniu(V);
			break;
		case 2: introduceElementeVector(V);
			meniu(V);
			break;
		case 3: afisareElementeVector(V);
			meniu(V);
			break;
		case 4: accesareElementeVector(V);
			meniu(V);
			break;
		case 5: modificareDimensiuneVector(V);
			meniu(V);
			break;
		case 6: normaVector(V);
			meniu(V);
			break;
		case 7: eliminareVector(V);
			meniu(V);
			break;
		case 8: iesireDinProgram(V);
			break;
		default: cout << "\nNu exista aceasta optiune! Incearca din nou.\n\n";
			meniu(V);
			break;
	}
}
void initializareVector(Vector &V)
{
	if (V.p != nullptr) //verifica daca vectorul nu a fost initializat
	{
		cout << "\nVectorul a fost deja initializat!\n\n";
		return; //intrerupe functia
	}

	int size;
	while (true) //bucla va rula la infinit pana nu se introdu un numar valid
	{
		cout << "\nIntrodu dimensiunea noului vector: ";
		cin >> size;
		if (size <= 0) cout << "\nAi introdus o dimensiune negativa sau egala cu 0! Introdu o dimeniune valida.\n";
		else break; //la introducerea unui numar valid, bucla se intrerupe
	}
	
	V.p = new float[size]; //se aloca memorie pentru un vector de numere de tip float
	V.nrElem = size; //se atribuie dimensiunea vectorului
	V.isEmpty = true; //indica faptul ca vectorul este gol (fara elemente)
	cout << "\nS-a initializat un vector cu dimensiunea " << V.nrElem << ".\n\n";
}

void introduceElementeVector(Vector &V)
{
	if (V.p == nullptr) //verifica daca vectorul a fost initializat
	{
		cout << "\nNu poti introduce elemente. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == false)
	{
		cout << "\nVectorul deja are elemente introduse!\n\n";
		return;
	}
	
	cout << "\nIntrodu " << V.nrElem << " elemente in vector:\n";
	for (int i = 0; i < V.nrElem; i++)
	{
		cout << "Elementul " << i + 1 << ": ";
		cin >> V.p[i]; //se citeste elementele de la tastatura
	}
	V.isEmpty = false; //indica faptul ca vectorul are elemente
	cout << "\nElementele au fost introduse in vector!\n\n";
}

void afisareElementeVector(Vector& V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu poti afisa elemente. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true) //verifica daca vectorul are elemente
	{
		cout << "\nVectorul nu are elemente.\n\n";
		return;
	}
	
	cout << "\nVectorul are urmatoarele elemente:\n";
	for (int i = 0; i < V.nrElem; i++)
	{
		cout << "  " << V.p[i]; //afiseaza la ecran elementele vectorului
	}
	cout << "\n\n";
}

void accesareElementeVector(Vector &V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu poti accesa elemente. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true) //verifica daca vectorul are elemente
	{
		cout << "\nVectorul nu are elemente.\n\n";
		return;
	}
	int index;
	while (true) //bucla ruleaza la infinit pana se introduce un index valid
	{
		cout << "\nIntrodu index-ul elementului pe care doriti sa-l accesati (0 - " << V.nrElem - 1 << "): ";
		cin >> index;
		if (index > V.nrElem - 1 || index < 0) cout << "\nElement inexistent! Introdu un index valid.\n";
		else break; //opreste bucla in momentul cand se introduce un index valid
	}
	cout << "\nElementul de pe index-ul " << index << " este " << V.p[index] << ".\n\n";
}

void verificarePtModificare(Vector& V, int& newSize) //functie ajutatoare pentru modificareDimensiuneVector
{
	cout << "\nDimensiunea actuala: " << V.nrElem;
	while (true) //bucla ruleaza la infinit pana se introduce o dimensiune valida
	{
		cout << "\nIntrodu dimensiunea noua pentru vector: ";
		cin >> newSize;
		if (newSize <= 0) cout << "\nAi introdus o dimensiune negativa sau egala cu 0! Introdu o dimeniune valida.\n";
		else if (V.nrElem == newSize) cout << "\nAi introdus aceeasi dimensiune!\n";
		else break;
	}
}

void modificareDimensiuneVector(Vector& V)
{
	int newSize; //primeste valoarea de la functia verificarePtModificare
	if (V.p == nullptr)
	{
		cout << "\nNu poti modifica dimensiunea. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true) //verifica daca nu sunt elemente in vector
	{
		verificarePtModificare(V, newSize); //apeleaza functia de verificare si citire a dimensiunii noi
		delete[] V.p; //elibereaza memoria veche
		V.p = new float[newSize]; //aloca memoria din nou, doar cu dimensiunea noua
		V.nrElem = newSize; //actualizeaza nr. de elemente din structura cu dimensiunea noua
		cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n\n";
	}
	else //in caz ca trebuie de modificat dimensiunea, dar in vector sunt elemente
	{
		int oldSize = V.nrElem; //atribuim dimensiunea veche
		verificarePtModificare(V, newSize); //apeleaza functia de verificare si citire a dimensiunii noi
		
		if (newSize > oldSize)  //verifica daca dimensiunea noua este mai mare decat cea veche
		{
			float* temp = new float[oldSize]; //vector temporar pentru a stoca elementele din vectorul de baza
			for (int i = 0; i < oldSize; i++)
			{
				temp[i] = V.p[i]; //copiaza elementele in vectorul temporar
			}

			delete[] V.p; //elibereaza memoria pentru vectorul de baza

			V.p = new float[newSize]; //aloca memorie vectorului pentru dimensiunea noua
			V.nrElem = newSize; //actualizeaza nr. de elemente din structura cu dimensiunea noua
			cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n";

			for (int i = 0; i < oldSize; i++)
			{
				V.p[i] = temp[i]; //copiaza elementele din vectorul temporar inapoi in cel de baza
			}
			delete[] temp; //elibereaza memoria pentru vectorul temporar

			cout << "\nAi marit dimensiunea, iar acum completeaza vectorul cu noi elemente:\n";
			for (int i = oldSize; i < V.nrElem; i++)
			{
				cout << "Elementul " << i + 1 << ": ";
				cin >> V.p[i]; //citeste si stocheaza in vector restul elementelor
			}
			cout << "\nRestul elementelor au fost introduse.\n\n";
		}
		else if (newSize < oldSize) //verifica daca dimensiunea noua este mai mica decat cea veche
		{
			float* temp = new float[newSize]; //vector temporar pentru a stoca elementele din vectorul de baza
			for (int i = 0; i < newSize; i++)
			{
				temp[i] = V.p[i]; //copiaza elementele din vectorul de baza in cel temporar
			}

			delete[] V.p; //elibereaza memoria vectorului de baza

			V.p = new float[newSize]; //aloca memorie vectorului pentru noua dimensiune
			V.nrElem = newSize; //actualizeaza nr. de elemente din structura
			cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n";

			for (int i = 0; i < newSize; i++)
			{
				V.p[i] = temp[i]; //copiaza inapoi elementele vectorului 
			}
			delete[] temp; //elibereaza memoria vectorului temporar
			if (newSize == 1) cout << "\nAi micsorat dimensiunea. Primul element a ramas in vector.\n\n";
			else cout << "\nAi micsorat dimensiunea. Primele " << V.nrElem << " elemente au ramas in vector.\n\n";
		}
	}
}

void normaVector(Vector& V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu se poate calcula. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true) //verifica daca vectorul nu are elemente
	{
		cout << "\nVectorul nu are elemente pentru a calcula.\n\n";
		return;
	}
	float norma = 0.0f; //va stoca valoarea normei
	for (int i = 0; i < V.nrElem; i++)
	{
		norma += V.p[i] * V.p[i]; //calculeaza norma
	}
	cout << "\nNorma vectorului este: " << sqrt(norma) << ".\n\n"; //calculeaza radacina sumei patratelor si afiseaza la ecran
}

void eliminareVector(Vector& V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu este nimic de eliminat. Vectorul nu a fost initializat!\n\n";
		return;
	}
	
	delete[] V.p; //elibereaza memoria vectorului
	V.p = nullptr; //seteaza pointerul ca nullptr pentru a indica ca vectorul a fost eliminat
	V.nrElem = 0; //seteaza dimensiunea la 0
	V.isEmpty = true; //seteaza true pentru a indica ca vectorul este gol
	cout << "\nVectorul a fost eliminat!\n\n";
}

void iesireDinProgram(Vector& V)
{
	if (V.p != nullptr) //verifica daca vectorul are memorie alocata
	{
		delete[] V.p; //daca da, se elibereaza memoria
		V.nrElem = 0; //seteaza dimensiunea la 0
		cout << "\nVectorul a fost eliminat.";
	}
	cout << "\nProgramul se inchide...";
}