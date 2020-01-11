#include "derivare.h"

arbore derivare(arbore A)
{
    if (esteVariabila(A->inf))
    {
        arbore rez = new nodAB("1");
        return rez;
    }
    else if (esteConstanta(A->inf) || esteNumar(A->inf))
    {
        arbore rez = new nodAB("0");
        return rez;
    }
    else
    {
        if (A->inf == "+")
            return derivareAdunare(A);
        else if (A->inf == "-")
            return derivareScadere(A);
        else if (A->inf == "*")
            return derivareInmultire(A);
        else if (A->inf == "/")
            return derivareImpartire(A);
        else if (A->inf == "^")
            return derivarePutere(A);
        else if (A->inf == "sin")
            return derivareSin(A);
        else if (A->inf == "cos")
            return derivareCos(A);
        else if (A->inf == "tg")
            return derivareTg(A);
        else if (A->inf == "ctg")
            return derivareCtg(A);
        else if (A->inf == "arcsin")
            return derivareArcsin(A);
        else if (A->inf == "arccos")
            return derivareArccos(A);
        else if (A->inf == "arctg")
            return derivareArctg(A);
        else if (A->inf == "arcctg")
            return derivareArcctg(A);
        else if (A->inf == "ln")
            return derivareLn(A);
        throw "Operatie necunoscuta";
    }
}

arbore derivareAdunare(arbore A)
{
    //(f+g)' = f'+g'
    arbore rez = new nodAB("+");
    arbore f = A->st;
    arbore g = A->dr;

    rez->st = derivare(f);
    rez->dr = derivare(g);

    return rez;
}

arbore derivareScadere(arbore A)
{
    //(f-g)' = f'-g'
    arbore rez = new nodAB("-");
    arbore f = A->st;
    arbore g = A->dr;

    rez->st = derivare(f);
    rez->dr = derivare(g);

    return rez;
}

arbore derivareInmultire(arbore A)
{
    //(f*g)' = f'g+g'f
    arbore rez = new nodAB("+");
    arbore f = A->st;
    arbore g = A->dr;


    arbore FiuSt = new nodAB("*");
    FiuSt->st=derivare(f);
    FiuSt->dr=copie(g);
    rez->st=FiuSt;

    arbore FiuDr = new nodAB("*");
    FiuDr->st=copie(f);
    FiuDr->dr=derivare(g);
    rez->dr=FiuDr;

    return rez;

}

arbore derivareImpartire(arbore A)
{
    //(f/g)' = (f'*g-f*g')/(g^2)
    arbore f = A->st;
    arbore g = A->dr;
    arbore rez = new nodAB("/");

    arbore numarator = new nodAB("-");
    arbore t1 = new nodAB("*");
    t1->st = derivare(f);
    t1->dr = copie(g);
    arbore t2 = new nodAB("*");
    t2->st = copie(f);
    t2->dr = derivare(g);
    numarator->st = t1;
    numarator->dr = t2;

    arbore numitor = new nodAB("^");
    numitor->st = copie(g);
    numitor->dr = new nodAB("2");

    rez->st = numarator;
    rez->dr = numitor;
    return rez;
}

arbore derivarePutere(arbore A)
{
    //(f^g)' = (f^g)*(g*ln(f))'
    arbore f = A->st;
    arbore g = A->dr;
    arbore rez = new nodAB("*");

    rez->st = A;

    arbore t2 = new nodAB("*");
    t2->st = copie(g);
    t2->dr = new nodAB("ln");
    t2->dr->dr = copie(f);
    rez->dr = derivare(t2);

    return rez;

}

arbore derivareSin(arbore A)
{
    //sin(f)' = cos(f)*f'
    arbore rez = new nodAB("*");
    arbore f = A->dr;

    arbore FiuSt = new nodAB("cos");
    FiuSt->dr=copie(f);
    rez->st=FiuSt;

    rez->dr=derivare(f);

    return rez;
}

arbore derivareCos(arbore A)
{
    //cos(f)' = -cos(f)*f'
    arbore rez = new nodAB("*");
    arbore f = A->dr;

    arbore FiuSt = new nodAB("*");
    arbore t1 = new nodAB("-1");
    arbore t2 = new nodAB("sin");
    t2->dr=f;

    FiuSt->st=t1;
    FiuSt->dr=t2;

    rez->st=FiuSt;
    rez->dr=derivare(f);

    return rez;
}

