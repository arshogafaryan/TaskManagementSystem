#ifndef USER_H
#define USER_H

#include <QMainWindow>

class User
{
    std::string username;
    std::string firstName;
    std::string surname;
    std::string password;
    std::string status;
    int age;
    int ID;
    int lastID();

    public:
    User() : username(), firstName(), surname(), password(), age{0}, ID{0} {}
    ~User() = default;
    void setAge(int new_age);
    void setFirstName(std::string new_firstName);
    void setSurname(std::string new_surname);
    void setUsername(std::string new_username);
    void setPassword(std::string new_password);
    void setStatus(std::string status);
    int getAge();
    int getID();
    std::string getFirstName();
    std::string getSurname();
    std::string getUsername();
    std::string getPassword();
    std::string getStatus();
    void updateID();
};

#endif // USER_H
