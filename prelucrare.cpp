#include "prelucrare.h"

void transforma(string &exp)  //MAI FA SA INLOCUIASCA SQRT CU ^(1/2) + CAZUL IN CARE E CEVA GEN -X -> -1*X
{
    int lg = exp.length();
    int i, j;
    string aux;

    j = 0;
    for (i=0;i<lg;i++)
    {
        if (esteLitera(exp[i]) || exp[i] == '(')
            if (i > 0 && esteCifra(exp[i - 1]))
                aux += '*';
        aux += exp[i];
    }
    exp = aux;
}

bool esteLitera(char c)
{
    return 'a' <= c && c <= 'z';
}

bool esteCifra(char c)
{
    return '0' <= c && c <= '9';
}