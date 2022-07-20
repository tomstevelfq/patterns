#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Display;
class StringDisplay;
class Border;
class SideBorder;
class FullBorder;

class Display{
    public:
        virtual int getColumns()=0;
        virtual int getRows()=0;
        virtual string getRowText(int row)=0;
        void show(){
            for(int i=0;i<getRows();i++){
                cout<<getRowText(i)<<endl;
            }
        }
};
class StringDisplay:public Display{
    public:
        StringDisplay(const string& str):str(str){}
        int getColumns(){
            return str.size();
        }
        int getRows(){
            return 1;
        }
        string getRowText(int row){
            return str;
        }
    private:
        string str;
};
class Border:public Display{
    public:
        Border(Display* d):d(d){}
    protected:
        Display* d;
};
class SideBorder:public Border{
    public:
        SideBorder(Display* d):Border(d){}
        SideBorder(Display* d,string borderChar):Border(d),borderChar(borderChar){}
        int getColumns(){
            return d->getColumns()+4;
        }
        int getRows(){
            return d->getRows();
        }
        string getRowText(int row){
            return borderChar+" "+d->getRowText(row)+" "+borderChar;
        }
    private:
        string borderChar="|";
};
class FullBorder:public Border{
    public:
       FullBorder(Display* d):Border(d){}
       int getColumns(){
        return d->getColumns()+4;
       } 
       int getRows(){
        return d->getRows()+2;
       }
       string getRowText(int row){
        if(row==0||row==d->getRows()+1){
            return "*"+string(d->getColumns()+2,'+')+"*";
        }else{
            return "+ "+d->getRowText(row-1)+" +";
        }
       }
};

int main(){
    StringDisplay* sd=new StringDisplay("hello world");
    Display *d=new FullBorder(
        new SideBorder(
            new SideBorder(
                new FullBorder(
                    sd
                ),"&"
            )
        )
    );
    d->show();
    return 0;
}