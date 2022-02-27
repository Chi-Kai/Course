#ifndef ARPATTACK_H
#define ARPATTACK_H

#include "head.h"
#include "ui_arp.h"

class arpattack :  public QWidget,public Ui::arpForm
{
    Q_OBJECT

public:
    arpattack(QWidget* par = 0) {}

    void attack();

private slots:

    void on_start_clicked();

private:

    u_char* src_ip;
    u_char* src_mac;

};

#endif // ARPATTACK_H
