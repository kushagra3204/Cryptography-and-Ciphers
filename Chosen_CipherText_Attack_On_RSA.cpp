#include<iostream>
using namespace std;

int modExp(int x, int n, int m) {
    int res = 1;
    while(n){
        if(n&1)
            res=(res*x)%m;
        n = n/2;
        x = (x*x)%m;
    }
    return res;
}

int gcd(int a,int b) {
    if(a==0)
        return b;
    return gcd(b%a,a);
}

int phi(int n) {
    int result = 1;
    for(int i=2;i<n;i++) {
        if(gcd(i,n)==1){
            result++;
        }
    }
    return result;
}

int find_e(int n) {
    for(int i = 2; i<phi(n)-1;i++) {
        if(gcd(i,phi(n))==1)
            return i;
    }
    return -1;
}

int Encryption(int pt,int pu1,int n) {
    return modExp(pt,pu1,n);
}

int Decryption(int ct,int pk1,int n) {
    return modExp(ct,pk1,n);
}

int extended_euclid_solve(int a,int b, int r,int t1,int t2) {
    int q;
    if(b>0) {
        q = int(a/b);
        r = a%b;
    }
    if(b == 0) return t1;
    int t = t1 - (t2 * q);
    return extended_euclid_solve(b,r,a%b,t2,t);
}

int modularInverse(int b,int n)
{
    int ans = extended_euclid_solve(n,b,0,0,1);
    if(ans<0)
        ans = n + ans;
    return ans;
}

int main()
{
    system("cls");
    int M=19,r=4,e=17,d=2753,N=3233;
    int c = Encryption(M,e,N);
    int c1 = (c*modExp(r,e,N))%N;
    cout<<"c1 : "<<c1<<endl;
    int r_1 = modularInverse(r,N);
    cout<<"r_1: "<<r_1<<endl;
    int s = Decryption(c1,d,N);
    cout<<"s: "<<s<<endl;
    int m = (s*r_1)%N;
    cout<<"m: "<<m<<endl;
    return 0;
}