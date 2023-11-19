#include <iostream>
using namespace std;

class numMariIntregi
{
    long num;
    public:
        //constructor de initializare
        numMariIntregi(long value = 0) : num(value) {}

        //destructor
        ~numMariIntregi()
        {
            num = NULL;
        }

        //supraincarcarea operatorului +
        numMariIntregi operator+(const numMariIntregi& otherNum)
        {
            return numMariIntregi(num + otherNum.num);
        }

        //supraincarcarea operatorului *
        numMariIntregi operator*(const numMariIntregi& otherNum)
        {
            return numMariIntregi(num * otherNum.num);
        }

        //operatorul - ca functie prietena
        friend numMariIntregi operator-(const numMariIntregi& num1, const numMariIntregi& num2);

        //operatorul / ca functie prietena
        friend numMariIntregi operator/(const numMariIntregi& num1, const numMariIntregi& num2);

        //supraincarcarea operatorului de incrementare prefixa
        numMariIntregi operator++()
        {
            numMariIntregi temp;
            temp.num = ++num;
            return temp;
        }

        //supraincarcarea operatorului de incrementare postfixa
        numMariIntregi operator++(int)
        {
            numMariIntregi temp;
            temp.num = num++;
            return temp;
        }

        //supraincarcarea operatorului de decrementare prefixa
        numMariIntregi operator--()
        {
            numMariIntregi temp;
            temp.num = --num;
            return temp;
        }

        //supraincarcarea operatorului de decrementare postfixa
        numMariIntregi operator--(int)
        {
            numMariIntregi temp;
            temp.num = num--;
            return temp;
        }

        //operatorul de afisare ca functie prietena
        friend ostream& operator<<(ostream& out, const numMariIntregi& obiect);
};

//supraincarcarea operatorului -
numMariIntregi operator-(const numMariIntregi& num1, const numMariIntregi& num2)
{
    return numMariIntregi(num1.num - num2.num);
}

//supraincarcarea operatorului / 
numMariIntregi operator/(const numMariIntregi& num1, const numMariIntregi& num2)
{
    return numMariIntregi(num1.num / num2.num);
}

//supraincarcarea operatorului de afisare
ostream& operator<<(ostream& out, const numMariIntregi& obiect)
{
    out << obiect.num;
    return out;
}

int main()
{
    numMariIntregi a(2120000);
    numMariIntregi b(356423400);
    numMariIntregi c(14);
    numMariIntregi d(20);
    numMariIntregi e;
    cout << a << " + " << b << " = " << a + b << endl;
    cout << b << " - " << a << " = " << b - a << endl;
    ++a;
    cout << "Incrementarea lui a: " << a << endl;
    --a;
    cout << "Decrementarea lui a: " << a << endl;
    cout << a << " / " << d << " = " << a / d << endl;
    cout << c << " * " << d << " = " << c * d << endl;
    e++;
    cout << "Incrementarea lui e: " << e << endl;
    cout << a << " / (" << c << " * " << d << ") = " << a / (c * d) << endl;
    return 0;
}