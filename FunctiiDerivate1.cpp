arbore derivareAdunare(A)
    {
    arbore rez = new nodAB("+");
    arbore f = A->st;
    arbore g = A->dr;

    rez->st=derivare(f);
    rez->st=derivare(g);

    return rez;
    }

arbore derivareScadere(A)
    {
    arbore rez = new nodAB("-");
    arbore f = A->st;
    arbore g = A->dr;

    rez->st=derivare(f);
    rez->st=derivare(g);

    return rez;
    }


arbore derivareInmultire(A)
    {
    arbore rez = new nodAB("+");
    arbore f = A->st;
    arbore g = A->dr;


    arbore FiuSt = new nodAB("*");
    rez->st=FiuSt;
    FiuSt->st=derivare(f);
    FiuSt->dr=g;

    arbore FiuDr = new nodAB("*");
    rez->dr=FiuDr;
    FiuDr->st=f;
    FiuDr->dr=derivare(g);

    return rez;

    }

arbore derivareSin(A)
    {
    arbore rez = new nodAB("*");
    arbore f = A->dr;

    arbore FiuSt = new nodAB("cos");
    FiuSt->dr=f;
    rez->st=FiuSt;

    rez->dr=derivare(f);

    return rez;
    }

arbore derivareCos(A)
    {
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

arbore derivareArcSin(A)
    {
    arbore rez = new nodAB("*");
    arbore f = A->dr;

    arbore FiuSt = new nodAB("/");
    rez->st=FiuSt;

    arbore num1 = new nodAB("1");
    arbore num2 = new nodAB("^");

    FiuSt->st=num1;
    FiuSt->dr=num2;

    arbore e1 = new nodAB("-");
    arbore e2 = new nodAB("/");

    num2->st=e1;
    num2->dr=e2;

    arbore d1 = new nodAB("1");
    arbore d2 = new nodAB("^");

    e1->st=d1;
    e1->dr=d2;

    arbore ee1 = new nodAB("x");
    arbore ee2 = new nodAB("2");

    d1->st=ee1;
    d2->dr=ee2;

    arbore div1 = new nodAB("1");
    arbore div2 = new nodAB("2");

    e2->st=div1;
    e2->dr=div2;


    rez->dr=derivare(f);

    return rez;
    }

arbore derivareArcCos(A)
    {
    arbore rez = new nodAB("*");
    arbore f = A->dr;

    arbore FiuSt = new nodAB("/");
    rez->st=FiuSt;

    arbore num1 = new nodAB("-1");
    arbore num2 = new nodAB("^");

    FiuSt->st=num1;
    FiuSt->dr=num2;

    arbore e1 = new nodAB("-");
    arbore e2 = new nodAB("/");

    num2->st=e1;
    num2->dr=e2;

    arbore d1 = new nodAB("1");
    arbore d2 = new nodAB("^");

    e1->st=d1;
    e1->dr=d2;

    arbore ee1 = new nodAB("x");
    arbore ee2 = new nodAB("2");

    d1->st=ee1;
    d2->dr=ee2;

    arbore div1 = new nodAB("1");
    arbore div2 = new nodAB("2");

    e2->st=div1;
    e2->dr=div2;


    rez->dr=derivare(f);

    return rez;
    }

