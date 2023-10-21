#include <iostream>

using namespace std;

struct Vector
{
	float* p = nullptr;
	int nrElem;
	bool isEmpty;
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
	if (V.p != nullptr)
	{
		cout << "\nVectorul a fost deja initializat!\n\n";
		return;
	}

	int size;
	while (true)
	{
		cout << "\nIntrodu dimensiunea noului vector: ";
		cin >> size;
		if (size <= 0) cout << "\nAi introdus o dimensiune negativa sau egala cu 0! Introdu o dimeniune valida.\n";
		else break;
	}
	
	V.p = new float[size];
	V.nrElem = size;
	V.isEmpty = true;
	cout << "\nS-a initializat un vector cu dimensiunea " << V.nrElem << ".\n\n";
}

void introduceElementeVector(Vector &V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu poti introduce elemente. Vectorul nu a fost initializat!\n\n";
		return;
	}
	
	cout << "\nIntrodu " << V.nrElem << " elemente in vector:\n";
	for (int i = 0; i < V.nrElem; i++)
	{
		cout << "Elementul " << i + 1 << ": ";
		cin >> V.p[i];
	}
	V.isEmpty = false;
	cout << "\nElementele au fost introduse in vector!\n\n";
}

void afisareElementeVector(Vector& V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu poti afisa elemente. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true)
	{
		cout << "\nVectorul nu are elemente.\n\n";
		return;
	}
	
	cout << "\nVectorul are urmatoarele elemente:\n";
	for (int i = 0; i < V.nrElem; i++)
	{
		cout << "  " << V.p[i];
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
	else if (V.isEmpty == true)
	{
		cout << "\nVectorul nu are elemente.\n\n";
		return;
	}
	int index;
	while (true)
	{
		cout << "\nIntrodu index-ul elementului pe care doriti sa-l accesati (0 - " << V.nrElem - 1 << "): ";
		cin >> index;
		if (index > V.nrElem - 1 || index < 0) cout << "\nElement inexistent! Introdu un index valid.\n";
		else break;
	}
	cout << "\nElementul de pe index-ul " << index << " este " << V.p[index] << ".\n\n";
}

void verificarePtModificare(Vector& V, int& newSize)
{
	cout << "\nDimensiunea actuala: " << V.nrElem;
	while (true)
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
	int newSize;
	if (V.p == nullptr)
	{
		cout << "\nNu poti modifica dimensiunea. Vectorul nu a fost initializat!\n\n";
		return;
	}
	else if (V.isEmpty == true)
	{
		verificarePtModificare(V, newSize);
		delete[] V.p;
		V.p = new float[newSize];
		V.nrElem = newSize;
		cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n\n";
	}
	else
	{
		int oldSize = V.nrElem;
		verificarePtModificare(V, newSize);
		
		if (newSize > oldSize)
		{
			float* temp = new float[oldSize];
			for (int i = 0; i < oldSize; i++)
			{
				temp[i] = V.p[i];
			}

			delete[] V.p;

			V.p = new float[newSize];
			V.nrElem = newSize;
			cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n";

			for (int i = 0; i < oldSize; i++)
			{
				V.p[i] = temp[i];
			}
			delete[] temp;

			cout << "\nAi marit dimensiunea, iar acum completeaza vectorul cu noi elemente:\n";
			for (int i = oldSize; i < V.nrElem; i++)
			{
				cout << "Elementul " << i + 1 << ": ";
				cin >> V.p[i];
			}
			cout << "\nRestul elementelor au fost introduse.\n\n";
		}
		else if (newSize < oldSize)
		{
			float* temp = new float[newSize];
			for (int i = 0; i < newSize; i++)
			{
				temp[i] = V.p[i];
			}

			delete[] V.p;

			V.p = new float[newSize];
			V.nrElem = newSize;
			cout << "\nDimensiunea noua a vectorului este: " << V.nrElem << ".\n";

			for (int i = 0; i < newSize; i++)
			{
				V.p[i] = temp[i];
			}
			delete[] temp;
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
	else if (V.isEmpty == true)
	{
		cout << "\nVectorul nu are elemente pentru a calcula.\n\n";
		return;
	}
	float norma = 0.0f;
	for (int i = 0; i < V.nrElem; i++)
	{
		norma += V.p[i] * V.p[i];
	}
	cout << "\nNorma vectorului este: " << sqrt(norma) << ".\n\n";
}

void eliminareVector(Vector& V)
{
	if (V.p == nullptr)
	{
		cout << "\nNu este nimic de eliminat. Vectorul nu a fost initializat!\n\n";
		return;
	}
	
	delete[] V.p;
	V.p = nullptr;
	V.nrElem = 0;
	V.isEmpty = true;
	cout << "\nVectorul a fost eliminat!\n\n";
}

void iesireDinProgram(Vector& V)
{
	if (V.p != nullptr)
	{
		delete[] V.p;
		V.nrElem = 0;
		cout << "\nVectorul a fost eliminat.";
	}
	cout << "\nProgramul se inchide...";
}