#include <iostream>
#include <math.h>
using namespace std;
int isperfect(int n){
    int temp=0;
    for (int i=1; i<=n/2; i++){
        if (n%i==0) temp+=i;
    }
    return (temp==n)?1:0;
}
void bai1a(int n, int&m){
    int count = 0;
    int sum = 0;
    int res[1000];
    for (int i = 1;i <=n;i++){
        if (isperfect(i)) {
            sum+=i;
            res[count++] = i;
        }
    }
    cout << "So luong so hoan hao nho hon N la: " << count << endl;
    cout << "Cac so do la: " ;
    for (int i=0;i<count;i++) cout << res[i] << " ";
    cout <<endl <<  "Tong cua chung la: " << sum << endl;
    m = res[count-1];
}

int bai1b(int m){
    int before = m - 1;
    int after = m + 1;
    while(before%5!=0) before--;
    while (after%5!=0) after--;
    int res;
    int count1 = abs(before - m);
    int count2 = abs(after - m);
    if (count1 > count2)
    {
        res = after;
    }else{
        res = before;
    }
    return res;  
}
int main(){
    int n = 8501;
    int m;
    bai1a(n,m);
    cout << "So K gan M nhat ma chia het cho 5 la: " << bai1b(m) << endl;
}

