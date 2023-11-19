#include <iostream>
using namespace std;

class Matrix
{
    int** data;
    int randuri;
    int coloane;
    public:
        //constructor implicit
        Matrix() : data(nullptr), randuri(0), coloane(0) {}

        //constructor de initializare
        Matrix(int r_size, int c_size) : randuri(r_size), coloane(c_size)
        {
            alocareMemorie(r_size, c_size);
        }

        //constructor de copiere
        Matrix(const Matrix& otherMx) : randuri(otherMx.randuri), coloane(otherMx.coloane)
        {
            alocareMemorie(randuri, coloane);

            for (int i = 0; i < randuri; i++)
                for (int j = 0; j < coloane; j++)
                {
                    data[i][j] = otherMx.data[i][j];
                }
        }

        //functie de alocare dinamica a memoriei
        void alocareMemorie(int r_size, int c_size)
        {
            if (r_size > 0 && c_size > 0)
            {
                data = new int* [r_size];
                for (int i = 0; i < r_size; i++)
                    data[i] = new int[c_size];
            }
            else return;
        }

        //destructor
        ~Matrix()
        {
            if (data != nullptr)
            {
                for (int i = 0; i < randuri; i++)
                    delete[] data[i];
                delete[] data;
                data = nullptr;
            }
            //cout << "Destructor: Obiect distrus!" << endl;
        }

        //supraincarcarea operatorului +
        Matrix operator+(const Matrix& otherMx)
        {
            if (randuri != otherMx.randuri || coloane != otherMx.coloane)
            {
                return Matrix(); //daca dimensiunile sunt incompatibile returneaza o matrice goala
            }

            Matrix suma(randuri, coloane);
            for (int i = 0; i < randuri; i++)
                for (int j = 0; j < coloane; j++)
                    suma.data[i][j] = data[i][j] + otherMx.data[i][j];
            return suma;
        }

        //supraincarcarea operatorului -
        Matrix operator-(const Matrix& otherMx)
        {
            if (randuri != otherMx.randuri || coloane != otherMx.coloane)
            {
                return Matrix();
            }

            Matrix diferenta(randuri, coloane);
            for (int i = 0; i < randuri; i++)
                for (int j = 0; j < coloane; j++)
                    diferenta.data[i][j] = data[i][j] - otherMx.data[i][j];
            return diferenta;
        }

        //supraincarcarea operatorului de atribuire =
        Matrix& operator=(const Matrix& otherMx)
        {
            //elibereaza memoria veche
            if (this != &otherMx)
            {
                for (int i = 0; i < randuri; i++)
                    delete[] data[i];
                delete[] data;

                //aloca memoria noua si copie datele
                randuri = otherMx.randuri;
                coloane = otherMx.coloane;
                data = new int* [randuri];
                for (int i = 0; i < randuri; i++)
                {
                    data[i] = new int[coloane];
                    for (int j = 0; j < coloane; j++)
                    {
                        data[i][j] = otherMx.data[i][j];
                    }
                }     
            }
            return *this;
        }

        //operatorul de comparare == ca functie prietena
        friend bool operator==(const Matrix& mx1, const Matrix& mx2);

        //operatorul de comparare != ca functie prietena
        friend bool operator!=(const Matrix& mx1, const Matrix& mx2);

        //operatorul de comparare < ca functie prietena
        friend bool operator<(const Matrix& mx1, const Matrix& mx2);

        //operatorul de comparare > ca functie prietena
        friend bool operator>(const Matrix& mx1, const Matrix& mx2);

        //calcularea normei matricei ca functie prietena
        friend int norma(const Matrix& mx);

        //supraincarcarea operatorului de index []
        int* operator[](int index)
        {
            return data[index];
        }

        //operatorul de iesire << ca functie prietena
        friend ostream& operator<<(ostream& out, const Matrix& mx);

        //operatorul de intrare >> ca functie prietena
        friend istream& operator>>(istream& in, Matrix& mx);
      
};

//supraincarcarea operatorului de comparare ==
bool operator==(const Matrix& mx1, const Matrix& mx2)
{
    if (mx1.randuri != mx2.randuri || mx1.coloane != mx2.coloane)
    {
        return false;
    }

    for (int i = 0; i < mx1.randuri; i++)
        for (int j = 0; j < mx1.coloane; j++)
            if (mx1.data[i][j] != mx2.data[i][j]) return false;
    return true;
}

//supraincarcarea operatorului de comparare !=
bool operator!=(const Matrix& mx1, const Matrix& mx2)
{
    return !(mx1 == mx2);
}

//functie de calculare a normei matricei
int norma(const Matrix& mx)
{
    int norma = 0;
    for (int i = 0; i < mx.randuri; i++)
        for (int j = 0; j < mx.coloane; j++)
            norma += mx.data[i][j] * mx.data[i][j];
    return norma;
}

//supraincarcarea operatorului de comparare <
bool operator<(const Matrix& mx1, const Matrix& mx2)
{
    return norma(mx1) < norma(mx2);
}

//supraincarcarea operatorului de comparare >
bool operator>(const Matrix& mx1, const Matrix& mx2)
{
    return norma(mx1) > norma(mx2);
}

//supraincarcarea operatorului de afisare <<
ostream& operator<<(ostream& out, const Matrix& mx)
{
    for (int i = 0; i < mx.randuri; i++)
    {
        for (int j = 0; j < mx.coloane; j++)
            out << mx.data[i][j] << " ";
        out << endl;
    }
    return out;
}

//supraincarcarea operatorului de afisare >>
istream& operator>>(istream& in, Matrix& mx)
{
    for (int i = 0; i < mx.randuri; i++)
    {
        for (int j = 0; j < mx.coloane; j++)
        {
            cout << "mx[" << i << "][" << j << "]: ";
            in >> mx.data[i][j];
        }  
    }
    return in;
}
       

int main()
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    Matrix c(2, 3);
    Matrix d(2, 2);
    cout << "Introdu elementele matricei a:\n";
    cin >> a;

    cout << "\nIntrodu elementele matricei b:\n";
    cin >> b;

    cout << "\nElementele matricei a:\n";
    cout << a;

    cout << "\nElementele matricei b:\n";
    cout << b;

    if (a == b) cout << "\nMatricele sunt egale!";

    if (a != b) cout << "\nMatricile nu sunt egale!";

    if (a < b) cout << "\nMatricea a este mai mica ca b!\n";

    cout << "\nValoarea dupa index: " << a[0][1] << endl;

    Matrix suma = a + b;
    cout << "Suma matricelor a si b:\n" << suma << endl;

    cout << "\nIntrodu elementele matricei c:\n";
    cin >> c;
   
    cout << "\nElementele matricei c:\n";
    cout << c;

    if (c > b) cout << "\nMatricea c este mai mare ca b!\n";

    cout << "\nAtribuirea elementelor din matricea c in matricea d: ";
    d = c;
    cout << "\nElementele matricei d:\n";
    cout << d;
    return 0;
}
