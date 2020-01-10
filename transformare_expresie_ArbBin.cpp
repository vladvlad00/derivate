#include <iostream>
#include <cstring>
#define NMAX 1000

using namespace std;


struct nodAB
{
char inf[10];
nodAB *st;
nodAB *dr;
};

struct nodList
{
char inf[10];
nodList *urm;
};

nodAB *stiva[NMAX];

void TransformareaExpresieiInArbBin(nodList *Postfix);

int main()
{
    nodList *Postfix = new nodList;
    TransformareaExpresieiInArbBin(Postfix);
    return 0;
}

void TransformareaExpresieiInArbBin(nodList *Postfix)
    {
    nodList *p=new nodList;
    p=Postfix;
    int top=0;

    while(p!=NULL)
        {
        if ((p->inf[0] >= '0' && p->inf[0] <= '9')|| (p->inf[0]=='x' || p->inf[0]=='e' || p->inf[0]=='p')) //daca nodul contine un numar/ variabila x/ constantele e sau pi
            {
            nodAB *q=new nodAB;
            strcpy(q->inf, p->inf);

            stiva[++top]= q;
            }

            else        //daca nodul contine o operatie matematica

            {
            if(p->inf[0]=='+' || p->inf[0]=='-' || p->inf[0]=='/' || p->inf[0]=='*' || p->inf[0]=='^') //operatori binari
                {
                nodAB *q=new nodAB;

                strcpy(q->inf, p->inf);

                q->dr=stiva[top];
                q->st=stiva[top-1];
                top-=2;
                stiva[++top]=q;
                }
                else //operatori unari
                {
                nodAB *q=new nodAB;

                strcpy(q->inf, p->inf);

                q->st=NULL;
                q->dr=stiva[top];

                stiva[top]=q;
                }

            }
        p=p->urm;
        }
    }



