#include <iostream>
#include "simplificare.h"
#include <graphics.h>
#include "winbgim.h"

int modificare;


void afisare(arboreBinar A)
{
    pregateste(A);
    arboreSimplificat B = transformaArbore(A);

    do
    {
        modificare = 0;
        restrange(B);
        simplifica(B);
        scoateInutile(B);
    } while (modificare);
    refaImpartiri(B);
    if (B->inf == "^" && esteNumar(B->fii[2]->inf) &&  stoi(B->fii[2]->inf) < 0) //am impartire in radacina
    {
        arboreSimplificat impartire = new nodSimplificat("/");
        int numar = stoi(B->fii[2]->inf);
        B->fii[2]->inf = to_string(-numar);;
        arboreSimplificat aux = new nodSimplificat("1");
        impartire->adaugaFiu(aux);
        impartire->adaugaFiu(B);
        B = impartire;
    }
    scoateInutile(B);
    refaScaderi(B);
    puneRadicali(B);
    scoateInutile(B);
    scrie(B);
}

int nrlit;

void scrie(arboreSimplificat B)
{
    if (!esteOperator(B->inf))
    {
        bgiout<< B->inf; nrlit++;
        return;
    }

    for (int i=1;i<=B->nrFii;i++)
    {
        arboreSimplificat nod = B->fii[i];
        if ((i > 1 || B->nrFii == 1) && !(B->inf == "+" && nod->inf == "-"))
            {bgiout << B->inf; nrlit++;

            if(nrlit>60 && (B->inf=="+" || B->inf=="-" || B->inf=="*"))
                {
                bgiout<<'\n';
                bgiout << B->inf;
                nrlit=0;
                }
            }
        if ((esteOperator(nod->inf) && (prioritate(nod->inf) > prioritate(B->inf) || ((B->inf == "^" || B->inf == "/") && prioritate(nod->inf) > 1))) || prioritate(B->inf) == 1)
        {
            bgiout<< '('; nrlit++;
            scrie(nod);
            bgiout<< ')'; nrlit++;
        }
        else
        scrie(nod);
    }
}

void pregateste(arboreBinar &A)
{
    if (!A)
        return;
    pregateste(A->st);
    pregateste(A->dr);
    if (A->inf == "/")
    {
        A->inf = "*";
        arboreBinar numitor = new nodAB("^");
        numitor->st = A->dr;
        numitor->dr = new nodAB("-1");
        A->dr = numitor;
    }
    else if (A->inf == "-")
    {
        A->inf = "+";
        arboreBinar scazator = new nodAB("*");
        scazator->st = new nodAB("-1");
        scazator->dr = A->dr;
        A->dr = scazator;
    }
    else if (esteVariabila(A->inf) || esteConstanta(A->inf) || (A->inf != "+" && A->inf != "*" && esteOperator(A->inf)))
    {
        arboreBinar aux = new nodAB("^");
        aux->st = A;
        aux->dr = new nodAB("1");

        arboreBinar aux2 = new nodAB("*");
        aux2->st = new nodAB("1");
        aux2->dr = aux;

        A = aux2;
    }
}

arboreSimplificat transformaArbore(arboreBinar A)
{
    if (!A)
        return nullptr;

    arboreSimplificat rez = new nodSimplificat(A->inf);

    rez->adaugaFiu(transformaArbore(A->st));
    rez->adaugaFiu(transformaArbore(A->dr));

    return rez;
}

void restrange(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        restrange(B->fii[i]);

    if (B->inf == "+")
    {
        arboreSimplificat rez = new nodSimplificat("+");
        cautaPlus(B,rez);
        B = rez;
    }
    else if (B->inf == "*")
    {
        arboreSimplificat rez = new nodSimplificat("*");
        cautaInmultit(B,rez);
        B = rez;
    }
    else if (B->inf == "^")
    {
        if (B->fii[1]->inf == "^" && esteNumar(B->fii[2]->inf))
            cautaPutere(B->fii[1],B);
    }
}

void cautaPlus(arboreSimplificat B, arboreSimplificat&rez)
{
    if (B->inf == "+")
    {
        for (int i=1;i<=B->nrFii;i++)
            cautaPlus(B->fii[i], rez);
    }
    else
        rez->adaugaFiu(B);
}

