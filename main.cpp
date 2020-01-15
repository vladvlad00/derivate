#include "derivare.h"
#include <iostream>
#include <graphics.h>
#include "winbgim.h"

using namespace std;

string s, rez;
int language, i;

void setup();
int language_selection_screen();
void citesteInModGrafic(char text[200], int x, int y, int culoareFundal, int culoareText);

int screenWidth, screenHeight;

int main()
{
    screenWidth= GetSystemMetrics(SM_CXSCREEN);
    screenHeight= GetSystemMetrics(SM_CYSCREEN)-70;

    setup();
    language = language_selection_screen();

    closegraph();

    initwindow(screenWidth, screenHeight);


    settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);
    setcolor(YELLOW);
    cout<<language;
    if(language==1)
        {
        outtextxy(200,100, "Introduceti expresia pe care vreti sa o derivati: ");
        }

    if(language==2)
        {
        outtextxy(200,100, "Insert the expression for which you want to find the derivative: ");
        }

    if(language==3)
        {
        return 0;
        }

    char text[200];

    citesteInModGrafic(text, 200, 200, BLACK, WHITE);

    s=text;
    int nrp, i;
    if(!VerificareFunctie(s, i, nrp))
        {
        settextstyle(BOLD_FONT, HORIZ_DIR, 6);
        if(language==1)
            outtextxy(200, 400, "Functie nevalida");
            else
            outtextxy(200, 400, "Invalid function");
        getch();
        closegraph();
        return 0;
        }

    closegraph();

    initwindow(screenWidth,screenHeight);

    transforma(s);
    postordine(s,rez);
    arboreBinar A = creeazaArboreExpresie(rez);

    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(RED);
    if(language==1)
        outtextxy(100,100,"Expresia ta este:");
        else
        outtextxy(100,100,"Your expression is:");


    bgiout<<'\n';
    bgiout<<s;
    bgiout<<'\n';

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);

    outstreamxy(100, 130);

    setcolor(GREEN);
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);


    if(language==1)
        outtextxy(100,250,"Derivata acesteia este:");
        else
        outtextxy(100,250,"Its derivative is:");

    arboreBinar D = derivare(A);

    bgiout<<'\n';
    bgiout << '(' << s << ")'="<<'\n'<<'\n'<<"= ";

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);

    afisare(D);
    outstreamxy(100, 280);


    settextstyle(BOLD_FONT, HORIZ_DIR, 3);

    if(language==1)
        outtextxy(100, 700, "Apasa orice tasta pentru a iesi");
        else
        outtextxy(100, 700, "Press any key to exit");

    getch();
    closegraph();

    return 0;
}

void setup()
{

    initwindow(screenWidth,screenHeight);

    setbkcolor(BLUE);

    readimagefile("ro.jpg", 250, 500, 750, 800);
    readimagefile("uk.jpg", 1170, 500, 1670, 800);

    settextstyle(BOLD_FONT, HORIZ_DIR, 5);

    outtextxy(550, 400, "Choose your desired language:");

    outtextxy(550, 900, "Click anywhere else to exit");

}

int language_selection_screen()
{
    int x, y;
    while(1)
    {if(ismouseclick(WM_LBUTTONDOWN))
        {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=250 && x<=750 && y>=500 && y<=800)
            {
            return 1;
            }
        if(x>=1170 && x<=1670 && y>=500 && y<=800)
            {
            return 2;
            }
        return 3;
        }
    }
}

void citesteInModGrafic(char text[200], int x, int y, int culoareFundal, int culoareText)
{
    char tasta, sir[2];
    char * sir_lung="MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM";
    bool vizibil=false;
    sir[1]='\0';
    strcpy(text,"");
    setcolor(culoareText);
    rectangle(x-5,y-5,x+textwidth(sir_lung),y+textheight("M")+5);
    outtextxy(x,y,text);
    do
    {
        if (kbhit())
        {
            tasta=getch();

            if (tasta==8 && strlen(text)>0)
            {
                setcolor(culoareFundal);
                outtextxy(x,y,text);
                outtextxy(x+textwidth(text),y,"_");
                text[strlen(text)-1]='\0';
                setcolor(culoareText);
                outtextxy(x,y,text);
            }
            if (tasta>=32 && tasta<=127 && strlen(text)<strlen(sir_lung)-2)
            {
                setcolor(culoareFundal);
                outtextxy(x,y,text);
                sir[0]=tasta;
                setcolor(culoareText);
                strcat(text,sir);
                outtextxy(x,y,text);
            }
        }
        else {
            if (vizibil) setcolor(culoareText);
            else setcolor(culoareFundal);
            outtextxy(x+textwidth(text),y,"_");
            vizibil=not vizibil;
            delay(100);
        }
    }
    while (tasta!=13 && tasta!=27);

    if(tasta==27) exit(0);
}
