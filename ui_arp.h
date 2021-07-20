/********************************************************************************
** Form generated from reading UI file 'arp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARP_H
#define UI_ARP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_arpForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *srciplineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *srcmaclineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *dstiplineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *dstmaclineEdit;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *numlineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *arpForm)
    {
        if (arpForm->objectName().isEmpty())
            arpForm->setObjectName(QString::fromUtf8("arpForm"));
        arpForm->resize(506, 596);
        arpForm->setMinimumSize(QSize(506, 596));
        arpForm->setMaximumSize(QSize(506, 596));
        gridLayout = new QGridLayout(arpForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(arpForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout->addWidget(label);

        srciplineEdit = new QLineEdit(arpForm);
        srciplineEdit->setObjectName(QString::fromUtf8("srciplineEdit"));
        srciplineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 14, 78);\n"
"font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout->addWidget(srciplineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(arpForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_2->addWidget(label_2);

        srcmaclineEdit = new QLineEdit(arpForm);
        srcmaclineEdit->setObjectName(QString::fromUtf8("srcmaclineEdit"));
        srcmaclineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 14, 78);\n"
"font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_2->addWidget(srcmaclineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(arpForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_3->addWidget(label_3);

        dstiplineEdit = new QLineEdit(arpForm);
        dstiplineEdit->setObjectName(QString::fromUtf8("dstiplineEdit"));
        dstiplineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 14, 78);\n"
"font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_3->addWidget(dstiplineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(arpForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_4->addWidget(label_4);

        dstmaclineEdit = new QLineEdit(arpForm);
        dstmaclineEdit->setObjectName(QString::fromUtf8("dstmaclineEdit"));
        dstmaclineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 14, 78);\n"
"font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_4->addWidget(dstmaclineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        textBrowser = new QTextBrowser(arpForm);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setStyleSheet(QString::fromUtf8("\n"
"font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        numlineEdit = new QLineEdit(arpForm);
        numlineEdit->setObjectName(QString::fromUtf8("numlineEdit"));
        QFont font;
        font.setFamily(QString::fromUtf8("Font Awesome 5 Free"));
        font.setPointSize(12);
        numlineEdit->setFont(font);

        horizontalLayout_5->addWidget(numlineEdit);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton = new QPushButton(arpForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("font: 81 italic 14pt \"JetBrainsMonoExtraBold Nerd Font Mono\";"));

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(arpForm);

        QMetaObject::connectSlotsByName(arpForm);
    } // setupUi

    void retranslateUi(QWidget *arpForm)
    {
        arpForm->setWindowTitle(QCoreApplication::translate("arpForm", "ARPAttack", nullptr));
        label->setText(QCoreApplication::translate("arpForm", "Src  IP", nullptr));
        label_2->setText(QCoreApplication::translate("arpForm", "Src  MAC", nullptr));
        label_3->setText(QCoreApplication::translate("arpForm", "Dst  IP", nullptr));
        dstiplineEdit->setText(QString());
        label_4->setText(QCoreApplication::translate("arpForm", "Dst MAC", nullptr));
        dstmaclineEdit->setText(QString());
        numlineEdit->setText(QCoreApplication::translate("arpForm", "Times", nullptr));
        pushButton->setText(QCoreApplication::translate("arpForm", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class arpForm: public Ui_arpForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARP_H
