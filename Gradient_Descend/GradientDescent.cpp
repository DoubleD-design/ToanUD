#include <iostream>
#include <math.h>
using namespace std; 
const double gamma = 0.001;
const double alpha = 0.1;
const double e = 0.00001;
double deriv(float x, char f){
    if (f == 'f')
    return 2 * pow(e,(pow(x,5) - pow(x,3))) - 5 * pow(x,3) - x + log(x + 45) + 20;
    else
    return 2*((2*x)/(x*x+15)+1)*(log(x*x+15)+x-15)+1;
}
double deriv2(float x, char f){
    if (f == 'f')
    return 10 * pow(e,(pow(x,5) - pow(x,3))) * (pow(x,4) - pow(x,2)) - 15 * pow(x,2) - 1 + 1 / (x + 45);
    else 
        return 2*(2/(x*x+15)-(4*x*x)/((x*x+15)*(x*x+15)))*(log(x*x+15)+x-15)+2*pow((2*x)/(x*x+15)+1,2);
    }
double newton(double x, int n, char f){
    for (int i=0;i<n;i++){
        x = x - deriv(x,f)/deriv2(x,f);
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
double grad(double x, int n, char f){
    double x_new, x0;
    for (int i=0;i<n;i++)
    {
        x_new = x - gamma*deriv(x,f);
        if (abs(x-x_new)<0.00001) break;
        x = x_new;
    }
    return x;
}
int main(){
    int n = 10000;
    double x;
    char f;
    cin >> x;
    cin >> f;
    cout << grad_momentum(x,n,e,f) << " " << newton(x,n,f);
    return 0;
}