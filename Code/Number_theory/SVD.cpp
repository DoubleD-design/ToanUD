#include <iostream>
#include <iomanip>
using namespace std;
#define MAX 100
void transpose(float A[][MAX], float B[][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            B[i][j] = A[j][i];
    }
}
void swap(float &a, float &b)
{
    float temp;
    temp = a;
    a = b;
    b = temp;
}
void printMatrix(float A[][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setprecision(8) << A[i][j] << " ";
        cout << endl;
    }
}
void squareMatrixProduct(float A[][MAX], float B[][MAX], float C[][MAX], int n)
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
void SolvedCubic(float C[], float X[])
{
    float delta, k;
    delta = pow(C[1], 2) - 3 * C[0] * C[2];
    k = (9 * C[0] * C[1] * C[2] - 2 * pow(C[1], 3) - 27 * pow(C[0], 2) * C[3]) / (2 * sqrt(pow(fabs(delta), 3)));
    if (delta > 0)
    {
        if (fabs(k) <= 1)
        {
            X[0] = (2 * sqrt(delta) * cos(acos(k) / 3) - C[1]) / (3 * C[0]);
            X[1] = (2 * sqrt(delta) * cos(acos(k) / 3 - (2 * M_PI / 3)) - C[1]) / (3 * C[0]);
            X[2] = (2 * sqrt(delta) * cos(acos(k) / 3 + (2 * M_PI / 3)) - C[1]) / (3 * C[0]);
        }
        if (fabs(k) > 1)
        {
            X[0] = ((sqrt(delta) * fabs(k)) / (3 * C[0] * k)) * (pow((fabs(k) + sqrt(pow(k, 2) - 1)), 1.0 / 3) + pow((fabs(k) - sqrt(pow(k, 2) - 1)), 1.0 / 3)) - (C[1] / (3 * C[0]));
        }
    }
    else if (delta == 0)
    {
        X[0] = (-C[1] - pow(-(pow(C[1], 3) - 27 * C[0] * C[0] * C[3]), 1.0 / 3)) / (3 * C[0]);
    }
    else
        X[0] = (sqrt(fabs(delta)) / (3 * C[0])) * (pow((k + sqrt(k * k + 1)), 1.0 / 3) - pow(-(k - sqrt(k * k + 1)), 1.0 / 3)) - (C[1] / (3 * C[0]));
}
void EigenDecomposition(float A[][MAX], float P[][MAX], float D[][MAX], int n)
{
    float M[MAX][MAX], M1[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                C[i][j] = 1;
            else
                C[i][j] = 0;
        }
    }
    for (int k = n - 2; k >= 0; k--)
    {
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
        squareMatrixProduct(A, M, B, n);
        squareMatrixProduct(M1, B, A, n);
        squareMatrixProduct(C, M, B, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                C[i][j] = B[i][j];
        }
    }
    float heso[MAX] = {1, -A[0][0], -A[0][1], -A[0][2]};
    cout << endl;
    float X[MAX];
    SolvedCubic(heso, X);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                D[i][j] = X[i];
            else
                D[i][j] = 0;
        }
    }
    float T[MAX][MAX];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            T[i][j] = pow(X[j], n - i - 1);
        }
    }
    float P1[MAX][MAX];
    squareMatrixProduct(B, T, P, n);
    for (int j = 0; j < n; j++)
    {
        float p = 0;
        for (int i = 0; i < n; i++)
            p += pow(P[i][j], 2);
        for (int i = 0; i < n; i++)
            P[i][j] = P[i][j] / sqrt(p);
    }
}
void SVD(float A[][MAX], int n)
{
    float At[MAX][MAX];
    transpose(A, At, n);
    float S[MAX][MAX], P[MAX][MAX], D[MAX][MAX], U[MAX][MAX];
    squareMatrixProduct(At, A, S, n);
    EigenDecomposition(S, P, D, n);
    float Vt[MAX][MAX];
    transpose(P, Vt, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            D[i][j] = sqrt(D[i][j]);
    }
    squareMatrixProduct(A, P, U, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            U[j][i] *= 1.0 / D[i][i];
        }
    }
    // in ma tran
    cout << "Singular value decomposition: " << endl;
    cout << "U" << endl;
    for (int i = 0; i < n; i++)
    {
        // Ma tran U
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
                cout << setprecision(4) << (-1 * U[i][j]) << "\t\t";
            else
                cout << setprecision(4) << U[i][j] << "\t\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "D" << endl;
    for (int i = 0; i < n; i++)
    {
        // Ma tran Σ (ma trận D)
        for (int j = 0; j < n; j++)
            cout << setprecision(4) << D[i][j] << "\t\t";
        cout << endl;
    }
    cout << endl;
    cout << "Vt" << endl;
    for (int i = 0; i < n; i++)
    {
        // Ma tran Vt
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
                cout << setprecision(4) << (-1 * Vt[i][j]) << "\t\t";
            else
                cout << setprecision(4) << Vt[i][j] << "\t\t";
        }
        cout << endl;
    }
}
int main()
{
    int n = 3;
    float A[][MAX] = {{7, 2, 1},
                      {8, 5, 2},
                      {1, 2, 6}};
    float P[MAX][MAX];
    cout << "Ma tran A:" << endl;
    printMatrix(A, 3);
    cout << "-------------------" << endl;
    cout << "Phan ra SVD: " << endl;
    SVD(A, n);
    return 0;
}
