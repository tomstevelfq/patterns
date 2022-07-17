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

int main(){
    Factory* fac=new IDCardFactory();
    Product* idc=fac->create("hello world");
    idc->use();
    return 0;
}