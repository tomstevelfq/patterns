#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Entry;
class File;
class Directory;
class Print;
class PrintStr;
class PrintLevel;
class PrintTree;

class Entry{
    public:
        virtual string getName()=0;
        virtual int getSize()=0;
        virtual Entry& add(Entry* e){return* this;}
        virtual void printList()=0;
        virtual void setPrint(Print* p)=0;
};
class Print{
    public:
        virtual void print(File* f,const string& str)=0;
        virtual void print(Directory* d,const string& str)=0;
};
class File:public Entry{
    public:
        File()=default;
        File(const string& str,int size):name(str),size(size){}
        string getName(){
            return name;
        }
        int getSize(){
            return size;
        }
        void setPrint(Print* p){
            prt=p;
        }
        void printList(){
            prt->print(this,"");
        }
    private:
        string name;
        int size;
        Print* prt;
};
class Directory:public Entry{
    public:
        friend class PrintStr;
        friend class PrintLevel;
        friend class PrintTree;
        Directory()=default;
        Directory(const string& str):name(str){}
        string getName(){
            return name;
        }
        int getSize(){
            int size=0;
            for(auto it:directory){
                size+=it->getSize();
            }
            return size;
        }
        Entry& add(Entry* e){
            directory.push_back(e);
            return *this;
        }
        void setPrint(Print* p){
            prt=p;
        }
        void printList(){
            prt->print(this,"");
        }
    private:
        string name;
        vector<Entry*> directory;
        Print* prt;
};
class PrintStr:public Print{
    public:
        void print(File* f,const string& str){
            cout<<str<<"/"<<f->getName()<<" "<<f->getSize()<<endl;
        }
        void print(Directory* d,const string& str){
            string s=str+"/"+d->getName();
            cout<<s<<" "<<d->getSize()<<endl;
            for(auto it:d->directory){
                if(typeid(*it)==typeid(File)){
                    print(dynamic_cast<File*>(it),s);
                }else if(typeid(*it)==typeid(Directory)){
                    print(dynamic_cast<Directory*>(it),s);
                }
            }
        }
};
class PrintLevel:public Print{
    public:
        void print(File* f,const string& str){
            cout<<str+f->getName()+" "+to_string(f->getSize())<<endl;
        }
        void print(Directory* d,const string& str){
            cout<<str+"/"+d->getName()+" "+to_string(d->getSize())<<endl;
            string s=str+"      ";
            for(auto it:d->directory){
                if(typeid(*it)==typeid(File)){
                    print(dynamic_cast<File*>(it),s);
                }else if(typeid(*it)==typeid(Directory)){
                    print(dynamic_cast<Directory*>(it),s);
                }
            }
        }
};
class PrintTree:public Print{
    public:
        void print(File* f,const string& str){
            cout<<"|____"+f->getName()+" "+to_string(f->getSize())<<endl;
        }
        void print(Directory* d,const string& str){
            cout<<"|____"+d->getName()<<endl;
            string s=string(str.size(),' ')+"|"+string(4+d->getName().size()/2,' ');
            for(auto it:d->directory){
                if(typeid(*it)==typeid(File)){
                    cout<<s;
                    print(dynamic_cast<File*>(it),s);
                }else if(typeid(*it)==typeid(Directory)){
                    cout<<s;
                    print(dynamic_cast<Directory*>(it),s);
                }
            }
        }
};

int main(){
    File* f1=new File("windows",232);
    File* f2=new File("linux",223);
    File* f3=new File("apple",556);
    File* f4=new File("banana",666);
    File* f5=new File("potato",778);
    File* f6=new File("air",34);
    Directory* d1=new Directory("usr");
    Directory* d2=new Directory("tomst");
    Directory* d3=new Directory("jack");
    d1->add(f1).add(f2);
    d2->add(f3).add(f4).add(f5);
    d3->add(f6);
    Directory* d4=new Directory("root");
    d4->setPrint(new PrintStr());
    File* f7=new File("end",7676575);
    d4->add(d1).add(d2).add(d3);
    d4->printList();
    cout<<endl<<endl;
    d4->setPrint(new PrintLevel());
    d4->printList();
    cout<<endl<<endl;
    d4->setPrint(new PrintTree());
    d4->printList();
    return 0;
}