#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    MyWindow(parent),   //QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlQueryModel(ui->tableView); //QSqlTableModel为读写模型,QSqlQueryModel为用来查询的只读模型
    Connection();
    show_vocabulary();

    connect(&d2, SIGNAL(refresh()), this, SLOT(on_pushButton_4_clicked()));     //绑定增加对话框的刷新信号
    connect(&d3, SIGNAL(refresh_2()), this, SLOT(on_pushButton_4_clicked()));  //绑定修改对话框的刷新信号
}

MainWindow::~MainWindow()
{
    db.close();      //关闭数据库
    delete ui;
}

void MainWindow::Connection()   //创建一个数据库来存储单词本
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//添加数据库的连接，连接名默认
    db.setDatabaseName("vocabulary.db");
    if(!db.open()){
        QMessageBox::warning(this,"错误","不能连接到数据库！",QMessageBox::Yes);
    }
    QSqlQuery query;
    query.exec("create table vocabulary (id int PRIMARY KEY,word varchar（30）,type text,definition text,example text)");
}

void MainWindow::show_table()      //设置表格的显示内容和格式
{
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));  //设置tableview的表头
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("单词"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("词性"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("释义"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("例句"));
    ui->tableView->setModel(model);         //Qt中用model/view模式来显示数据，将tableView与存储数据的model关联后才有显示的内容
    ui->tableView->verticalHeader()->setVisible(false);                //隐藏表格的行号
    ui->tableView->hideColumn(0);                                     //隐藏第一列，即id
    ui->tableView->hideColumn(4);                                    //隐藏第四列，即例句
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置选中时为整行选中
    ui->tableView->setColumnWidth(1,100);                             //设置第二列的宽度
    ui->tableView->setColumnWidth(2,100);                            //设置第三列的宽度
    ui->tableView->horizontalHeader()->setStretchLastSection(true); //最后一列自动填充满空间
    //ui->tableView->resizeRowsToContents();                       //所有行根据内容自动调整行高
}

void MainWindow::show_vocabulary()   //显示单词本并计算当前单词总数
{
    QSqlQuery query;
    query.exec("select * from vocabulary order by word asc");   //desc为降序
    model->setQuery(query);   //把从数据库查询到的结果集存到model中
    show_table();
    query.exec("select * from vocabulary ");
    sum=0;
    while(1){
        if(query.next())
            ++sum;
        else
            break;
    }
    ui->label->setText("单词量："+QString::number(sum));
}




void MainWindow::on_pushButton_clicked()   //增加单词到数据库中
{
    d2.show();
    d2.raise();   //只能同时存在一个对话框，再按增加按钮会让对话框显示到最上层
}




void MainWindow::on_pushButton_2_clicked()      //删除某一行数据
{
    QModelIndex index = ui->tableView->currentIndex();      //获取鼠标在tableView中选中的单元格的index即索引
    QModelIndex index_2;   //不知道未选中时currentIndex()的返回值是什么，所以另外新建一个index_2来判断index是否赋值了
    if( index == index_2 )
    {
        QMessageBox::warning(this,"删除失败","没有选中单词！",QMessageBox::Yes);
        return;
    }
    int row = ui->tableView->currentIndex().row();
    int num = index.sibling(row,0).data().toInt();

    QSqlQuery query;
    query.prepare("delete from vocabulary where id = :id");
    query.bindValue(":id",num);
    query.exec();
    show_vocabulary();
    QMessageBox::warning(this,"删除","已删除该单词！",QMessageBox::Yes);
}




void MainWindow::on_pushButton_6_clicked()
{
    QString input = ui->lineEdit->text();
    if(input.isEmpty())      //判断是否有输入查询内容
    {
        QMessageBox::warning(this,"查询失败","请输入要查询的单词！",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from vocabulary where word LIKE :word order by word asc");//搜索以:word开头的所有单词，全字匹配是where word = :word
    query.bindValue(":word",ui->lineEdit->text()+"%");//参考http://www.qtdebug.com/qtbook-db-common/
    query.exec();
    if(!query.next())
    {
        QMessageBox::warning(this,"查询失败","没有查找到该单词！",QMessageBox::Yes);
        return;
    }
    model->setQuery(query);   //重新设置model的内容
    show_table();

}




void MainWindow::on_pushButton_4_clicked()   //刷新，先清空表格，延时后再显示
{
    model->clear();
    show_table();
    MyWindow::delay(100);
    show_vocabulary();
}



void MainWindow::on_checkBox_stateChanged(int state)  //勾选显示单词
{
    if (state == Qt::Checked)   //若处于选中状态，则回到原态
    {
        ui->tableView->showColumn(1);
        show_vocabulary();
        return;
    }
    ui->tableView->hideColumn(1);
}

void MainWindow::on_checkBox_2_stateChanged(int state)  //勾选显示词性和释义
{
    if (state == Qt::Checked)   //若处于选中状态，则回到原态
    {
        ui->tableView->showColumn(2);
        ui->tableView->showColumn(3);
        show_vocabulary();
        return;
    }
    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);
}




void MainWindow::on_pushButton_7_clicked()  //登录按钮的槽函数
{
    d1.show();
    d1.raise();
}

void MainWindow::on_pushButton_3_clicked()   //关闭按钮的槽函数
{
    d1.close();   //设置mainwindow关闭的时候login也关闭
    d2.close();
    d3.close();
}
void MainWindow::on_pushButton_8_clicked()   //修改按钮的槽函数
{
    QModelIndex index = ui->tableView->currentIndex();      //获取鼠标在tableView中选中的单元格的index即索引
    QModelIndex index_2;   //不知道未选中时currentIndex()的返回值是什么，所以另外新建一个index_2来判断index是否赋值了
    if( index == index_2 )
    {
        QMessageBox::warning(this,"修改失败","没有选中单词！",QMessageBox::Yes);
        return;
    }
    int row = ui->tableView->currentIndex().row();
    int num = index.sibling(row,0).data().toInt();
    d3.modify(num);
    d3.show();
    d3.raise();
}

void MainWindow::on_tableView_doubleClicked()  //在表格中双击可以直接打开修改框
{
    on_pushButton_8_clicked();
}