void cautaInmultit(arboreSimplificat B, arboreSimplificat&rez)
{
    if (B->inf == "*")
    {
        for (int i=1;i<=B->nrFii;i++)
            cautaInmultit(B->fii[i], rez);
    }
    else
        rez->adaugaFiu(B);
}

void cautaPutere(arboreSimplificat B, arboreSimplificat&rez)
{
    if (esteNumar(B->fii[2]->inf))
    {
        rez->fii[2]->inf = to_string(stoi(rez->fii[2]->inf)*stoi(B->fii[2]->inf));
        if (B->fii[1]->inf == "^")
            cautaPutere(B->fii[1],rez);
        else rez->fii[1] = B->fii[1];
    }
    else
        rez->fii[1] = B;
}

void simplifica(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        simplifica(B->fii[i]);
    if (B->inf == "+")
        simplificaAdunare(B);
    else if (B->inf == "*")
        simplificaInmultire(B);
    else if (B->inf == "^")
        simplificaPutere(B);
    else if (esteTrigonometrica(B->inf))
        simplificaTrigonometrice(B);
    else if (esteTrigonometricaInversa(B->inf))
        simplificaTrigonometriceInverse(B);
    else if (B->inf == "ln")
        simplificaLn(B);

}

void simplificaAdunare(arboreSimplificat&B)
{
    //0+0+0+0+0
    bool nenul = false;
    for (int i=1;i<=B->nrFii;i++)
    {
        arboreSimplificat nod = B->fii[i];
        if (nod->inf != "0")
        {
            nenul = true;
            break;
        }
    }
    if (!nenul)
    {
        modificare = 1;
        stergeFii(B);
        B->inf = "0";
    }
    else
    {
        arboreSimplificat rez = new nodSimplificat("+");
        int pozNumar = -1;
        int suma = 0;
        for (int i=1;i<=B->nrFii;i++)
        {
            arboreSimplificat nod = B->fii[i];
            if (nod->inf == "^" && nod->fii[1]->inf == "sin" && nod->fii[2]->inf == "2")
            {
                if (cautaCos(B,nod->fii[1]->fii[1]))
                {
                    stergeFii(B->fii[i]);
                    B->fii[i]->inf = "1";
                }
            }
            if (esteNumar(nod->inf))
            {
                suma += stoi(nod->inf);
                if (pozNumar == -1)
                {
                    pozNumar = i;
                    rez->adaugaFiu(nod);
                }
                else
                {
                    delete nod;
                    modificare = 1;
                }
            }
            else
                rez->adaugaFiu(nod);
        }
        if (pozNumar != -1)
            rez->fii[pozNumar]->inf = to_string(suma);
        if (rez->nrFii == 1)
        {
            modificare = 1;
            arboreSimplificat copie = rez->fii[1];
            delete rez;
            rez = copie;
        }
        else
            daInFactor(rez);
        B = rez;
    }
}

bool cautaCos(arboreSimplificat&B, arboreSimplificat exp)
{
    for (int i=1;i<=B->nrFii;i++)
    {
        arboreSimplificat nod = B->fii[i];
        if (nod->inf == "^" && nod->fii[1]->inf == "cos" && nod->fii[2]->inf == "2")
            if (expresiiEgale(nod->fii[1]->fii[1],exp))
            {
                B->fii[i]->inf = "$";
                return true;
            }
    }
    return false;
}

void daInFactor(arboreSimplificat&B)
{
    int uz[105] = {0};

    for (int i=1;i<B->nrFii;i++)
    {
        if (uz[i] || B->fii[i]->inf != "*")
            continue;
        for (int j=i+1;j<=B->nrFii;j++)
        {
            if (B->fii[j]->inf != "*")
                continue;
            if (expresiiCompatibile(B->fii[i], B->fii[j]))
            {
                modificare = 1;
                combina(B->fii[i], B->fii[j]);
                B->fii[j]->inf = "$"; //trebuie sters
                uz[j] = 1;
            }
        }
    }
    curataFii(B);
    if (B->nrFii == 1)
    {
        B = B->fii[1];
        modificare = 1;
    }
}

