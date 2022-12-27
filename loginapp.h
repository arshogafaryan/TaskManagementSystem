#ifndef LOGINAPP_H
#define LOGINAPP_H

#include <QMainWindow>
#include "workingwindow1.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginApp; }
QT_END_NAMESPACE

class LoginApp : public QMainWindow
{
    Q_OBJECT

public:
    LoginApp(QWidget *parent = nullptr);
    ~LoginApp();
    void set_curUsername(std::string username);
private slots:
    void on_log_in_button_clicked();
    void on_create_new_account_button_clicked();

private:
    Ui::LoginApp *ui;
    WorkingWindow1 *workingWindow1;
    bool isUsername(std::string username, std::string password);
    bool checkStatus(std::string username);
};
#endif // LOGINAPP_H
