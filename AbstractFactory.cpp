#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Item;
class Link;
class Tray;
class Page;
class Factory;
class ListLink;
class ListTray;
class ListPage;
class ListFactory;
class YahooFactory;
class YahooPage;

class Factory{
    public:
        static Factory* getFactory(const string& name){
            auto it=facList.find(name);
            if(it!=facList.end()){
                return it->second;
            }else{
                return NULL;
            }
        };
        static void registerFactory(const string& str,Factory* f){
            facList.insert(make_pair<const string&,Factory*&>(str,f));
        }
        virtual Item* createLink(const string& cap,const string& url)=0;
        virtual Item* createTray(const string& cap)=0;
        virtual Page* createPage(const string& title,const string& author)=0;
        virtual Page* createYahooPage(){
            return NULL;
        }
    private:
        static unordered_map<string,Factory*> facList;
};
unordered_map<string,Factory*> Factory::facList;
class Item{
    public:
        Item(const string& str):caption(str){}
        virtual void makeHTML()=0;
    protected:
        string caption;
};
class Link:public Item{
    public:
        Link(const string& cap,const string& url):Item(cap),url(url){}
    protected:
        string url;
};
class Tray:public Item{
    public:
        Tray(const string& cap):Item(cap){}
        Tray& add(Item* item){
            tray.push_back(item);
            return *this;
        }
    protected:
        vector<Item*> tray;
};
class Page{
    public:
        Page(const string& title,const string& author):title(title),author(author){}
        Page& add(Item* item){
            content.push_back(item);
            return *this;
        }
        virtual void makeHTML()=0;
    protected:
        string title;
        string author;
        vector<Item*> content;
};
class ListLink:public Link{
    public:
        ListLink(const string& cap,const string& url):Link(cap,url){}
        void makeHTML(){
            cout<<"<li><a href=\""+url+"\">"+caption+"</a></li>"<<endl;
        }
};
class ListTray:public Tray{
    public:
        ListTray(const string& cap):Tray(cap){}
        void makeHTML()override{
            cout<<"<li>"<<endl<<caption<<endl<<"<ul>"<<endl;
            for(auto& it:tray){
                it->makeHTML();
            }
            cout<<"</ul>"<<endl<<"</li>"<<endl;
        }
};
class ListPage:public Page{
    public:
        ListPage(const string& title,const string& author):Page(title,author){}
        void makeHTML(){
            cout<<"<html>"<<endl<<"<head><title>"+title+"</title></head>"<<endl;
            cout<<"<body>"<<endl;
            cout<<"<h1>"+title+"</h1>"<<endl;
            cout<<"<ul>"<<endl;
            for(auto& it:content){
                it->makeHTML();
            }
            cout<<"</h1>"<<endl;
            cout<<"<hr><address>"+author+"</address>"<<endl;
            cout<<"</body>"<<endl;
            cout<<"</html>"<<endl;
        }
};
class ListFactory:public Factory{
    public:
        Item* createLink(const string& cap,const string& url)override{
            return new ListLink(cap,url);
        }
        Item* createTray(const string& cap)override{
            return new ListTray(cap);
        }
        Page* createPage(const string& title,const string& author)override{
            return new ListPage(title,author);
        }
};
class YahooPage:public ListPage{
    public:
        YahooPage():ListPage("Yahoo","Yahoo"){
            createYahooPage();
        }
        void createYahooPage(){
            ListFactory* fac=new ListFactory();
            Item* link=fac->createLink("Yahoo","www.Yahoo.com");
            Tray* tray=(Tray*)fac->createTray("Yahoo");
            tray->add(link);
            this->add(tray);
        }
};
class YahooFactory:public ListFactory{
    public:
        Page* createYahooPage(){
            return new YahooPage();
        }
};

int main(){
    Factory::registerFactory("ListFactory",new ListFactory());
    Factory* fac=Factory::getFactory("ListFactory");
    Item* link=fac->createLink("baidu","www.baidu.com");
    Page* page=fac->createPage("websites collection","tomcat");
    Item* link2=fac->createLink("wangyi","www.wangyi.com");
    Item* link3=fac->createLink("google","www.google.com");
    Item* link4=fac->createLink("youtube","www.youtube.com");
    Item* link5=fac->createLink("qq","www.qq.com");
    Tray* tray=(Tray*)fac->createTray("websites");
    Tray* tray2=(Tray*)fac->createTray("web2");
    Tray* tray3=(Tray*)fac->createTray("chinawebsite");
    tray->add(link).add(link2).add(link3).add(link4);
    tray2->add(link2).add(link);
    tray3->add(link).add(link2).add(link5);
    page->add(tray).add(link2).add(link3);
    page->makeHTML();
    cout<<endl<<endl<<endl;
    Factory::registerFactory("YahooFactory",new YahooFactory());
    Factory *yahoo=Factory::getFactory("YahooFactory");
    Page* yahooPage=yahoo->createYahooPage();
    yahooPage->makeHTML();
    return 0;
}