arbore derivareTg(arbore A)
{
    //tg(f)' = f'/cos(f)^2
    arbore f = A->dr;
    arbore rez = new nodAB("/");

    rez->st = derivare(f);

    arbore numitor = new nodAB("^");
    numitor->st = new nodAB("cos");
    numitor->st->dr = copie(f);
    numitor->dr = new nodAB("2");
    rez ->dr = numitor;

    return rez;
}

arbore derivareCtg(arbore A)
{
    //ctg(f)' = -f'/sin(f)^2
    arbore f = A->dr;
    arbore rez = new nodAB("/");

    arbore numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr= derivare(f);
    rez->st=  numarator;

    arbore numitor = new nodAB("^");
    numitor->st = new nodAB("sin");
    numitor->st->dr = copie(f);
    numitor->dr = new nodAB("2");
    rez ->dr = numitor;

    return rez;
}

arbore derivareArcsin(arbore A)
{
    //arcsin(f)' = f'/sqrt(1-f^2)
    arbore rez = new nodAB("/");
    arbore f = A->dr;

    rez->st = derivare(f);

    arbore numitor = new nodAB("^");

    arbore subRadical = new nodAB("-");
    subRadical->st = new nodAB("1");
    subRadical->dr = new nodAB("^");
    subRadical->dr->st = copie(f);
    subRadical->dr->dr = new nodAB("2");

    numitor->st = subRadical;
    numitor->dr = new nodAB("/");
    numitor->dr->st = new nodAB("1");
    numitor->dr->dr = new nodAB("2");

    rez->dr = numitor;
    return rez;
}

arbore derivareArccos(arbore A)
{
    //arccos(f)' = -f'/sqrt(1-f^2)
    arbore rez = new nodAB("/");
    arbore f = A->dr;

    arbore numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr = derivare(f);

    arbore numitor = new nodAB("^");

    arbore subRadical = new nodAB("-");
    subRadical->st = new nodAB("1");
    subRadical->dr = new nodAB("^");
    subRadical->dr->st = copie(f);
    subRadical->dr->dr = new nodAB("2");

    numitor->st = subRadical;
    numitor->dr = new nodAB("/");
    numitor->dr->st = new nodAB("1");
    numitor->dr->dr = new nodAB("2");

    rez->st = numarator;
    rez->dr = numitor;
    return rez;
}

arbore derivareArctg(arbore A)
{
    //arctg(f)' = f'/(1+f^2)
    arbore f = A->dr;
    arbore rez = new nodAB("/");

    rez->st = derivare(f);

    arbore numitor = new nodAB("+");
    numitor->st = new nodAB("1");
    numitor->dr = new nodAB("^");
    numitor->dr->st = copie(f);
    numitor->dr->dr = new nodAB("2");
    rez->dr = numitor;

    return rez;
}

arbore derivareArcctg(arbore A)
{
    //arcctg(f)' = -f'/(1+f^2)
    arbore f = A->dr;
    arbore rez = new nodAB("/");

    arbore numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr = derivare(f);
    rez->st = numarator;

    arbore numitor = new nodAB("+");
    numitor->st = new nodAB("1");
    numitor->dr = new nodAB("^");
    numitor->dr->st = copie(f);
    numitor->dr->dr = new nodAB("2");
    rez->dr = numitor;

    return rez;
}

arbore derivareLn(arbore A)
{
    //ln(f)' = f'/f
    arbore f = A->dr;
    arbore rez = new nodAB("/");

    rez->st = derivare(f);
    rez->dr = copie(f);

    return rez;
}

arbore copie(arbore A)
{
    if (!A)
        return nullptr;
    arbore rez = new nodAB(A->inf);
    rez->st = copie(A->st);
    rez->dr = copie(A->dr);
    return rez;
}

