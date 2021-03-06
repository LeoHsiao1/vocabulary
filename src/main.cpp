#include "mainwindow.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
ver2.0更新记录（有些遗漏）：

2017.6.4
实现排序功能
搜索改为模糊搜索
设置了按刷新后0.1秒才显示，像刷新文件夹一样
增加的方法改为弹出一个窗口来输入
增加的快捷键改成了ctrl + s
登录界面改为由主界面的云团点击后打开
搜索按钮改为一个放大镜，其它功能按钮也由文字改成了图案
实现了修改的功能，双击单词或按按钮都会弹出修改框

2017.6.5
增加单词后会自动刷新
设置了没有选中单词时按删除和修改键都会提示没有选中单词
（以后可以把打地鼠游戏加进来，改成显示单词点击释义的游戏）
（以后把删除时改成先弹出确认删除的对话框）
因为提示也会被设置了背景图片，所以没有给按钮增加鼠标移上去的提示
编辑的快捷键设置成了Enter
把自定义窗界面的代码另存成了MyWindow类，在主窗口中继承
*/
