#include "mainwindow.h"
#include "head.h"
#include <QMessageBox>
#include<QStringList>
#include"capturethread.h"
#include<QDebug>

u_int eth_len = sizeof(struct eth_hd);
u_int ip_len = sizeof(struct ip_hd);
u_int tcp_len = sizeof(struct tcp_hd);
u_int udp_len = sizeof(struct udp_hd);


MainWindow::MainWindow(QWidget* par)
 : QMainWindow(par)
{

    pcap_if_t* alldevs;

    QStringList devlist;

    setupUi(this);
    // init table

    /*
    tableWidget->resizeColumnToContents(1);
    tableWidget->resizeColumnToContents(2);
    tableWidget->resizeColumnToContents(3);
    tableWidget->resizeRowToContents(1);
    tableWidget->resizeRowToContents(2);
    tableWidget->resizeRowToContents(3);
    */

    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // init treewidget

    treeWidget->setHeaderHidden(true);

    // init device
    if (pcap_findalldevs(&alldevs,errBuf) == -1)
    {
        QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
        return;
    }


    for (pcap_if_t* dv = alldevs;dv;dv = dv->next)
    {
        devlist<<dv->name;
        dev_list.push_back(dv);
    }

    devcomboBox->addItems(devlist);
    devcomboBox->setCurrentIndex(0);


    pdev = alldevs;
    opendev = pcap_open_live(pdev->name,byte,allfitter,time,errBuf);
    if ( !opendev )
    {
        QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
        return;
    }

    startButton->setEnabled(true);
  //  textEdit->setEnabled(false);

    connect(startButton,SIGNAL(clicked()),this,SLOT(on_startButton_clicked()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(on_stopButton_clicked()));
    connect(tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(on_singleitem_click()));
    connect(actionClear,SIGNAL(triggered()),this,SLOT(on_actioneclear_triggered()));

    connect(actionarp,SIGNAL(triggered()),this,SLOT( on_actionarp_triggered()));
    connect(devcomboBox,SIGNAL( currentIndexChanged(int)),SLOT(on_comboBox_changed()) );

    // !

    capthread = new capturethread;
    capthread->mainwindow = this;

   // connect(capthread,&QThread::finished ,this,&QObject::deleteLater);


}

MainWindow::~MainWindow()
{
    delete capthread;

    for (unsigned i = 0;i <packet_list.size();++i)
    {
        delete [] packet_list[i]; //!
    }

}

void MainWindow::on_startButton_clicked()
{

    QString fitler = lineEdit->text();
    bpf_program bpf_p;

    if (pcap_compile(opendev,&bpf_p,fitler.toLatin1()
                     ,0,0) == -1)
    {
        QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
        return;
    }

    if (pcap_setfilter(opendev,&bpf_p) == -1)
    {
        QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
        return;
    }

    lineEdit->setEnabled(false);
    devcomboBox->setEnabled(false);

    capthread->isrun = 1;
    capthread->start();


    startButton->setEnabled(false);
    startButton->setText("Runing");
    stopButton->setEnabled(true);


}

void MainWindow::on_stopButton_clicked()
{
    capthread->isrun = 0;
    capthread->quit();
    capthread->wait();
    refresh_table();

    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    startButton->setText("Start");
    lineEdit->setEnabled(true);
    devcomboBox->setEnabled(true);



 //   refresh_table();

}

 void MainWindow::on_comboBox_changed()
 {
   int curindex = devcomboBox->currentIndex();
   pdev = dev_list[curindex];
   opendev = pcap_open_live(pdev->name,byte,allfitter,time,errBuf);
   if ( !opendev )
   {
       QMessageBox::critical(this,"Error",QString("Error ")+errBuf);
       return;
   }
   tableWidget->clearContents();
   tableWidget->setRowCount(0);
   treeWidget->clear();
   textEdit->clear();
   pkthdr_list.clear();
   packet_list.clear();
 //  pkthdr_list.swap( std::vector <pcap_pkthdr>());
   std::vector <pcap_pkthdr>().swap(pkthdr_list);
   std::vector <const u_char*>().swap(packet_list);


 }




void MainWindow::on_singleitem_click(){

    treeWidget->clear();
    //QTreeWidgetItem* frame=new QTreeWidgetItem(treeWidget);
    int row=tableWidget->currentRow();


    // Frame
    QTreeWidgetItem* frame = new QTreeWidgetItem(treeWidget);
    frame->setText(0,QString("Frame %1: %2 bytes on wire (%3 bits), %4 bytes captured (%5 bits) on interface %6")
                 .arg(row).arg(pkthdr_list[row].len).arg(pkthdr_list[row].len*8).arg(pkthdr_list[row].caplen)
                  .arg(pkthdr_list[row].caplen*8).arg(pdev->name));
    QTreeWidgetItem* fra = new QTreeWidgetItem(frame);
    fra->setText(0,QString("interface: %1").arg(pdev->name));
    fra = new QTreeWidgetItem(frame);
    fra->setText(0,QString("time: %1").arg(pkthdr_list[row].ts.tv_usec));
    fra = new QTreeWidgetItem(frame);
    fra->setText(0,QString("Length: %1").arg(pkthdr_list[row].len));
    fra = new QTreeWidgetItem(frame);
    fra->setText(0,QString("capture len: %1").arg(pkthdr_list[row].caplen));

    // ethernet II
    char tmp[20];
    QString a;
    struct eth_hd* eth = (eth_hd*) packet_list[row];
    QTreeWidgetItem* ethernet = new QTreeWidgetItem(treeWidget);
    ethernet->setText(0,QString("ethernet II"));
    QTreeWidgetItem* ethitem = new QTreeWidgetItem(ethernet);
    sprintf(tmp,"%02x-%02x-%02x-%02x-%02x-%02x",eth->src_mac[0],eth->src_mac[1],eth->src_mac[2],eth->src_mac[3],eth->src_mac[4],eth->src_mac[5]);
    ethitem->setText(0,QString("Source MAC : %1").arg(a + tmp));

    ethitem = new QTreeWidgetItem(ethernet);
    sprintf(tmp,"%02x-%02x-%02x-%02x-%02x-%02x",eth->dst_mac[0],eth->dst_mac[1],eth->dst_mac[2],eth->dst_mac[3],eth->dst_mac[4],eth->dst_mac[5]);
    ethitem->setText(0,QString("Destination : %1").arg(a + tmp));


    u_short pro = ntohs(eth->eth_type);
    switch (pro)
       {
          case 0x0800:
              a = "IPV4";
              parse_ip(packet_list[row]);
              break;
          case 0x86DD:
              a = "IPV6";
              break;
          case 0x0806:
              a = "ARP protocol";
              parse_arp(packet_list[row]);
              break;
          case 0x8035:
              a = "RARP protocol";
              break;
          case 0x880B:
              a = "PPP protocol";
              break;
          default:
              a = "Other Network Layer protocol is used";
              break;
       }

    ethitem = new QTreeWidgetItem(ethernet);
    ethitem->setText(0,QString("Type : %1").arg(a));


    textEdit->clear();
    const u_char* packet_content = packet_list[row];
    QString content;
    char cont[10];
    for (uint i = 0;i < pkthdr_list[row].caplen;i ++) {
         sprintf(cont," %02x",packet_content[i]);
         content += cont;
         if ((i+1)%16 == 0) { sprintf(cont,"\n"); content += cont;textEdit->append(content);}
         }
}

void MainWindow::on_actioneclear_triggered()
{

  tableWidget->clearContents();
  tableWidget->setRowCount(0);
  treeWidget->clear();
  textEdit->clear();
  pkthdr_list.clear();
  packet_list.clear();
//  pkthdr_list.swap( std::vector <pcap_pkthdr>());
  std::vector <pcap_pkthdr>().swap(pkthdr_list);
  std::vector <const u_char*>().swap(packet_list);

}


void MainWindow::on_actionarp_triggered()
{
    ARP* arp = new ARP(pdev->name);

    arp->showNormal();
}


void MainWindow::refresh_table()
{


    int table_size = tableWidget->rowCount();
    int pack_count = packet_list.size();

    if (table_size == pack_count) return;

    tableWidget->setRowCount(pack_count);

    char buf[30];

    for (;table_size < pack_count; table_size++)
    {
        tableWidget->setItem(table_size,0,new QTableWidgetItem(QString::number(table_size)));

        tm* time = localtime(&pkthdr_list[table_size].ts.tv_sec);
        sprintf(buf,"%02d:%02d:%02d",time->tm_hour,time->tm_min,time->tm_sec);

        tableWidget->setItem(table_size,1,new QTableWidgetItem(buf+QString::number(pkthdr_list[table_size].ts.tv_usec)));
        tableWidget->setItem(table_size,6,new QTableWidgetItem(QString::number(pkthdr_list[table_size].len)));

        QString space;
        ip_hd* ip = (ip_hd*)(packet_list[table_size]+eth_len);
        sprintf(buf,"%d.%d.%d.%d",ip->srcIP[0],ip->srcIP[1],ip->srcIP[2],ip->srcIP[3]);
        tableWidget->setItem(table_size,2,new QTableWidgetItem(buf + space));
        sprintf(buf,"%d.%d.%d.%d",ip->dstIP[0],ip->dstIP[1],ip->dstIP[2],ip->dstIP[3]);
        tableWidget->setItem(table_size,4,new QTableWidgetItem(buf + space));

        u_char protocl = ip->protocol;

        QString ptl;


        if (protocl == 0x01) ptl = "ICMP";
        else if (protocl == 0x06)
        {
            ptl = "TCP";

            struct tcp_hd* tcp = (tcp_hd*) (packet_list[table_size]+eth_len+ip_len);

            tableWidget->setItem(table_size,3,new QTableWidgetItem(QString::number(tcp->sport)));
            tableWidget->setItem(table_size,5,new QTableWidgetItem(QString::number(tcp->dport)));

        }

        else if (protocl == 0x11)
        {

            ptl = "UDP";
            struct udp_hd* udp = (udp_hd*) (packet_list[table_size] + eth_len + ip_len);

            tableWidget->setItem(table_size,3,new QTableWidgetItem(QString::number(udp->sport)));
            tableWidget->setItem(table_size,5,new QTableWidgetItem(QString::number(udp->dport)));

        }
        else
        {
            struct eth_hd* eth = (eth_hd*) packet_list[table_size];
            u_short pro = ntohs(eth->eth_type);
            switch (pro)
               {
                  case 0x0800:
                     ptl  = "IPV4";

                      break;
                  case 0x86DD:
                      ptl = "IPV6";
                      break;
                  case 0x0806:
                      ptl = "ARP";

                      break;
                  case 0x8035:
                      ptl = "RARP";
                      break;
                  case 0x880B:
                      ptl = "PPP";
                      break;
                  default:
                      ptl = "Other Network Layer protocol is used";
                      break;
               }

        }

        tableWidget->setItem(table_size,7,new QTableWidgetItem(ptl));
        tableWidget->scrollToBottom();
    }

}


void MainWindow::parse_ip(const u_char* packet)
{
    struct ip_hd* ip = (ip_hd*)(packet+eth_len);
    QTreeWidgetItem* ipv4 = new QTreeWidgetItem(treeWidget);
    ipv4->setText(0,QString("IPV4"));

    QTreeWidgetItem* item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("Total Length: %1").arg(ip->total_len));
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("TOS : %1").arg(ip->tos));
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("ID : %1").arg(ip->id));
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("TTL : %1").arg(ip->ttl));
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("Checksum : %1").arg(ip->checksum));
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("TOS : %1").arg(ip->tos));

    QString space;
    char buf[30];

    sprintf(buf,"%d.%d.%d.%d",ip->srcIP[0],ip->srcIP[1],ip->srcIP[2],ip->srcIP[3]);
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("Source IP : ") + space+buf);
    sprintf(buf,"%d.%d.%d.%d",ip->dstIP[0],ip->dstIP[1],ip->dstIP[2],ip->dstIP[3]);
    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("Destination IP : ") + space+buf);

    item = new QTreeWidgetItem(ipv4);
    item->setText(0,QString("Protocol : %1").arg(ip->protocol));

    if (ip->protocol  == 0x06) parse_tcp(packet);
    else if (ip->protocol == 0x11) parse_udp(packet);

}

