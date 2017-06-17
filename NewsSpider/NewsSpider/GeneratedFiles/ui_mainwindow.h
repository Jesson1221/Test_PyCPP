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
#include <QtGui/QSpacerItem>
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
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *previousPageLable;
    QWidget *leftPagesWidget;
    QLabel *leftSeparateLable;
    QWidget *centerPagesWidget;
    QLabel *rightSeparateLable;
    QWidget *rightPagesWidget;
    QLabel *nextPageLable;
    QSpacerItem *horizontalSpacer_2;
    QLabel *DiLable;
    QLineEdit *pageLineEdit;
    QLabel *YeLable;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NewsSpiderClass)
    {
        if (NewsSpiderClass->objectName().isEmpty())
            NewsSpiderClass->setObjectName(QString::fromUtf8("NewsSpiderClass"));
        NewsSpiderClass->resize(800, 516);
        centralWidget = new QWidget(NewsSpiderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 30, 189, 22));
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
        newsListWidget->setGeometry(QRect(50, 60, 691, 331));
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 401, 351, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        previousPageLable = new QLabel(layoutWidget1);
        previousPageLable->setObjectName(QString::fromUtf8("previousPageLable"));

        horizontalLayout_2->addWidget(previousPageLable);

        leftPagesWidget = new QWidget(layoutWidget1);
        leftPagesWidget->setObjectName(QString::fromUtf8("leftPagesWidget"));

        horizontalLayout_2->addWidget(leftPagesWidget);

        leftSeparateLable = new QLabel(layoutWidget1);
        leftSeparateLable->setObjectName(QString::fromUtf8("leftSeparateLable"));

        horizontalLayout_2->addWidget(leftSeparateLable);

        centerPagesWidget = new QWidget(layoutWidget1);
        centerPagesWidget->setObjectName(QString::fromUtf8("centerPagesWidget"));

        horizontalLayout_2->addWidget(centerPagesWidget);

        rightSeparateLable = new QLabel(layoutWidget1);
        rightSeparateLable->setObjectName(QString::fromUtf8("rightSeparateLable"));

        horizontalLayout_2->addWidget(rightSeparateLable);

        rightPagesWidget = new QWidget(layoutWidget1);
        rightPagesWidget->setObjectName(QString::fromUtf8("rightPagesWidget"));

        horizontalLayout_2->addWidget(rightPagesWidget);

        nextPageLable = new QLabel(layoutWidget1);
        nextPageLable->setObjectName(QString::fromUtf8("nextPageLable"));

        horizontalLayout_2->addWidget(nextPageLable);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        DiLable = new QLabel(layoutWidget1);
        DiLable->setObjectName(QString::fromUtf8("DiLable"));

        horizontalLayout_2->addWidget(DiLable);

        pageLineEdit = new QLineEdit(layoutWidget1);
        pageLineEdit->setObjectName(QString::fromUtf8("pageLineEdit"));
        pageLineEdit->setMaxLength(32000);

        horizontalLayout_2->addWidget(pageLineEdit);

        YeLable = new QLabel(layoutWidget1);
        YeLable->setObjectName(QString::fromUtf8("YeLable"));

        horizontalLayout_2->addWidget(YeLable);

        NewsSpiderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NewsSpiderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
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
#ifndef QT_NO_TOOLTIP
        previousPageLable->setToolTip(QApplication::translate("NewsSpiderClass", "\344\270\212\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        previousPageLable->setText(QApplication::translate("NewsSpiderClass", "<<", 0, QApplication::UnicodeUTF8));
        leftSeparateLable->setText(QApplication::translate("NewsSpiderClass", "..", 0, QApplication::UnicodeUTF8));
        rightSeparateLable->setText(QApplication::translate("NewsSpiderClass", "..", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        nextPageLable->setToolTip(QApplication::translate("NewsSpiderClass", "\344\270\213\344\270\200\351\241\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        nextPageLable->setText(QApplication::translate("NewsSpiderClass", ">>", 0, QApplication::UnicodeUTF8));
        DiLable->setText(QApplication::translate("NewsSpiderClass", "\347\254\254", 0, QApplication::UnicodeUTF8));
        YeLable->setText(QApplication::translate("NewsSpiderClass", "\351\241\265", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewsSpiderClass: public Ui_NewsSpiderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
