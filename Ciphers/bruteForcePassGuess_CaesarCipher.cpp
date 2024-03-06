/***********************************************
* Brute Force: Password                        *
***********************************************/

#include <iostream>
using namespace std;
int main()
{
    system("cls");
    string pass;
    cin>>pass;
    int count=0;
    for(int i=65;i<91;i++)
    {
        for(int j=65;j<91;j++)
        {
            for(int k=65;k<91;k++)
            {
                string a;
                a+=(char)i;
                a+=(char)j;
                a+=(char)k;
                if(a==pass)
                {
                    cout<<a<<endl;
                    break;
                }
            }
        }
    }
    return 0;
}