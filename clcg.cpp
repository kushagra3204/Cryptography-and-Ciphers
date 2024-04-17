#include<iostream>
using namespace std;

int* lcg(int x,int a,int c,int m,int n)
{
    int *result = new int[n];
    result[0] = x;
    for(int i=1;i<n;i++)
    {
        result[i] = (result[i-1]*a + c)%m;
    }
    return result;
}

int main()
{
    int seed1 = 3, seed2 = 5, multiplier1 = 7, multiplier2 = 9, increment1 = 4, increment2 = 6, m1 = 51, m2 = 19; 
    int n;
    cout<<"Enter number of random variables: ";
    cin>>n;

    int random_numbers[n];
    cout<<"Random Numbers Generated are: "<<endl;
    int* random_number1 = lcg(seed1,multiplier1,increment1,m1,n);
    int* random_number2 = lcg(seed2,multiplier2,increment2,m2,n);

    int random_number[n];
    cout<<"Random numbers:"<<endl;
    for(int i=0;i<n;i++)
    {
        random_number[i] = (random_number1[i] - random_number2[i])%(m1-1);
        int r1 = abs(random_number[i]/(m1-1)) + 1;
        if(random_number[i]<0)
        {
            random_number[i] = random_number[i] + (m1-1)*r1;
        }
        cout<<random_number[i]<<endl;
    }
    return 0;
}