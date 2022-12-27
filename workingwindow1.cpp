#include "workingwindow1.h"
#include "ui_workingwindow1.h"
#include "loginapp.h"
#include <string>
#include <utility>
#include <fstream>
#include <ios>
#include <QString>
#include <QLabel>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextCursor>
WorkingWindow1::WorkingWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorkingWindow1)
{
    ui->setupUi(this);
}

WorkingWindow1::~WorkingWindow1()
{
    delete ui;
}



int WorkingWindow1::lastProjectNumber()
{
    std::vector<std::string> buff = fill_in_buffer("projects.txt");
    int count = 0;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
            count++;
    }
    fill_in_file("projects.txt", buff);
    return count;
}

int WorkingWindow1::lastTaskNumber()
{
    std::vector<std::string> buff = fill_in_buffer("tasks.txt");
    int count = 0;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
            count++;
    }
    fill_in_file("tasks.txt", buff);
    return count;
}

std::vector<std::string> WorkingWindow1::displayProjects()
{
    std::vector<std::string> buff = fill_in_buffer("projects.txt");
    std::vector<std::string> res;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
            res.push_back(buff[i].substr(buff[i].find("ProjectName:") + 12, buff[i].find("ProjectDescription:")));
    }
    fill_in_file("projects.txt", buff);
    return res;
}

std::vector<std::string> WorkingWindow1::displayTasks()
{
    std::vector<std::string> buff = fill_in_buffer("tasks.txt");
    std::vector<std::string> res;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
            res.push_back(buff[i].substr(buff[i].find("TaskName:") + 12, buff[i].find("TaskDescription:")));
    }
    fill_in_file("tasks.txt", buff);
    return res;
}

void WorkingWindow1::incProjectNumber()
{
    this->ProjectNumber = this->lastProjectNumber();
    ++this->ProjectNumber;
}

void WorkingWindow1::incTaskNumber()
{
    this->TaskNumber = this->lastTaskNumber();
    ++this->TaskNumber;
}

void WorkingWindow1::decProjectNumber()
{
    this->ProjectNumber = this->lastProjectNumber();
    --this->ProjectNumber;
}

void WorkingWindow1::decTaskNumber()
{
    this->TaskNumber = this->lastTaskNumber();
    --this->TaskNumber;
}

int WorkingWindow1::getProjectNumber()
{
    return this->ProjectNumber;
}

int WorkingWindow1::getTaskNumber()
{
    return this->TaskNumber;
}

void WorkingWindow1::set_curUsername(std::string username)
{
    this->cur_username = username;
    ui->username_title->setText("User:" + QString::fromStdString(cur_username));
}

std::vector<std::string> WorkingWindow1::fill_in_buffer(std::string filename)
{
    std::fstream file;
    file.open(filename);
    std::string line;
    std::vector<std::string> buffer;
    while (getline(file, line, '#'))
    {
        if (line != "\n")
            buffer.push_back(line);
    }
    file.clear();
    return buffer;
}

void WorkingWindow1::fill_in_file(std::string filename, std::vector<std::string> buffer)
{
    std::fstream file;
    file.open(filename);
    std::string line;
    for (unsigned int i = 0; i < buffer.size(); ++i)
    {
        file << buffer[i] << '#';
    }
}

std::string WorkingWindow1::get_curUsername()
{
    return this->cur_username;
}

bool WorkingWindow1::checkTaskStatus()
{
    std::vector<std::string> buff = fill_in_buffer("tasks.txt");
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos)
        {
            if (buff[i].find('-') == std::string::npos)
                return true;
        }
    }
    return false;
}

void WorkingWindow1::deleteStatus()
{
    std::vector<std::string> buff = fill_in_buffer("users.txt");
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos)
        {
            buff[i].replace(buff[i].find("+"), 1, "-");
        }
    }
    fill_in_file("users.txt", buff);
}

void WorkingWindow1::deleteTask(std::string task_name)
{
    std::vector<std::string> buff = fill_in_buffer("tasks.txt");
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find(task_name) != std::string::npos)
        {
            buff[i].replace(buff[i].find("+"), 1, "-");
        }
    }
    fill_in_file("tasks.txt", buff);
    decTaskNumber();
}

void WorkingWindow1::deleteProject(std::string project_name)
{
    std::vector<std::string> buff = fill_in_buffer("projects.txt");
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find(project_name) != std::string::npos)
        {
            buff[i].replace(buff[i].find("+"), 1, "-");
        }
    }
    fill_in_file("projects.txt", buff);
    decProjectNumber();
}

void WorkingWindow1::on_add_project_button_clicked()
{
    std::string project_name = ui->project_field->text().toStdString();
    std::string project_description = ui->project_description->toPlainText().toStdString();
    if (project_name.size() < 2 || project_description.size() < 2)
    {
        QMessageBox::warning(this, "Error", "Name or Description is too short");
        ui->project_field->clear();
        ui->project_description->clear();
        return;
    }
    std::fstream file;
    file.open("projects.txt", std::ios_base::app);
    incProjectNumber();
    file << "Username:" << get_curUsername() << "\n"
    << "ProjectName:" << project_name << "\n"
    << "ProjectDescription:" << project_description << "\n"
    << "ProjectStatus:" << "+" << "\n"
    << "ProjectNumber:" << getProjectNumber() << "\n"
    << "#" << "\n";
    ui->project_field->clear();
    ui->project_description->clear();
}


