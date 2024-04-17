#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>

using namespace std;

int random_number(long x,long a,long c,int m)
{
    long result = (x*a + c)%m;
    int res = (int)result;
    return res;
}

int main()
{
    
    int S,n,k;
    cout<<"Enter Secret (S): ";
    cin>>S;
    cout<<"Enter Number Of Partitions(n): ";
    cin>>n;
    cout<<"Enter number of points(k): ";
    cin>>k;
    int polynomial[k];
    polynomial[0] = S;
    for(int i=1;i<k;i++)
    {
        polynomial[i] = random_number(time(0),17,time(0)+3,967);
    }
    int points[n][2];
    for(int i=1;i<n+1;i++)
    {
        points[i-1][0] = i;
        int sum = 0;
        for(int j=0;j<k;j++)
        {
            sum+=pow(points[i-1][0],j)*polynomial[j];
        }
        points[i-1][1] = sum;
    }
    int random_points[k][2];
    
    for(int i=0;i<k;i++)
    {
        random_points[i][0] = points[i][0];
        random_points[i][1] = points[i][1];
    }
    
    //Lagrange [For only finding S (term not having any polynomial)]
    double l[k];
    int found_Secret = 0;
    for(int i=0;i<k;i++)
    {
        l[i] = 1.0;
        for(int j=0;j<k;j++)
        {
            if(j!=i)
            {
                l[i] *= (double)-1*(random_points[j][0])/(random_points[i][0]-random_points[j][0]);
            }
        }
        found_Secret += (int)(l[i])*random_points[i][1];
    }
    cout<<"\nSecret Found: "<<found_Secret<<endl;
    return 0;
}