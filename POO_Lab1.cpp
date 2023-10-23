#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
const string fisier = "date_case.txt";
//trebuie de creat un fisier in locatia programului

struct Casa
{
    string firma;
    string adresa;
    int etaje;
    int apartamente;
};

void meniu(int n);
void afisareDate(int n);
void adaugareStructura(int &n);
void modificareStructura(int n);
void comparareApartamente(int n);
void sortareEtaje(int n);
void sortareAdrese(int n);
void iesireProgram();

int main()
{
    int n = 0;
    ifstream ft(fisier); //deschide fisierul pentru citire folosind obiectul ft
    if (ft.is_open()) //verifica daca fisierul s-a deschis cu succes
    {
        string linie;
        while (getline(ft, linie))
        {
            n++; //numara cate linii de text sunt in fisier
        }
        ft.close();

        //pentru a obtine numarul total de structuri se imparte la 4
        n /= 4;

        meniu(n); //apeleaza meniul
    }
    else
    {
        cout << "\nFisierul nu a putut fi deschis sau nu a fost creat.\n";
    }
    return 0;
}

void meniu(int n)
{
    int option;
    cout << "1. Afiseaza elementele din fisier;"
        << "\n2. Adauga o structura noua in fisier;"
        << "\n3. Modificarea unei structuri a fisierului;"
        << "\n4. Compararea structurilor;"
        << "\n5. Sorteaza structurile dupa etaje;"
        << "\n6. Sorteaza structurile dupa adresa;"
        << "\n7. Iesire din program."
        << "\nOptiunea nr: ";
    cin >> option;
    switch (option)
    {
        case 1: afisareDate(n);
                meniu(n);
            break;
        case 2: adaugareStructura(n);
                meniu(n);
            break;
        case 3: modificareStructura(n);
                meniu(n);
            break;
        case 4: comparareApartamente(n);
                meniu(n);
            break;
        case 5: sortareEtaje(n);
                meniu(n);
            break;
        case 6: sortareAdrese(n);
                meniu(n);
            break;
        case 7: iesireProgram();
            break;
        default: cout << "\nNu exista aceasta optiune. Incearca din nou.\n\n";
                meniu(n);
            break;
    }
}

void afisareDate(int n)
{
    //deschide fisierul pentru citire
    ifstream ft(fisier, ios::in);
    if (ft.is_open()) //verifica daca fisierul s-a deschis cu succes
    {
        //citeste datele din fisier pentru fiecare structura
        for (int i = 0; i < n; i++)
        {
            Casa* curent = new Casa; //aloca memoria dinamica pentru o structura
            getline(ft, curent->firma);
            getline(ft, curent->adresa);
            ft >> curent->etaje >> curent->apartamente;
            ft.ignore(); //ignora newline-ul ramas in buffer

            //afiseaza datele citite la ecran
            cout << "\nFirma de constructie: " << curent->firma << endl;
            cout << "Adresa casei: " << curent->adresa << endl;
            cout << "Etaje: " << curent->etaje << endl;
            cout << "Apartamente: " << curent->apartamente << endl;
            
            //eliberam memoria alocata pentru structura curenta
            delete curent;
        }
        ft.close();
    }
    else
    {
        cout << "Eroare la deschiderea fisierului.";
    }
    cout << "\n";
}

void adaugareStructura(int &n)
{
    //deschide fisierul pentru adaugare (append)
    ofstream ft(fisier, ios::app);
    if (!ft.is_open())
    {
        cout << "Eroare la deschiderea fisierului pentru adaugare.\n";
        return; //daca este eroare la deschidere, iese din funcite
    }

    Casa casaNoua; //s-a declarat un obiect pentru a stoca datele noi
    cout << "\nIntroduceti datele despre casa noua:";
    cout << "\nFirma de constructie: ";
    cin.ignore(); //ignora newline-ul ramas in buffer
    getline(cin, casaNoua.firma);
    cout << "Adresa casei: ";
    getline(cin, casaNoua.adresa);
    cout << "Etaje: ";
    cin >> casaNoua.etaje;
    cout << "Apartamente: ";
    cin >> casaNoua.apartamente;

    //adauga noua structura la sfarsit de fisier
    ft << casaNoua.firma << endl;
    ft << casaNoua.adresa << endl;
    ft << casaNoua.etaje << endl;
    ft << casaNoua.apartamente << endl;

    ft.close();
    n++; //incrementeaza n cu 1, deoarece s-a adaugat o structura noua
    cout << "\nStructura noua a fost adauga cu succes in fisier.\n\n";
}

