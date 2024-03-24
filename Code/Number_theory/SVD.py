from math import pow
import math
from numpy import cumproduct, roots
from numpy.linalg import eig
import numpy as np

def sortMatrix(e, A):
    A = A.transpose()
    d = list(zip(e, A))
    e.sort(reverse=True)
    d.sort(key=lambda x: x[0], reverse=True)
    return np.array([i[1] for i in d]).transpose()

def SVD(A, m, n):
    U = np.zeros((m, m), float)
    V = np.zeros((n, n), float)
    e, V = np.linalg.eig(np.dot(np.transpose(A), A))
    e = list(e)
    V = sortMatrix(e, V)
    D = np.zeros((m, n), float)
    temp = V.transpose()
    if n > m:
        for i in range(m):
            D[i][i] = math.sqrt(e[i])
        for i in range(m):
            U[i] = np.dot(np.array(A), np.array(temp[i])) / D[i][i]
    else:
        for i in range(n):
            D[i][i] = math.sqrt(e[i])
        for i in range(n):
            U[i] = np.dot(np.array(A), np.array(temp[i])) / D[i][i]
    U = np.transpose(U)
    V = temp
    return U, D, V

if __name__ == '__main__':
    m = int(input("Nhap so hang : "))
    n = int(input("Nhap so cot: "))
    A = np.zeros((m, n), float)
    for i in range(0, m):
        for j in range(0, n):
            print("Nhap a[", i+1, "][", j+1, "]: ", end='')
            A[i][j] = float(input())

    print('----- Ma tran A: -----\n' + str(A) + '\n')
    U, D, VT = SVD(A, m, n)
    print('----- Ma tran U: -----\n' + str(U) + '\n')
    print('----- Ma tran D: -----\n' + str(D) + '\n')
    print('----- Ma tran V^T: -----\n' + str(VT) + '\n')
    print('----- Kiem Tra SVD: -----\n' + str(np.dot(np.dot(U, D), VT)) + '\n')
