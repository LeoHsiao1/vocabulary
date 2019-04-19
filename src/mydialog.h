#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragPosition;
};

#endif // MYDIALOG_H
