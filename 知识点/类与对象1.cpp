// 练习1：定义一个 Person 类
// 练习2：定义一个Book 类，将 salary 作为私有成员，提供 getSalary成员函数访问salary
// 练习3：定义一个 BankAccount类，包含账户余额（balance），提供存款（deposit）和取款（withdraw）成员函数。

#include <string>
#include <iostream>

using namespace std;

class Person {
   public:
    string name;
    int age;
    Person(string s, int age) : name(s), age(age) {}
    void show() { 
        cout << "Name: " << name << ", Age: " << age << endl; 
    }
};

class Book{
    private:
    double salary;
    public:
     string title;
     string author;
     double price;
    Book(string t,string a,double p,double s):title(t),author(a),price(p),salary(s){}
    double getSalary() { return salary; }
    void show(){
        cout << "Tille:" << title <<endl<< "Author:" << author <<endl<< "Price:" << price
             <<endl<< "Salary:" << salary << endl;
    }
};

class BankAccount{
    private:
     double salary;
     string name;
    public:
     BankAccount(string n,double s):name(n),salary(s){}
     void deposit(double amount) { salary += amount; }
     void withdraw(double amount){
        if(salary>=amount){
            salary -= amount;
        }else{
            salary = 0;
            cout << "Insufficient funds!" << endl;
        }
     }
     void show() { cout << "Name:" << name <<endl<< "Salary:" << salary << endl; }
};

int main() {
    cout << "=====Person=====" << endl;
    Person p1("Tom", 20);
    p1.show();
    cout << "=====Book=====" << endl;
    Book b1("C++ Primer", "Stanley B. Lippman", 59.99,45.5);
    double salary = b1.getSalary();
    cout << "salary=" << salary << endl;
    b1.show();
    cout << "=====BankAccount=====" << endl;
    BankAccount ba1("Tom", 666.66);
    ba1.show();
    cout << "存入55.555：" << endl;
    ba1.deposit(55.555);
    ba1.show();
    ba1.withdraw(99.999);
    cout << "取出99.999：" << endl;
    ba1.show();
    cout << "取出99999999.999：" << endl;
    ba1.withdraw(99999999.999);
    ba1.show();
    

    return 0;
}