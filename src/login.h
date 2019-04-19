#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mydialog.h"

namespace Ui {
class Login;
}

class Login : public MyDialog //public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
