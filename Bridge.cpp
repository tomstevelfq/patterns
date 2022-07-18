#include<iostream>
#include<ctime>
using namespace std;

class Display;
class CountDisplay;
class DisplayImpl;
class StringDisplayImpl;

class DisplayImpl{
    public:
        virtual void rawOpen()=0;
        virtual void rawPrint()=0; 
        virtual void rawClose()=0; 
};
class StringDisplayImpl:public DisplayImpl{
    public:
        StringDisplayImpl(const string& str):str(str),width(str.size()){}
        void rawOpen(){
            string s(width,'+');
            cout<<"*"+s+"*"<<endl;
        }
        void rawPrint(){
            cout<<"+"+str+"+"<<endl;
        }
        void rawClose(){
            rawOpen();
        }
    private:
        string str;
        int width;
};
class Display{
    public:
        Display(DisplayImpl* impl):impl(impl){}
        void open(){
            impl->rawOpen();
        };
        void print(){
            impl->rawPrint();
        };
        void close(){
            impl->rawClose();
        };
        virtual void display()final{
            open();
            print();
            close();
        };
    private:
        DisplayImpl* impl;
};
class CountDisplay:public Display{
    public:
        CountDisplay(DisplayImpl* impl):Display(impl){}
        void multiDisplay(int times){
            open();
            for(int i=0;i<times;i++){
                print();
            }
            close();
        }
};
class RandomDisplay:public Display{
    public:
        RandomDisplay(DisplayImpl* impl):Display(impl){}
        void randomDisplay(){
            srand(time(0));
            int times=rand()%10;
            open();
            for(int i=0;i<times;i++){
                print();
            }
            close();
        }
};

int main(){
    Display* dis=new Display(new StringDisplayImpl("hello world"));
    dis->display();
    cout<<endl<<endl;
    CountDisplay* cdis=new CountDisplay(new StringDisplayImpl("hello world"));
    cdis->multiDisplay(6);
    CountDisplay* cdis2=new CountDisplay(new StringDisplayImpl("summer fruits"));
    cdis2->multiDisplay(6);
    cout<<endl<<endl;
    RandomDisplay* rdis=new RandomDisplay(new StringDisplayImpl("RandomDisplay"));
    rdis->randomDisplay();
    return 0;
}