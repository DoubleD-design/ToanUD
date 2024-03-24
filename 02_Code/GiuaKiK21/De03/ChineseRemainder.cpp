#include <iostream>
#include <math.h>
using namespace std;

long long Mod_Inverse(int x, int m){
    int k = 0;
    while(true){
        if((k*m + 1 ) % x == 0) {
            return (k * m + 1 ) / x;
        }
        k++;
    }
}

void Chinese(int n) {
    pair<int, int> pairs[n+1];
    long long M = 1, Mx[n+1];
    for(int i = 1; i < n+1; i++){
        cout << "a" << i << " = ";
        cin >> pairs[i].first;
        cout << "m" << i << " = ";
        cin >> pairs[i].second;
        M *= pairs[i].second;
    }

    for(int i = 1; i <= n; i++){
        Mx[i] = M / pairs[i].second;
    }

    long long result = 0;
    for(int i = 1; i <= n; i++){
        result += pairs[i].first * Mx[i] *Mod_Inverse(Mx[i], pairs[i].second);
    }
    cout << "x = k * " << M << " + " << result % M;
}

int main(){
    int n;
    cout << "Nhap so phuong trinh: ";
    cin >> n;
    Chinese(n);
}