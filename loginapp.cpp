#include "loginapp.h"
#include "ui_loginapp.h"
#include "registration.h"
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <QCloseEvent>

LoginApp::LoginApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginApp)
{
    ui->setupUi(this);
}

LoginApp::~LoginApp()
{
    delete ui;
}

bool LoginApp::isUsername(std::string username, std::string password)
{
    std::string line;
    std::fstream file;
    file.open("users.txt");
    file.seekg(0);
    while(getline(file, line))
    {
        if (line.find(username, 0) != std::string::npos)
        {
            std::string line2;
            getline(file, line2);
            if (line2.find(password, 0) != std::string::npos)
                return true;
        }
    }
    return false;
}

bool LoginApp::checkStatus(std::string username)
{
    std::string filename = "users.txt";
    std::fstream file;
    std::string line;
    file.open(filename);
    while (getline(file, line))
    {
        if (line.find(username) != std::string::npos)
        {
            line.clear();
            getline(file, line, '#');
            if (line.find("-") != std::string::npos)
                return false;
        }
    }
    return true;
}

void LoginApp::set_curUsername(std::string username)
{
    workingWindow1->set_curUsername(username);
}

void LoginApp::on_log_in_button_clicked()
{
    std::string username = ui->username_field->text().toStdString();
    std::string password = ui->password_field->text().toStdString();
    if (isUsername(username, password) && checkStatus(username))
    {
        workingWindow1 = new WorkingWindow1(this);
        set_curUsername(username);
        QCloseEvent();
        workingWindow1->show();

    }
    else
    {
        QMessageBox::warning(this,"Log in","Username or Password is incorrect");
    }
    ui->username_field->clear();
    ui->password_field->clear();
}


void LoginApp::on_create_new_account_button_clicked()
{
    Registration *reg = new Registration;
    reg->show();
    hide();
}

