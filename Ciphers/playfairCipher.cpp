/*****************************************
 * Playfair Cipher                       *
 *****************************************/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    cout<<boolalpha;
    cout<<"PlayFair Cipher!!"<<endl;
    bool stop = false;
    char keyArray[5][5];
    bool isPresent[26];
    string key;
    while(!stop)
    {
        int choice;
        cout<<"\n\n1. Encryption\n2. Decryption\n3. Exit\nEnter your choice: ";
        cin>>choice;
        if(choice==1 || choice==2)
        {
            cout<<"Enter the key: ";
            cin>>key;
            string repli="";
            for(auto sc:key)
                repli+=tolower(sc);
            key=repli;

            int count=0;
            for(int i=0;i<26;i++)
            {
                isPresent[i]=false;
            }

            //Forming keyArray 5x5
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    if(count!=key.length())
                    {
                        if(key[count]=='j')
                            key[count]='i';
                        if(!isPresent[(int)(key[count])-97])
                        {
                            keyArray[i][j]=key[count];
                            isPresent[(int)(key[count])-97]=true;
                        }
                        else
                        {
                            j--;
                        }
                        count++;
                    }
                    else
                    {
                        for(int k=0;k<26;k++)
                        {
                            if((char)(k+97)!='j')
                            {
                                if(!isPresent[k])
                                {
                                    keyArray[i][j]=(char)(k+97);
                                    isPresent[k]=true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            //display keyArray
            cout<<"\nKey Array 5x5:"<<endl;
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    cout<<keyArray[i][j]<<" ";
                }
                cout<<endl;
            }

            cout<<endl;
        }
        if(choice==1)
        {
            // Encryption
            string plainText;
            string cipherText="";
        
            cout<<"Enter the plain text: ";
            cin>>plainText;
            string repli="";
            for(auto sc:plainText)
                repli+=tolower(sc);
            plainText=repli;


            for(int i=0;i<plainText.length();i++)
            {
                if(plainText[i]=='j')
                {
                    plainText[i]='i';
                }
            }
            
            int c=0;
            if(plainText.length()%2!=0)
            {
                plainText+='x';
            }
        
            while(c<plainText.length())
            {
                int ix1,iy1,ix2,iy2;
                int f1=0,f2=0;
                for(int i=0;i<5;i++)
                {
                    for(int j=0;j<5;j++)
                    {
                        if(plainText[c]==keyArray[i][j])
                        {
                            ix1=i;
                            iy1=j;
                            f1=1;
                            if(f2)
                            {
                                j=5;
                                i=5;
                            }
                        }
                        if(plainText[c+1]==keyArray[i][j])
                        {
                            ix2=i;
                            iy2=j;
                            f2=1;
                            if(f1)
                            {
                                j=5;
                                i=5;
                            }
                        }
                    }
                }
                if(f1 && f2)
                {
                    if(ix1==ix2)
                    {
                        cipherText+=keyArray[ix1][(iy1+1)%5];
                        cipherText+=keyArray[ix1][(iy2+1)%5];
                    }
                    else if(iy1==iy2)
                    {
                        cipherText+=keyArray[(ix1+1)%5][iy1];
                        cipherText+=keyArray[(ix2+1)%5][iy2];
                    }
                    else
                    {
                        cipherText+=keyArray[ix1][iy2];
                        cipherText+=keyArray[ix2][iy1];
                    }
                    c+=2;
                    f1=0;f2=0;ix1=0;ix2=0;iy1=0;iy2=0;
                }
            }
        
            cout<<"\nCipher Text: "<<cipherText<<endl;
        }
        else if(choice==2)
        {
            // Decryption
            string plainText="";
            string cipherText;
            cout<<"Enter the Cipher Text: ";
            cin>>cipherText;
            string repli="";
            for(auto sc:cipherText)
                repli+=tolower(sc);
            cipherText=repli;

            int c=0;
            while(c<cipherText.length())
            {
                int ix1,iy1,ix2,iy2;
                int f1=0,f2=0;
                for(int i=0;i<5;i++)
                {
                    for(int j=0;j<5;j++)
                    {
                        if(cipherText[c]==keyArray[i][j])
                        {
                            ix1=i;
                            iy1=j;
                            f1=1;
                            if(f2)
                            {
                                j=5;
                                i=5;
                            }
                        }
                        if(cipherText[c+1]==keyArray[i][j])
                        {
                            ix2=i;
                            iy2=j;
                            f2=1;
                            if(f1)
                            {
                                j=5;
                                i=5;
                            }
                        }
                    }
                }
                if(f1 && f2)
                {
                    if(ix1==ix2)
                    {
                        plainText+=keyArray[ix1][(iy1-1+5)%5];
                        plainText+=keyArray[ix1][(iy2-1+5)%5];
                    }
                    else if(iy1==iy2)
                    {
                        plainText+=keyArray[(ix1-1+5)%5][iy1];
                        plainText+=keyArray[(ix2-1+5)%5][iy2];
                    }
                    else
                    {
                        plainText+=keyArray[ix1][iy2];
                        plainText+=keyArray[ix2][iy1];
                    }
                    c+=2;
                    f1=0;f2=0;ix1=0;ix2=0;iy1=0;iy2=0;
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
            cout<<"\nInvalid input!"<<endl;
        }
    }
    return 0;
}