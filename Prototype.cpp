#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

class Product;
class UnderlinePen;
class MessageBox;

class Product{
    public:
        virtual Product* clone()=0;
        virtual void use(const string& str)=0;
};
class Manager{
    public:
        bool registerInstance(const string& str,Product* p){
            if(instanceTable.find(str)==instanceTable.end()){
                instanceTable.insert(make_pair(str,p));
                return true;
            }
            return false;
        }
        Product* create(const string& str){
            auto it=instanceTable.find(str);
            if(it!=instanceTable.end()){
                return it->second->clone();
            }
            return NULL;
        };
    private:
        unordered_map<string,Product*> instanceTable; 
};
class UnderlinePen:public Product{
    public:
        UnderlinePen(char c):ulchar(c){}
        Product* clone(){
            return new UnderlinePen(ulchar);
        }
        void use(const string& str){
            cout<<"\" "+str+" \""<<endl;
            for(int i=0;i<str.size()+4;i++){
                cout<<ulchar;
            }
            cout<<endl;
        }
    private:
        char ulchar;
};
class MessageBox:public Product{
    public:
        MessageBox(char c):decochar(c){}
        Product* clone(){
            return new MessageBox(decochar);
        }
        void use(const string& str){
            int len=str.size()+4;
            for(int i=0;i<len;i++){
                cout<<decochar;
            }
            cout<<endl;
            cout<<string(1,decochar)+" "+str+" "+string(1,decochar)<<endl;
            for(int i=0;i<len;i++){
                cout<<decochar;
            }
            cout<<endl;
        }
    private:
        char decochar;
};

int main(){
    Manager m;
    Product* upen=new UnderlinePen('_');
    Product* mbox=new MessageBox('*');
    m.registerInstance("UnderlinePen",upen);
    m.registerInstance("MessageBox",mbox);

    Product* pen=m.create("UnderlinePen");
    Product* box=m.create("MessageBox");
    pen->use("helloworld");
    box->use("Minecraft");

    Product* upen1=new UnderlinePen('~');
    m.registerInstance("UnderlinePen2",upen1);
    Product* pen1=m.create("UnderlinePen2");
    pen1->use("Minecraft");
    pen1->use("HelloWorld");
    Product* box2=new MessageBox('~');
    m.registerInstance("MessageBox2",box2);
    Product* b2=m.create("MessageBox2");
    b2->use("HelloWorld");
    return 0;
}