#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class Visitor;
class ListVisitor;
class Element;
class Entry;
class File;
class Directory;
class FileFindVisitor;

class Element{
    public:
        virtual void accept(Visitor*)=0;
};
class Entry:public Element{
    public:
        virtual string getName()=0;
        virtual int getSize()=0;
        virtual Entry& add(Entry* e){return *this;}
};
class Visitor{
    public:
        virtual void visit(File* f)=0;
        virtual void visit(Directory* d)=0;
};
class File:public Entry{
    public:
        File(const string& str,int size):name(str),size(size){}
        void accept(Visitor* v){
            v->visit(this);
        }
        string getName(){
            return name;
        }
        int getSize(){
            return size;
        }
    private:
        string name;
        int size;
};
class Directory:public Entry{
    public:
        Directory(const string& str):name(str){}
        void accept(Visitor* v){
            v->visit(this);
        }
        string getName(){
            return name;
        }
        int getSize(){
            int size=0;
            for(auto it:dir){
                size+=it->getSize();
            }
            return size;
        }
        Entry& add(Entry* v){
            dir.push_back(v);
            return *this;
        }
        vector<Entry*>* getdir(){
            return &dir;
        }
    private:
        string name;
        vector<Entry*> dir;
};
class ListVisitor:public Visitor{
    public:
        ListVisitor()=default;
        ListVisitor(const string& str):currentdir(str){}
        void visit(File* f){
            cout<<currentdir+"/"+f->getName()<<endl;
        }
        void visit(Directory* d){
            auto& dir=*(d->getdir());
            string save=currentdir;
            currentdir=currentdir+"/"+d->getName();
            cout<<currentdir<<endl;
            for(auto it:dir){
                it->accept(this);
            }
            currentdir=save;
        }
    private:
        string currentdir;
};
class FileFindVisitor:public Visitor{
    public:
        FileFindVisitor(const string& str):suffix(str){}
        void visit(File* f){
            string fname=f->getName();
            if(fname.substr(fname.size()-suffix.size())==suffix){
                if(find(files.begin(),files.end(),f)==files.end())
                    files.push_back(f);
            }
        }
        void visit(Directory* d){
            auto& dir=*(d->getdir());
            for(auto it:dir){
                it->accept(this);
            }
        }
        void showFiles(){
            cout<<suffix<<endl;
            for(auto it:files){
                cout<<it->getName()+" "+to_string(it->getSize())<<endl;
            }
        }

    private:
        vector<Entry*> files;
        string suffix;
};

int main(){
    File* f1=new File("baidu.html",34);
    File* f2=new File("tomato.css",123);
    File* f3=new File("CCS.css",567);
    File* f4=new File("jimmy.cpp",34);
    File* f5=new File("gus.html",45);
    File* f6=new File("pinkman.html",234);
    Directory* d1=new Directory("people");
    Directory* d2=new Directory("season");
    Directory* d3=new Directory("country");
    d1->add(f1).add(f3);
    d2->add(f1).add(f2).add(f4).add(d1);
    d3->add(f4).add(f5).add(f6);
    Directory* d5=new Directory("whole");
    d5->add(f4).add(d1).add(d2).add(d3);
    ListVisitor* lv=new ListVisitor();
    //d5->accept(lv);
    FileFindVisitor* ffv=new FileFindVisitor(".html");
    d5->accept(ffv);
    ffv->showFiles();
    return 0;
}