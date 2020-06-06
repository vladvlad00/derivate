#include "prelucrare.h"

void transforma(string &exp)
{
    int lg = exp.length();
    int i, j, radical=0, paranteze[100]={0};
    string aux;

    j = 0;
    for (i=0;i<lg;i++)
    {
        if (exp.find("sqrt",i) == i) //suntem pe radical
        {
            radical++;
            paranteze[radical] = 0;
            i+=3; //sarim peste qrt
            continue;
        }
        if (esteLitera(exp[i]) || exp[i] == '(')
            if (i > 0 && esteCifra(exp[i - 1]))
                aux += '*';
        aux += exp[i];
        if (radical)
        {
            if (exp[i] == '(')
                paranteze[radical]++;
            if (exp[i] == ')')
            {
                paranteze[radical]--;
                if (!paranteze[radical]) //gata radicalul
                {
                    radical--;
                    aux+="^(1/2)";
                }
            }
        }
        if (exp[i] == '-' && (i == 0 || exp[i-1] == '('))
            aux += "1*";
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
