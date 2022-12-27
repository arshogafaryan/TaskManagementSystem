#ifndef WORKINGWINDOW1_H
#define WORKINGWINDOW1_H

#include <QMainWindow>

namespace Ui {
class WorkingWindow1;
}

class WorkingWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkingWindow1(QWidget *parent = nullptr);
    ~WorkingWindow1();
    WorkingWindow1() : cur_username(), ProjectNumber(0), TaskNumber(0) {}
    std::string get_curUsername();
    void set_curUsername(std::string username);
    void incProjectNumber();
    void incTaskNumber();
    void decProjectNumber();
    void decTaskNumber();
    int getTaskNumber();
    int getProjectNumber();
    bool checkTaskStatus();
    void deleteProject(std::string project_name);
    void deleteTask(std::string task_name);
    void deleteStatus();
    std::vector<std::string> displayProjects();
    std::vector<std::string> displayTasks();
    std::vector<std::string> fill_in_buffer(std::string filename);
    void fill_in_file(std::string filename, std::vector<std::string> buffer);


private slots:

    void on_add_project_button_clicked();

    void on_add_task_button_clicked();

    void on_del_project_button_clicked();

    void on_del_user_button_clicked();

    void on_del_task_button_clicked();

    void on_show_project_button_clicked();

    void on_show_task_button_clicked();

    void on_log_out_button_clicked();

    void on_show_all_button_clicked();

    void on_user_info_clicked();

private:
    int lastTaskNumber();
    int lastProjectNumber();
    Ui::WorkingWindow1 *ui;
    std::string cur_username;
    int ProjectNumber;
    int TaskNumber;
};

#endif // WORKINGWINDOW1_H
