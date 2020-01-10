#include "prelucrare.h"
#include <cstring>

void transforma(string &exp)
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