/********************************************************************************
** Form generated from reading UI file 'realtimedisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEDISPLAY_H
#define UI_REALTIMEDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            realtimeDisplayClass->setObjectName(QStringLiteral("realtimeDisplayClass"));
        realtimeDisplayClass->resize(704, 501);
        centralWidget = new QWidget(realtimeDisplayClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 22);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 18);
        verticalLayout_2->setStretch(2, 4);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 3);
        realtimeDisplayClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(realtimeDisplayClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 704, 21));
        realtimeDisplayClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(realtimeDisplayClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        realtimeDisplayClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(realtimeDisplayClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        realtimeDisplayClass->setStatusBar(statusBar);

        retranslateUi(realtimeDisplayClass);

        QMetaObject::connectSlotsByName(realtimeDisplayClass);
    } // setupUi

    void retranslateUi(QMainWindow *realtimeDisplayClass)
    {
        realtimeDisplayClass->setWindowTitle(QApplication::translate("realtimeDisplayClass", "realtimeDisplay", 0));
        label->setText(QApplication::translate("realtimeDisplayClass", "TextLabel", 0));
        label_2->setText(QApplication::translate("realtimeDisplayClass", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class realtimeDisplayClass: public Ui_realtimeDisplayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEDISPLAY_H
