#include <iostream>
using namespace std;
int isprime(int n){
    int flag = 1;
    if (n <2) return flag = 0; 
    int i = 2;
    while(i <n){
        if( n%i==0 ) {
            flag = 0;
            break; 
        }
        i++;
    }
    return flag;
}
int isperfect(int n){
    int temp=0;
    for (int i=1; i<=n/2; i++){
        if (n%i==0) temp+=i;
    }
    return (temp==n)?1:0;
}
int bai1a(int n){
    for (int i = n/2;i>=2;i--){
        if ((n%i==0) && (isprime(i))) return i;
    }
    return 0;
}
void bai1b(int m){
    int count = 0;
    int sum = 0;
    int res[1000];
    for (int i = 1;i <=m;i++){
        if (isperfect(i)) {
            sum+=i;
            res[count++] = i;
        }
    }
    cout << "So luong so hoan hao nho hon M la: " << count << endl;
    cout << "Cac so do la: " ;
    for (int i=0;i<count;i++) cout << res[i] << " ";
    cout <<endl <<  "Tong cua chung la: " << sum << endl;
}
int main(){
    int n = 9550;
    cout << "Uoc so nguyen to lon nhat cua N la: ";
    cout << bai1a(n) << endl;
    bai1b(bai1a(n));
    return 0;
}
