#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;
const int MAX = 100;

// Hàm nhân hai ma trận vuông A và B cấp n
void Nhan2MaTran(float A[][MAX], float B[][MAX], float C[][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Hàm giải nghiệm phương trình bậc 2
void GiaiPTBac2(float f[], float x[])
{
    // tính delta
    float delta = f[1] * f[1] - 4 * f[0] * f[2];
    // tính nghiem
    if (delta > 0)
    {
        x[0] = (float)((-f[1] + sqrt(delta)) / (2 * f[0]));
        x[1] = (float)((-f[1] - sqrt(delta)) / (2 * f[0]));
        x[2] = 2; // Có 2 nghiệm
    }
    else if (delta == 0)
    {
        x[0] = (-f[1] / (2 * f[0]));
        x[2] = 1; // Có 1 nghiệm
    }
    else
        return;
}

// Hàm giải nghiệm phương trình bậc 3
void GiaiPTBac3(float f[], float x[])
{
    float PI = 3.14159265358979323846;
    float delta = (float)pow(f[1], 2) - 3 * f[0] * f[2];
    float k = (float)(9 * f[0] * f[1] * f[2] - 2 * pow(f[1], 3) - 27 * pow(f[0], 2) * f[3]) / (2 * sqrt(fabs(pow(delta, 3))));
    if (delta > 0)
    {
        if (fabs(k) <= 1)
        {
            x[0] = (2 * sqrt(delta) * cos((acos(k) / 3)) - f[1]) / (3 * f[0]);
            x[1] = (2 * sqrt(delta) * cos((acos(k) / 3 - (2 * PI / 3))) - f[1]) / (3 * f[0]);
            x[2] = (2 * sqrt(delta) * cos((acos(k) / 3 + (2 * PI / 3))) - f[1]) / (3 * f[0]);
            x[3] = 3; // Có 3 nghiệm
        }
        else
        {
            x[0] = ((sqrt(delta) * fabs(k)) / (3 * f[0] * k)) * (pow(fabs(k) + sqrt(pow(k, 2) - 1), 1.0 / 3) + pow(fabs(k) - sqrt(pow(k, 2) - 1), 1.0 / 3)) - (f[1] / (3 * f[0]));
        }
    }
    if (delta == 0)
    {
        x[0] = (-f[1] + pow(pow(f[1], 3) - 27 * pow(f[0], 2) * f[3], 1.0 / 3)) / (3 * f[0]);
        x[3] = 1; // Có 1 nghiệm
    }
    if (delta < 0)
    {
        x[0] = (sqrt(fabs(delta)) / (3 * f[0])) * (pow(k + sqrt(pow(k, 2) + 1), 1.0 / 3) + pow(k - sqrt(pow(k, 2) + 1), 1.0 / 3)) - (f[1] / (3 * f[0]));
        x[3] = 1; // Có 1 nghiệm
    }
}

// Tính định thức của ma trận vuông A cấp n
float det(float a[][MAX], int n)
{
    int i, j, k, dem = 0, kt;
    float b[MAX], h, kq = 1;
    for (i = 0; i < n - 1; i++)
    {
        if (a[i][i] == 0)
        {
            kt = 0;
            for (j = i + 1; j < n; j++)
            {
                if (a[i][j] != 0)
                {
                    for (k = 0; k < n; k++)
                    {
                        float t = a[k][i];
                        a[k][i] = a[k][j];
                        a[k][j] = t;
                    }
                    dem++;
                    kt++;
                    break;
                }
            }
            if (kt == 0)
                return 0;
        }
        b[i] = a[i][i];
        for (j = 0; j < n; j++)
            a[i][j] /= b[i];
        for (j = i + 1; j < n; j++)
        {
            h = a[j][i];
            for (k = 0; k < n; k++)
                a[j][k] = a[j][k] - h * a[i][k];
        }
    }
    b[n - 1] = a[n - 1][n - 1];
    for (i = 0; i < n; i++)
        kq *= b[i];
    if (dem % 2 == 0)
        return kq;
    return -kq;
}

// Tính định thức ma trận con của ma trận A cấp n
float con(float a[][MAX], int n, int h, int c)
{
    float b[MAX][MAX];
    int i, j, x = -1, y;
    for (i = 0; i < n; i++)
    {
        if (i == h)
            continue;
        x++;
        y = -1;
        for (j = 0; j < n; j++)
        {
            if (j == c)
                continue;
            y++;
            b[x][y] = a[i][j];
        }
    }
    if ((h + c) % 2 == 0)
        return det(b, n - 1);
    return -det(b, n - 1);
}

// Tìm ma trận nghịch đảo của ma trận vuông A cấp n
void nghichdao(float a[][MAX], float b[][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = con(a, n, i, j);
        }
    }
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            float t = b[i][j];
            b[i][j] = b[j][i];
            b[j][i] = t;
        }
    float k = det(a, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] /= k;
}

