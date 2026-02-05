// 练习1：继承与重载
// 定义一个 `Person` 类，并从 `Person` 类继承出一个 `Student` 类。`Student` 类中添加一个 `grade` 成员变量，重载 `show()` 方法，输出学生的姓名、年龄和成绩。

// 练习2：虚函数与多态
// 定义一个 `Shape` 类，派生出 `Circle` 和 `Rectangle` 类，并实现虚函数 `area()` 来计算它们的面积。

// 练习3：抽象类与纯虚函数
// 定义一个抽象类 `Animal`，包含纯虚函数 `speak()`，然后继承出 `Dog` 和 `Cat` 类，实现各自的 `speak()` 方法。

#include <iostream>
#include <string>

using namespace std;

class Person {
   public:
    string name;
    int age;
    Person(string n, int a) : name(n), age(a) {}
    virtual void show() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
class Student : public Person {
   public:
    int grade;
    Student(string n, int a, int g) : Person(n, a), grade(g) {}
    void show() override {
        Person::show();
        cout << "Grade: " << grade << endl;
    }
};

class Shape {
   public:
    virtual double area() = 0;
};
class Circle : public Shape {
   public:
    double radius;
    Circle(double r) : radius(r) {}
    double area() override { return 3.14159 * radius * radius; }
};
class Rectangle : public Shape {
   public:
    double width, height;
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() override { return width * height; }
};

class Animal {
    public:
     virtual void speak() = 0;
 };
class Dog : public Animal {
   public:
    void speak() override { cout << "Woof!" << endl; }
};
class Cat : public Animal {
   public:
    void speak() override { cout << "Meow!" << endl; }
};

int main() {
    
    cout << "===Person/Student===" << endl;
    Person p("Alice", 25);
    Student s("Bob", 20, 3);
    p.show();
    cout << endl;
    s.show();
    cout << endl;
    Person* ptr = &s;
    ptr->show();
    cout << endl;

    cout << "===Shape===" << endl;
    Circle circle(5.0);
    Rectangle rect(4.0, 6.0);
    cout << "Circle area: " << circle.area() << endl;
    cout << "Rectangle area: " << rect.area() << endl;
    cout << endl;

    cout << "===Animal===" << endl;
    Dog dog;
    Cat cat;
    dog.speak();
    cat.speak();

    return 0;
}