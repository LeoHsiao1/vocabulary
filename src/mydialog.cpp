#include "mydialog.h"
//#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowOpacity(1);     //设置显示的透明程度，1为不透明，0为完全透明，0.8为80%不透明
    this->setWindowFlags(Qt::FramelessWindowHint);   //去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);
}

MyDialog::~MyDialog()
{

}

void MyDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MyDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
