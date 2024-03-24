#include <iostream>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"

#define MAX 100

Eigen::MatrixXf computeAtAManually(const Eigen::MatrixXf &A);
void computeEigenvaluesAndVectors(float[][MAX], int, int, Eigen::VectorXf &, Eigen::MatrixXf &);
void computeSVD(float[][MAX], int, int, Eigen::MatrixXf &, Eigen::VectorXf &, Eigen::MatrixXf &);

int main()
{
  int m, n;
  float A[MAX][MAX];

  std::cout << "Nhap so hang cua ma tran: ";
  std::cin >> m;
  std::cout << "Nhap so cot cua ma tran: ";
  std::cin >> n;

  std::cout << "Nhap cac phan tu cua ma tran: " << std::endl;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; j++)
    {
      std::cout << "A[" << i << "][" << j << "] = ";
      std::cin >> A[i][j];
    }

  Eigen::MatrixXf U, Vt;
  Eigen::VectorXf S;

  computeSVD(A, m, n, U, S, Vt);

  std::cout << "A = U * sigma * V^T" << std::endl;

  std::cout << "\nMa tra U:\n"
            << U << std::endl;

  std::cout << "\nMa tran Sigma:\n";
  Eigen::MatrixXf Sigma = Eigen::MatrixXf::Zero(m, n);
  for (int i = 0; i < S.size(); ++i)
  {
    Sigma(i, i) = S(i);
  }
  std::cout << Sigma << std::endl;

  std::cout << "\nMa tran V^T:\n"
            << Vt << std::endl;

  return 0;
}

Eigen::MatrixXf computeAtAManually(const Eigen::MatrixXf &A)
{
  int rows = A.rows();
  int cols = A.cols();
  Eigen::MatrixXf AtA(cols, cols);

  for (int i = 0; i < cols; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      AtA(i, j) = 0.0f;
    }
  }

  for (int i = 0; i < cols; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < rows; k++)
      {
        AtA(i, j) += A(k, i) * A(k, j);
      }
    }
  }

  return AtA;
}

Eigen::MatrixXf manualTranspose(const Eigen::MatrixXf &matrix)
{
  int rows = matrix.rows();
  int cols = matrix.cols();

  Eigen::MatrixXf transposedMatrix(cols, rows);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      transposedMatrix(j, i) = matrix(i, j);
    }
  }

  return transposedMatrix;
}

void computeSVD(float A[][MAX], int m, int n, Eigen::MatrixXf &U, Eigen::VectorXf &S, Eigen::MatrixXf &Vt)
{
  Eigen::VectorXf eigenValues;
  Eigen::MatrixXf eigenVectors;

  computeEigenvaluesAndVectors(A, m, n, eigenValues, eigenVectors);

  Eigen::MatrixXf V = eigenVectors;

  S.resize(n);
  for (int i = 0; i < n; ++i)
  {
    S(i) = sqrt(std::abs(eigenValues(i)));
  }

  Eigen::MatrixXf matrix(m, n);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; j++)
      matrix(i, j) = A[i][j];

  U.resize(n, n);
  for (int i = 0; i < n; ++i)
  {
    U.col(i) = matrix * V.col(i) / S(i);
  }

  Vt = manualTranspose(V);
}

void computeEigenvaluesAndVectors(float A[][MAX], int m, int n, Eigen::VectorXf &eigenValues, Eigen::MatrixXf &eigenVectors)
{
  Eigen::MatrixXf matrix(m, n);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; j++)
      matrix(i, j) = A[i][j];

  Eigen::MatrixXf AtA = computeAtAManually(matrix);

  Eigen::EigenSolver<Eigen::MatrixXf> es(AtA);
  eigenValues = es.eigenvalues().real();
  eigenVectors = es.eigenvectors().real();
}
