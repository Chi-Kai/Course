#include<QApplication>
#include"mainwindow.h"

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    MainWindow WoShark;
    if (WoShark.opendev)
     {
        WoShark.show();
        app.exec();
     }
    else return 1;

}
