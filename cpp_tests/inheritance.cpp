#include <iostream>

struct B1
{
    B1() {std::cout << "B1" << std::endl;}
    ~B1() {std::cout << "~B1" << std::endl;}
    virtual void fun() {std::cout << "f B1" << std::endl;}
};

struct B2
{
    B2() {std::cout << "B2" << std::endl;}
    ~B2() {std::cout << "~B2" << std::endl;}
    virtual void fun() {std::cout << "f B2" << std::endl;}
};

struct C: B1, B2
{
    virtual void fun() {std::cout << "C" << std::endl;}
};

int main()
{
    C c;
    c.fun();
    return 0;
}
