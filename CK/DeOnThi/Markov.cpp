#include <iostream>
#include <iomanip>
using namespace std;

const int N = 4;

void out(float P[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setprecision(3) << P[i][j] << "\t";
        }
        cout << endl;
    }
}

void assign(float A[][N], float B[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            B[i][j] = A[i][j];
        }
    }
}

void makeIdentity(float A[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void multiply(float A[][N], float B[][N], float C[][N]) {
    float temp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[i][j] = 0;
            for (int k = 0; k < N; k++) {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    assign(temp, C);
}

void power(float A[][N], float B[][N], int n) {
    if (n == 0) {
        makeIdentity(B);
        return;
    }
    if (n == 1) {
        assign(A, B);
        return;
    }
    float temp[N][N];
    power(A, B, n / 2);
    multiply(B, B, temp);
    if (n % 2 != 0) {
        multiply(temp, A, B);
    } else {
        assign(temp, B);
    }
}

int main() {
    float P[N][N] = {
        {0.6, 0.4, 0, 0},
        {0.3, 0.3, 0.3, 0.1},
        {0, 0, 0.7, 0.3},
        {0, 0.5, 0.5, 0}
    };

    int n = 3; // Số giai đoạn vận hành
    float P_n[N][N];
    power(P, P_n, n);

    cout << "Ma tran chuyen doi trang thai P sau " << n << " giai doan van hanh:" << endl;
    out(P_n);

    // Vector phân phối xác suất ban đầu
    float pi0[N] = {0, 1, 0, 0}; // Hệ thống bắt đầu ở trạng thái 1

    // Tính toán vector phân phối xác suất sau n giai đoạn vận hành
    float pi_n[N] = {0, 0, 0, 0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pi_n[i] += pi0[j] * P_n[j][i];
        }
    }

    cout << "Vector phan phoi xac suat sau " << n << " giai doan van hanh:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "pi[" << i << "] = " << setprecision(3) << pi_n[i] << endl;
    }

    // Tìm xác suất lớn nhất khi hệ thống làm việc ở trạng thái 3
    float max_prob = pi_n[3];
    cout << "Xac suat lon nhat he thong lam viec o trang thai 3 sau " << n << " giai doan van hanh: " << max_prob << endl;

    return 0;
}
