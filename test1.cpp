#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Container;
class Iterator;
class Book;
class BookList;
class BookIterator;
class TaskTable;
class Task;
class TaskIterator;
class Element;
class Element{
};
class Container{
    public:
        virtual Iterator* getIterator()=0;
};
class Iterator{
    public:
        virtual bool hasNext()=0;
        virtual Element& next()=0;
};
class Book:public Element{
    public:
        const string& getName(){
            return name;
        }
        void setName(const string& str){
            name=str;
        }
    private:
        string name;
};
class BookList:public Container{
    friend class BookIterator;
    public:
        Iterator* getIterator();
        BookList& appendBook(const Book& b){
            v.push_back(b);
            return *this;
        }
        Element& getBook(int i){
            return v[i];
        }
    private:
        vector<Book> v;
};

class BookIterator:public Iterator{
    public:
        BookIterator(){}
        BookIterator(BookList* bl):bl(bl),i(0){}
        bool hasNext(){
            return i<bl->v.size();
        }
        Element& next(){
            return bl->v[i++];
        }
    private:
        int i;
        BookList* bl;
};

Iterator* BookList::getIterator(){
    return new BookIterator(this);
}

class TaskTable:public Container{
    friend class TaskIterator;
    public:
        Iterator* getIterator();

    private:
        vector<Task> v;
};
class TaskIterator:public Iterator{
    public:
        TaskIterator(TaskTable* t):tb(t),i(0){}
        bool hasNext(){
            return i<tb->v.size();
        }
        Element& next(){
            return tb->v[i++];
        }
    private:
        TaskTable* tb;
        int i;
};
Iterator* TaskTable::getIterator(){
    return new TaskIterator(this);
}
class Task:public Element{
    public:
        Task()=default;
        Task(int i):tid(i){}
    private:
        int tid;    
};

int main(){
    Book a,b,c,d;
    a.setName("this is");
    b.setName("Rose");
    c.setName("luobo");
    d.setName("jiayou");
    BookList bl;
    bl.appendBook(a).appendBook(b).appendBook(c).appendBook(d);
    
    return 0;
}