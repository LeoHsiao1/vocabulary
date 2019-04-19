#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    MyDialog(parent),   //QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text() == "测试用户" && ui->lineEdit_4->text() == "123456")
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,"警告！","用户名或密码错误！",QMessageBox::Yes);
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_3->setFocus();
    }
}
