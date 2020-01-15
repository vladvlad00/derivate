#include "prelucrare.h"
#include "postordine.h"

struct nodSimplificat
{
    string inf;
    nodSimplificat *fii[105];
    int nrFii;

    nodSimplificat(string s="")
    {
        inf = s;
        nrFii = 0;
    }

    void adaugaFiu(nodSimplificat *x)
    {
        if (!x)
            return;
        fii[++nrFii] = x;
    }
};

typedef nodSimplificat* arboreSimplificat;

void restrange(arboreSimplificat&B);
void adaugaCoeficienti(arboreSimplificat&B);
void simplifica(arboreSimplificat&B);
void simplificaAdunare(arboreSimplificat&B);
void daInFactor(arboreSimplificat&B);
void simplificaInmultire(arboreSimplificat&B);
void adunaExponenti(arboreSimplificat&B);
void simplificaPutere(arboreSimplificat&B);
void simplificaTrigonometrice(arboreSimplificat&B);
void simplificaTrigonometriceInverse(arboreSimplificat&B);
void simplificaLn(arboreSimplificat&B);
void scoateInutile(arboreSimplificat&B);
void refaImpartiri(arboreSimplificat&B);
void refaScaderi(arboreSimplificat&B);
void puneRadicali(arboreSimplificat&B);

bool expresiiCompatibile(arboreSimplificat B1, arboreSimplificat B2);
bool expresiiEgale(arboreSimplificat B1, arboreSimplificat B2);
void combina(arboreSimplificat&B1, arboreSimplificat B2);
void curataFii(arboreSimplificat&B);

void afisare(arboreBinar A);
void pregateste(arboreBinar&A);
arboreSimplificat transformaArbore(arboreBinar A);
void cautaPlus(arboreSimplificat B, arboreSimplificat&rez);
void cautaInmultit(arboreSimplificat B, arboreSimplificat&rez);
void cautaPutere(arboreSimplificat B, arboreSimplificat&rez);
void scrie(arboreSimplificat B);
void stergeSubarbore(arboreSimplificat&B);
void stergeFii(arboreSimplificat&B);