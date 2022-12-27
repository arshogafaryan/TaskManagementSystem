#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>
#include "user.h"
#include "database.h"

namespace Ui {
class Registration;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
    void fill_to_database(User& new_user);

private slots:
    void on_age_dateChanged(const QDate &date);
    void on_confirm_button_clicked();
    bool checkStatus(std::string username);
private:
    bool isUsername(std::string username);
    int age(const QDate &birthday);
    Ui::Registration *ui;
    User new_user;
    Database db;
};

#endif // REGISTRATION_H
