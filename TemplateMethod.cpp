#include<iostream>
#include<string>
using namespace std;

class AbstractDisplay;
class CharDisplay;
class StringDisplay;

class AbstractDisplay{
    public:
        virtual void open()=0;
        virtual void print()=0;
        virtual void close()=0;
        void display(){
            open();
            for(int i=0;i<5;i++){
                print();
            }
            close();
        }
};
class CharDisplay:public AbstractDisplay{
    public:
        CharDisplay(char c):c(c){}
        void open(){
            cout<<"<<";
        }
        void print(){
            cout<<c;
        }
        void close(){
            cout<<">>"<<endl;
        }
    private:
        char c;
};
class StringDisplay:public AbstractDisplay{
    public:
        StringDisplay(const string& str):str(str),len(str.size()){}
        void open(){
            cout<<"+";
            for(int i=0;i<len;i++){
                cout<<"-";
            }
            cout<<"+"<<endl;
        }
        void print(){
            cout<<"|"+str+"|"<<endl;
        }
        void close(){
            open();
        }
    private:
        int len;
        string str;
};

int main(){
    AbstractDisplay* cdis=new CharDisplay('e');
    cdis->display();
    AbstractDisplay* strdis=new StringDisplay("hello world");
    strdis->display();
    strdis=new StringDisplay("nihao,shijie");
    strdis->display();
    return 0;
}