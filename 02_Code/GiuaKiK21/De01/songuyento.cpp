#include <stdio.h>
#include <cstring>

const int N = 25000;

void sieveOfEratosthenes(long long int n)
{
  bool prime[n + 1];
  memset(prime, true, sizeof(prime));
  long long int p = 2;

  while (p * p <= n)
  {
    if (prime[p] == true)
    {
      for (long long int i = p * p; i <= n; i += p)
        prime[i] = false;
    }
    p++;
  }

  printf("Cac so nguyen to nho hon %lld la: ", n);
  long long int sum = 0;
  for (long long int i = 2; i <= n; i++)
  {
    if (prime[i])
    {
      printf("%lld ", i);
      sum += i;
    }
  }
  printf("\n");

  printf("Tong cua day so tren la: %lld\n", sum);
}

bool isPrime(int n)
{
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;

  if (n % 2 == 0 || n % 3 == 0)
    return false;

  int i = 5;
  while (i * i <= n)
  {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
    i += 6;
  }
  return true;
}

void nearestPrime(int n)
{
    int before = n - 1, after = n + 1;
    int nearest;
    while (!isPrime(before))
        before--;
    while (!isPrime(after))
        after++;
    if(before > after) nearest = after;
    else nearest = before;

    printf("So nguyen to gan nhat voi %d la: %d \n", n, nearest);
}

int main()
{
  sieveOfEratosthenes(N);
  nearestPrime(N);
  return 0;
}
