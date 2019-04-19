#include "mywindow.h"
//#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowOpacity(1);     //设置显示的透明程度，1为不透明，0为完全透明，0.8为80%不透明
    this->setWindowFlags(Qt::FramelessWindowHint);   //去除窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground);
}

MyWindow::~MyWindow()
{

}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void MyWindow::delay(unsigned int ms)
{
    QTime endTime=QTime::currentTime().addMSecs(ms);   //获取当前时间并加上要延迟的毫秒数，得到结束时间
    while(QTime::currentTime()<endTime)                //不断把当前时间与结束时间作比较
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);   //没有到结束时间，则继续处理所有线程
}
