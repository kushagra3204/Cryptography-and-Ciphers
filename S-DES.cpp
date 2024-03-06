#include<iostream>
using namespace std;

int* axorb(int arr1[],int arr2[],int n) {
    int* temp = new int[n];
    for(int i=0;i<n;i++)
    {
        temp[i] = arr1[i]^arr2[i];
    }
    return temp;
}

int* Pn(int key[],int P[],int n) {
    int* temp = new int[n];
    for(int i = 0;i<n;i++)
    {
        temp[i] = key[P[i]-1];
    }
    return temp;
}

int B2I(int a,int b) {
    if(a==0 && b==0) return 0;
    else if(a==0 && b==1) return 1;
    else if(a==1 && b==0) return 2;
    else return 3;
}

int* I2B(int i) {
    int* temp = new int[2];
    if(i == 0){
        temp[0] = 0;
        temp[1] = 0;
    }
    else if(i == 1){
        temp[0] = 0;
        temp[1] = 1;
    }
    else if(i == 2){
        temp[0] = 1;
        temp[1] = 0;
    }
    else{
        temp[0] = 1;
        temp[1] = 1;
    }
    return temp;
}

int* SBOX(int key1xorep[]) {
    int P4[] ={2,4,3,1};
    int S0[4][4] = {
        {1,0,3,2},
        {3,2,1,0},
        {0,2,1,3},
        {3,1,3,2}
    };
    int S1[4][4] = {
        {0,1,2,3},
        {2,0,1,3},
        {3,0,1,0},
        {2,1,0,3}
    };

    //divide key1xorep
    int l_xor[4],r_xor[4];
    for(int i=0;i<8;i++)
    {
        if(i<4)
            l_xor[i] = key1xorep[i];
        else
            r_xor[i-4] = key1xorep[i];
    }

    //S-BOX-0
    int r1 = B2I(l_xor[0],l_xor[3]);
    int c1 = B2I(l_xor[1],l_xor[2]);
    int* val1 = I2B(S0[r1][c1]);
    
    //S-BOX-1
    int r2 = B2I(r_xor[0],r_xor[3]);
    int c2 = B2I(r_xor[1],r_xor[2]);
    int *val2 = I2B(S1[r2][c2]);
    
    //Combining output of S0 & S1
    int outs0s1[4];
    for(int i=0;i<4;i++)
    {
        if(i<2)
            outs0s1[i] = val1[i];
        else
            outs0s1[i] = val2[i-2];
    }
    int* Ps0s1 = Pn(outs0s1,P4,4);
    return Ps0s1;
}

int* LS(int shift,int arr[]) {
    int* tempKey2 = new int[10];
    for(int i=0;i<10;i++)
    {
        if(i<5)
            tempKey2[(5+i-shift)%5] = arr[i];
        else
            tempKey2[(5+i-shift)%5+5] = arr[i];
    }
    return tempKey2;
}

