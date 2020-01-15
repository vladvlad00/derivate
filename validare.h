#include <string>

using namespace std;

int EsteLitera(string s,int i);
int EsteCifra(string s,int i);
int EsteOperator(string s,int i);
int LiteraMare(string s,int i);
int OperatoriValizi(string s,int i,int &ok);
int FunctiiElemValide(string s,int &i);
int ElementInvalid(string s,int &i,int &ok);
int ParantezeValide(string s,int i);
int VerificareFunctie(string s,int &i,int nrp);
