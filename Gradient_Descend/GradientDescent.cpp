#include <iostream>
#include <cmath>
using namespace std; 

const double gamma = 0.001;
const double alpha = 0.1;
const double e = 0.00001;

double f1(double x) {
    return 2*exp(pow(x,5)-pow(x,3)) - 5*pow(x,3) - x + log(x+45) + 20;
}

double f2(double x) {
    return 3*exp(pow(x,5)-pow(x,4)) + pow(x,2) - 20*x + log(x+25) - 10;
}

double deriv(double x, double (*f)(double)){
    double h = 0.00001;
    return (f(x+h) - f(x-h)) / (2*h);
}

double grad(double x, int n, double (*f)(double)){
    double x_new;
    for (int i=0;i<n;i++)
    {
        x_new = x - gamma*deriv(x,f);
        if (abs(x-x_new)<e) break;
        x = x_new;
    }
    return x;
}

double grad_momentum(double x, int n, double e, char f){
    double x_new, x0=0;
    for (int i=0;i<n;i++){
        double delta = x - x0;
        x_new = x - gamma*deriv(x,f) + alpha*delta;
        if (abs(deriv(x,f))<e) break;
        x0 = x;
        x = x_new;
    }
    return x;
}

double newton(double x, int n, char f){
    for (int i=0;i<n;i++){
        x = x - deriv(x,f)/deriv(x,f);
    }
    return x;
}

int main(){
    int n = 10000;
    double x = 0;
    char f;
    cin >> x;
    cin >> f;
    cout << grad_momentum(x,n,e,f) << " " << newton(x,n,f);
    return 0;
}