#include<iostream>
#include<string>
using namespace std;

class Print;
class Banner;
class PrintBanner;

class Print{
    public:
        virtual void printWeak()=0;
        virtual void printStrong()=0;
};
class Banner{
    public:
        Banner()=default;
        Banner(const string& str):str(str){}
        void showWithParen(){
            cout<<"("+str+")"<<endl;
        };
        void showWithAster(){
            cout<<"*"+str+"*"<<endl;
        };
    private:
        string str;
};
class PrintBanner:public Print,public Banner{
    public:
        PrintBanner()=default;
        PrintBanner(const string& str):Banner(str){}
        void printWeak(){
            showWithParen();
        }
        void printStrong(){
            showWithAster();
        }
};

void testFun(Print* p){
    p->printWeak();
    p->printStrong();
}

int main(){
    Print* p=new PrintBanner("hello world");
    testFun(p);
    return 0;
}