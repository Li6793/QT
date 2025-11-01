/********************************************************************************
** Form generated from reading UI file 'clementine.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLEMENTINE_H
#define UI_CLEMENTINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Clementine
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Clementine)
    {
        if (Clementine->objectName().isEmpty())
            Clementine->setObjectName("Clementine");
        Clementine->resize(800, 600);
        centralwidget = new QWidget(Clementine);
        centralwidget->setObjectName("centralwidget");
        Clementine->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Clementine);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        Clementine->setMenuBar(menubar);
        statusbar = new QStatusBar(Clementine);
        statusbar->setObjectName("statusbar");
        Clementine->setStatusBar(statusbar);

        retranslateUi(Clementine);

        QMetaObject::connectSlotsByName(Clementine);
    } // setupUi

    void retranslateUi(QMainWindow *Clementine)
    {
        Clementine->setWindowTitle(QCoreApplication::translate("Clementine", "Clementine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Clementine: public Ui_Clementine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEMENTINE_H
