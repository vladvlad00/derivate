#include "postordine.h"

stivaString stivaStr;
stivaArbore stivaArb;

void postordine(string s, string &rez)
{
    int n = s.length();
    string aux;

    for (int i=0;i<n;i++)
    {
        if ((s[i] == '-' && (i == 0 || s[i-1] == '(')) || ('0' <= s[i] && s[i] <= '9'))
        {
            string numar;
            numar += s[i++];
            while ('0' <= s[i] && s[i] <= '9')
                numar += s[i++];
            i--;
            rez += numar + ' ';
            continue;
        }
        aux += s[i];
        if (esteOperator(aux))
        {
            insereazaOperator(aux,rez);
            aux = "";
        }
        else if (esteConstanta(aux) || esteVariabila(aux))
        {
            rez += aux + ' ';
            aux = "";
        }
        else if (aux[0] == '(')
        {
            stivaStr.push(aux);
            aux = "";
        }
        else if (aux[0] == ')')
        {
            scoateParanteza(rez);
            aux = "";
        }
    }
    if (aux != "")
        throw "WRONG";
    while (!stivaStr.empty())
    {
        rez += stivaStr.top() + ' ';
        stivaStr.pop();
    }
}

arboreBinar creeazaArboreExpresie(string exp)
{
    string aux;
    int n = exp.length();

    for (int i=0;i<n;i++)
    {
        if (exp[i] == ' ')
        {
            if (esteOperator(aux))
            {
                arboreBinar aux2 = new nodAB(aux);
                aux2->dr = stivaArb.top();
                stivaArb.pop();
                if (aux == "+" || aux == "-" || aux == "*" || aux == "/" || aux == "^")
                {
                    aux2->st = stivaArb.top();
                    stivaArb.pop();
                }
                stivaArb.push(aux2);
            }
            else
            {
                arboreBinar aux2 = new nodAB(aux);
                stivaArb.push(aux2);
            }
            aux = "";
        }
        else
            aux += exp[i];
    }
    return stivaArb.top();
}

void insereazaOperator(string s,string &rez)
{
    while (!stivaStr.empty() && stivaStr.top()[0] != '(' && prioritate(stivaStr.top()) <= prioritate(s))
    {
        rez += stivaStr.top() + ' ';
        stivaStr.pop();
    }
    stivaStr.push(s);
}

void scoateParanteza(string &rez)
{
    while (stivaStr.top()[0] != '(')
    {
        rez += stivaStr.top() + ' ';
        stivaStr.pop();
    }
    stivaStr.pop();
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
    {
        if (i == 0 && s[i] == '-' && lg > 1)
            continue;
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

int esteTrigonometrica(string s)
{
    if (s == "sin")
        return 1;
    if (s == "cos")
        return 2;
    if (s == "tg")
        return 3;
    if (s == "ctg")
        return 4;
    return 0;
}

int esteTrigonometricaInversa(string s)
{
    if (s == "arcsin")
        return 1;
    if (s == "arccos")
        return 2;
    if (s == "arctg")
        return 3;
    if (s == "arcctg")
        return 4;
    return 0;
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
