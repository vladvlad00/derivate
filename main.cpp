#include "derivare.h"
#include <iostream>

using namespace std;

string s, rez;

int main()
{
    cin >> s;
    transforma(s);
    postordine(s,rez);
    arboreBinar A = creeazaArboreExpresie(rez);
    cout << '\n';
    arboreBinar D = derivare(A);
    cout << '(' << s << ")' = ";
    afisare(D);
    return 0;
}