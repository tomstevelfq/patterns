#include<iostream>
#include<string>
using namespace std;

class Singleton{
    public:
        static Singleton* instance;
        void doSomething(){
            cout<<"singleton dosomething"<<endl;
        }
        static Singleton* getInstance(){
            return instance;
        }
    private:
        Singleton(){}
};
Singleton* Singleton::instance=new Singleton();

int main(){
    Singleton* p1=Singleton::getInstance();
    Singleton* p2=Singleton::getInstance();
    p1->doSomething();
    p2->doSomething();
    cout<<p1<<endl;
    cout<<p2<<endl;
    return 0;
}