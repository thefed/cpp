// OOP exampple: virtual function; copy constructor, deep/shallow copy, assignment operator
// 4/19/2017
#include<iostream>
using namespace std;

class Person {
    public: 
        /*
        virtual print_me(void) { cout << "Person's virtual func\n"; }
        virtual ~Person() { printf("Person's virtual destructor\n"); }
        */
    int id;
    int *pInt;  // contains pointer member, need to impl copy constructor and assignment operator
    Person() { id = 0; pInt = new int(id + 10); printf("Person's default cons\n"); }
    ~Person() { delete pInt; }
    Person(int _id, int *_pInt) { id = _id; pInt = new int(*_pInt); printf("Person's cons\n"); }
    Person(const Person &person) { id = person.id; pInt = new int(*person.pInt); printf("Person's copy cons\n"); }

    Person& operator=(const Person &person) { 
        id = person.id; *pInt = *person.pInt; 
        printf("Person's assign operator\n");
        return *this; 
    }
    void print() { printf("id = %d, age = %d\n", id, *pInt); }
};

// virtual func example
class Shape {
	protected: int width, height;
	public:
		Shape(int w=0, int h=0): width(w), height(h) {}
		// normal function: static resolution, the func call is fixed before the program is executed, incorrect!
 		// void area() { printf("Parent class area\n"); }	
		// vitual function: dynamic binding(linkage)
 		virtual void area() { printf("Parent class area\n"); }	
		// or pure virtual function, no impl
		// virtual void area() = 0;

};
class Rectangle: public Shape {
	public: 
		Rectangle(int w=0, int h=0):Shape(w, h) {}
		void area() { printf("Rectangle's area: %d\n", width * height); }
};
class Triangle: public Shape {
	public:
	   	Triangle(int w=0, int h=0): Shape(w, h) {}
		void area() { printf("Triangle's area: %d\n", width * height / 2); }
};

void print_by_ref(const Person &person) {
    printf("id = %d, age = %d\n", person.id, *person.pInt);
}
void print_by_val(Person person) {
    printf("id = %d, age = %d\n", person.id, *person.pInt);
}

void test_constructor() {
    int id = 11;
    int age = 22;
    int *pInt = &age;

    printf("p1:\n");
    Person p1(id, pInt);
    p1.print();
    
    printf("p2:\n");
    Person p2(p1);  // call copy constructor, the same as "Person p2 = p1;"

    printf("p3:\n");
    Person p3;
    p3 = p1;    // call assignment operator

    printf("p4:\n");
    Person p4;
    p4.print();

    printf("*****\n");
    print_by_ref(p4);
    printf("*****\n");
    print_by_val(p4);
    printf("*****\n");
}

int main() {
	// test_constructor();
	Shape *shape;
	Rectangle rect(10, 7);
	Triangle tri(10, 5);
	
	shape = &rect;
	shape->area();

	shape = &tri;
	shape->area();
    return 0;
}
