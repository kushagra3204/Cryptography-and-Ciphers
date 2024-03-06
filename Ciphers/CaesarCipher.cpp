#include <bits/stdc++.h>
using namespace std;
int main()
{
    bool stop=false;
    int choice;
    cout<<"Caesar Cipher!"<<endl;
    
    while(!stop)
    {
        cout<<"\n\n1. Encryption\n2. Decryption\n3. Exit\nEnter from the choice: ";
        cin>>choice;
        if(choice==1)
        {
            // Encyption
            int key;
            cout<<"Enter the key: ";
            cin>>key;
            string plainText;
            cout<<"Enter the plain Text: ";
            getline(cin,plainText);
            getline(cin,plainText);
            for(int j=0;j<plainText.length();j++)
            {
                if(plainText[j]!=' ')
                {
                    if((int)(plainText[j])>90)
                    {
                        cout<<(char)(((int)plainText[j]-97+key)%26+97);
                    }
                    else
                    {
                        cout<<(char)(((int)plainText[j]-65+key)%26+65);
                    }
                }
                else
                    cout<<plainText[j];
            }

        }
        else if(choice==2)
        {
            int key;
            cout<<"Enter the key: ";
            cin>>key;
            string cipherText;
            cout<<"Enter the Cipher text: ";
            getline(cin,cipherText);
            getline(cin,cipherText);
            for(int j=0;j<cipherText.length();j++)
            {
                if(cipherText[j]!=' ')
                {
                    if((int)(cipherText[j])>90)
                    {
                        cout<<(char)(((int)cipherText[j]-97-key)%26+97);
                    }
                    else
                    {
                        cout<<(char)(((int)cipherText[j]-65-key)%26+65);
                    }
                }
                else
                    cout<<cipherText[j];
            }
        }
        else if(choice==3)
        {
            stop=true;
        }
        else
        {
            cout<<"\nInvalid Choice!"<<endl;
        }
    }
    
    
    return 0;
}