void MainWindow::parse_arp(const u_char* packet)
{
    arp_hd* arp = (arp_hd*)(packet + eth_len);
    QTreeWidgetItem* net = new QTreeWidgetItem(treeWidget);
    net->setText(0,QString("ARP"));

    QTreeWidgetItem* item = new QTreeWidgetItem(net);
    item->setText(0,QString("Hardware : %1").arg(arp->arp_hrd));
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Protocol : %1").arg(arp->arp_pro));
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Hardware Address Length : %1").arg(arp->arp_hdlen));
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Protocol Length: %1").arg(arp->arp_prolen));
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Operations : %1").arg(arp->arp_op));

    QString space;
    char buf[30];

    sprintf(buf,"%d.%d.%d.%d",arp->arp_sip[0],arp->arp_sip[1],arp->arp_sip[2],arp->arp_sip[3]);
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Source IP : ") + space+buf);

    sprintf(buf,"%02x-%02x-%02x-%02x-%02x-%02x",arp->arp_shost[0],arp->arp_shost[1],arp->arp_shost[2],arp->arp_shost[3],arp->arp_shost[4],arp->arp_shost[5]);
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Source MAC : %1").arg(space + buf));


    sprintf(buf,"%d.%d.%d.%d",arp->arp_dip[0],arp->arp_dip[1],arp->arp_dip[2],arp->arp_dip[3]);
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Destination IP : ") + space+buf);

    sprintf(buf,"%02x-%02x-%02x-%02x-%02x-%02x",arp->arp_dhost[0],arp->arp_dhost[1],arp->arp_dhost[2],arp->arp_dhost[3],arp->arp_dhost[4],arp->arp_dhost[5]);
    item = new QTreeWidgetItem(net);
    item->setText(0,QString("Destination MAC : %1").arg(space + buf));

}

