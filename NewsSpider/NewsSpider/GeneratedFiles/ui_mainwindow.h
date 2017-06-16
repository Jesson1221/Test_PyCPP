/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewsSpiderClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QListWidget *newsListWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NewsSpiderClass)
    {
        if (NewsSpiderClass->objectName().isEmpty())
            NewsSpiderClass->setObjectName(QString::fromUtf8("NewsSpiderClass"));
        NewsSpiderClass->resize(583, 522);
        centralWidget = new QWidget(NewsSpiderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(190, 30, 189, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        newsListWidget = new QListWidget(centralWidget);
        newsListWidget->setObjectName(QString::fromUtf8("newsListWidget"));
        newsListWidget->setGeometry(QRect(50, 60, 481, 331));
        NewsSpiderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NewsSpiderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 583, 23));
        NewsSpiderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NewsSpiderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        NewsSpiderClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NewsSpiderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NewsSpiderClass->setStatusBar(statusBar);

        retranslateUi(NewsSpiderClass);

        QMetaObject::connectSlotsByName(NewsSpiderClass);
    } // setupUi

    void retranslateUi(QMainWindow *NewsSpiderClass)
    {
        NewsSpiderClass->setWindowTitle(QApplication::translate("NewsSpiderClass", "NewsSpider", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewsSpiderClass", "\346\220\234\347\264\242\346\226\260\351\227\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewsSpiderClass: public Ui_NewsSpiderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
