#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include "mydialog.h"

namespace Ui {
class Modify;
}

class Modify : public MyDialog //public QDialog
{
    Q_OBJECT

public:
    explicit Modify(QWidget *parent = 0);
    ~Modify();

    void modify(int num);

signals:
    void refresh_2();   //刷新信号

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Modify *ui;

    void Connection();
    void save();
    int id;
};

#endif // MODIFY_H