// EigenDecomposition = pp Danhilepski
void EigenDecomposition(float A[][MAX], int n)
{
    float M[MAX][MAX], M1[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    bool transpose = false;
    if (A[n - 1][n - 2] == 0)
    {
        transpose = true;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                float temp = A[i][j];
                A[i][j] = A[j][i];
                A[j][i] = temp;
            }
        }
    }

    // khoi tao ma tran don vi C
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                C[i][j] = 1;
            else
                C[i][j] = 0;
        }
    }

    for (int k = n - 2; k >= 0; k--)
    {
        // Tinh 2 ma tran M, M1
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != k)
                {
                    if (i == j)
                    {
                        M[i][j] = 1;
                        M1[i][j] = 1;
                    }
                    else
                    {
                        M[i][j] = 0;
                        M1[i][j] = 0;
                    }
                }
                else
                {
                    M1[i][j] = A[k + 1][j];
                    if (j == k)
                        M[i][j] = 1.0 / A[k + 1][k];
                    else
                        M[i][j] = -A[k + 1][j] / A[k + 1][k];
                }
            }
        }

        Nhan2MaTran(A, M, B, n);
        Nhan2MaTran(M1, B, A, n);
        Nhan2MaTran(C, M, B, n);
        // Gan lai C = B
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                C[i][j] = B[i][j];
            }
        }
    }

    float f[n + 1];
    f[0] = 1;
    for (int i = 0; i < n; i++)
    {
        f[i + 1] = -A[0][i];
    }
    float x[n + 1];
    x[n] = 0;
    if (n == 2)
        GiaiPTBac2(f, x);
    else
        GiaiPTBac3(f, x);
    float D[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                D[i][j] = x[i];
            else
                D[i][j] = 0;
        }
    }
    cout << "Ma tran D: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << setprecision(5) << fixed << D[i][j] << "\t";
        }
        cout << endl;
    }

    float T[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            T[i][j] = (float)pow(x[j], n - i - 1);
        }
    }
    float P[MAX][MAX];
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            P[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                P[i][j] += B[i][k] * T[k][j];
            }
        }
    }
    // Chuẩn hóa ma trận P
    for (int j = 0; j < n; j++)
    {
        float p = 0;
        for (int i = 0; i < n; i++)
            p = p + P[i][j] * P[i][j];
        for (int i = 0; i < n; i++)
            P[i][j] = P[i][j] / sqrt(p);
    }
    if (transpose)
    {
        cout << "Ma tran V^(-1): " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(10) << setprecision(5) << fixed << P[j][i] << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Ma tran V: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(10) << setprecision(5) << fixed << P[i][j] << "\t";
            }
            cout << endl;
        }
    }
    float Q[MAX][MAX];
    nghichdao(P, Q, n);
    if (transpose)
    {
        cout << "Ma tran V: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(10) << setprecision(5) << fixed << Q[j][i] << "\t";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Ma tran V^(-1): " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(10) << setprecision(5) << fixed << Q[i][j] << "\t";
            }
            cout << endl;
        }
    }
}
void nhapMaTran(float A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A[i][j];
        }
}
int main()
{
    int n;
    float A[MAX][MAX];
    cout << "Nhap n = ";
    cin >> n;
    cout << "Nhap ma tran A: " << endl;
    nhapMaTran(A, n);
    cout << "\nMa tran A: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(10) << setprecision(5) << fixed << A[j][i] << "\t";
        }
        cout << endl;
    }
    // float A[MAX][MAX] = {{2, 1, 0},
    //                      {1, 4, 1},
    //                      {2, 0, 4}};
    // float A[MAX][MAX] = {{5, -1},
    //                      {-1, 7}};
    cout << "-----------------------" << endl;
    cout << "Phan ra Eigenvalue va Eigenvector: A = VDV^-1 " << endl;
    EigenDecomposition(A, n);
    return 0;
}