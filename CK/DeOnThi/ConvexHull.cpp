#include <iostream>
using namespace std;
#define N 500
typedef struct
{
    double x;
    double y;
} point;

double det(point &p, point &q, point &r)
{
    double d1, d2;
    d1 = q.x * r.y + p.x * q.y + p.y * r.x;
    d2 = q.x * p.y + p.x * r.y + r.x * q.y;
    return d1 - d2;
}

float area(point *a, int n)
{
    float s = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == n)
        {
            s += a[i].x * a[1].y - a[i].y * a[1].x;
        }
        else
        {
            s += a[i].x * a[i + 1].y - a[i].y * a[i + 1].x;
        }
    }
    return abs(s) / 2;
}

void ConvexHull(point *a, const int &n)
{
    int i, j, j1, j2, n2;
    point tg, Lupp[N], Llow[N];
    cout << "\nTap hop diem: ";
    for (i = 1; i <= n; i++)
        cout << "(" << a[i].x << "," << a[i].y << "), ";
    cout << endl;
    // sort các điểm theo buble sort
    for (i = 1; i <= n - 1; i++)
    {
        for (j = n - 1; j >= i; j--)
        {
            if ((a[j].x > a[j + 1].x) || ((a[j].x == a[j + 1].x) && (a[j].y > a[j + 1].y)))
            {
                tg = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tg;
            }
        }
    }
    // tính tập L upper
    Lupp[1] = a[1];
    Lupp[2] = a[2];
    j1 = 2;
    for (i = 3; i <= n; i++)
    {
        j1++;
        Lupp[j1] = a[i];
        while ((j1 > 2) && (det(Lupp[j1 - 2], Lupp[j1 - 1], Lupp[j1]) > -0.001))
        {
            Lupp[j1 - 1] = Lupp[j1];
            j1--;
        }
    }
    // tính tập L lower
    Llow[1] = a[n];
    Llow[2] = a[n - 1];
    j2 = 2;
    for (i = n - 2; i >= 1; i--)
    {
        j2++;
        Llow[j2] = a[i];
        while ((j2 > 2) && (det(Llow[j2 - 2], Llow[j2 - 1], Llow[j2]) > -0.001))
        {
            Llow[j2 - 1] = Llow[j2];
            j2--;
        }
    }
    // Xóa điểm đầu và cuối của tập bao lồi dưới
    // Hợp hai tập bao lồi trên và bao lồi dưới lại với nhau
    for (i = 1; i <= j2 - 2; i++)
        Lupp[j1 + i] = Llow[i + 1];
    n2 = j1 + j2 - 2;
    cout << "\nTap bao loi la: ";
    for (i = 1; i <= n2; i++)
    {
        cout << "(" << Lupp[i].x << "," << Lupp[i].y << "), ";
    }

    cout << "\n\nDien tich bao loi la: " << area(Lupp, n2);
    cout << endl;
}

int main()
{
    int n;
    point points[N];
    points[0] = {0, 0};
    point p;
    cout << "Nhap so diem n = ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << "Nhap x" << i << " = ";
        cin >> p.x;
        cout << "Nhap y" << i << " = ";
        cin >> p.y;
        points[i] = {p.x, p.y};
    }
    ConvexHull(points, n);
    return 0;
}