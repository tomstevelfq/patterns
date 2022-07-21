#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<sstream>
using namespace std;

class PageMaker;
class Database{
    friend class PageMaker;
    private:
        Database()=delete;
        static bool flag;
        static void readFile(){
            fstream fs("./test.txt");
            if(!fs.good()){
                cout<<"fail"<<endl;
                return;
            }
            string name;
            string addr;
            while(!fs.eof()){
                fs>>addr;
                fs>>name;
                prop.insert(make_pair(name,addr));
            }
        }
        static string getProperty(const string& name){
            if(!flag){
                readFile();
                flag=true;
            }
            auto it=prop.find(name);
            if(it==prop.end()){
                throw runtime_error("no user find");
            }
            return it->second;
        }
        static unordered_map<string,string> prop;
};
unordered_map<string,string> Database::prop;
bool Database::flag=false;

class HTMLWriter{
    friend class PageMaker;
    private:
        HTMLWriter(const string& fileName):wrt(fileName){}
        ~HTMLWriter(){
            if(wrt.good()){
                wrt.close();
            }
        }
        void title(const string& str){
            wrt<<"<html>"<<endl;
            wrt<<"<head><title>"+str+"</title></head>"<<endl;
            wrt<<"<body>"<<endl;
            wrt<<"<h1>"+str+"</h1>"<<endl;
        }
        void paragraph(const string& str){
            wrt<<"<p>"+str+"</p>"<<endl;
        }
        void link(const string& url,const string& caption){
            wrt<<"<a href=\""+url+"\">"+caption+"</a>"<<endl;
        }
        void mailto(const string& user,const string& addr){
            link("mailto:"+addr,user);
        }
        void close(){
            wrt<<"</body>"<<endl;
            wrt<<"</html>"<<endl;
            wrt.close();
        }
        ofstream wrt;
};
class PageMaker{
    public:
        PageMaker()=delete;
        static void makeWelcomePage(const string& user){
            const string& addr=Database::getProperty(user);
            HTMLWriter hw(user+".html");
            hw.title("Welcome to "+user+"'s Page");
            hw.paragraph("this is the web page of "+user);
            hw.paragraph("waitting for your email here");
            hw.mailto(user,addr);
            hw.close();
        }
};

int main(){
    string user;
    while(cin>>user){
        try{
            PageMaker::makeWelcomePage(user);
        }catch(runtime_error r){
            cout<<r.what()<<endl;
            cout<<"N|n is end and Y|y is continue"<<endl;
            char c;
            cin>>c;
            if(c!='Y'&&c!='y'){
                break;
            }else{
                continue;
            }
        }
        break;
    }
    return 0;
}