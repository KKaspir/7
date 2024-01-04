#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class Grade {
private:
    std::string subject;
    double score;
    std::string date;


public:
    Grade(const std::string& subj, double scr, const std::string& dt)
        : subject(subj), score(scr), date(dt) {}

    void print() const {
        std::cout << "Предмет: " << subject << std::endl;
        std::cout << "Оценка: " << score << std::endl;
        std::cout << "Дата: " << date << std::endl;
    }

    Grade(double score) : score(score) {
        if ((score < 0.0) || (score > 100.0)) {
            throw std::invalid_argument("Оценка Должна быть в диапазоне [0; 100]!");
        }
    }

    static Grade inputFromConsole() {
        std::string subject;
        double score;
        std::string date;

        std::cout << "Введите предмет: ";
        std::cin >> subject;
        std::cout << "Введите оценку: ";
        std::cin >> score;
        std::cout << "Введите дату: ";
        std::cin >> date;

        return Grade(subject, score, date);
    }

    double getScore() const {
        return score;
    }

    double* getScorePointer() {
        return &score;
    }

    double& getScoreReference() {
        return score;
    }
};


class Person {
public:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    int age;

    Person(const std::string& first, const std::string& last, const std::string& dob, const int& a) : firstName(first), lastName(last), dateOfBirth(dob), age(a) {}

    virtual void display() const {
        std::cout << "Имя: " << firstName << ", Фамилия: " << lastName << ", ДР: " << dateOfBirth << ", Возраст: " << age << std::endl;
    }
};

class Student : public Person {

protected:
    std::string email;
    std::vector<Grade> grades;
public:
    std::string studentID;
    Student(
        const std::string& first,
        const std::string& last,
        const std::string& dob,
        const int& a, 
        const std::string& id,
        const std::string& mail,
        const std::vector<Grade>& gr
    ) : Person(first, last, dob, a), studentID(id), email(mail), grades(gr) {}

    double avgGrade() const {
        if (grades.empty()) {
            return 0.0;
        }
        double totalScore = 0.0;
        for (const Grade& grade : grades) {
            totalScore += grade.getScore();
        }
        return totalScore / grades.size();
    }

    void display() const override {
        std::cout << "Студент: " << firstName << " " << lastName << ", Номер студ. билета: " << studentID << std::endl;
    }




    static Student inputFromConsole() {
        std::string first, last, dob; 
        int a;
        std::string id, mail;
        std::vector<Grade> grades;

        std::cout << "Введите имя: ";
        std::cin >> first;
        std::cout << "Введите фамилию: ";
        std::cin >> last;
        std::cout << "Введите дату рождения: ";
        std::cin >> dob;
        std::cout << "Введите возраст: ";
        std::cin >> a;
        std::cout << "Введите номер студенческого билета: ";
        std::cin >> id;
        std::cout << "Введите email: ";
        std::cin >> mail;

        char addGrade;
        do {
            Grade grade = Grade::inputFromConsole();
            grades.push_back(grade);

            std::cout << "Добавить еще одну оценку? (y/n): ";
            std::cin >> addGrade;
        } while (addGrade == 'y' || addGrade == 'Y');

        return Student(first, last, dob, a, id, mail, grades);
    }
    std::string getFirstName() const {
        return firstName;
    }

    std::string getLastName() const {
        return lastName;
    }

    std::string getFullName() const {
        return this->firstName + " " + this->lastName;
    }

    Grade& getGradeReference() {
        return grades.front();
    }

    
    virtual void printStudent() const {
        std::cout << *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Имя и фамилия: " << student.firstName << " " << student.lastName << std::endl;
        os << "Дата рождения: " << student.dateOfBirth << std::endl;
        os << "Номер студенческого билета: " << student.studentID << std::endl;
        os << "Email: " << student.email << std::endl;

        os << "\nОценки:" << std::endl;
        for (const Grade& grade : student.grades) {
            grade.print();
            os << std::endl;
        }

        return os;
    }

