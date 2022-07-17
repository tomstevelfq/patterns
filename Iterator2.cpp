#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Iterator;
class BookIterator;
class Obj;
class Book;
class Container;
class BookList;
class Task;
class TaskTable;
class TaskIterator;

class Iterator{
    public:
        virtual bool hasNext()=0;
        virtual Obj* next()=0;
};
class Container{
    public:
        virtual Iterator* getIterator()=0;
};
class Obj{
    public:
        virtual string getName()=0;
};
class Book:public Obj{
    public:
        string getName(){
            return name;
        }
        void setName(const string& str){
            name=str;
        }
    private:
        string name;
};
class Task:public Obj{
    public:
        string getName(){
            return to_string(id);
        }
        void setId(int a){
            id=a;
        }
    private:
        int id;
};
class BookIterator:public Iterator{
    public:
        BookIterator(BookList* bl):bl(bl),i(0){}
        bool hasNext();
        Book* next();
    private:
        int i;
        BookList *bl;
};
class BookList:public Container{
    friend class BookIterator;
    public:
        bool hasNext(int i){
            return i<v.size();
        }
        Book* getBook(int i){
            return &(v[i]);
        }
        BookIterator* getIterator(){
            return new BookIterator(this);
        };
        BookList& appendBook(const Book& b){
            v.push_back(b);
            return *this;
        }
    private:
        vector<Book> v;
};
bool BookIterator::hasNext(){
    return bl->hasNext(i);
}
Book* BookIterator::next(){
    return bl->getBook(i++);
}

class TaskTable:public Container{
    friend class TaskIterator;
    public:
        Iterator* getIterator();
        Task* getTask(int i){
            return &v[i];
        }
        TaskTable& appendTask(const Task& t){
            v.push_back(t);
            return *this;
        }
    private:
        vector<Task> v;
};
class TaskIterator:public Iterator{
    public:
        TaskIterator(TaskTable* tb):tb(tb),i(0){}
        bool hasNext(){
            return i<tb->v.size();
        }
        Task* next(){
            return tb->getTask(i++);
        }
    private:
        int i;
        TaskTable* tb;
};
Iterator* TaskTable::getIterator(){
    return new TaskIterator(this);
}

void visit(Container& con){
    Iterator* it=con.getIterator();
    while(it->hasNext()){
        cout<<it->next()->getName()<<endl;
    }
}
int main(){
    BookList bl;
    Book a,b,c,d;
    a.setName("hello");
    b.setName("world");
    c.setName("nihao");
    d.setName("shijie");
    bl.appendBook(a).appendBook(b).appendBook(c).appendBook(d);
    visit(bl);

    TaskTable tb;
    Task m,n,s,t;
    m.setId(12);
    n.setId(34);
    s.setId(45);
    t.setId(55);
    tb.appendTask(m).appendTask(n).appendTask(s).appendTask(t);
    visit(tb);
    return 0;
}