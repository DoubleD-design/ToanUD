#include <stdio.h>
#include <math.h>

#define MAX 100

#define EPSILON 1e-5

void inputMatrix(int *n, double matrix[MAX][MAX])
{
  printf("Nhap n: ");
  scanf("%d", n);

  for (int i = 0; i < *n; i++)
  {
    for (int j = 0; j < *n; j++)
    {
      printf("Nhap phan tu thu [%d][%d]: ", i, j);
      scanf("%lf", &matrix[i][j]);
    }
  }
}

double determinant(int p, double mat[MAX][MAX])
{
  if (p == 1)
    return mat[0][0];
  if (p == 2)
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

  double det = 0;
  double temp[MAX][MAX];
  int sign = 1;

  for (int i = 0; i < p; i++)
  {
    int subi = 0;
    for (int j = 1; j < p; j++)
    {
      int subj = 0;
      for (int k = 0; k < p; k++)
      {
        if (k == i)
          continue;
        temp[subi][subj] = mat[j][k];
        subj++;
      }
      subi++;
    }
    det += (sign * mat[0][i] * determinant(p - 1, temp));
    sign = -sign;
  }

  return det;
}

int isPositiveDefinite(int n, double mat[MAX][MAX])
{
  for (int i = 1; i <= n; i++)
  {
    if (determinant(i, mat) <= EPSILON)
      return 0;
  }
  return 1;
}

void CholeskyDecomposition(int n, double matrix[MAX][MAX], double L[MAX][MAX])
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      double sum = 0;
      if (j == i)
      {
        for (int k = 0; k < j; k++)
        {
          sum += L[j][k] * L[j][k];
        }
        L[j][j] = sqrt(matrix[j][j] - sum);
      }
      else
      {
        for (int k = 0; k < j; k++)
        {
          sum += L[i][k] * L[j][k];
        }
        L[i][j] = (matrix[i][j] - sum) / L[j][j];
      }
    }
  }
}

void printMatrix(int n, double matrix[MAX][MAX])
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%lf ", matrix[i][j]);
    }
    printf("\n");
  }
}

void transposeMatrix(int n, double matrix[MAX][MAX], double transposed[MAX][MAX])
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      transposed[j][i] = matrix[i][j];
    }
  }
}

int main()
{
  int n;
  double matrix[MAX][MAX];
  double L[MAX][MAX];
  double L_T[MAX][MAX];
  double D[MAX];

  inputMatrix(&n, matrix);

  if (!isPositiveDefinite(n, matrix))
  {
    printf("Ma tran khong duong xac dinh\n");
    return 0;
  }

  CholeskyDecomposition(n, matrix, L);

  transposeMatrix(n, L, L_T);

  printf("\nMa tran A: \n");
  printMatrix(n, matrix);

  printf("\nMa tran L: \n");
  printMatrix(n, L);

  printf("\nMa tran L^T: \n");

  printMatrix(n, L_T);

  return 0;
}