void modificareStructura(int n)
{
    //creaza un array de structuri pentru a stoca temporar datele din fisier in memorie
    Casa* temp = new Casa[n];

    //deschide fișierul pentru citire si scriere
    fstream ft(fisier, ios::in | ios::out);

    if (!ft.is_open())
    {
        cout << "\nEroare la deschiderea fisierului pentru modificare.\n";
        return;
    }

    //citeste toate structurile din fisier in memorie
    for (int i = 0; i < n; i++)
    {
        getline(ft, temp[i].firma);
        getline(ft, temp[i].adresa);
        ft >> temp[i].etaje;
        ft >> temp[i].apartamente;
        ft.ignore(); //ignora newline-ul ramas in buffer
    }

    //afiseaza structurile existente
    cout << "\nStructurile existente:\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". Firma de constructie: " << temp[i].firma << endl;
        cout << "   Adresa casei: " << temp[i].adresa << endl;
        cout << "   Etaje: " << temp[i].etaje << endl;
        cout << "   Apartamente: " << temp[i].apartamente << "\n" << endl;
    }

    int index;
    cout << "Introduceti indexul structurii pe care doriti sa o modificati: ";
    cin >> index;

    if (index >= 1 && index <= n)
    {
        //realizeaza modificarea structurii selectate
        cout << "Introduceti noile date pentru structura:\n";
        cout << "Firma de constructie: ";
        cin.ignore(); //ignora newline-ul ramas dupa citire
        getline(cin, temp[index - 1].firma);
        cout << "Adresa casei: ";
        getline(cin, temp[index - 1].adresa);
        cout << "Etaje: ";
        cin >> temp[index - 1].etaje;
        cout << "Apartamente: ";
        cin >> temp[index - 1].apartamente;

        //repozitioneaza cursorul la inceputul fisierului
        ft.seekp(0);

        //rescrie toate structurile din memorie in fisier
        for (int i = 0; i < n; i++)
        {
            ft << temp[i].firma << endl;
            ft << temp[i].adresa << endl;
            ft << temp[i].etaje << endl;
            ft << temp[i].apartamente << endl;
        }

        cout << "\nStructura nr." << index <<" a fost modificata cu succes.\n";
    }
    else
    {
        cout << "\nIndex invalid. Nu s-a realizat nicio modificare.";
    }

    ft.close();
    delete[] temp; //elibereaza memoria alocata
    cout << "\n";
}

void comparareApartamente(int n)
{
    ifstream ft(fisier, ios::in);
    if (!ft.is_open())
    {
        cout << "\nEroare la deschiderea fisierului.\n";
        return;
    }

    Casa maxAptm; //obiect pentru stocare a unei structuri
    Casa minAptm;
    int max = INT_MIN; //initializeaza variabila cu cea mai mic valoare minima
    int min = INT_MAX; //initializeaza variabila cu cea mai mare valoare maxima

    while (!ft.eof()) //ruleaza pana cand ajunge la sfarsit de fisier
    {
        Casa casa; //s-a creat un obiect pentru a stoca datele citite din fisier
        getline(ft, casa.firma);
        //if (ft.eof()) break;
        getline(ft, casa.adresa);
        ft >> casa.etaje >> casa.apartamente;
        ft.ignore(); //ignora newline-ul ramas in buffer

        if (ft.eof()) break; //iesire din ciclu daca s-a ajuns la sfarsit de fisier

        if (casa.apartamente > max) //verifica daca nr. de apartamente din structura curenta este mai mare decat maximul anterior
        {
            max = casa.apartamente; //actualizeaza valoarea maximului
            maxAptm = casa; //actualizeaza structura cu cele mai multe apartamente
        }
        if (casa.apartamente < min)
        {
            min = casa.apartamente;
            minAptm = casa;
        }
    }
    ft.close();

    cout << "\nStructura cu cel mai mare numar de apartamente este:"
         << "\nFirma de constructie: " << maxAptm.firma
         << "\nAdresa casei: " << maxAptm.adresa
         << "\nEtaje: " << maxAptm.etaje
         << "\nApartamente: " << maxAptm.apartamente;

    cout << "\n\nStructura cu cel mai mic numar de apartamente este:"
        << "\nFirma de constructie: " << minAptm.firma
        << "\nAdresa casei: " << minAptm.adresa
        << "\nEtaje: " << minAptm.etaje
        << "\nApartamente: " << minAptm.apartamente;
    cout << "\n\n";
}

