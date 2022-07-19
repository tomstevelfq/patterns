#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<sstream>
using namespace std;

class Hand;
class Strategy;
class WinningStrategy;
class ProbStrategy;
class Player;
class Random;

class Hand{
    public:
        Hand(int val):handvalue(val){}  
        static Hand* getHand(int num){
            return v[num];
        }
        bool isStrongerThan(Hand* h){
            return (handvalue+1)%3==h->handvalue;
        }
        bool isWeakerThan(Hand* h){
            return (h->handvalue+1)%3==handvalue;
        }
        int fight(Hand* h){
            if(handvalue==h->handvalue){
                return 0;
            }
            return isStrongerThan(h)?1:-1;
        }
        string getName(){
            return name[handvalue];
        }
    private:
        const int STONE=0;
        const int SCISSOR=1;
        const int CLOTH=2;
        static vector<Hand*> v;   
        int handvalue;
        static vector<string> name;
};
vector<Hand*> Hand::v={};
vector<string> Hand::name={"stone","scissor","cloth"};

class Strategy{
    public:
        virtual Hand* nextHand()=0;
        virtual void study(bool val)=0;
        virtual void toString(){}
};
class Random{
    public:
        Random(){
            srand(time(0));
        }
        int getNum(){
            return rand();
        }
};
class WinningStrategy:public Strategy{
    public:
        Hand* nextHand(){
            if(won){
                return new Hand(preHand);
            }else{
                int r=ran.getNum()%3;
                preHand=r;
                return new Hand(preHand);
            }
        }
        void study(bool val){
            won=val;
        }
    private:
        int preHand=0;
        bool won=false;
        Random ran;
};
class ProbStrategy:public Strategy{
    public:
        Hand* nextHand(){
            int val1=history[curHandValue][0];
            int val2=history[curHandValue][0]+history[curHandValue][1];
            int val3=history[curHandValue][0]+history[curHandValue][1]+history[curHandValue][2];
            int r=ran.getNum()%val3;
            preHandValue=curHandValue;
            if(r<val1){
                curHandValue=0;
                return new Hand(0);
            }else if(r<val2){
                curHandValue=1;
                return new Hand(1);
            }else{
                curHandValue=2;
                return new Hand(2);
            }
        }
        void study(bool val){
            if(val){
                history[preHandValue][curHandValue]++;
            }
        }
        void toString(){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++)
                    cout<<history[i][j]<<"  ";
                cout<<endl;
            }
            cout<<endl;
        }
    private:
        int preHandValue=0;
        int curHandValue=0;
        int history[3][3]={
            {1,1,1},
            {1,1,1},
            {1,1,1}
        };
        Random ran;
};
class Player{
    public:
        Player(const string& str,Strategy* sta):name(str),sta(sta){}
        Hand* nextHand(){
            return sta->nextHand();
        }
        void win(){
            winCount++;
            gameCount++;
            sta->study(true);
        }
        void lose(){
            loseCount++;
            gameCount++;
            sta->study(false);
        }
        void even(){
            gameCount++;
            evenCount++;
        }
        string getResult(){
            stringstream ss;
            ss<<name<<" : winCount: "<<winCount<<" loseCount: "<<loseCount<<" evenCount: "<<evenCount<<" gameCount: "<<gameCount<<endl;
            return ss.str();
        }
        void toString(){
            sta->toString();
        }
    private:
        int winCount=0;
        int loseCount=0;
        int evenCount=0;
        int gameCount=0;
        string name;
        Strategy* sta;
};
int main(){
    Strategy* sta1=new WinningStrategy();
    Strategy* sta2=new WinningStrategy();
    Player* play1=new Player("tom",sta1);
    Player* play2=new Player("jack",sta2);
    int nums=10000;
    for(int i=0;i<nums;i++){
        Hand* h1=play1->nextHand();
        Hand* h2=play2->nextHand();
        int res=h1->fight(h2);
        if(res==1){
            play1->win();
            play2->lose();
        }else if(res==-1){
            play1->lose();
            play2->win();
        }else{
            play1->even();
            play2->even();
        }
    }
    cout<<play1->getResult()<<endl;
    cout<<play2->getResult()<<endl;

    Strategy* s1=new ProbStrategy();
    Strategy* s2=new ProbStrategy();
    Player* p1=new Player("mike",s1);
    Player* p2=new Player("jeeny",s2);
    for(int i=0;i<10000;i++){
        Hand* h1=p1->nextHand();
        Hand* h2=p2->nextHand();
        int ret=h1->fight(h2);
        if(ret==1){
            p1->win();
            p2->lose();
        }else if(ret==-1){
            p2->win();
            p1->lose();
        }else{
            p1->even();
            p2->even();
        }
    }
    cout<<p1->getResult()<<endl;
    cout<<p2->getResult()<<endl;
    p1->toString();
    cout<<endl;
    p2->toString();
    return 0;
}