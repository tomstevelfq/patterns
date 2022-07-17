#include<iostream>
#include<vector>
#include<thread>
using namespace std;

template<typename T>
void test(T& t);

class A{
    public:
        A(){}
        string getName(){
            return "hello world";
        }
};
void fun(){
    A a;
    test(a);
}
template<typename T>
void test(T& t){
    cout<<t.getName()<<endl;
}
int main(){
    fun();
    return 0;
}