#include <iostream>
#include <vector>
#include <regex>
#include <string>
//#include <Windows.h>

using namespace std;

class Date {
public:
    int day;
    int month;
    int year;
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    };
    void print() {
        cout << this->day << "." << this->month << "." << this->year;
    };
};

class AbstractUser {
public:
    string login;
    string FIO;
    string password;
    Date* date;
    AbstractUser(string login, string FIO, string password, Date* date) {
        this->login = login;
        this->FIO = FIO;
        this->date = date;
        if (validatePassword(password)) {
            this->password = password;
        }
        else {
            throw "Wrong password exception";
        }
    }
    /*
    ~AbstractUser() {
        cout << "\nЛогин: " << this->login << " удален\n\n";
    }
    */

    bool validatePassword(string enteredPassword) {
        if (regex_match(enteredPassword, regex(R"((?=^.{8,}$)((?=.*\d)|(?=.*\W+))(?![.\n])(?=.*[A-Z])(?=.*[a-z]).*$)"))) {
            return true;
        }
        else {
            cout << "Неправильно введен пароль. Убедитесь, что у Вас есть хотя бы одна заглавная и строчная буквы, цифра и специальныйй символ. Минимальная длинна пароля 8 символов.\n\n";
            return false;

        }
    }
};

class User : public AbstractUser {
public:
    Date* birthDate;
    string gender;
    int balance;
public:
    User(string login, string FIO, string password, Date* date, Date* birthDate, string gender, float balance) : AbstractUser(login, FIO, password, date) {
        this->birthDate = birthDate;
        this->gender = gender;
        this->balance = balance;
    }
    void print() {
        cout << "Логин: " << this->login << ", ФИО: " << this->FIO << ", Пароль: " << this->password << ", Дата регистрации: ";
        date->print();
        cout << ", Дата рождения: ";
        birthDate->print();
        cout << " , Баланс: " << this->balance << endl;
    }
    /*
    ~User() {
        cout << "\nПользователь: " << this->login << " удален" << ", баланс: " << this->balance << " списан\n\n";
    }
    */
};

vector <User> users;

class Admin : public User {
private:
    bool isSuperAdmin;
public:
    Admin(string login, string FIO, string password, Date* date, Date* birthDate, string gender, float balance, bool isSuperAdmin) : User(login, FIO, password, date, birthDate, gender, balance) {
        this->isSuperAdmin = isSuperAdmin;
    }

    void print() {
        cout << "Логин: " << this->login << ", ФИО: " << this->FIO << ", Пароль: " << this->password << ", Дата регистрации: ";
        date->print();
        cout << ", Дата рождения: ";
        birthDate->print();
        cout << " , Баланс: " << this->balance << endl;
        if (this->isSuperAdmin) {
            cout << "Пользователь супер админ!!!" << endl;
        }
        else {
            cout << "Пользователь админ!" << endl;
        }
    }

    void DeletUser(string login) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].login == login) {
                users.erase(users.begin() + i);
                cout << "Пользователь успешно удалён" << endl;
                break;
            }
        }
    }

    void DeletAllUsers();
    /*~Admin() {
        cout << "\nАдмин: " << this->login << " удален" << ", баланс: " << this->balance << " списан\n\n";
    }
    */

};

vector <Admin> admins;

void Admin::DeletAllUsers() {
    if (this->isSuperAdmin) {
        users.clear();
        admins.clear();
        cout << "Все пользователи удалены!" << endl;
    }
    else {
        cout << "Отказано в доступе" << endl;
    }
}


int main() {
    /*SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    */
    setlocale(LC_ALL, "");
    Date* date1 = new Date(24, 04, 2023);
    Date* date2 = new Date(24, 04, 2007);

    User u1("ApS", "Фролов Александр Денисович", "2007Alex__", date1, date2, "male", 567414);
    users.push_back(u1);
    users[0].print();
    cout << endl;

    Admin a1("ApSA", "Фролов Александр Денисович", "20072007Alex__", date1, date2, "male", 5674142, false);
    admins.push_back(a1);
    admins[0].print();
    cout << endl;

    admins[0].DeletUser("ApS");
    cout << endl;

    Admin a2("ApSAs", "Петрыкин Артём Сергеевич", "20072007ARTeM__", date1, date2, "male", 5674142, true);
    admins.push_back(a2);
    admins[1].print();
    cout << endl;

    admins[0].DeletAllUsers();
    cout << endl;

    admins[1].DeletAllUsers();
    cout << "Конец программы!";
};