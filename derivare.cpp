#include "derivare.h"

arboreBinar derivare(arboreBinar A)
{
    if (esteVariabila(A->inf))
    {
        arboreBinar rez = new nodAB("1");
        return rez;
    }
    else if (esteConstanta(A->inf) || esteNumar(A->inf))
    {
        arboreBinar rez = new nodAB("0");
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

arboreBinar derivareAdunare(arboreBinar A)
{
    //(f+g)' = f'+g'
    arboreBinar rez = new nodAB("+");
    arboreBinar f = A->st;
    arboreBinar g = A->dr;

    rez->st = derivare(f);
    rez->dr = derivare(g);

    return rez;
}

arboreBinar derivareScadere(arboreBinar A)
{
    //(f-g)' = f'-g'
    arboreBinar rez = new nodAB("-");
    arboreBinar f = A->st;
    arboreBinar g = A->dr;

    rez->st = derivare(f);
    rez->dr = derivare(g);

    return rez;
}

arboreBinar derivareInmultire(arboreBinar A)
{
    //(f*g)' = f'g+g'f
    arboreBinar rez = new nodAB("+");
    arboreBinar f = A->st;
    arboreBinar g = A->dr;


    arboreBinar FiuSt = new nodAB("*");
    FiuSt->st=derivare(f);
    FiuSt->dr=copie(g);
    rez->st=FiuSt;

    arboreBinar FiuDr = new nodAB("*");
    FiuDr->st=copie(f);
    FiuDr->dr=derivare(g);
    rez->dr=FiuDr;

    return rez;

}

arboreBinar derivareImpartire(arboreBinar A)
{
    //(f/g)' = (f'*g-f*g')/(g^2)
    arboreBinar f = A->st;
    arboreBinar g = A->dr;
    arboreBinar rez = new nodAB("/");

    arboreBinar numarator = new nodAB("-");
    arboreBinar t1 = new nodAB("*");
    t1->st = derivare(f);
    t1->dr = copie(g);
    arboreBinar t2 = new nodAB("*");
    t2->st = copie(f);
    t2->dr = derivare(g);
    numarator->st = t1;
    numarator->dr = t2;

    arboreBinar numitor = new nodAB("^");
    numitor->st = copie(g);
    numitor->dr = new nodAB("2");

    rez->st = numarator;
    rez->dr = numitor;
    return rez;
}

arboreBinar derivarePutere(arboreBinar A)
{
    //(f^g)' = (f^g)*(g*ln(f))'
    arboreBinar f = A->st;
    arboreBinar g = A->dr;
    arboreBinar rez = new nodAB("*");

    rez->st = A;

    arboreBinar t2 = new nodAB("*");
    t2->st = copie(g);
    t2->dr = new nodAB("ln");
    t2->dr->dr = copie(f);
    rez->dr = derivare(t2);

    return rez;

}

arboreBinar derivareSin(arboreBinar A)
{
    //sin(f)' = cos(f)*f'
    arboreBinar rez = new nodAB("*");
    arboreBinar f = A->dr;

    arboreBinar FiuSt = new nodAB("cos");
    FiuSt->dr=copie(f);
    rez->st=FiuSt;

    rez->dr=derivare(f);

    return rez;
}

arboreBinar derivareCos(arboreBinar A)
{
    //cos(f)' = -cos(f)*f'
    arboreBinar rez = new nodAB("*");
    arboreBinar f = A->dr;

    arboreBinar FiuSt = new nodAB("*");
    arboreBinar t1 = new nodAB("-1");
    arboreBinar t2 = new nodAB("sin");
    t2->dr=f;

    FiuSt->st=t1;
    FiuSt->dr=t2;

    rez->st=FiuSt;
    rez->dr=derivare(f);

    return rez;
}

arboreBinar derivareTg(arboreBinar A)
{
    //tg(f)' = f'/cos(f)^2
    arboreBinar f = A->dr;
    arboreBinar rez = new nodAB("/");

    rez->st = derivare(f);

    arboreBinar numitor = new nodAB("^");
    numitor->st = new nodAB("cos");
    numitor->st->dr = copie(f);
    numitor->dr = new nodAB("2");
    rez ->dr = numitor;

    return rez;
}

arboreBinar derivareCtg(arboreBinar A)
{
    //ctg(f)' = -f'/sin(f)^2
    arboreBinar f = A->dr;
    arboreBinar rez = new nodAB("/");

    arboreBinar numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr= derivare(f);
    rez->st=  numarator;

    arboreBinar numitor = new nodAB("^");
    numitor->st = new nodAB("sin");
    numitor->st->dr = copie(f);
    numitor->dr = new nodAB("2");
    rez ->dr = numitor;

    return rez;
}

arboreBinar derivareArcsin(arboreBinar A)
{
    //arcsin(f)' = f'/sqrt(1-f^2)
    arboreBinar rez = new nodAB("/");
    arboreBinar f = A->dr;

    rez->st = derivare(f);

    arboreBinar numitor = new nodAB("^");

    arboreBinar subRadical = new nodAB("-");
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

arboreBinar derivareArccos(arboreBinar A)
{
    //arccos(f)' = -f'/sqrt(1-f^2)
    arboreBinar rez = new nodAB("/");
    arboreBinar f = A->dr;

    arboreBinar numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr = derivare(f);

    arboreBinar numitor = new nodAB("^");

    arboreBinar subRadical = new nodAB("-");
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

arboreBinar derivareArctg(arboreBinar A)
{
    //arctg(f)' = f'/(1+f^2)
    arboreBinar f = A->dr;
    arboreBinar rez = new nodAB("/");

    rez->st = derivare(f);

    arboreBinar numitor = new nodAB("+");
    numitor->st = new nodAB("1");
    numitor->dr = new nodAB("^");
    numitor->dr->st = copie(f);
    numitor->dr->dr = new nodAB("2");
    rez->dr = numitor;

    return rez;
}

arboreBinar derivareArcctg(arboreBinar A)
{
    //arcctg(f)' = -f'/(1+f^2)
    arboreBinar f = A->dr;
    arboreBinar rez = new nodAB("/");

    arboreBinar numarator = new nodAB("*");
    numarator->st = new nodAB("-1");
    numarator->dr = derivare(f);
    rez->st = numarator;

    arboreBinar numitor = new nodAB("+");
    numitor->st = new nodAB("1");
    numitor->dr = new nodAB("^");
    numitor->dr->st = copie(f);
    numitor->dr->dr = new nodAB("2");
    rez->dr = numitor;

    return rez;
}

arboreBinar derivareLn(arboreBinar A)
{
    //ln(f)' = f'/f
    arboreBinar f = A->dr;
    arboreBinar rez = new nodAB("/");

    rez->st = derivare(f);
    rez->dr = copie(f);

    return rez;
}

arboreBinar copie(arboreBinar A)
{
    if (!A)
        return nullptr;
    arboreBinar rez = new nodAB(A->inf);
    rez->st = copie(A->st);
    rez->dr = copie(A->dr);
    return rez;
}