void simplificaInmultire(arboreSimplificat&B)
{
    bool nenul = true;

    for (int i=1;i<=B->nrFii;i++)
    {
        arboreSimplificat nod = B->fii[i];
        if (nod->inf == "0")
        {
            nenul = false;
            break;
        }
    }
    if (!nenul)
    {
        stergeFii(B);
        B->inf = "0";
        modificare = 1;
    }
    else
    {
        arboreSimplificat rez = new nodSimplificat("*");
        int pozNumar = -1;
        int prod = 1;
        for (int i=1;i<=B->nrFii;i++)
        {
            arboreSimplificat nod = B->fii[i];
            if (esteNumar(nod->inf))
            {
                prod *= stoi(nod->inf);
                if (pozNumar == -1)
                {
                    pozNumar = i;
                    rez->adaugaFiu(nod);
                }
                else
                {
                    delete nod;
                    modificare = 1;
                }
            }
            else
                rez->adaugaFiu(nod);
        }
        if (pozNumar != -1)
            rez->fii[pozNumar]->inf = to_string(prod);
        if (rez->nrFii == 1)
        {
            modificare = 1;
            arboreSimplificat copie = rez->fii[1];
            delete rez;
            rez = copie;
        }
        else
            adunaExponenti(rez);
        B = rez;
    }
}

void adunaExponenti(arboreSimplificat&B)
{
    int uz[105] = {0};

    for (int i=1;i<B->nrFii;i++)
    {
        if (uz[i] || B->fii[i]->inf != "^")
            continue;
        for (int j=i+1;j<=B->nrFii;j++)
        {
            if (B->fii[j]->inf != "^")
                continue;
            arboreSimplificat nod1 = B->fii[i];
            arboreSimplificat nod2 = B->fii[j];
            if (esteNumar(nod1->fii[2]->inf) && esteNumar(nod2->fii[2]->inf) && expresiiEgale(nod1->fii[1], nod2->fii[1]))
            {
                modificare = 1;
                nod1->fii[2]->inf = to_string(stoi(nod1->fii[2]->inf)+stoi(nod2->fii[2]->inf));
                B->fii[j]->inf = "$"; //trebuie sters
                uz[j] = 1;
            }
        }
    }
    curataFii(B);
    if (B->nrFii == 1)
    {
        B = B->fii[1];
        modificare = 1;
    }
}

void simplificaPutere(arboreSimplificat&B)
{
    if (esteNumar(B->fii[1]->inf) && esteNumar(B->fii[2]->inf))
    {
        int nr1 = stoi(B->fii[1]->inf);
        int nr2 = stoi(B->fii[2]->inf);
        int rez = 1;
        if (nr2 < 0)
            return;
        for (int i=1;i<=nr2;i++)
            rez *= nr1;
        delete B->fii[1];
        delete B->fii[2];
        B->nrFii = 0;
        B->inf = to_string(rez);
    }
}

void simplificaTrigonometrice(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        simplificaTrigonometrice(B->fii[i]);
    if (esteTrigonometrica(B->inf) && esteTrigonometricaInversa(B->fii[1]->inf) && esteTrigonometrica(B->inf) == esteTrigonometricaInversa(B->fii[1]->inf))
    {
        B = B->fii[1]->fii[1];
        modificare = 1;
    }
}

void simplificaTrigonometriceInverse(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        simplificaTrigonometriceInverse(B->fii[i]);
    if (esteTrigonometricaInversa(B->inf) && esteTrigonometrica(B->fii[1]->inf) && esteTrigonometricaInversa(B->inf) == esteTrigonometrica(B->fii[1]->inf))
    {
        B = B->fii[1]->fii[1];
        modificare = 1;
    }
}

void simplificaLn(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        simplificaLn(B->fii[i]);
    if (B->inf == "ln" && B->fii[1]->inf == "e")
    {
        stergeFii(B);
        B->inf = "1";
        modificare = 1;
    }
}

