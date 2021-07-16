#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include<QThread>
#include"head.h"
#include"mainwindow.h"
#include<QDebug>
#include<QMutex>

class MainWindow;
class capturethread:public QThread
{
Q_OBJECT

public:
    capturethread():QThread(){}
    bool isrun = 1;
    MainWindow* mainwindow;
    virtual void run();

private:

QMutex m_lock;

};

#endif // CAPTURETHREAD_H
