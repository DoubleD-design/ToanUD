#include <iostream>
using namespace std;

int thangDuTrungHoa(int m[], int a[], int k)
{
    int x = 1;
    while (true)
    {
        int j;
        for (j = 0; j < k; j++)
            if (x % m[j] != a[j])
                break;
        if (j == k)
            return x;
        x++;
    }
    return x;
}

int main(void)
{
    // x == ai mod mi
    int k;
    cout << "Nhap so phuong trinh k = ";
    cin >> k;
    int a[k];
    int m[k];
    for (int i = 0; i < k; i++)
    {
        cout << "a" << i + 1 << " = ";
        cin >> a[i];
        cout << "m" << i + 1 << " = ";
        cin >> m[i];
    }
    int M = 1;
    for (int i = 0; i < k; i++)
    {
        M = M * m[i];
    }
    int result = thangDuTrungHoa(m, a, k);
    cout << "Ket qua: " << result << "(mod " << M << ") = " << result;
    return 0;
}
