#include<iostream>
using namespace std;

int main()
{
    int seed = 3, multiplier = 7, increment = 4, m = 51; 
    int n;
    cout<<"Enter number of random variables: ";
    cin>>n;

    int random_numbers[n];
    cout<<"Random Numbers Generated are: "<<endl;
    random_numbers[0] = seed;
    cout<<random_numbers[0]<<endl;
    for(int i=1;i<n;i++)
    {
        random_numbers[i] = (random_numbers[i-1]*multiplier + increment)%m;
        cout<<random_numbers[i]<<endl;
    }
    return 0;
}