void MainWindow::parse_tcp(const u_char* packet)
{
    struct tcp_hd* tcp = (tcp_hd*)(packet+eth_len+ip_len);
    QTreeWidgetItem* tran = new QTreeWidgetItem(treeWidget);
    tran->setText(0,QString("TCP"));

    QTreeWidgetItem* item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Source Port : %1").arg(tcp->sport));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Destination Port : %1").arg(tcp->dport));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Seq : %1").arg(tcp->seq));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("ACK : %1").arg(tcp->ack));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Header Length : %1").arg(tcp->header_len));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Flags : %1").arg(tcp->flags));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Window Size : %1").arg(tcp->win_size));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Checksum : %1").arg(tcp->checksum));

}


void MainWindow::parse_udp(const u_char* packet)
{

    struct udp_hd* udp = (udp_hd*)(packet + eth_len + ip_len);
    QTreeWidgetItem* tran = new QTreeWidgetItem(treeWidget);
    tran->setText(0,QString("UDP"));

    QTreeWidgetItem* item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Source Port : %1").arg(udp->sport));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Destination Port : %1").arg(udp->dport));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Checksum : %1").arg(udp->checksum));
    item = new QTreeWidgetItem(tran);
    item->setText(0,QString("Total Length : %1").arg(udp->total_len));

}


