#include <iostream>
#include <iomanip>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;
void _Solve(MatrixXd matrix, int m, int n){
    SelfAdjointEigenSolver<MatrixXd> eig_sol(matrix);
    VectorXd lambdas = eig_sol.eigenvalues();
    MatrixXd P = eig_sol.eigenvectors();
    MatrixXd D(m,n);
    for (int i = 0; i < m;i++){
        for (int j = 0;j< n ;j++){
            if (i==j) D(i,j) = lambdas[i];
            else D(i,j) = 0;
        }
    }
    MatrixXd inv = P.inverse();
    cout << setw(6) << " P" 
         << setw(70) << "Diagonal matrix" << setw(50) << "P inverse" << endl;
    for (int i = 0; i < n; i++) {     
        for (int j = 0; j < n; j++)
            cout <<  setw(10) << setprecision(5) << P(i,j) << "\t";
        cout << "\t";
        for(int j = 0; j < n; j++)
            cout << setw(10) << setprecision(5) << D(i,j) << "\t";
        cout << "\t";
        for (int j = 0; j < n; j++)
            cout << setw(10) << setprecision(5) << inv(i,j) << "\t";
        cout << endl;
    }
    cout << "Reconstruct matrix: " << endl;
    cout << P*D*inv;  
}

int main(){
    int m = 3, n = 3;
    MatrixXd matrix(m,n);
    matrix << 14, -5, 4, -5, 25,12,4,12,14 ;
    _Solve(matrix,m,n);
    return 0;
}
