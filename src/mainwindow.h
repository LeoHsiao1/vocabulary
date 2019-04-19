#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include "login.h"
#include "attribute.h"
#include "modify.h"
#include "mywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public MyWindow //public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_checkBox_stateChanged(int state);

    void on_checkBox_2_stateChanged(int state);

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_tableView_doubleClicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;        //用QSqlDatabase声明一个数据库类，名为db
    QSqlQueryModel *model;
    void Connection();
    void show_table();
    void show_vocabulary();
    int sum;
    Login d1;         //登录对话框，创建指针对象的话会允许存在多个对话框
    Attribute d2;    //单词属性对话框
    Modify d3;      //修改属性对话框    
};

#endif // MAINWINDOW_H
