#include <string>

using namespace std;

const string OPERATORI[15] = {"+","-","*","/","^","sin","cos","tg","ctg","arcsin","arccos","arctg","arcctg","ln","sqrt"};
const string CONSTANTE[2] = {"e","pi"};
const string VARIABILE[4] = {"x","y","z"};

void postordine(string exp, string &rez);
void insereazaOperator(string s,string &rez);
void scoateParanteza(string &rez);
bool esteOperator(string s);
bool esteVariabila(string s);
bool esteConstanta(string s);
int prioritate(string s);
bool esteNumar(string s);
int esteTrigonometrica(string s);
int esteTrigonometricaInversa(string s);

struct nodAB
{
    string inf;
    nodAB *st;
    nodAB *dr;

    nodAB(string s)
    {
        inf = s;
        st = nullptr;
        dr = nullptr;
    }
};

typedef nodAB* arboreBinar;

arboreBinar creeazaArboreExpresie(string exp);

struct stivaString
{
    struct nod
    {
        nod *urm;
        string inf;

        nod(string s = "", nod*ptr= nullptr)
        {
            inf = s;
            urm=ptr;
        }
    };

    nod*inceput;
    int size;

    stivaString()
    {
        inceput= nullptr;
        size = 0;
    }

    void push(string s)
    {
        size++;
        nod *p = new nod(s,inceput);
        inceput=p;
    }

    void pop()
    {
        if (!inceput)
            throw "stiva vida";
        size--;
        nod *p = inceput;
        inceput = inceput->urm;
        delete p;
    }

    string top()
    {
        return inceput->inf;
    }

    bool empty()
    {
        return size == 0;
    }
};

struct stivaArbore
{
    struct nod
    {
        nod *urm;
        arboreBinar inf;

        nod(arboreBinar A = nullptr, nod*ptr= nullptr)
        {
            inf = A;
            urm=ptr;
        }
    };

    nod*inceput;
    int size;

    stivaArbore()
    {
        inceput= nullptr;
        size = 0;
    }

    void push(arboreBinar A)
    {
        size++;
        nod *p = new nod(A,inceput);
        inceput=p;
    }

    void pop()
    {
        if (!inceput)
            throw "stiva vida";
        size--;
        nod *p = inceput;
        inceput = inceput->urm;
        delete p;
    }

    arboreBinar top()
    {
        return inceput->inf;
    }

    bool empty()
    {
        return size == 0;
    }
};