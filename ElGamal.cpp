#include <iostream>
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

int extended_euclid_solve(int a,int b, int r,int t1,int t2) {
    int q = int(a/b);
        r = a%b;
        if(r == 0)
            return t2;
        int t = t1 - (t2 * q);
        return extended_euclid_solve(b,r,a%b,t2,t);
}

int extended_euclid(int b,int n)
{
    int ans = extended_euclid_solve(n,b,0,0,1);
    if(ans<0)
        ans = n + ans;
    return ans;
}

int generator(int p)
{
    bool arr[p];
    for(int i=1;i<p;i++)
    {
        arr[i] = false;
    }
    int i = 2;
    while(true)
    {
        for(int j=1;j<=p-1;j++)
        {
            int g = modExp(i,j,p);
            if(arr[g])
            {
                break;
            }
            else
            {
                arr[g] = true;
                if(j==p-1)
                {
                    return i;
                }
            }
        }
        i++;
        for(int i=1;i<p;i++)
        {
            arr[i] = false;
        }
    }
}

int main()
{
    system("cls");
    int p=43,m=14,x=7,r=26,c1,c2;
    int g = generator(p);
    int y = modExp(g,x,p); // y = (g^x)mod(p)
    c1 = modExp(g,r,p); //c1 = (g^r)mod(p)
    c2 = (modExp(y,r,p)*m)%p; //c2 = ((y^r)*m)mod(p)
    cout<<"Encryption:\nc = ("<<c1<<","<<c2<<")"<<endl;
    int plainText = (c2*extended_euclid(modExp(c1,x,p),p))%p; //m = (c2/(c1^x))mod(p)
    cout<<"Decryption:\nm = "<<plainText<<endl;
    
    return 0;
}