#ifndef ARP_H
#define ARP_H

#include "head.h"
#include <QWidget>
#include "ui_arp.h"
#include "mainwindow.h"


class ARP: public QWidget,public Ui::arpForm
{
    Q_OBJECT
public:


    ARP(const char* device,QWidget* par = 0) ;

    void attack();

private slots:

    void on_start_clicked();

private:
    char* src_ip ;
    char* src_mac;
    char* dst_ip ;
    char* dst_mac;

    char errBuf[LIBNET_ERRBUF_SIZE];
    libnet_t* net_t = NULL;
    const char* dev;

    int sendtimes;


};

#endif // ARP_H
