#include <iostream>
#include <math.h>
using namespace std;
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}
long long productPrimeFactor(int n)
{
    if (n <= 1)
        return 0;
    long long product = 1;
    for (int i = 2; i <= n; i++)
    {
        if (isPrime(i))
            product = product * i;
    }
    return product;
}
int main()
{
    int n;
    cout << "Nhap n = ";
    cin >> n;
    cout << "Tich cac so nguyen to khong vuot qua n la: " << productPrimeFactor(n);
    return 0;
}
