#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Director;
class Builder;
class TextBuilder;
class HTMLBuilder;

class Builder{
    public:
        virtual void makeTitle(const string& title)=0;
        virtual void makeString(const string& str)=0;
        virtual void makeItems(const vector<string>& items)=0;
        virtual string getResult()=0;
        virtual void close()=0;
};
class Director{
    public:
        Director(Builder* builder):b(builder){}
        void construct(){
            b->makeTitle("Greeting");
            b->makeString("from morning to afternoon");
            b->makeItems({"GoodMorning","GoodAfternoon"});
            b->makeString("night");
            b->makeItems({"GoodEvening","CoodNight","Bye"});
            b->close();
        };
    private:
        Builder *b;
};
class TextBuilder:public Builder{
    public:
        string getResult(){
            return string();
        }
        void makeTitle(const string& title){
            string s(30,'=');
            cout<<s<<endl;
            cout<<"| "+title+" |"<<endl;
            cout<<endl;

        }
        void makeString(const string& str){
            cout<<"% "+str+" %"<<endl;
        }
        void makeItems(const vector<string>& items){
            for(auto it:items){
                cout<<"## "+it+" ##"<<endl;
            }
        }
        void close(){
            string str(30,'#');
            cout<<str<<endl;
        }
    private:
        string buffer;
};
class HTMLBuilder:public Builder{
    public:
        string getResult(){
            return string();
        }
        void makeTitle(const string& title){
            cout<<"<html>"<<endl<<"<head><title>"+title+"</title></head>"<<endl;
            cout<<"<body>"<<endl;
            cout<<"<h1>"+title+"</h1>"<<endl;
        }
        void makeString(const string& str){
            cout<<"<p>"+str+"</p>"<<endl;
        }
        void makeItems(const vector<string>& items){
            cout<<"<ul>"<<endl;
            for(auto& it:items){
                cout<<"<li>"+it+"</li>"<<endl;
            }
            cout<<"</ul>"<<endl;
        }
        void close(){
            cout<<"</body>"<<endl;
            cout<<"</html>"<<endl;
        }
    private:
        string writer;
};

int main(){
    Builder* text=new TextBuilder();
    Builder* html=new HTMLBuilder();
    Director* d1=new Director(text);
    Director* d2=new Director(html);
    d1->construct();
    cout<<endl;
    d2->construct();
    return 0;
}