void refaImpartiri(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        refaImpartiri(B->fii[i]);
    bool gasitImpartire = false;
    for (int i=1;i<=B->nrFii;i++)
    {
        arboreSimplificat nod = B->fii[i];
        if (nod->inf == "^" && esteNumar(nod->fii[2]->inf) && stoi(nod->fii[2]->inf) < 0) //am gasit o impartire
        {
            gasitImpartire = true;
            break;
        }
    }
    if (gasitImpartire)
    {
        if (B->inf == "*")
        {
            arboreSimplificat numarator = new nodSimplificat("*");
            arboreSimplificat numitor = new nodSimplificat("*");

            for (int i=1;i<=B->nrFii;i++)
            {
                arboreSimplificat nod = B->fii[i];
                if (nod->inf == "^" && esteNumar(nod->fii[2]->inf) &&  stoi(nod->fii[2]->inf) < 0) //am gasit o impartire
                {
                    int numar = stoi(nod->fii[2]->inf);
                    nod->fii[2]->inf = to_string(-numar);
                    numitor->adaugaFiu(nod);
                }
                else
                    numarator->adaugaFiu(nod);
            }
            if (numarator->nrFii == 0)
                numarator->inf = "1";
            if (numarator->nrFii == 1)
            {
                arboreSimplificat copie = numarator->fii[1];
                delete numarator;
                numarator = copie;
            }
            if (numitor->nrFii == 1)
            {
                arboreSimplificat copie = numitor->fii[1];
                delete numitor;
                numitor = copie;
            }
            arboreSimplificat impartire = new nodSimplificat("/");
            impartire->adaugaFiu(numarator);
            impartire->adaugaFiu(numitor);
            B = impartire;
        }
        else
        {
            for (int i=1;i<=B->nrFii;i++)
            {
                arboreSimplificat nod = B->fii[i];
                if (nod->inf == "^" && esteNumar(nod->fii[2]->inf) &&  stoi(nod->fii[2]->inf) < 0) //am gasit o impartire
                {
                    arboreSimplificat impartire = new nodSimplificat("/");
                    int numar = stoi(nod->fii[2]->inf);
                    nod->fii[2]->inf = to_string(-numar);;
                    arboreSimplificat aux = new nodSimplificat("1");
                    impartire->adaugaFiu(aux);
                    impartire->adaugaFiu(nod);
                    nod = impartire;
                }
                B->fii[i] = nod;
            }
        }
    }
}

void refaScaderi(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        refaScaderi(B->fii[i]);
    if (B->inf == "*")
    {
        bool gasitMinus = false;
        for (int i=1;i<=B->nrFii;i++)
            if (esteNumar(B->fii[i]->inf) && stoi(B->fii[i]->inf) < 0)
            {
                gasitMinus = true;
                int numar = stoi(B->fii[i]->inf);
                if (numar == -1)
                    B->fii[i]->inf = "$";
                else
                    B->fii[i]->inf = to_string(-numar);
                break;
            }
        if (gasitMinus)
        {
            curataFii(B);
            arboreSimplificat aux = new nodSimplificat("-");
            aux->adaugaFiu(B);
            B = aux;
        }
    }
    else
    {
        for (int i=1;i<=B->nrFii;i++)
            if (esteNumar(B->fii[i]->inf) && stoi(B->fii[i]->inf) < 0)
            {
                int numar = stoi(B->fii[i]->inf);
                B->fii[i]->inf = to_string(-numar);
                arboreSimplificat scadere = new nodSimplificat("-");
                scadere->adaugaFiu(B->fii[i]);
                B->fii[i] = scadere;
            }
    }
}

void puneRadicali(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        puneRadicali(B->fii[i]);
    if (B->inf == "^")
    {
        arboreSimplificat fiu = B->fii[2];
        if (fiu->inf == "/" && fiu->fii[1]->inf == "1" && fiu->fii[2]->inf == "2")
        {
            B->inf = "sqrt";
            stergeSubarbore(fiu);
            B->nrFii--;
        }
        /*else if (fiu->inf == "2" && B->fii[1]->inf == "sqrt")
        {
            delete fiu;
            B = B->fii[1]->fii[1];
        }*/
    }
}

