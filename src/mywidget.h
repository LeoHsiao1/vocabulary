#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTime>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget  //本想把MyWindow和MyDialog两个自定义的类合并为这一个类，然后在mainwindow中多重继承，但是并不能多重继承，会提示调用的函数名冲突
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragPosition;
};

#endif // MYWIDGET_H
