#include "derivare.h"
#include "postordine.h"

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
        if (A->inf == "/")
            return derivareImpartire(A);
        else if (A->inf == "^")
            return derivarePutere(A);
        else if (A->inf == "tg")
            return derivareTg(A);
        else if (A->inf == "ctg")
            return derivareCtg(A);
        else if (A->inf == "arctg")
            return derivareArctg(A);
        else if (A->inf == "arcctg")
            return derivareArcctg(A);
        else if (A->inf == "ln")
            return derivareLn(A);
    }
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
    t1->dr = g;
    arbore t2 = new nodAB("*");
    t2->st = f;
    t2->dr = derivare(g);
    numarator->st = t1;
    numarator->dr = t2;

    arbore numitor = new nodAB("^");
    numitor->st = g;
    numitor->dr = new nodAB("2");

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
    t2->st = g;
    t2->dr = new nodAB("ln");
    t2->dr->dr = f;
    rez->dr = derivare(t2);

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
    numitor->st->dr = f;
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
    numitor->st->dr = f;
    numitor->dr = new nodAB("2");
    rez ->dr = numitor;

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
    numitor->dr->st = f;
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
    numitor->dr->st = f;
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
    rez->dr = f;

    return rez;
}