bool expresiiCompatibile(arboreSimplificat B1, arboreSimplificat B2)
{
    if (B1->nrFii != B2->nrFii)
        return false;
    if (B1->inf != B2->inf)
        return false;

    bool gasitNumar1= false, gasitNumar2=false;
    int n = B1->nrFii;
    for (int i=1;i<=n;i++)
    {
        arboreSimplificat nod1 = B1->fii[i];
        arboreSimplificat nod2 = B2->fii[i];

        if (esteNumar(nod1->inf))
            gasitNumar1 = true;
        if (esteNumar(nod2->inf))
            gasitNumar2 = true;
    }
    if (!gasitNumar1 || !gasitNumar2)
        return false;

    int uz[105] = {0};

    for (int i=1;i<=n;i++)
    {
        bool gasit = false;
        arboreSimplificat nod1 = B1->fii[i];
        if (esteNumar(nod1->inf))
            continue;
        for (int j=1;j<=n;j++)
        {
            if (uz[j])
                continue;
            arboreSimplificat nod2 = B2->fii[j];
            if (expresiiEgale(nod1,nod2))
            {
                uz[j] = 1;
                gasit = 1;
                break;
            }
        }
        if (!gasit)
            return false;
    }
    return true;
}

bool expresiiEgale(arboreSimplificat B1, arboreSimplificat B2)
{
    if (B1->nrFii != B2->nrFii)
        return false;
    if (B1->inf != B2->inf)
        return false;

    int uz[105] = {0};
    int n = B1->nrFii;

    for (int i=1;i<=n;i++)
    {
        bool gasit = false;
        arboreSimplificat nod1 = B1->fii[i];
        for (int j=1;j<=n;j++)
        {
            if (uz[j])
                continue;
            arboreSimplificat nod2 = B2->fii[j];
            if (expresiiEgale(nod1,nod2))
            {
                uz[j] = 1;
                gasit = 1;
                break;
            }
        }
        if (!gasit)
            return false;
    }
    return true;
}

void combina(arboreSimplificat&B1, arboreSimplificat B2)
{
    int n = B1->nrFii;
    int pozNumar1=69, pozNumar2=69;

    for (int i=1;i<=n;i++)
    {
        arboreSimplificat nod1 = B1->fii[i];
        arboreSimplificat nod2 = B2->fii[i];

        if (esteNumar(nod1->inf))
            pozNumar1 = i;
        if (esteNumar(nod2->inf))
            pozNumar2 = i;
    }
    int suma = stoi(B1->fii[pozNumar1]->inf) + stoi(B2->fii[pozNumar2]->inf);
    B1->fii[pozNumar1]->inf = to_string(suma);
}

void curataFii(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
    {
        if (B->fii[i]->inf == "$")
        {
            stergeSubarbore(B->fii[i]);
            for (int j=i;j<B->nrFii;j++)
                B->fii[j] = B->fii[j+1];
            B->nrFii--;
        }
    }
    if ((B->inf == "+" || B->inf == "*") && B->nrFii == 1)
        B = B->fii[1];
}

void stergeSubarbore(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        stergeSubarbore(B->fii[i]);
    delete B;
}

void stergeFii(arboreSimplificat&B)
{
    B->nrFii=0;
    for (int i=1;i<=B->nrFii;i++)
        stergeSubarbore(B->fii[i]);
}

void scoateInutile(arboreSimplificat&B)
{
    for (int i=1;i<=B->nrFii;i++)
        scoateInutile(B->fii[i]);
    if (B->inf == "+")
    {
        for (int i = 1; i <= B->nrFii; i++)
            if (B->fii[i]->inf == "0")
                B->fii[i]->inf = "$"; //trebuie sters
    }
    else if (B->inf == "*")
    {
        for (int i=1;i<=B->nrFii;i++)
        {
            if (B->fii[i]->inf == "1")
                B->fii[i]->inf = "$"; //trebuie sters
            else if (B->fii[i]->inf == "0")
            {
                stergeFii(B);
                B->inf = "0";
                return;
            }
        }
    }
    else if (B->inf == "^")
    {
        if (B->fii[2]->inf == "1")
        {
            delete B->fii[2];
            B = B->fii[1];
        }
        else if (B->fii[1]->inf == "0")
        {
            stergeFii(B);
            B->inf = "0";
        }
        else if (B->fii[2]->inf == "0")
        {
            stergeFii(B);
            B->inf = "1";
        }
    }
    else if (B->inf == "/")
    {
        if (expresiiEgale(B->fii[1],B->fii[2]))
        {
            stergeFii(B);
            B->inf = "1";
        }
    }
    curataFii(B);
}
