// compare virtual function and normal function
// virtual function: member func redefined in derived class, while preserving its calling properties through its reference
// pure virtual func: in abstract base class, without definition, add "=0" at the end
// normal member func: resolved statically at compile-time, virtual-func resolved dynamically at run-time
// virtual func refers to vtable (an array of pointers to virtual funcs)
#include<iostream>
using namespace std;
class Creature{
    public:
        virtual void printName() =0; // pure virtual func, declared, no impl, abstract class, cannot be instantiated.
};
class Animal{
    // int age;
    public:
        virtual void move() { printf("An animal moved.\n"); }   // virtual, implemented, can be overridden by child class
        void eat() { printf("An animal ate.\n"); }  // normal member func
};
class Dog: public Animal, Creature{
    public:
        void move() { printf("A dog moved.\n");}
        void printName() { printf("I am a dog.\n"); }
        void eat() { printf("A dog ate.\n"); }
};
class Cat: public Animal {
    public:
        // to see how many func can be derived
        void move() { printf("A cat moved\n"); }
};
int main() {
    Animal animal;
    Dog dog;
    Animal *pAnimal = &dog;
    pAnimal->move();    // virtual func, for polymorphism, deriving
    dog.printName();    // impl base class's pure virtual func
    dog.eat();          // call its own member func
    pAnimal->eat();     // non-virtual func, call base class's, print animal ate, not dog ate
    
    printf("\nCat example:\n");
    Cat cat;
    pAnimal = &cat;
    pAnimal->move();   
    pAnimal->eat();     // both func (virtual + normal) are derived, if move/eat() are not defined, call Base class's

    printf("\nBase class Animal:\n");
    pAnimal = &animal;
    pAnimal->move();
}
