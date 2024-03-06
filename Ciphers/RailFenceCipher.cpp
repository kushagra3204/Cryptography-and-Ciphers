/*******************************************
* Rail Fence Cipher                        *
*******************************************/


#include <bits/stdc++.h>
using namespace std;
int main()
{
    bool stop=false;
    int choice;
    cout<<"Rail Fence Cipher"<<endl;
    while(!stop)
    {
        cout<<"\n\n1. Encryption\n2. Decryption\n3. Quit\nEnter your choice: ";
        cin>>choice;
        if(choice==1)
        {
            // Encryption
            string plainText,cipherText;
            int keySpace;
            int countx=0,flag=0;
            cout<<"Enter the Plain Text: ";
            cin>>plainText;
            cout<<"Enter the key: ";
            cin>>keySpace;
            char arr[keySpace][plainText.length()];
            for(int i=0;i<keySpace;i++)
            {
                for(int j=0;j<plainText.length();j++)
                {
                    arr[i][j]='*';
                }
            }
            
            countx=0;
            flag=0;
            for(int i=0;i<plainText.length();i++)
            {
                if(countx==0)
                {
                    flag=0;
                }
                if(countx==keySpace-1)
                {
                    flag=1;
                }
                
                arr[countx][i]=plainText[i];
                
                if(!flag)
                {
                    countx++;
                }
                else
                {
                    countx--;
                }
            }
            cout<<endl;
            for(int i=0;i<keySpace;i++)
            {
                for(int j=0;j<plainText.length();j++)
                {
                    if(arr[i][j]!='*')
                        cipherText+=arr[i][j];
                    cout<<arr[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<"\n\nCipher Text: "<<cipherText<<endl;
        }
        else if(choice==2)
        {
            // Decryption
            string plainText,cipherText;
            int keySpace;
            int countx=0,flag=0;
            cipherText="";
            cout<<"Enter the Cipher Text: ";
            cin>>cipherText;
            cout<<"Enter the Key: ";
            cin>>keySpace;
            
            char arr1[keySpace][cipherText.length()];
            
            for(int i=0;i<keySpace;i++)
            {
                for(int j=0;j<cipherText.length();j++)
                {
                    arr1[i][j]='*';
                }
            }
            countx=0;
            flag=0;
            for(int i=0;i<cipherText.length();i++)
            {
                if(countx==0)
                {
                    flag=0;
                }
                if(countx==keySpace-1)
                {
                    flag=1;
                }
                
                arr1[countx][i]='#';
                
                if(!flag)
                {
                    countx++;
                }
                else
                {
                    countx--;
                }
            }
            int count=0;
            for(int i=0;i<keySpace;i++)
            {
                for(int j=0;j<cipherText.length();j++)
                {
                    if(arr1[i][j]=='#')
                    {
                        arr1[i][j]=cipherText[count];
                        count++;
                    }
                }
            }
            cout<<endl;
            for(int i=0;i<keySpace;i++)
            {
                for(int j=0;j<cipherText.length();j++)
                {
                    cout<<arr1[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<"\n\n";
            
            plainText="";
            countx=0;
            flag=0;
            for(int i=0;i<cipherText.length();i++)
            {
                if(countx==0)
                {
                    flag=0;
                }
                if(countx==keySpace-1)
                {
                    flag=1;
                }
                
                plainText+=arr1[countx][i];
                
                if(!flag)
                {
                    countx++;
                }
                else
                {
                    countx--;
                }
            }
            cout<<"Plain Text: "<<plainText<<endl;
        }
        else if(choice==3)
        {
            stop=true;
        }
        else
        {
            cout<<"Invalid Input! Enter from given choices. "<<endl;
        }
    }
    return 0;
}