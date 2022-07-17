#include<iostream>
#include<string>
using namespace std;

class Print;
class PrintBanner;
class Banner;

class Print{
    public:
        virtual void printWeak()=0;
        virtual void printStrong()=0;
};
class Banner{
    public:
        Banner(const string& str):str(str){}
        void showWithParen(){
            cout<<"("+str+")"<<endl;
        }
        void showWithAster(){
            cout<<"*"+str+"*"<<endl;
        }
    private:
        string str;
};
class PrintBanner:public Print{
    public:
        PrintBanner()=default;
        PrintBanner(const string& str):banner(str){}
        void printWeak(){
            banner.showWithParen();
        }
        void printStrong(){
            banner.showWithAster();
        }
    private:
        Banner banner;
};

void testFun(Print* p){
    p->printStrong();
    p->printWeak();
}

int main(){
    Print* p=new PrintBanner("hello world");
    testFun(p);
    return 0;
}