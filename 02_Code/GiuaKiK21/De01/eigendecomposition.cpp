#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 3

struct Root1
{
  float x1;
  float x2;
  float x3;
};

struct Root2
{
  float x;
  float r;
  float i;
  float discriminant;
};

Root1 root1;
Root2 root2;

void PrintMatrix(float mat[N][N], int n)
{

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < N; j++)
    {
      cout << fixed << setprecision(5) << mat[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void MulMatric(float mat1[][N], float mat2[][N], float res[][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      res[i][j] = 0;

      for (int k = 0; k < N; k++)
      {
        res[i][j] += mat1[i][k] * mat2[k][j];
      }
      res[i][j] = (res[i][j] * 1e5) / 1e5;
    }
  }
}

void NhanTungToe(float mat[][N])
{
  float x1 = mat[0][0];
  float x2 = mat[0][1];
  float x3 = mat[0][2];

  float y1 = mat[1][0];
  float y2 = mat[1][1];
  float y3 = mat[1][2];

  float z1 = mat[2][0];
  float z2 = mat[2][1];
  float z3 = mat[2][2];

  float ld3 = -1;
  float ld2 = x1 + y2 + z3;
  float ld1 = -x1 * y2 - x1 * z3 - y2 * z3 - y3 * z2 + x2 * y1 + x3 * z1;
  float du = x1 * y2 * z3 - x1 * y3 * z2 - x2 * y1 * z3 + x2 * y3 * z1 + x3 * y1 * z2 - x3 * y2 * z1;

  cout << ld3 << " " << ld2 << " " << ld1 << " " << du;
}
void SolveCubicEquation(float a, float b, float c, float d)
{

  const float PI = 4.0 * atan(1.0);
  // Reduced equation: X^3 - 3pX - 2q = 0, where X = x-b/(3a)
  float p = (b * b - 3.0 * a * c) / (9.0 * a * a);
  float q = (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b) / (54.0 * a * a * a);
  float offset = b / (3.0 * a);

  // Discriminant
  float discriminant = p * p * p - q * q;

  // co 3 nghiem
  if (discriminant > 0)
  {
    // set X = 2 sqrt(p) cos(theta) and compare 4 cos^3(theta)-3 cos(theta) = cos(3 theta)
    float theta = acos(q / (p * sqrt(p)));
    float r = 2.0 * sqrt(p);

    root1.x1 = r * cos((theta + 2.0 * 0 * PI) / 3.0) - offset;
    root1.x2 = r * cos((theta + 2.0 * 1 * PI) / 3.0) - offset;
    root1.x3 = r * cos((theta + 2.0 * 2 * PI) / 3.0) - offset;
  }
  else
  {
    float gamma1 = cbrt(q + sqrt(-discriminant));
    float gamma2 = cbrt(q - sqrt(-discriminant));

    root2.x = gamma1 + gamma2 - offset;
    // real number
    float re = -0.5 * (gamma1 + gamma2) - offset;
    // Imaginary number
    float im = (gamma1 - gamma2) * sqrt(3.0) / 2.0;

    root2.r = re;
    root2.i = im;
    root2.discriminant = discriminant;
  }
}

void CreateUnitMatrix(float E[][N], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (j == i)
        E[i][j] = 1;
      else
        E[i][j] = 0;
    }
  }
}
void CopyMatrix(float A[][N], float B[][N], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      A[i][j] = B[i][j];
    }
  }
}
// sort giam dan
void SortArr(float a[N], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (a[j] > a[i])
      {
        float tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
    }
  }
}

void FindEigenvaluesAndEigenVector(float A[][N], float M[][N], float M1[][N], float P[N][N], int n)
{
  float Acopy[N][N];
  CopyMatrix(Acopy, A, n);
  float temp[N][N];
  float C[N][N];
  CreateUnitMatrix(C, n);
  for (int k = n - 2; k >= 0; k--)
  {
    // duyet ma tran
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
          M1[i][j] = Acopy[k + 1][j];
          if (j == k)
          {
            M[i][j] = 1 / Acopy[k + 1][k];
          }
          else
          {
            M[i][j] = -Acopy[k + 1][j] / Acopy[k + 1][k];
          }
        }
      }
    }
    MulMatric(Acopy, M, temp);
    MulMatric(M1, temp, Acopy);
    MulMatric(C, M, temp);
    CopyMatrix(C, temp, n);
  }

  float sign = pow(-1, n);
  SolveCubicEquation(sign, -sign * Acopy[0][0], -sign * Acopy[0][1], -sign * Acopy[0][2]);
  float root[N];
  root[0] = root1.x1;
  root[1] = root1.x2;
  root[2] = root1.x3;
  SortArr(root, n);

  float y[N][N];
  float x[N][N];

  for (int i = 0; i < n; i++)
  {
    float eigenValue = root[i];
    for (int j = n - 1; j >= 0; j--)
    {
      y[n - 1 - j][0] = pow(eigenValue, j);
    }
    MulMatric(C, y, x);
    for (int k = 0; k < n; k++)
    {
      P[k][i] = round(x[k][0] * 1e5) / 1e5; // lam tron den chu so thap phan thu 5
    }
  }
}

void FindInverseMatrix(float A[][N], float inverse[][N], int n)
{
  float Acopy[N][N];
  CopyMatrix(Acopy, A, n);
  float I[N][N];
  CreateUnitMatrix(I, n);
  for (int i = 0; i < n; i++)
  {
    float pivot = Acopy[i][i];
    for (int j = 0; j < n; j++)
    {
      Acopy[i][j] /= pivot;
      I[i][j] /= pivot;
    }
    for (int k = 0; k < n; k++)
    {
      if (k != i)
      {
        float factor = Acopy[k][i];
        for (int j = 0; j < n; j++)
        {
          Acopy[k][j] -= factor * Acopy[i][j];
          I[k][j] -= factor * I[i][j];
        }
      }
    }
  }
  CopyMatrix(inverse, I, n);
}

int main()
{
  float A[N][N] = {{1, 3, 7}, {5, 6, 7}, {7, 9, 7}};

  float M[N][N];
  float M1[N][N];
  float P[N][N];
  float P1[N][N];

  cout << "Ma tran A: " << endl;
  PrintMatrix(A, N);
  FindEigenvaluesAndEigenVector(A, M, M1, P, N);

  cout << "Ma tran P: " << endl;
  PrintMatrix(P, N);
  FindInverseMatrix(P, P1, N);

  MulMatric(P1, A, M);

  MulMatric(M, P, M1);
  cout << "Ma tran D: " << endl;
  PrintMatrix(M1, N);

  return 0;
}
