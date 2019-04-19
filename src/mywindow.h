#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTime>

namespace Ui {
class MyWindow;
}

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragPosition;
    void delay(unsigned int ms);
};

#endif // MYWINDOW_H
