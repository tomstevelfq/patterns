#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Factory;
class Product;
class IDCardFactory;
class IDCard;

class Factory{
    public:
        Product* create(const string& owner){
            Product* p=createProduct(owner);
            registerProduct(p);
            return p;
        }
        virtual Product* createProduct(const string& owner)=0;
        virtual void registerProduct(Product* p)=0;
};
class Product{
    public:
        virtual void use()=0;
};
class IDCard:public Product{
    public:
        IDCard(const string& str):owner(str){}
        void use(){
            cout<<owner<<" use the IDcard"<<endl;
        }
        string getName(){
            return owner;
        }
    private:
        string owner;
};
class IDCardFactory:public Factory{
    public:
        Product* createProduct(const string& str){
            return new IDCard(str);
        }
        void registerProduct(Product* p){
            owners.push_back(((IDCard*)p)->getName());
        }
    private:
        vector<string> owners;
};
class Television:public Product{
    public:
        static int i;
        Television(const string& str):channel(str),id(i++){}
        void use(){
            cout<<"the TV numbered "+to_string(i)+" is showing channel "+channel<<endl;
        }
    private:
        int id;
        string channel;
};
class TelevisionFactory:public Factory{
    public:
        Product* createProduct(const string& str){
            return new Television(str);
        }
        void registerProduct(Product* p){
            TVs.push_back(to_string(((Television*)p)->i));
        }
    private:
        vector<string> TVs;
};
int Television::i=0;

int main(){
    Factory* fac=new IDCardFactory();
    Product* idc=fac->create("hello world");
    idc->use();
    Factory* tvfac=new TelevisionFactory();
    Product* tv=tvfac->create("cctv");
    tv->use();
    return 0;
}