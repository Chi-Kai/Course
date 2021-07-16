#include"capturethread.h"
#include"head.h"


void capturethread::run()
{
    struct pcap_pkthdr*   tmp_head;
    const u_char*         tmp_packet; // !
    QString err;
    while(1)
    {

        QMutexLocker locker(&m_lock); if(!isrun) return;
        int flag = pcap_next_ex(mainwindow->opendev,&tmp_head,&tmp_packet);
        if (flag == 1){

            u_char* head_content = new  uchar[tmp_head->len];
            memcpy(head_content,tmp_packet,tmp_head->len);
            mainwindow->pkthdr_list.push_back(*tmp_head);
            mainwindow->packet_list.push_back(head_content);
        }


        else if(flag == 0){
            err = "time out";
            break;
        }
        else {
            err = "error";
            break;
        }
       mainwindow->refresh_table();

    }


}
