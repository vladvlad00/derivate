#include <string>

using namespace std;

int EsteLitera(string s,int i)
{
    if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
        return 1;
    return 0;
}
int EsteCifra(string s,int i)
{
    if(s[i]>='0'&&s[i]<='9')
        return 1;
    return 0;
}
int EsteOperator(string s,int i)
{
    if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
        return 1;
    return 0;
}
int LiteraMare(string s,int i)
{
    if(s[i]>='A'&&s[i]<='Z')
        return 1;
    return 0;
}
int OperatoriValizi(string s,int i,int &ok)
{
    if(EsteOperator(s,i)==1)
        {

            if((s[i+1]=='x'||s[i+1]=='y'||s[i+1]=='t'||s[i+1]=='z'||(s[i+2]=='i'&&s[i+1]=='p')||EsteCifra(s,i+1)==1))
                    return 1;
            if(i==0)
                if(s[i]=='-')
                    return 1;
                else
                    return 0;
            if((EsteCifra(s,i-1)!=1)&&(s[i-1]!='x'&&s[i-1]!='y'&&s[i-1]!='t'&&s[i-1]!='z'&&s[i-1]!='e'&&(s[i-2]!='p'&&s[i-1]!='i'))&&(EsteCifra(s,i+1)!=1&&(s[i+1]!='x'||s[i+1]!='y'||s[i+1]!='t'||s[i+1]!='z'||s[i+1]!='e'||(s[i+1]!='p'&&s[i+2]!='i'))))
                return 0;
            if(s[i+1]==NULL)
                return 0;
            if(EsteOperator(s,i+1)==1)
                return 0;
        }

    return 1;
}
int FunctiiElemValide(string s,int &i)
{
    if(((s[i]=='l'&&s[i+1]=='n')&&(s[i+2]!='('))||((s[i]=='t'&&s[i+1]=='g')&&(s[i+2]!='(')))
        return 0;
    else
        {
            if((s[i]=='l'&&s[i+1]=='n')&&(s[i+2]=='(')||((s[i]=='t'&&s[i+1]=='g')&&(s[i+2]=='(')))
            {
                    i=i+1;
                    return 1;
            }

            if(((s[i]=='s'&&s[i+1]=='i'&&s[i+2]=='n')&&(s[i+3]!='('))||((s[i]=='c'&&s[i+1]=='o'&&s[i+2]=='s')&&(s[i+3]!='('))||((s[i]=='c'&&s[i+1]=='t'&&s[i+2]=='g')&&(s[i+3]!='(')))
                return 0;
            else
                {
                    if(((s[i]=='s'&&s[i+1]=='i'&&s[i+2]=='n')&&(s[i+3]=='('))||((s[i]=='c'&&s[i+1]=='o'&&s[i+2]=='s')&&(s[i+3]=='('))||((s[i]=='c'&&s[i+1]=='t'&&s[i+2]=='g')&&(s[i+3]=='(')))
                    {
                        i=i+2;
                        return 1;
                    }

                    if((s[i]=='s'&&s[i+1]=='q'&&s[i+2]=='r'&&s[i+3]=='t')&&(s[i+4]!='('))
                        return 0;
                    else
                    {
                        if((s[i]=='s'&&s[i+1]=='q'&&s[i+2]=='r'&&s[i+3]=='t')&&(s[i+4]=='('))
                        {
                            i=i+3;
                            return 1;
                        }

                        if((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='t'&&s[i+4]=='g')&&(s[i+5]!='('))
                            return 0;
                        else
                        {
                            if((((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='t'&&s[i+4]=='g')&&(s[i+5]=='('))))
                            {
                                i=i+4;
                                return 1;
                            }

                            if(((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='s'&&s[i+4]=='i'&&s[i+5]=='n')&&(s[i+6]!='('))||((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='o'&&s[i+5]=='n')&&(s[i+6]!='('))||((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='t'&&s[i+5]=='g')&&(s[i+6]!='(')))
                                return 0;
                            else
                            {
                                if(((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='s'&&s[i+4]=='i'&&s[i+5]=='n')&&(s[i+6]=='('))||((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='o'&&s[i+5]=='n')&&(s[i+6]=='('))||((s[i]=='a'&&s[i+1]=='r'&&s[i+2]=='c'&&s[i+3]=='c'&&s[i+4]=='t'&&s[i+5]=='g')&&(s[i+6]=='(')))
                                {
                                    i=i+5;
                                    return 1;
                                }
                            }
                        }
                    }
                }
        }
}
int ElementInvalid(string s,int &i,int &ok)
{
    ok=0;
    if(EsteLitera(s,i)==1&&LiteraMare(s,i)!=1)
        {
            if(s[i]=='s'||s[i]=='l'||s[i]=='t'||s[i]=='c'||s[i]=='a')
                if(FunctiiElemValide(s,i)==1)
                {
                    ok=1;
                    return 1;
                }
                else
                {
                    if(s[i]=='t')
                        return 1;
                    return 0;
                }
            if(EsteLitera(s,i+1)==1&&LiteraMare(s,i+i)!=1)
                if(s[i]!='p'&&s[i+1]!='i')
                    return 0;
                else
                    if(s[i]=='p'&&s[i+1]=='i')
                        i=i+1;
                        else
                            if(s[i]!='x'&&s[i]!='y'&&s[i]!='z'&&s[i]!='t'&&s[i]!='e')
                                return 0;
        }
    return 1;
}
int ParantezeValide(string s,int i)
{
    if((s[i]=='x'||s[i]=='y'||s[i]=='t'||s[i]=='z'||(s[i]=='i'&&s[i-1]=='p')||EsteCifra(s,i)==1)&&(s[i+1]=='('))
                return 0;
    return 1;
}
int VerificareFunctie(string s,int &i,int nrp)
{
    int n, ok;
    n=s.length();
    while(i<n)
    {
        if(s[i]=='/'&&s[i+1]=='0')
                return 0;
        if(s[i]=='0'&&s[i+1]=='^'&&s[i+2]=='0')
                return 0;
        if(EsteLitera(s,i)==1)
        {
            if(LiteraMare(s,i)==1)
                return 0;
            else
            {
                if(ElementInvalid(s,i,ok)==0)
                    return 0;
                else
                    if(ok==1&&s[i+2]=='-')
                    {
                        nrp++;
                        i=i+1;
                    }
                if(ok!=1)
                    if(ParantezeValide(s,i)==0)
                        return 0;
            }
        }
        else
        {
            if(!(ok==1&&s[i]=='-'))
                if(EsteOperator(s,i)==1)
                    if(OperatoriValizi(s,i,ok)==0)
                        return 0;
            if(s[i]=='(')
                nrp++;
            if(s[i]==')')
                {
                if(EsteOperator(s,i-1)==1)
                    return 0;
                if(s[i-1]=='(')
                    return 0;
                nrp--;

                }
        }
        i++;
    }
    if(nrp!=0)
        return 0;
    return 1;
}