void display(int arr[],int n) {
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

pair<int*,int*> keyGeneration(int key[]) {
    int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int P8Arr[] = {6, 3, 7, 4, 8, 5, 10, 9};
    
    //Permutation - 10
    int* tempKey1 = Pn(key,P10,10);
    display(tempKey1,10);

    //LS-1
    int* tempKey2 = LS(1,tempKey1);
    display(tempKey2,10);

    //P-8
    int* key1 = Pn(tempKey2,P8Arr,8);

    //LS-2
    int* tempKey3 = LS(2,tempKey2);
    display(tempKey3,10);

    //P-8
    int* key2 = Pn(tempKey3,P8Arr,8);

    return make_pair(key1,key2);
}

int* step2(int l_ip[],int r_ip[],int key[]) {
    int epTable[] = {4, 1, 2, 3, 2, 3, 4, 1};

    //ep
    int* ep = Pn(r_ip,epTable,8);
    // cout<<"ep: ";
    // display(ep,8);

    //key1 xor ep
    int* key1xorep = axorb(key,ep,8);
    // cout<<"key1 xor ep: ";
    // display(key1xorep,8);

    //SBOX
    int* p4 = SBOX(key1xorep);
    // display(p4,4);
    
    //lip xor p4
    int* lipxorp4 = axorb(l_ip,p4,4);
    // display(lipxorp4,4);

    return lipxorp4;
}

int* Encryption(int key[],int data[]) {
    
    int ipTable[] = {2, 6, 3, 1, 4, 8, 5, 7};
    int epTable[] = {4, 1, 2, 3, 2, 3, 4, 1};
    int ip_1Table[] = {4, 1, 3, 5, 7, 2, 8, 6};


    //generate keys
    pair<int*,int*> keys = keyGeneration(key);
    
    //ip
    int* ip = Pn(data,ipTable,8);
    // cout<<"ip: ";
    // display(ip,8);
    
    //divide ip
    int l_ip[4],r_ip[4];
    for(int i=0;i<8;i++)
    {
        if(i<4)
            l_ip[i] = ip[i];
        else
            r_ip[i-4] = ip[i];
    }
    
    //------------------ STEP - 2 -------------------

    int* lipxorp4 = step2(l_ip,r_ip,keys.first);

    // ---------------- STEP - 3 --------------------
    //repeat step - 2

    int* ripxorp42 = step2(r_ip,lipxorp4,keys.second);

    int combiner42l4[8];
    for(int i=0;i<8;i++)
    {
        if(i<4)
            combiner42l4[i] = ripxorp42[i];
        else
            combiner42l4[i] = lipxorp4[i-4];
    }

    //Inverse ip
    int* cipherText = Pn(combiner42l4,ip_1Table,8);
    
    return cipherText;
}

int* Decryption(int key[],int data[]) {
    int ipTable[] = {2, 6, 3, 1, 4, 8, 5, 7};
    int epTable[] = {4, 1, 2, 3, 2, 3, 4, 1};
    int ip_1Table[] = {4, 1, 3, 5, 7, 2, 8, 6};

    //generate keys
    pair<int*,int*> keys = keyGeneration(key);
    
    //ip
    int* ip = Pn(data,ipTable,8);
    // cout<<"ip: ";
    // display(ip,8);
    
    //divide ip
    int l_ip[4],r_ip[4];
    for(int i=0;i<8;i++)
    {
        if(i<4)
            l_ip[i] = ip[i];
        else
            r_ip[i-4] = ip[i];
    }
    
    //------------------ STEP - 2 -------------------

    int* lipxorp4 = step2(l_ip,r_ip,keys.second);

    // ---------------- STEP - 3 --------------------
    //repeat step - 2

    int* ripxorp42 = step2(r_ip,lipxorp4,keys.first);

    int combiner42l4[8];
    for(int i=0;i<8;i++)
    {
        if(i<4)
            combiner42l4[i] = ripxorp42[i];
        else
            combiner42l4[i] = lipxorp4[i-4];
    }

    //Inverse ip
    int* plainText = Pn(combiner42l4,ip_1Table,8);
    
    return plainText;
}

int main() {
    system("cls");
    
    //eg-1
    // int key[] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};
    // int data[] = {1, 0, 0, 1, 0, 1, 1, 1};
    
    //eg-2
    // int key[] = {1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    // int data[] = {0, 0, 1, 0, 1, 0, 0, 0};

    //eg-3
    int key[] = {1, 0, 0, 0, 0, 1, 1, 1, 0, 1};
    int data[] = {1, 1, 1, 1, 0, 0, 1, 1};

    pair<int*,int*> keys = keyGeneration(key);
    cout<<"Key1: ";
    display(keys.first,8);
    cout<<"Key2: ";
    display(keys.second,8);

    cout<<"\nPlain Text: ";
    display(data,8);

    //Encryption
    int* cipherText = Encryption(key,data);
    cout<<"\nCipher Text: ";
    display(cipherText,8);
    
    int* plainText = Decryption(key,cipherText);
    cout<<"\nPlain Text: ";
    display(plainText,8);

    cout<<endl;
    system("pause");
    return 0;
}