#include <iostream>
using namespace std;
#define MAX 100
typedef int VECTOR[MAX];
void PrimeFactors(int n, VECTOR S, int &k);
int main()
{
    int k;
    int F[MAX];
    int n;
    cout << "Nhap n = ";
    cin >> n;
    PrimeFactors(n, F, k);
    cout << "Ket qua phan tich: ";
    cout << "n = " << F[0] << " = ";
    for (int i = 1; i <= k; i++)
    {
        if (i != k)
            cout << F[i] << "*";
        else
            cout << F[i];
    }

    return 0;
}
void PrimeFactors(int n, VECTOR S, int &k)
{
    k = 0;
    S[k] = n;
    for (int i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            k++;
            S[k] = i;
            n = n / i;
        }
    }
    if (n > 1)
        S[++k] = n;
}
