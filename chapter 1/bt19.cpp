#include<bits/stdc++.h>
using namespace std;
int main(){
    double ans=0.367879;
    double MacSeries1=1.0;
    double MacSeries2=1.0;
    double facto=1.0;
    double j=2.0;
    cout<<left<<setw(20)<<"terms"<<setw(20)<<"e^(-x)"<<setw(20)<<"1/e^x"<<setw(20)<<"ans"<<endl;
    for (int i=0;i<8;i++){
        MacSeries1=MacSeries1-1/facto;
        MacSeries2=MacSeries2+abs(1/facto);
        facto*=j;
        j++;
        facto=-facto;
        if (i>=3)
            cout<<fixed<<setprecision(6)<<left<<setw(20)<<i+2<<setw(20)<<MacSeries1<<setw(20)<<1/MacSeries2<<setw(20)<<ans<<endl;
    }

}