    void inputGrades() {
        try {
            int numGrades;
            std::cout << "Введите количество оценок: ";
            std::cin >> numGrades;

            for (int i = 0; i < numGrades; ++i) {
                double score;
                std::cout << "Введите оценку #" << i + 1 << ": ";
                std::cin >> score;

                grades.push_back(Grade(score));
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }

    virtual void introduce() const {
        std::cout << "Привет, меня зовут " << getFullName() << std::endl;
    }
};


class InternationalStudent : public Student {
private:
    std::string country;

public:
    InternationalStudent(
        const std::string& first,
        const std::string& last,
        const std::string& dob,
        const int& a,
        const std::string& id,
        const std::string& mail,
        const std::vector<Grade>& gr,
        const std::string& country
    ) : Student(first, last, dob, a, id, mail, gr), country(country) {} 


    void printStudent() const override {
        Student::printStudent();

        std::cout << "Страна: " << country << std::endl;
    }

    void introduce() const override {
        std::cout << "Hello, my name is " << getFullName() << " from " << country << std::endl;
    }


    virtual void greet(const Student& student) {
        student.introduce();
    }

    InternationalStudent& operator=(const Student& other) {
        Student::operator=(other);


        return *this;
    }
};


void greet(const Student& student) {
    student.introduce();
}

class AbstractGrader {
public:
    virtual void grade() const = 0;  
};

class GoodStudent : public AbstractGrader {
public:
    void grade() const override {
        std::cout << "I am a good student!" << std::endl;
    }
};


template <typename T>
class Container {
private:
    T value;

public:
    Container(const T& val) : value(val) {}

    T getValue() const {
        return value;
    }
};


/************ КОД К ПРОШЛЫМ ЛР ****************/
class Project {
private:
    std::string projectName;
    std::string description;
    std::string startDate;
    std::string endDate;
    std::vector<Student> teamMembers;

public:
    Project(
        const std::string& name,
        const std::string& desc,
        const std::string& start,
        const std::string& end,
        const std::vector<Student>& members
    ) : projectName(name), description(desc), startDate(start), endDate(end), teamMembers(members) {}

    void addTeamMember(const Student& student) {
        teamMembers.push_back(student);
    }

    void print() const {
        std::cout << "Название проекта: " << projectName << std::endl;
        std::cout << "Описание: " << description << std::endl;
        std::cout << "Дата начала: " << startDate << std::endl;
        std::cout << "Дата окончания: " << endDate << std::endl;

        std::cout << "\nУчастники:" << std::endl;
        for (const Student& student : teamMembers) {
            std::cout << "Имя: " << student.getFirstName() << " " << student.getLastName() << std::endl;
        }
    }

    static Project inputFromConsole() {
        std::string name, desc, start, end;
        std::vector<Student> members;

        std::cout << "Введите название проекта: ";
        std::cin >> name;
        std::cout << "Введите описание проекта: ";
        std::cin >> desc;
        std::cout << "Введите дату начала: ";
        std::cin >> start;
        std::cout << "Введите дату окончания: ";
        std::cin >> end;

        char addMember;
        do {
            Student student = Student::inputFromConsole();
            members.push_back(student);

            std::cout << "Добавить еще одного участника? (y/n): ";
            std::cin >> addMember;
        } while (addMember == 'y' || addMember == 'Y');

        return Project(name, desc, start, end, members);
    }
};

class Event {
private:
    std::string eventName;
    std::string date;
    std::string location;
    std::vector<Student> eventMembers;

public:
    Event(
        const std::string& name,
        const std::string& dt,
        const std::string& loc,
        const std::vector<Student>& members
    ) : eventName(name), date(dt), location(loc), eventMembers(members) {}

    void addParticipant(const Student& student) {
        eventMembers.push_back(student);
    }

    void print() const {
        std::cout << "Название мероприятия: " << eventName << std::endl;
        std::cout << "Дата: " << date << std::endl;
        std::cout << "Место проведения: " << location << std::endl;

        std::cout << "\nУчастники:" << std::endl;
        for (const Student& student : eventMembers) {
            std::cout << "Имя: " << student.getFirstName() << " " << student.getLastName() << std::endl;
        }
    }

    static Event inputFromConsole() {
        std::string name, date, location;
        std::vector<Student> members;

        std::cout << "Введите название мероприятия: ";
        std::cin >> name;
        std::cout << "Введите дату мероприятия: ";
        std::cin >> date;
        std::cout << "Введите место проведения мероприятия: ";
        std::cin >> location;

        char addParticipant;
        do {
            Student student = Student::inputFromConsole();
            members.push_back(student);

            std::cout << "Добавить еще одного участника мероприятия? (y/n): ";
            std::cin >> addParticipant;
        } while (addParticipant == 'y' || addParticipant == 'Y');

        return Event(name, date, location, members);
    }

    std::string getEvenName() const {
        return eventName;
    }


    Event operator+(const Event& other) const {
        std::vector<Student> combinedMembers = eventMembers;
        combinedMembers.insert(combinedMembers.end(), other.eventMembers.begin(), other.eventMembers.end());
        return Event(eventName + " & " + other.eventName, date, location, combinedMembers);
    }

    Event& operator++() {
        for (Student& student : eventMembers) {
            student.getGradeReference().getScoreReference() += 1.0;
        }
        return *this;
    }

    Event operator++(int) {
        Event temp = *this;
        ++(*this);
        return temp;
    }
};

class Course {
private:
    std::string courseName;
    std::string startDate;
    std::string endDate;
    std::string instructor;
    std::vector<Event> events;

public:
    Course(
        const std::string& name,
        const std::string& start,
        const std::string& end,
        const std::string& instr,
        const std::vector<Event>& evts
    ) : courseName(name), startDate(start), endDate(end), instructor(instr), events(evts) {}

    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void print() const {
        std::cout << "Название курса: " << courseName << std::endl;
        std::cout << "Дата начала: " << startDate << std::endl;
        std::cout << "Дата окончания: " << endDate << std::endl;
        std::cout << "Предподаватель: " << instructor << std::endl;

        std::cout << "Мероприятия: " << std::endl;
        for (const Event& event : events) {
            std::cout << "Название: " << event.getEvenName() << std::endl;
        }
    }

    static Course inputFromConsole() {
        std::string name, start, end, instructor;
        std::vector<Event> events;

        std::cout << "Введите название курса: ";
        std::cin >> name;
        std::cout << "Введите дату начала курса: ";
        std::cin >> start;
        std::cout << "Введите дату окончания курса: ";
        std::cin >> end;
        std::cout << "Введите имя предподавателя: ";
        std::cin >> instructor;

        char addEvent;
        do {
            Event event = Event::inputFromConsole();
            events.push_back(event);

            std::cout << "Добавить еще одно мероприятие курса? (y/n): ";
            std::cin >> addEvent;
        } while (addEvent == 'y' || addEvent == 'Y');

        return Course(name, start, end, instructor, events);
    }
};
/************ КОД К ПРОШЛЫМ ЛР ****************/



int main() {
    setlocale(LC_ALL, "Russian");

    // Создание коллекции объектов Person и Student
    std::vector<Person*> people;
    people.push_back(new Person("Иван", "Иванов", "01.01.2000", 4));
    people.push_back(new Student("Анна", "Кипяткова", "02.01.2000", 8, "12345", "test@mail", {}));
    people.push_back(new Student("Петр", "Петров", "02.01.2000", 6 ,  "67890", "test@mail", {}));

    // Использование алгоритма сортировки для сортировки по возрасту
    std::sort(people.begin(), people.end(), [](const Person* a, const Person* b) {
        return a->age < b->age;
        });

    // Вывод отсортированной коллекции
    std::cout << "Отсортированные объекты:" << std::endl;
    for (const auto& person : people) {
        person->display();
    }

    // Использование алгоритма поиска для поиска студента по номеру студ. билета
    std::string searchID = "67890";
    auto it = std::find_if(people.begin(), people.end(), [&searchID](const Person* p) {
        const Student* student = dynamic_cast<const Student*>(p);
        return student && student->studentID == searchID;
        });

    // Вывод результата поиска
    if (it != people.end()) {
        std::cout << "\nСтудент с номером студ. билета " << searchID << " найден:" << std::endl;
        (*it)->display();
    }
    else {
        std::cout << "\nСтудент с номером студ. билета " << searchID << " не найден." << std::endl;
    }

    // Очистка памяти
    for (const auto& person : people) {
        delete person;
    }

    return 0;
}