#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <assert.h>

using namespace std;

class Student {
    private:
        static int lastId;
        static int objectCount;

        int id;
        string name, surname;
        int age;
        double scholarship;

    public:
        // Constructors
        Student(string name, string surname, int age, double scholarship) {
            init(name, surname, age, scholarship);
        }
        Student(string name, string surname, int age) {
            init(name, surname, age, 0.0);
        }

        // Destructor
        ~Student() {
            --objectCount;
        }
        
        void init(string name, string surname, int age, double scholarship){
            setName(name);
            setSurname(surname);
            setAge(age);
            setScholarship(scholarship); 
            id = ++lastId;
            ++objectCount;
        }

        // Setters
        void setName(string name) { 
            this->name = name;
        }
        void setSurname(string surname) { 
            this->surname = surname; 
        }
        void setAge(int age) {
            if (age <= 0) throw invalid_argument("Age must be positive");
            this->age = age;
        }
        void setScholarship(double scholarship) {
            if (scholarship < 0) throw invalid_argument("Scholarship cannot be negative");
            this->scholarship = scholarship;
        }

        // Getters
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
            ss << getId() << " " << getName() << " " << getSurname() 
               << " " << getAge() << " " << getScholarship();
            return ss.str();
        }
};
int Student::lastId = 0;
int Student::objectCount = 0;


int main() {

    // test5 initial state
    assert(Student::getObjectCount() == 0);
    {
        // test1
        Student s1("John", "Doe", 20, 1000);
        assert(s1.getName() == "John");
        assert(s1.getSurname() == "Doe");
        assert(s1.getAge() == 20);
        assert(s1.getScholarship() == 1000);

        string expected = s1.toString();
        assert(!expected.empty());

        // test2
        s1.setName("Jane");
        s1.setSurname("Smith");
        s1.setAge(22);
        s1.setScholarship(1500);
        assert(s1.getName() == "Jane");
        assert(s1.getSurname() == "Smith");
        assert(s1.getAge() == 22);
        assert(s1.getScholarship() == 1500);

        // test3
        bool exceptionThrown = false;
        try {
            s1.setAge(-5);
        } catch (const invalid_argument&) {
            exceptionThrown = true;
        }
        assert(exceptionThrown);

        // test4
        Student* s2 = new Student("Alice", "Johnson", 19, 1200);
        assert(s2->getId() > s1.getId());
        delete s2;

        // test5 
        Student* s4 = new Student("Kate", "Brown", 21, 700);
        assert(Student::getObjectCount() == 2);

        delete s4;
        assert(Student::getObjectCount() == 1);
        
        // list of objects
        Student* arr = new Student[2]{
            Student("Tom","A",18,100),
            Student("Bob","B",19,200)
        };
        assert(Student::getObjectCount() >= 3);
        delete[] arr;
        assert(Student::getObjectCount() == 1);
    }
    assert(Student::getObjectCount() == 0);

    return 0;
}
