/*************************************
* Hill Cipher                        *
*************************************/

#include <bits/stdc++.h>
using namespace std;

// Prototypes{
vector<vector<int>> matrixMultiplication(vector<vector<int>>,vector<vector<int>>);
bool isPerfectSquare(int);
vector<vector<int>> getSubmatrix(vector<vector<int>>, int, int);
int calculateDeterminant(vector<vector<int>>);
vector<vector<int>> transposeMatrix(vector<vector<int>>);
vector<vector<int>> calculateAdjoint(vector<vector<int>>);
int modInverse(int,int);
vector<vector<int>> inverseOfKeyMatrix(vector<vector<int>>);
void decrypt(string,string);
// }

int main()
{
    int choice;
    bool stop = false;
    cout<<"Hill Cipher"<<endl;
    while(!stop)
    {
        cout<<"\n\n1. Encrypt\n2. Decrypt\n3. Exit\nEnter from your choice: ";
        cin>>choice;
        if(choice==1)
        {
            // Encryption
            string key;
            string plainText;
            cout<<"Enter key: ";
            cin>>key;
            cout<<"Enter Plain Text: ";
            cin>>plainText;
            int index=sqrt(key.length());
            
            vector <vector<int>> keyArr(index,vector<int>(index,0));
            vector <vector<int>> plainTextArr(index,vector<int>((int)(plainText.length()/index),0));
            int count=0;
            for(int i=0;i<index;i++)
            {
                for(int j=0;j<index;j++)
                {
                    keyArr[i][j]=(int)key[count++]-97;
                }
            }
            count=0;
            for(int i=0;i<(int)(plainText.length()/index);i++)
            {
                for(int j=0;j<index;j++)
                {
                    plainTextArr[j][i]=(int)plainText[count++]-97;
                }
            }
            
            string cipherText="";
            vector <vector<int>> mul = matrixMultiplication(keyArr,plainTextArr);
            for(int i=0;i<mul[0].size();i++)
            {
                for(int j=0;j<mul.size();j++)
                    cipherText+=(char)(mul[j][i]%26+97);
            }
            cout<<"Cipher Text: "<<cipherText<<endl;
        }
        else if(choice==2)
        {
            // Decryption
            string cipherText,key;
            cout<<"Enter Key: ";
            cin>>key;
            cout<<"Enter Cipher Text: ";
            cin>>cipherText;
            decrypt(cipherText,key);
        }
        else if(choice==3)
        {
            stop=true;
        }
        else
        {
            cout<<"Enter from the given choice!"<<endl;
        }
    }
    return 0;
}



vector<vector<int>> matrixMultiplication(const vector<vector<int>> a, const vector<vector<int>> b) 
{
    int r1 = a.size();
    int c1 = a[0].size();
    int c2 = b[0].size();
    int r2 = b.size();
    vector<vector<int>> mul(r1, vector<int>(c2, 0));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                mul[i][j] +=  a[i][k]*b[k][j];
            }
        }
    }
    return mul;
}

bool isPerfectSquare(int a)
{
    int root = sqrt(a);
    if(root*root==a)
    {
        return true;
    }
    return false;
}

vector<vector<int>> getSubmatrix(vector<vector<int>> matrix, int rowToRemove, int colToRemove) 
{
    int size = matrix.size();
    vector<vector<int>> submatrix(size-1,vector<int>(size-1,0));
    int rowIndex = 0;
    int colIndex;

    for (int i = 0; i < size; i++) {
        if (i == rowToRemove) {
            continue;
        }

        colIndex = 0;
        for (int j = 0; j < size; j++) {
            if (j == colToRemove) {
                continue;
            }

            submatrix[rowIndex][colIndex] = matrix[i][j];
            colIndex++;
        }
        rowIndex++;
    }

    return submatrix;
}

int calculateDeterminant(vector<vector<int>> matrix) 
{
    int size = matrix.size();

    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int determinant = 0;
    for (int i = 0; i < size; i++) {
        determinant += matrix[0][i] * pow(-1, i) * calculateDeterminant(getSubmatrix(matrix, 0, i));
    }

    return determinant;
}

vector<vector<int>> transposeMatrix(vector<vector<int>> matrix) 
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols,vector<int>(cols,0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

vector<vector<int>> calculateAdjoint(vector<vector<int>> matrix) 
{
    int size = matrix.size();
    vector<vector<int>> adjoint(size,vector<int>(size,0));

    if (size == 1) {
        adjoint[0][0] = 1;
    } else if (size == 2) {
        adjoint[0][0] = matrix[1][1];
        adjoint[0][1] = -matrix[0][1];
        adjoint[1][0] = -matrix[1][0];
        adjoint[1][1] = matrix[0][0];
    } else {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                vector<vector<int>> submatrix = getSubmatrix(matrix, i, j);
                adjoint[i][j] = pow(-1, i + j) * calculateDeterminant(submatrix);
            }
        }
        adjoint = transposeMatrix(adjoint);
    }

    return adjoint;
}

int modInverse(int A, int M) 
{
    for (int i = 1; i < M; i++) {
        if ((((A % M)*(i % M))% M) == 1) {
            return i;
        }
    }
    return -1;
}

vector<vector<int>> inverseOfKeyMatrix(vector<vector<int>> keyMatrix) 
{
    int determinant = calculateDeterminant(keyMatrix);
    if (determinant < 0) {
        determinant = 26 - (abs(determinant) % 26);
    }
    determinant = determinant % 26;
    int modularInverse = modInverse(determinant, 26);

    vector<vector<int>> inverseMatrix = calculateAdjoint(keyMatrix);

    for (int i = 0; i < inverseMatrix.size(); i++) {
        for (int j = 0; j < inverseMatrix[0].size(); j++) {
            inverseMatrix[i][j] = (inverseMatrix[i][j]) % 26;
            if (inverseMatrix[i][j] < 0) {
                inverseMatrix[i][j] = 26 - abs(inverseMatrix[i][j]);
            }
            inverseMatrix[i][j] = (inverseMatrix[i][j] * modularInverse) % 26;
        }
    }
    return inverseMatrix;
}

void decrypt(string str,string key)
{
    if(!isPerfectSquare(key.length())){
        cout<<"Enter a key whose length is a perfect square root."<<endl;
    }
    int root = (int)sqrt(key.length());
    vector<vector<int>> keyMat(root,vector<int>(root,0));
    int k=0;
    for (int i = 0; i < root; i++) {
        for (int j = 0; j < root; j++) {
            keyMat[i][j] = ((int)key[k]-97)%26;
            k++;
        }
    }
    int temp =0;
    vector<vector<int>> inverseKey = inverseOfKeyMatrix(keyMat);
    vector<vector<int>> strMat(root,vector<int>(str.length()/root,0));
    for (int i = 0; i < strMat[0].size(); i++) {
        for (int j = 0; j < strMat.size(); j++) {
            strMat[j][i] = ((int)str[temp]-97)%26;
            temp++;
        }
    }
    
    
    vector<vector<int>> mul = matrixMultiplication(inverseKey,strMat);
    string ans = "";
    for(int i=0;i<mul[0].size();i++)
    {
        for(int j=0;j<mul.size();j++)
            ans+=(char)(mul[j][i]%26+97);
    }
    
    cout<<"Plain Text: "<<ans<<endl;
}