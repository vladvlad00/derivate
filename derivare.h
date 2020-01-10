#include <string>

using namespace std;

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

typedef nodAB* arbore;

arbore derivare(arbore A);
arbore derivareImpartire(arbore A);
arbore derivarePutere(arbore A);
arbore derivareTg(arbore A);
arbore derivareCtg(arbore A);
arbore derivareArctg(arbore A);
arbore derivareArcctg(arbore A);
arbore derivareLn(arbore A);