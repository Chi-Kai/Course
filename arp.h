#ifndef ARP_H
#define ARP_H

#include "head.h"
#include <QWidget>
#include "ui_arp.h"
#include "mainwindow.h"

class MainWindow;
class ARP: public QWidget,public Ui::arpForm
{
    Q_OBJECT
public:

    ARP(QWidget* par = 0);
    void attack();

private slots:

    void on_start_clicked();

private:
    char* src_ip = NULL;
    char* src_mac = NULL;
    char* dst_ip = NULL;
    char* dst_mac = NULL;

    char errBuf[LIBNET_ERRBUF_SIZE];
    libnet_t* net_t = NULL;

    int sendtimes;
public:

    MainWindow*  mainwindow;

};

#endif // ARP_H
