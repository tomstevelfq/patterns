#ifndef testin_h
#define testin_h
const int a=23;
static int b=12;

#include<iostream>
using namespace std;

class A{
    public:
        int a;
        static int c;
        A();
        void fun();
};
#endif