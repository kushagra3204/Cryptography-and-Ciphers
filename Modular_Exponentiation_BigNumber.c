#include<stdio.h>

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

int main()
{
    int base = 123;
    int exp = 456789;
    int mod = 789012;
    int result = modExp(base,exp,mod);
    printf("\n(%d^%d)mod(%d) = %d\n",base,exp,mod,result);
    printf("\n(%d^%d)mod(%d) = %d\n\n",2,123,17,modExp(2,123,17));
}