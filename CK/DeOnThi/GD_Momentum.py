from __future__ import division, print_function, unicode_literals
import math
import numpy as np

# f(x)


def cost(x):
    return (math.exp(4*x) - 2*(x**2) - 5*(x**3))**2 + 2*(x**4)


# f'(x)
def grad(x):
    return 2*(math.exp(4*x) - 2*(x**2) - 5*(x**3))*(4*math.exp(4*x) - 4*x - 15*(x**2)) + 8*(x**3)


def GD_momentum(theta_init, grad, learningRate, momentum, e, loop):
    theta = [theta_init]
    v_old = np.zeros_like(theta_init)
    for it in range(loop):
        v_new = momentum*v_old + learningRate*grad(theta[-1])
        theta_new = theta[-1] - v_new
        if abs(grad(theta_new)) < e:
            break
        theta.append(theta_new)
        v_old = v_new
    return theta, it


if __name__ == '__main__':
    x0 = input("Nhap diem bat dau x0: ")
    x0 = float(x0)
    learningRate = input("Nhap tham so hoc learning rate: ")
    learningRate = float(learningRate)
    momentum = input("Nhap tham so momentum: ")
    momentum = float(momentum)
    e = input("Nhap do chinh xac e: ")
    e = float(e)
    loop = input("Nhap so lan lap loop: ")
    loop = int(loop)
    (x, it) = GD_momentum(x0, grad, learningRate, momentum, e, loop)

    print('Gia tri nho nhat tai x = %f, min(fx) = %f' % (x[-1], cost(x[-1])))
