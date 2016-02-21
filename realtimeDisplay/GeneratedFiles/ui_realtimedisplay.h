/********************************************************************************
** Form generated from reading UI file 'realtimedisplay.ui'
**
** Created: Sun Feb 21 15:13:09 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEDISPLAY_H
#define UI_REALTIMEDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_realtimeDisplayClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *realtimeDisplayClass)
    {
        if (realtimeDisplayClass->objectName().isEmpty())
            realtimeDisplayClass->setObjectName(QString::fromUtf8("realtimeDisplayClass"));
        realtimeDisplayClass->resize(769, 602);
        centralWidget = new QWidget(realtimeDisplayClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 22);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 19);
        verticalLayout_2->setStretch(2, 3);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 3);
        realtimeDisplayClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(realtimeDisplayClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 769, 23));
        realtimeDisplayClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(realtimeDisplayClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        realtimeDisplayClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(realtimeDisplayClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        realtimeDisplayClass->setStatusBar(statusBar);

        retranslateUi(realtimeDisplayClass);

        QMetaObject::connectSlotsByName(realtimeDisplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *realtimeDisplayClass)
    {
        realtimeDisplayClass->setWindowTitle(QApplication::translate("realtimeDisplayClass", "realtimeDisplay", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("realtimeDisplayClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("realtimeDisplayClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class realtimeDisplayClass: public Ui_realtimeDisplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEDISPLAY_H
