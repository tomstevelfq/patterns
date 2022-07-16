#include<iostream>
#include<vector>
#include<thread>
using namespace std;

int fun(){
    int a=34;
    return a;
}

int main(){
    cout<<fun()<<endl;
    return 0;
}