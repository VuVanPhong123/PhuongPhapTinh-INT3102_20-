#include<bits/stdc++.h>
using namespace std;
double f(double x){
    return (x+3/x)/2;
}
int main(){
    double accuracy=0.00000000001;
    double tempPoint=1.0;
    double endPoint1=2.5;
    double endPoint2=3.0;
    double oldPoint=tempPoint;
    cout<<left<<setw(20)<<"iterations"<<setw(20)<<"p"<<endl;
    for (int i=0;i<100;i++){
        if (i>=1){
            if (abs(tempPoint-oldPoint)<accuracy)
                break;
            oldPoint=tempPoint;
        }
        cout<<left<<setw(20)<<i;
        cout<<left<<setw(20)<<setw(20)<<fixed<<setprecision(10)<<tempPoint<<endl;
        tempPoint=f(tempPoint);

    }
}

