#include "modify.h"
#include "ui_modify.h"

Modify::Modify(QWidget *parent) :
    MyDialog(parent),   //QDialog(parent),
    ui(new Ui::Modify)
{
    ui->setupUi(this);

    Connection();
}

Modify::~Modify()
{
    delete ui;
}

void Modify::Connection()   //打开数据库
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("vocabulary.db");
    if(!db.open()){
        QMessageBox::warning(this,"错误","不能连接到数据库！",QMessageBox::Yes);
    }
    QSqlQuery query;
    query.exec("create table vocabulary (id int PRIMARY KEY,word varchar（30）,type text,definition text,example text)");
}

void Modify::modify(int num)   //显示选中的单词的属性
{
    id = num;
    QSqlQuery query;
    query.prepare(QString("select * from vocabulary where id = %1").arg(id));   //找到指定id的单词，%1是保证值为整数
    //query.bindValue(":id",id);
    query.exec();
    query.next();
    QString word = query.value(1).toString();
    QString type = query.value(2).toString();
    QString definition = query.value(3).toString();
    QString example = query.value(4).toString();
    ui->lineEdit_3->setText(word);
    ui->lineEdit_4->setText(type);
    ui->textEdit_3->setText(definition);
    ui->textEdit_4->setText(example);
    ui->lineEdit_3->setReadOnly(true);      //设置单词对应的输入栏不可编辑
}

void Modify::save()   //更新数据库中的指定项
{
    QSqlQuery query;
    query.prepare(QString("update vocabulary set word = :word, type = :type, "
                  "definition = :definition, example = :example where id = %1").arg(id));
    query.bindValue(":word",ui->lineEdit_3->text());      //从输入框读取数据
    query.bindValue(":type",ui->lineEdit_4->text());
    query.bindValue(":definition",ui->textEdit_3->toPlainText());
    query.bindValue(":example",ui->textEdit_4->toPlainText());
    query.exec();      //先准备插入数据，存在缓存区中，再执行对数据库的操作
}

void Modify::on_pushButton_2_clicked()   //修改按钮的槽函数
{
    save();
    emit refresh_2();
    this->reject();
}