void WorkingWindow1::on_add_task_button_clicked()
{
    std::string task_name = ui->task_field->text().toStdString();
    std::string task_description = ui->task_description->toPlainText().toStdString();
    if (task_name.size() < 2 || task_description.size() < 2)
    {
        QMessageBox::warning(this, "Error", "Name or Description is too short");
        ui->task_field->clear();
        ui->task_description->clear();
        return;
    }
    std::fstream file;
    file.open("tasks.txt", std::ios_base::app);
    incTaskNumber();
    file << "Username:" << get_curUsername() << "\n"
    << "TaskName:" << task_name << "\n"
    << "TaskDescription:" << task_description << "\n"
    << "TaskStatus:" << "+" << "\n"
    << "TaskNumber:" << getTaskNumber() << "\n"
    << "#" << "\n";
    ui->task_field->clear();
    ui->task_description->clear();
}

void WorkingWindow1::on_del_user_button_clicked()
{
    deleteStatus();
    hide();
}

void WorkingWindow1::on_del_project_button_clicked()
{
    std::string del_project_name = ui->del_project_field->text().toStdString();
    deleteProject(del_project_name);
    ui->del_project_field->clear();
}


void WorkingWindow1::on_del_task_button_clicked()
{
    std::string del_task_name = ui->del_project_field->text().toStdString();
    deleteTask(del_task_name);
    ui->del_task_field->clear();
}


void WorkingWindow1::on_show_project_button_clicked()
{
    std::vector<std::string> buff = fill_in_buffer("projects.txt");
    std::string des;
    std::string target;
    std::string proj_name = ui->show_project_field->text().toStdString();
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos && buff[i].find(proj_name) != std::string::npos)
        {
            target = buff[i];
            int pos1 = target.find("ProjectDescription:") + 19;
            int pos2 = target.find("ProjectStatus") - 1;
            int name_pos1 = target.find("ProjectName:") + 12;
            int name_pos2 = target.find("ProjectDescription:") - 1;
            if (target.substr(name_pos1,name_pos2 - name_pos1) == proj_name)
            {
                des = target.substr(pos1,pos2 - pos1);
            }
        }
    }
    if (des.empty())
    {
        ui->show_project_description->clear();
        QMessageBox::warning(this, "Error", "No such project");
        return;
    }
    fill_in_file("projects.txt", buff);
    ui->show_project_description->setText(QString::fromStdString(des));
}


void WorkingWindow1::on_show_task_button_clicked()
{
    std::vector<std::string> buff = fill_in_buffer("tasks.txt");
    std::string des;
    std::string target;
    std::string task_name = ui->show_task_field->text().toStdString();
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos && buff[i].find(task_name) != std::string::npos)
        {
            target = buff[i];
            int pos1 = target.find("TaskDescription:") + 16;
            int pos2 = target.find("TaskStatus") - 1;
            int name_pos1 = target.find("TaskName:") + 9;
            int name_pos2 = target.find("TaskDescription:") - 1;
            if (target.substr(name_pos1,name_pos2 - name_pos1) == task_name)
            {
                des = target.substr(pos1,pos2 - pos1);
            }
        }
    }
    if (des.empty())
    {
        ui->show_task_field->clear();
        QMessageBox::warning(this, "Error", "No such task");
        return;
    }
    fill_in_file("tasks.txt", buff);
    ui->show_task_description->setText(QString::fromStdString(des));
}


void WorkingWindow1::on_log_out_button_clicked()
{
    LoginApp* login = new LoginApp(this);
    login->show();
    hide();
    QCloseEvent();
}


void WorkingWindow1::on_show_all_button_clicked()
{
    std::vector<std::string> buff = fill_in_buffer("projects.txt");
    std::vector<std::pair<std::string,std::string>> res;
    std::string target;
    std::string proj_des;
    std::string proj_name;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
        {
            target = buff[i];
            int pos1 = target.find("ProjectDescription:") + 19;
            int pos2 = target.find("ProjectStatus") - 1;
            int name_pos1 = target.find("ProjectName:") + 12;
            int name_pos2 = target.find("ProjectDescription:") - 1;
            proj_name = target.substr(name_pos1,name_pos2 - name_pos1);
            proj_des = target.substr(pos1,pos2 - pos1);
            res.push_back(make_pair(proj_name,proj_des));
        }
    }
    fill_in_file("projects.txt", buff);
    ui->show_all->setText("Projects Number: " + QString::fromStdString(std::to_string(lastProjectNumber())));
    for (unsigned int i = 0; i < res.size(); ++i)
    {
        ui->show_all->append(QString::fromStdString(res[i].first + " -> " + res[i].second));
    }

    buff.clear();
    res.clear();
    target.clear();
    buff = fill_in_buffer("tasks.txt");
    std::string task_des;
    std::string task_name;
    for (unsigned int i = 0; i < buff.size(); ++i)
    {
        if (buff[i].find(cur_username) != std::string::npos && buff[i].find('+') != std::string::npos)
        {
            target = buff[i];
            int pos1 = target.find("TaskDescription:") + 16;
            int pos2 = target.find("TaskStatus") - 1;
            int name_pos1 = target.find("TaskName:") + 9;
            int name_pos2 = target.find("TaskDescription:") - 1;
            task_name = target.substr(name_pos1,name_pos2 - name_pos1);
            task_des = target.substr(pos1,pos2 - pos1);
            res.push_back(make_pair(task_name,task_des));
        }
    }
    fill_in_file("tasks.txt", buff);
    ui->show_all->append("Tasks Number: " + QString::fromStdString(std::to_string(lastTaskNumber())));
    for (unsigned int i = 0; i < res.size(); ++i)
    {
        ui->show_all->append(QString::fromStdString(res[i].first + " -> " + res[i].second));
    }
}


void WorkingWindow1::on_user_info_clicked()
{

}

