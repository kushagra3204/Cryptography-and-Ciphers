#include<iostream>
using namespace std;

int extended_euclid_solve(int a,int b, int r,int t1,int t2) {
    int q;
    if(b>0)
    {
        q = int(a/b);
        r = a%b;
    }
    if(b == 0)
    {
        cout<<"X"<<"\t"<<a<<"\t"<<b<<"\t"<<"X"<<"\t"<<t1<<"\t"<<t2<<"\t"<<"X"<<endl;
        return t1;
    }
    int t = t1 - (t2 * q);
    cout<<q<<"\t"<<a<<"\t"<<b<<"\t"<<r<<"\t"<<t1<<"\t"<<t2<<"\t"<<t<<endl;
    return extended_euclid_solve(b,r,a%b,t2,t);
}

void extended_euclid(int a,int b)
{
    cout<<"\nQ\tA\tB\tR\tT1\tT2\tT"<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    if(a<b) {
        int t = a;
        a = b;
        b = t;
    }
    int ans = extended_euclid_solve(a,b,0,0,1);
    if(ans<0)
        ans = a + ans;
    cout<<"\n\nSolution of Extended Euclidean("<<a<<","<<b<<") (Inverse): "<<ans<<"\n\n";
}

int main()
{
    system("cls");
    int A,B;
    cout<<"Enter first number: ";
    cin>>A;
    cout<<"Enter second number: ";
    cin>>B;
    extended_euclid(A,B);
}