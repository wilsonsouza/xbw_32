/********************************************************************************
** Form generated from reading UI file 'xbw32.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XBW32_H
#define UI_XBW32_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xbw32Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *xbw32Class)
    {
        if (xbw32Class->objectName().isEmpty())
            xbw32Class->setObjectName(QStringLiteral("xbw32Class"));
        xbw32Class->resize(600, 400);
        menuBar = new QMenuBar(xbw32Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        xbw32Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(xbw32Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        xbw32Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(xbw32Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        xbw32Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(xbw32Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        xbw32Class->setStatusBar(statusBar);

        retranslateUi(xbw32Class);

        QMetaObject::connectSlotsByName(xbw32Class);
    } // setupUi

    void retranslateUi(QMainWindow *xbw32Class)
    {
        xbw32Class->setWindowTitle(QApplication::translate("xbw32Class", "xbw32", nullptr));
    } // retranslateUi

};

namespace Ui {
    class xbw32Class: public Ui_xbw32Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XBW32_H
