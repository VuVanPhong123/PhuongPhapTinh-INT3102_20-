
#include<bits/stdc++.h>
using namespace std;

long double f(long double x){
    return 10*(0.5*M_PI-asin(x)-x*sqrt(1-pow(x,2)))-12.4;   //phương trình
}
long double midPoint(long double a,long double b){
    return (a+b)/2;
}
int main(){
    long double accuracy=0.00000000001;  //độ chính xác
    long double endPoint1=0.0;  // 2 đầu mút.
    long double endPoint2=1.0;
    long double NumOfIteration=0.0;
    while ((endPoint2-endPoint1)/pow(2,NumOfIteration)>accuracy){
        NumOfIteration++;
    }
    long double oldMid = midPoint(endPoint1,endPoint2);
    cout<<left<<setw(20)<<"iterations"<<setw(20)<<"a"<<setw(20)<<"b"<<setw(20)<<"midPoint"<<setw(20)<<"f(midPoint)"<<endl;
    for (int i=1;i<=NumOfIteration;i++){
        if (i>=2){
            if (abs(midPoint(endPoint1,endPoint2)-oldMid)<accuracy)
                break;
            oldMid=midPoint(endPoint1,endPoint2);
        }
        cout<<setw(20)<<i;
        cout<<setw(20)<<fixed<<setprecision(15)<<endPoint1;
        cout<<setw(20)<<fixed<<setprecision(15)<<endPoint2;
        cout<<setw(20)<<fixed<<setprecision(15)<<1-midPoint(endPoint1,endPoint2);
        cout<<setw(20)<<fixed<<setprecision(15)<<f(midPoint(endPoint1,endPoint2))<<endl;
        if (f(endPoint1)*f(midPoint(endPoint1,endPoint2))<0)
            endPoint2=midPoint(endPoint1,endPoint2);
        else if (f(endPoint1)*f(midPoint(endPoint1,endPoint2))>0)
            endPoint1=midPoint(endPoint1,endPoint2);
    }
}
