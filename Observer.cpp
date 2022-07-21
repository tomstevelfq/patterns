#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include<ctime>
#include<algorithm>
using namespace std;

class NumberGenerator;
class RandomNumberGenerator;
class DigitObserver;
class GraphicObserver;
class Observer{
    public:
        virtual void update(NumberGenerator*)=0;
};
class NumberGenerator{
    public:
        NumberGenerator& addObserver(Observer* o){
            v.push_back(o);
            return *this;
        }
        void deleteObserver(Observer* o){
            auto it=find(v.begin(),v.end(),o);
            if(it!=v.end()){
                v.erase(it);
            }
        }
        void notifyObservers(){
            for(auto it:v){
                it->update(this);
            }
        }
        virtual int getNumber()=0;
        virtual void execute()=0;
    private:
        vector<Observer*> v;
};
class RandomNumberGenerator:public NumberGenerator{
    public:
        RandomNumberGenerator(){
            srand(time(0));
            number=rand()%30;
        }
        int getNumber(){
            return number;
        }
        void execute(){
            for(int i=0;i<20;i++){
                number=rand()%30;
                notifyObservers();
            }
        }
    private:
        int number;
};
class DigitObserver:public Observer{
    public:
        void update(NumberGenerator* g){
            cout<<"DigitObserver: "<<g->getNumber()<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};
class GraphicObserver:public Observer{
    public:
        void update(NumberGenerator* g){
            cout<<"GraphicObserver: ";
            for(int i=0;i<g->getNumber();i++){
                cout<<"*";
            }
            cout<<endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
};

int main(){
    NumberGenerator* g=new RandomNumberGenerator();
    Observer* o1=new DigitObserver();
    Observer* o2=new GraphicObserver();
    g->addObserver(o1).addObserver(o2);
    g->execute();
    return 0;
}