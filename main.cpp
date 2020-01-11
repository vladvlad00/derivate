#include "derivare.h"
#include <iostream>

using namespace std;

string s, rez;

void inordine(arbore A);

int main()
{
    cin >> s;
    transforma(s);
    postordine(s,rez);
    arbore A = creeazaArboreExpresie(rez);
    inordine(A);
    cout << '\n';
    arbore D = derivare(A);
    //simplifica(D);
    cout << '(' << s << ")' = ";
    inordine(D);
    return 0;
}

void inordine(arbore A)
{
    if(!A)
        return;
    if (A->st && esteOperator(A->st->inf) && prioritate(A->inf) < prioritate(A->st->inf))
        cout << '(';
    inordine(A->st);
    if (A->st && esteOperator(A->st->inf) && prioritate(A->inf) < prioritate(A->st->inf))
        cout << ')';
    cout << A->inf;
    if (A->dr && esteOperator(A->dr->inf) && prioritate(A->inf) < prioritate(A->dr->inf) || (esteOperator(A->inf) && prioritate(A->inf) == 1))
        cout << '(';
    inordine(A->dr);
    if (A->dr && esteOperator(A->dr->inf) && prioritate(A->inf) < prioritate(A->dr->inf) || (esteOperator(A->inf) && prioritate(A->inf) == 1))
        cout << ')';
}