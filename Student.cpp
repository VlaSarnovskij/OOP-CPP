#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>

using namespace std;

class Student {
    private:
        int id;
        static int lastId;
        static int objectCount;
        string name, surname;
        int age;
        double scholarship;

    public:
        Student(string name, string surname, int age, double scholarship) {
            init(name, surname, age, scholarship);
        }

         Student(string name, string surname) {
            init(name, surname, 0, 0.0);
        }
        ~Student() {
            --objectCount;
            cout << "Destructor" << endl;
        }

    private:
        void init(string name, string surname, int age, double scholarship){
            cout << "Constructor" << endl;
            ++objectCount;
            id = ++lastId;
            setName(name);
            setSurname(surname);
            setAge(age);
            setScholarship(scholarship); 
        }
        void setName(string name) {
            this->name = name;
        }
        void setSurname(string surname) {
            this->surname = surname;
        }
        void setAge(int age) {
            if(age > 0) {
                this->age = age;
            } else 
                throw invalid_argument("Age must be a positive integer.");
        }
        void setScholarship(double scholarship) {
            this->scholarship = scholarship;
        }
    public:
        static int getObjectCount() {
            return objectCount;
        }
        int getId() {
            return id;
        }   
        string getName() {
            return name;
        }
        string getSurname() {
            return surname;
        }
        int getAge() {
            return age;
        }
        double getScholarship() {
            return scholarship;
        }
        string toString() {
            stringstream ss;
            ss << getId() << " " << getName() << " " << getSurname() << " " << getAge() << " " << getScholarship();
            return ss.str();
        }


};
int Student::lastId = 0;
int Student::objectCount = 0;


int main() {
    try{
        Student s0("John", "Doe", 20, 1500.0);
        Student* s1 = new Student("Jane", "Smith", 22, 2000.0);
        
        cout << s0.toString() << endl;
        cout << s1->toString() << endl;

        delete s1;
    } catch (const exception& e) {
        cout << "Unexpected error occurred!" << endl;
        cout << "Error: " << e.what() << endl;
    }
    cout << "Current object count: " << Student::getObjectCount() << endl;

    return 0;
}
