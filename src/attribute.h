#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QDialog>
#include <QSqlQuery>
#include <QtSql>
#include "mydialog.h"

namespace Ui {
class Attribute;
}

class Attribute : public MyDialog //public QDialog
{
    Q_OBJECT

public:
    explicit Attribute(QWidget *parent = 0);
    ~Attribute();

signals:
    void refresh();   //刷新信号

private slots:
    void on_pushButton_clicked();

private:
    Ui::Attribute *ui;

    void Connection();
    void save();
};

#endif // ATTRIBUTE_H
