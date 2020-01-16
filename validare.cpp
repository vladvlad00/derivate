#include "validare.h"
#include "postordine.h"
#define NUMAR 1
#define VARIABILA 2
#define CONSTANTA 3
#define PARANTEZA_D 4
#define PARANTEZA_I 5
#define OPERATOR_B 6
#define OPERATOR_U 7

bool VerificareFunctie(string s)
{
    string aux;
    int n = s.length(), nrParanteze=0;
    int pre=0;

    if (n == 0)
        return false;
    for (int i=0;i<n;i++)
    {
        aux += s[i];
        if (esteNumar(aux))
        {
            if (pre == VARIABILA || pre == CONSTANTA || pre == PARANTEZA_I || pre == OPERATOR_U)
                return false;
            aux = "";
            pre = NUMAR;
        }
        else if (esteVariabila(aux))
        {
            if (pre == VARIABILA || pre == CONSTANTA || pre == PARANTEZA_I || pre == OPERATOR_U)
                return false;
            aux = "";
            pre = VARIABILA;
        }
        else if (esteConstanta(aux))
        {
            if (pre == VARIABILA || pre == CONSTANTA || pre == PARANTEZA_I || pre == OPERATOR_U)
                return false;
            aux = "";
            pre = CONSTANTA;
        }
        else if (esteOperator(aux))
        {
            if (i == n-1)
                return false;
            if (aux == "-")
            {
                if (pre == OPERATOR_U || pre == OPERATOR_B)
                    return false;
                aux = "";
                pre = OPERATOR_B;
            }
            else if (aux == "+" || aux == "*" || aux == "/" || aux == "^")
            {
                if (i == 0)
                    return false;
                if (pre == PARANTEZA_D || pre == OPERATOR_U || pre == OPERATOR_B)
                    return false;
                aux = "";
                pre = OPERATOR_B;
            }
            else
            {
                if (s[i+1] != '(')
                    return false;
                if (pre == VARIABILA || pre == CONSTANTA || pre == NUMAR || pre == PARANTEZA_I || pre == OPERATOR_U)
                    return false;
                aux = "";
                pre = OPERATOR_U;
            }
        }
        else if (aux == "(")
        {
            nrParanteze++;
            if (pre == VARIABILA || pre == CONSTANTA || pre == PARANTEZA_I)
                return false;
            aux = "";
            pre = PARANTEZA_D;
        }
        else if (aux == ")")
        {

            nrParanteze--;
            if (nrParanteze<0)
                return false;
            if (pre == OPERATOR_B || pre == OPERATOR_U || pre == PARANTEZA_D)
                return false;
            aux = "";
            pre = PARANTEZA_I;
        }
    }
    if (nrParanteze)
        return false;
    if (aux != "")
        return false;
    string variabila;
    for (int i=0; i<n; i++)
    {
        aux = s[i];
        if (esteVariabila(aux))
        {
            if (variabila == "")
                variabila = aux;
            else
            {
                if (aux != variabila)
                    return false;
            }
        }
    }
    return true;
}
