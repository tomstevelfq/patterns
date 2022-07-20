#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Trouble{
    public:
        Trouble(int num):num(num){}
        int getNum()const{
            return num;
        }
        string toString() const{
            return "[Trouble"+to_string(num)+"]";
        }
    private:
        int num;
};
class Support{
    public:
        Support(const string& str):name(str){}
        Support& setNext(Support* next){
            this->next=next;
            return *next;
        };
        void support(const Trouble& t){
            if(resolve(t)){
                done(t);
            }else if(next!=NULL){
                next->support(t);
            }else{
                fail(t);
            }
        }
    protected:
        virtual bool resolve(const Trouble& t)=0;
        void done(const Trouble& t){
            cout<<"trouble "+t.toString()+" is resolved by support "+name<<endl;
        }
        void fail(const Trouble& t){
            cout<<"trouble "+t.toString()+" is not resolved at support "+name<<endl;
        }
        string name;
        Support* next=NULL;
};
class NoSupport:public Support{
    public:
        NoSupport(const string& str):Support(str){}
        bool resolve(const Trouble& t){
            return false;
        }
};
class LimitSupport:public Support{
    public:
        LimitSupport(const string& str,int lim):Support(str),limit(lim){}
        bool resolve(const Trouble& t){
            if(t.getNum()<limit){
                return true;
            }
            return false;
        }
    private:
        int limit;
};
class OddSupport:public Support{
    public:
        OddSupport(const string& str):Support(str){}
        bool resolve(const Trouble& t){
            if(t.getNum()%2==1){
                return true;
            }
            return false;
        }      
};
class SpecialSupport:public Support{
    public:
        SpecialSupport(const string& str,int n):Support(str),num(n){}
        bool resolve(const Trouble& t){
            if(t.getNum()==num){
                return true;
            }
            return false;
        }
    private:
        int num;
};

int main(){
    Support* s=new NoSupport("nosup");
    s->setNext(new LimitSupport("tom",100)).setNext(new SpecialSupport("Alice",234)).setNext(new LimitSupport("Bob",200)).setNext(new OddSupport("oddsup")).setNext(new LimitSupport("jack",300));
    for(int i=0;i<500;i+=23){
        Trouble t(i);
        s->support(t);
    }
    return 0;
}