#include "postordine.h"

stiva S;

void postordine(string s, string &rez)
{
    int n = s.length();
    string aux;

    for (int i=0;i<n;i++)
    {
        aux += s[i];
        if (esteOperator(aux))
        {
            insereazaOperator(aux,rez);
            aux = "";
        }
        else if (esteConstanta(aux) || esteVariabila(aux) || esteNumar(aux))
        {
            rez += aux + ' ';
            aux = "";
        }
        else if (aux[0] == '(')
        {
            S.push(aux);
            aux = "";
        }
        else if (aux[0] == ')')
        {
            scoateParanteza(rez);
            aux = "";
        }
    }
    if (aux != "")
        throw "YEET";
    while (!S.empty())
    {
        rez += S.top();
        rez += ' ';
        S.pop();
    }
}

void insereazaOperator(string s,string &rez)
{
    while (!S.empty() && S.top()[0] != '(' && prioritate(S.top()) <= prioritate(s))
    {
        rez += S.top();
        rez += ' ';
        S.pop();
    }
    S.push(s);
}

void scoateParanteza(string &rez)
{
    while (S.top()[0] != '(')
    {
        rez += S.top();
        rez += ' ';
        S.pop();
    }
    S.pop();
}

bool esteOperator(string s)
{
    for (string aux:OPERATORI)
        if (aux == s)
            return 1;
    return 0;
}

bool esteVariabila(string s)
{
    for (string aux:VARIABILE)
        if (aux == s)
            return 1;
    return 0;
}

bool esteConstanta(string s)
{
    for (string aux:CONSTANTE)
        if (aux == s)
            return 1;
    return 0;
}

bool esteNumar(string s)
{
    int lg = s.length();

    for (int i=0;i<lg;i++)
        if (s[i] < '0' || s[i] > '9')
            return 0;
    return 1;
}

int prioritate(string s)
{
    if (s == "+" || s == "-")
        return 4;
    if (s == "*" || s == "/")
        return 3;
    if (s == "^")
        return 2;
    return 1; //oricare din celelalte functii trebuie facute inainte
}