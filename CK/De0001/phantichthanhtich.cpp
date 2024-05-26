#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void phantich(int n)
{
    int count;
    for (int i = 2; i <= n; i++)
    {
        count = 0;
        while (n % i == 0)
        {
            ++count;
            n /= i;
        }
        if (count)
        {
            cout << i;
            if (count > 1)
                cout << "^" << count;
            if (n > i)
            {
                cout << " * ";
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    phantich(n);
    return 0;
}