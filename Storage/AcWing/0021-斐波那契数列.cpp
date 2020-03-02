class Solution {
public:
    int Fibonacci(int n) {
       int f[50];
       f[1]=f[2]=1;
       for(int i=3;i<=n;i++){
           f[i]=f[i-1]+f[i-2];
       }
       return f[n];
    }
};