#include <iostream>
using namespace std;
double e = M_E;
float f(float x)
{
    return pow((exp(2 * x * x + 1) - 2 * x + 1), 2) - 5 * pow(x + 1, 3);
}

float grad(float x)
{
    return 2*(pow(e,4*x) - 2*pow(x,2) - 5*pow(x,3))*(4*pow(e,4*x) - 4*x - 15*pow(x,2)) - 8*pow(x,3);
}
void gradient_momentum(float x, float theta, float alpha, float n, float e)
{
    float x_new, x0 = 0;
    for (int i = 0; i < n; i++)
    {
        float delta = x - x0;
        x_new = x - theta * grad(x) - alpha * delta;
        if (abs(grad(x)) <= e)
        {
            break;
        }
        x0 = x;
        x = x_new;
        cout << "x[" << i + 1 << "] = " << x << endl;
    }
}
int main()
{
    float theta, alpha, e, n;
    float x;
    cout << "Nhap x: " << endl;
    cin >> x;
    cout << "Nhap tham so hoc (learning rate) : " << endl;
    cin >> theta;
    cout << "Nhap he so dong luong : " << endl;
    cin >> alpha;
    cout << "Nhap so buoc lap : " << endl;
    cin >> n;
    cout << "Nhap sai so : " << endl;
    cin >> e;
    gradient_momentum(x, theta, alpha, n, e);
}