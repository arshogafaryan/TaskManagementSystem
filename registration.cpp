#include "registration.h"
#include "ui_registration.h"
#include "loginapp.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

Registration::Registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

int Registration::age(const QDate &birthday)
{
    const auto today = QDate::currentDate();
    auto age = today.year() - birthday.year();
    return today.month() >= birthday.month() && today.day() >= birthday.day() ? age : age - 1;
}

void Registration::on_age_dateChanged(const QDate &date)
{
    int new_age = age(date);
    new_user.setAge(new_age);
}

bool Registration::isUsername(std::string username)
{
    std::string line;
    std::fstream file;
    file.open("users.txt");
    file.seekg(0);
    while(getline(file, line))
    {
        if (line.find(username, 0) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

bool Registration::checkStatus(std::string username)
{
    std::string filename = "users.txt";
    std::fstream file;
    std::string line;
    file.open(filename);
    bool isValid = true;
    while (getline(file, line))
    {
        if (line.find(username) != std::string::npos)
        {
            line.clear();
            getline(file, line, '#');
            if (line.find("-") != std::string::npos)
                isValid = false;
            else
                isValid = true;
        }
    }
    return isValid;
}



void Registration::on_confirm_button_clicked()
{
    std::string new_username = ui->new_username_field->text().toStdString();
    std::string new_firstName = ui->new_firstName_field->text().toStdString();
    std::string new_surname = ui->new_surname_field->text().toStdString();
    std::string new_password = ui->new_password_field->text().toStdString();
    if (new_username.size() < 4)
    {
        QMessageBox::warning(this, "Error", "Username is too short");
    }
    else if (isUsername(new_username) && checkStatus(new_username))
    {
        QMessageBox::warning(this, "Error", "Username already exists");
    }
    else if (new_surname.size() < 3 || new_firstName.size() < 3)
    {
        QMessageBox::warning(this, "Error", "First Name or Surname is too short");
    }
    else if(new_password.size() < 8)
    {
        QMessageBox::warning(this, "Error", "Password is too short");
    }
    else
    {
        this->new_user.setUsername(new_username);
        this->new_user.setFirstName(new_firstName);
        this->new_user.setSurname(new_surname);
        this->new_user.setPassword(new_password);
        this->new_user.setStatus("+");
    }
    fill_to_database(this->new_user);
    LoginApp *login = new LoginApp;
    login->show();
    hide();
}

void Registration::fill_to_database(User& new_user)
{
    std::ofstream file;
    file.open("users.txt", std::ios_base::app);
        file << "Username:" << new_user.getUsername() << "\n"
        << "Password:" << new_user.getPassword() << "\n"
        << "FirstName:" << new_user.getFirstName() << "\n"
        << "Surname:" << new_user.getSurname() << "\n"
        << "Age:" << new_user.getAge() << "\n"
        << "Status:" << new_user.getStatus() << "\n"
        << "#" << "\n";
}


