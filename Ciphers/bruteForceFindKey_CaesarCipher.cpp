/***************************************************
* Brute Force: Find key (Caesar Cipher)            *
***************************************************/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    string cipherText;
    getline(cin,cipherText);
    for(int i=1;i<26;i++)
    {
        cout<<"Key: -"<<i<<"/+"<<26-i<<") ";
        for(int j=0;j<cipherText.length();j++)
        {
            if(cipherText[j]!=' ')
            {
                if((int)(cipherText[j])>90)
                {
                    cout<<(char)(((int)cipherText[j]-97+i)%26+97);
                }
                else
                {
                    cout<<(char)(((int)cipherText[j]-65+i)%26+65);
                }
            }
            else
                cout<<cipherText[j];
        }
        cout<<endl;
    }
    return 0;
}