void simplifica(arbore &A)
{
    if (!A || !esteOperator(A->inf))
        return;

    simplifica(A->st);
    simplifica(A->dr);

    if (A->inf == "+")
        simplificaAdunare(A);
    else if (A->inf == "-")
        simplificaScadere(A);
    else if (A->inf == "*")
        simplificaInmultire(A);
    else if (A->inf == "/")
        simplificaImpartire(A);
    else if (A->inf == "^")
    {

    }
    else if (A->inf == "sin")
    {

    }
    else if (A->inf == "cos")
    {

    }
    else if (A->inf == "ln")
    {

    }
}

void simplificaAdunare(arbore&A)
{
    arbore fiuSt = A->st;
    arbore fiuDr = A->dr;

    if (esteNumar(fiuSt->inf) && esteNumar(fiuDr->inf))
    {
        int nr1 = stoi(fiuSt->inf);
        int nr2 = stoi(fiuDr->inf);
        delete fiuSt;
        delete fiuDr;
        A->st = nullptr;
        A->dr = nullptr;
        A->inf = to_string(nr1 + nr2);
    }
    else if (esteNumar(fiuSt->inf))
    {
        int nr = stoi(fiuSt->inf);
        if (nr == 0)
        {
            A = fiuDr;
            delete fiuSt;
        }
    }
    else if (esteNumar(fiuDr->inf))
    {
        int nr = stoi(fiuDr->inf);
        if (nr == 0)
        {
            A = fiuSt;
            delete fiuDr;
        }
    }
}

void simplificaScadere(arbore&A)
{
    arbore fiuSt = A->st;
    arbore fiuDr = A->dr;

    if (esteNumar(fiuSt->inf) && esteNumar(fiuDr->inf))
    {
        int nr1 = stoi(fiuSt->inf);
        int nr2 = stoi(fiuDr->inf);
        delete fiuSt;
        delete fiuDr;
        A->st = nullptr;
        A->dr = nullptr;
        A->inf = to_string(nr1 - nr2);
    }
    else if (esteNumar(fiuDr->inf))
    {
        int nr = stoi(fiuDr->inf);
        if (nr == 0)
        {
            A = fiuSt;
            delete fiuDr;
        }
    }
}

void simplificaInmultire(arbore&A)
{
    arbore fiuSt = A->st;
    arbore fiuDr = A->dr;

    if (esteNumar(fiuSt->inf) && esteNumar(fiuDr->inf))
    {
        int nr1 = stoi(fiuSt->inf);
        int nr2 = stoi(fiuDr->inf);
        delete fiuSt;
        delete fiuDr;
        A->st = nullptr;
        A->dr = nullptr;
        A->inf = to_string(nr1 * nr2);
    }
    else if (esteNumar(fiuSt->inf))
    {
        int nr = stoi(fiuSt->inf);
        if (nr == 0)
        {
            delete fiuSt;
            delete fiuDr;
            A->st = nullptr;
            A->dr = nullptr;
            A->inf = "0";
        }
        else if (nr == 1)
        {
            delete fiuSt;
            A = fiuDr;
        }
    }
    else if (esteNumar(fiuDr->inf))
    {
        int nr = stoi(fiuDr->inf);
        if (nr == 0)
        {
            delete fiuSt;
            delete fiuDr;
            A->st = nullptr;
            A->dr = nullptr;
            A->inf = "0";
        }
        else if (nr == 1)
        {
            delete fiuDr;
            A = fiuSt;
        }
    }
}

void simplificaImpartire(arbore &A)
{
    arbore fiuSt = A->st;
    arbore fiuDr = A->dr;

    if (esteNumar(fiuSt->inf) && esteNumar(fiuDr->inf))
    {
        int nr1 = stoi(fiuSt->inf);
        int nr2 = stoi(fiuDr->inf);
        if (nr1 % nr2 == 0)
        {
            delete fiuSt;
            delete fiuDr;
            A->st = nullptr;
            A->dr = nullptr;
            A->inf = to_string(nr1 / nr2);
        }
    }
    else if (esteNumar(fiuSt->inf))
    {
        int nr = stoi(fiuSt->inf);
        if (nr == 0)
        {
            delete fiuSt;
            delete fiuDr;
            A->st = nullptr;
            A->dr = nullptr;
            A->inf = "0";
        }
    }
    else if (esteNumar(fiuDr->inf))
    {
        int nr = stoi(fiuDr->inf);
        if (nr == 1)
        {
            delete fiuDr;
            A = fiuSt;
        }
    }
}