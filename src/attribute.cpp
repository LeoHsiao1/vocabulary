#include "attribute.h"
#include "ui_attribute.h"
#include "mainwindow.h"

Attribute::Attribute(QWidget *parent) :
    MyDialog(parent),   //QDialog(parent),
    ui(new Ui::Attribute)
{
    ui->setupUi(this);   //Attribute类用于弹出一个对话框，显示单词具体属性

    Connection();
}

Attribute::~Attribute()
{
    delete ui;
}

void Attribute::Connection()   //打开数据库
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("vocabulary.db");
    if(!db.open()){
        QMessageBox::warning(this,"错误","不能连接到数据库！",QMessageBox::Yes);
    }
    QSqlQuery query;
    query.exec("create table vocabulary (id int PRIMARY KEY,word varchar（30）,type text,definition text,example text)");
}

void Attribute::save()
{
    QSqlQuery query;
    query.exec("select * from vocabulary ");
    query.last();
    int last_id = query.value(0).toInt();   //获取最后一个单词的编号
    query.prepare("insert into vocabulary (id,word,type,definition,example)values(:id, :word, :type, :definition, :example)");
    query.bindValue(":id",++last_id);
    query.bindValue(":word",ui->lineEdit->text());      //从输入框读取数据
    query.bindValue(":type",ui->lineEdit_2->text());
    query.bindValue(":definition",ui->textEdit->toPlainText());
    query.bindValue(":example",ui->textEdit_2->toPlainText());
    query.exec();      //先准备插入数据，存在缓存区中，再执行对数据库的操作
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

void Attribute::on_pushButton_clicked()   //保存按钮的槽函数
{
    QString input = ui->lineEdit->text();
    if(input.isEmpty())      //判断是否有输入单词
    {
        QMessageBox::warning(this,"保存失败","请输入单词！",QMessageBox::Yes);
        return;
    }

    QSqlQuery query;     //打开数据库
    query.prepare("select * from vocabulary where word = :word ");   //判断输入的单词是否已经存在
    query.bindValue(":word",ui->lineEdit->text());
    query.exec();
    if(query.next())
    {
        QMessageBox::warning(this,"保存失败","该单词已经存在！",QMessageBox::Yes);
        return;
    }
    save();
    emit refresh();
    this->reject();
}
