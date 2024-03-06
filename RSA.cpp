#include <iostream>
#include <cmath>
using namespace std;

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

int extended_euclid_solve(int a,int b, int r,int t1,int t2) {
    int q = int(a/b);
        r = a%b;
        if(r == 0)
            return t2;
        int t = t1 - (t2 * q);
        return extended_euclid_solve(b,r,a%b,t2,t);
}

int extended_euclid(int a,int b)
{
    if(a<b) {
        int t = a;
        a = b;
        b = t;
    }
    int ans = extended_euclid_solve(a,b,0,0,1);
    if(ans<0)
        ans = a + ans;
    return ans;
}

int Encryption(int pt,int pu1,int n) {
    return modExp(pt,pu1,n);
}

int Decryption(int ct,int pk1,int n) {
    return modExp(ct,pk1,n);
}

int main()
{
    system("cls");
    int p = 19, q = 7;
    int pt = 6;
    int n = p*q;
    int pu1 = find_e(n);
    cout<<find_e(n)<<" - "<<phi(n)<<endl;
    int pk1 = extended_euclid(find_e(n),phi(n));
    cout<<"Public Key: ["<<pu1<<","<<n<<"]"<<endl;
    cout<<"Private Key: ["<<pk1<<","<<n<<"]"<<endl;
    int ct = Encryption(pt,pu1,n);
    cout<<"Cipher Text: "<<ct<<endl;
    int plaintext = Decryption(ct,pk1,n);
    cout<<"Plain Text: "<<plaintext<<endl;
    return 0;
}


