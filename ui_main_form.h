/********************************************************************************
** Form generated from reading UI file 'main_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_FORM_H
#define UI_MAIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *importPushButton;
    QPushButton *startPushButton;

    void setupUi(QDialog *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(303, 74);
        horizontalLayout = new QHBoxLayout(MainForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        importPushButton = new QPushButton(MainForm);
        importPushButton->setObjectName(QString::fromUtf8("importPushButton"));

        verticalLayout->addWidget(importPushButton);

        startPushButton = new QPushButton(MainForm);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));
        startPushButton->setEnabled(false);

        verticalLayout->addWidget(startPushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QDialog *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \342\204\2263", nullptr));
        importPushButton->setText(QCoreApplication::translate("MainForm", "\320\230\320\274\320\277\320\276\321\200\321\202 \320\262\321\205\320\276\320\264\320\275\321\213\321\205 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        startPushButton->setText(QCoreApplication::translate("MainForm", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_FORM_H
