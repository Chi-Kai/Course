/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionstart;
    QAction *actionstop;
    QAction *actionarp;
    QAction *actionchange;
    QAction *actionquit;
    QAction *actionOpen;
    QAction *actionClear;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *startButton;
    QPushButton *stopButton;
    QComboBox *devcomboBox;
    QTableWidget *tableWidget;
    QTreeWidget *treeWidget;
    QTextBrowser *textEdit;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menudevice;
    QMenu *menuattack;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1085, 783);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionstart = new QAction(MainWindow);
        actionstart->setObjectName(QString::fromUtf8("actionstart"));
        actionstop = new QAction(MainWindow);
        actionstop->setObjectName(QString::fromUtf8("actionstop"));
        actionarp = new QAction(MainWindow);
        actionarp->setObjectName(QString::fromUtf8("actionarp"));
        QFont font;
        font.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        actionarp->setFont(font);
        actionchange = new QAction(MainWindow);
        actionchange->setObjectName(QString::fromUtf8("actionchange"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font Mono"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        actionchange->setFont(font1);
        actionquit = new QAction(MainWindow);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        actionquit->setFont(font);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setFont(font1);
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font Mono"));
        font2.setPointSize(12);
        actionClear->setFont(font2);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("JetBrainsMono Nerd Font Mono"));
        font3.setPointSize(12);
        font3.setItalic(true);
        lineEdit->setFont(font3);

        horizontalLayout->addWidget(lineEdit);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(false);
        QFont font4;
        font4.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font"));
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setWeight(75);
        startButton->setFont(font4);

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setEnabled(false);
        stopButton->setFont(font4);

        horizontalLayout->addWidget(stopButton);

        devcomboBox = new QComboBox(layoutWidget);
        devcomboBox->setObjectName(QString::fromUtf8("devcomboBox"));
        QFont font5;
        font5.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font Mono"));
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setWeight(75);
        devcomboBox->setFont(font5);

        horizontalLayout->addWidget(devcomboBox);

        splitter->addWidget(layoutWidget);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QFont font6;
        font6.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font"));
        font6.setPointSize(14);
        font6.setBold(true);
        font6.setItalic(true);
        font6.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font6);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font6);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font7;
        font7.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font Mono"));
        font7.setPointSize(14);
        font7.setBold(true);
        font7.setItalic(true);
        font7.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font7);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font7);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font6);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font7);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font7);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font7);
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("JetBrainsMonoExtraBold Nerd Font"));
        font8.setPointSize(11);
        font8.setBold(false);
        font8.setItalic(true);
        font8.setWeight(10);
        tableWidget->setFont(font8);
        tableWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(160, 203, 255);\n"
"font: 81 italic 11pt \"JetBrainsMonoExtraBold Nerd Font\";"));
        splitter->addWidget(tableWidget);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QFont font9;
        font9.setFamily(QString::fromUtf8("JetBrainsMonoMedium Nerd Font Mono"));
        font9.setPointSize(14);
        font9.setBold(false);
        font9.setItalic(true);
        font9.setWeight(7);
        treeWidget->setFont(font9);
        treeWidget->setStyleSheet(QString::fromUtf8("font: 57 italic 14pt \"JetBrainsMonoMedium Nerd Font Mono\";"));
        splitter->addWidget(treeWidget);
        textEdit = new QTextBrowser(splitter);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(300, 0));
        textEdit->setFont(font9);
        textEdit->setStyleSheet(QString::fromUtf8("font: 57 italic 14pt \"JetBrainsMonoMedium Nerd Font Mono\";"));
        splitter->addWidget(textEdit);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1085, 36));
        QFont font10;
        font10.setFamily(QString::fromUtf8("JetBrainsMonoMedium Nerd Font Mono"));
        font10.setPointSize(14);
        menuBar->setFont(font10);
        menudevice = new QMenu(menuBar);
        menudevice->setObjectName(QString::fromUtf8("menudevice"));
        menuattack = new QMenu(menuBar);
        menuattack->setObjectName(QString::fromUtf8("menuattack"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menudevice->menuAction());
        menuBar->addAction(menuattack->menuAction());
        menudevice->addAction(actionchange);
        menudevice->addAction(actionOpen);
        menudevice->addAction(actionClear);
        menudevice->addAction(actionquit);
        menuattack->addAction(actionarp);

        retranslateUi(MainWindow);
        QObject::connect(actionquit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionstart->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        actionstop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        actionarp->setText(QCoreApplication::translate("MainWindow", "arp", nullptr));
        actionchange->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionquit->setText(QCoreApplication::translate("MainWindow", "quit", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "filter", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Src IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Src Port", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Dst IP", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Dst Port", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Length", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Protocol", nullptr));
        menudevice->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuattack->setTitle(QCoreApplication::translate("MainWindow", "Attack", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
