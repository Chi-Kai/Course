#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <vector>
#include"head.h"
#include"capturethread.h"
#include"arp.h"

class capturethread;
class ARP;

class MainWindow : public QMainWindow,public Ui::MainWindow

{

Q_OBJECT

public:
    MainWindow(QWidget* par = 0);
    ~MainWindow(); //

    void refresh_table();
    void parse_eth(const u_char* packet);
    void parse_ip(const u_char* packet);
    void parse_arp(const u_char* packet);
    void parse_tcp(const u_char* packet);
    void parse_udp(const u_char* packet);



    std::vector<pcap_pkthdr>   pkthdr_list;
    std::vector<const u_char*> packet_list;
    std::vector<pcap_if_t*> dev_list;


private slots:

    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_singleitem_click();
    void on_comboBox_changed();
    void on_actioneclear_triggered();
    void on_actionarp_triggered();

private:


    int byte = 65535;
    int time = 0;
    int allfitter = 1;

public:


    char errBuf[PCAP_ERRBUF_SIZE];
    pcap_if_t * pdev = NULL;
    pcap_t* opendev = NULL;
    capturethread* capthread;
    ARP* arp;

};

#endif // MAINWINDOW_H