void sortareEtaje(int n)
{
    //creaza un array de structuri pentru a stoca temporar datele din fisier in memorie
    Casa* temp = new Casa[n];

    ifstream ft(fisier, ios::in);
    if (!ft.is_open())
    {
        cout << "\nEroare la deschiderea fisierului pentru sortare.\n";
        return;
    }
    
    //citeste datele din fisier si le stocheaza in structurile din vectorul C
    for (int i = 0; i < n; i++)
    {
        getline(ft, temp[i].firma);
        getline(ft, temp[i].adresa);
        ft >> temp[i].etaje; 
        ft >> temp[i].apartamente;
        ft.ignore(); //ingora newline-ul ramas
    }
    ft.close();

    //sorteaza structurile in vectorul C in functie de numarul de etaje
    sort(temp, temp + n, [](const Casa& a, const Casa& b)
        {
            return a.etaje < b.etaje;
        });

    //afiseaza structurile sortate
    cout << "\nStructurile sortate dupa numarul de etaje (crescator):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Firma de constructie: " << temp[i].firma << endl;
        cout << "Adresa casei: " << temp[i].adresa << endl;
        cout << "Etaje: " << temp[i].etaje << endl;
        cout << "Apartamente: " << temp[i].apartamente << endl;
        cout << endl;
    }
    ofstream ftr(fisier, ios::out); //deschide fisierul pentru scriere
    if (!ftr.is_open())
    {
        cout << "\nEroare la deschiderea fisierului pentru rescriere.\n";
        return;
    }
    ftr.seekp(0);

    //rescrie structurile sortate in fisier
    for (int i = 0; i < n; i++)
    {
        ftr << temp[i].firma << endl;
        ftr << temp[i].adresa << endl;
        ftr << temp[i].etaje << endl;
        ftr << temp[i].apartamente << endl;
    }
    ftr.close();
    delete[] temp; //elibereaza memoria alocata
}

void sortareAdrese(int n)
{
    //creaza un array de structuri pentru a stoca temporar datele din fisier in memorie
    Casa* temp = new Casa[n];
    
    ifstream ft(fisier, ios::in);
    if (!ft.is_open())
    {
        cout << "\nEroare la deschiderea fisierului pentru sortare.\n";
        return;
    }

    //citeste datele din fisier
    for (int i = 0; i < n; i++)
    {
        getline(ft, temp[i].firma);
        getline(ft, temp[i].adresa);
        ft >> temp[i].etaje;
        ft >> temp[i].apartamente;
        ft.ignore();
    }
    ft.close();

    //sorteaza structurile in vectorul C in functie de adresa (alfabetic)
    sort(temp, temp + n, [](const Casa& a, const Casa& b)
        {
            return a.adresa < b.adresa;
        });
    //afiseaza structurile sortate
    cout << "\nStructurile sortate dupa adresa (alfabetic):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Firma de constructie: " << temp[i].firma << endl;
        cout << "Adresa casei: " << temp[i].adresa << endl;
        cout << "Etaje: " << temp[i].etaje << endl;
        cout << "Apartamente: " << temp[i].apartamente << endl;
        cout << endl;
    }
    ofstream ftr(fisier, ios::out); //deschide fisierul pentru scriere
    if (!ftr.is_open())
    {
        cout << "\nEroare la deschiderea fisierului pentru rescriere.\n";
        return;
    }
    ftr.seekp(0);

    //rescrie structurile sortate in fisier
    for (int i = 0; i < n; i++)
    {
        ftr << temp[i].firma << endl;
        ftr << temp[i].adresa << endl;
        ftr << temp[i].etaje << endl;
        ftr << temp[i].apartamente << endl;
    }
    ftr.close();
    delete[] temp; //elibereaza memoria alocata
}

void iesireProgram()
{
    cout << "\nProgramul se inchide...";
    exit(0); //iesire din program (inchidere fara erori)
}