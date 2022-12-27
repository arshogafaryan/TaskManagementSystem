#include "user.h"
#include <fstream>

void User::setAge(int new_age)
{
    this->age = new_age;
}

void User::setFirstName(std::string new_firstName)
{
    this->firstName = new_firstName;
}

void User::setSurname(std::string new_surname)
{
    this->surname = new_surname;
}

void User::setUsername(std::string new_username)
{
    this->username = new_username;
}

void User::setPassword(std::string new_password)
{
    this->password = new_password;
}

void User::setStatus(std::string status)
{
    this->status = status;
}

int User::getAge()
{
    return this->age;
}

std::string User::getFirstName()
{
    return this->firstName;
}

std::string User::getSurname()
{
    return this->surname;
}

std::string User::getUsername()
{
    return this->username;
}

std::string User::getPassword()
{
    return this->password;
}

int User::lastID()
{
    std::string filename = "users.txt";
    std::fstream fin;
    std::string lastLine;
    fin.open(filename);
    bool isEmpty = true;
    std::string line;
    while(getline(fin,line) )
        isEmpty = false;
    if(isEmpty)
        return 0;
    if(fin.is_open()) {
        fin.seekg(-1,std::ios_base::end);
        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            fin.get(ch);
            if(ch == ':')
            {
                keepLooping = false;
            }
            else {
                fin.seekg(-2,std::ios_base::cur);
            }
        }
        getline(fin,lastLine);
    }
    return std::stoi(lastLine);
}

int User::getID()
{
    return this->ID;
}

void User::updateID()
{
    this->ID = this->lastID();
    ++this->ID;
}

std::string User::getStatus()
{
    return this->status;
}
