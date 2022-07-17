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
        Singleton(){
            cout<<"chushihua"<<endl;
        }
};
Singleton* Singleton::instance=new Singleton();

class TicketMaker{
    public:
        static TicketMaker* getMaker(){
            return maker;
        }
        int getNextTicketNumber(){
            return ticket++;
        }
    private:
        TicketMaker()=default;
        int ticket=1000;
        static TicketMaker* maker;
    
};
TicketMaker* TicketMaker::maker=new TicketMaker();

class Triple{
    public:
        static Triple* t1;
        static Triple* t2;
        static Triple* t3;
        void doSomething(){
            cout<<to_string(id)+" is doing something"<<endl;
        }
        static Triple* getInstance(){
            return t1;
        }
        static Triple* getInstance(int i){
            return i==2?t3:i==1?t2:i==0?t1:NULL;
        }
    private:
        int id;
        Triple(int id):id(id){}
};
Triple* Triple::t1=new Triple(0);
Triple* Triple::t2=new Triple(1);
Triple* Triple::t3=new Triple(2);

int main(){
    Singleton* p1=Singleton::getInstance();
    Singleton* p2=Singleton::getInstance();
    p1->doSomething();
    p2->doSomething();
    cout<<p1<<endl;
    cout<<p2<<endl;

    TicketMaker* maker=TicketMaker::getMaker();
    cout<<maker->getNextTicketNumber()<<endl;
    cout<<maker->getNextTicketNumber()<<endl;

    Triple* t1=Triple::getInstance(1);
    if(t1){
        t1->doSomething();
    }
    return 0;
}