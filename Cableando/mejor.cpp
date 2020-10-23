#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, a, o, p;
    cin>>n>>a;
    p = o = a;
    for(int i = 0; i < n; i++){
        cin>>a;
        o = min(o, a);
        p = max(p, a);
    }
    cout<<(p - o)<<"\n";
    return 0;
}