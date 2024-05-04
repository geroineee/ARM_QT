/********************************************************************************
** Form generated from reading UI file 'testwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_testwindow
{
public:
    QPushButton *button_cancel;
    QPushButton *button_apply;
    QPlainTextEdit *TextEdit_lab_desc;
    QLineEdit *lineEdit_lab_name;

    void setupUi(QDialog *testwindow)
    {
        if (testwindow->objectName().isEmpty())
            testwindow->setObjectName(QString::fromUtf8("testwindow"));
        testwindow->resize(800, 600);
        button_cancel = new QPushButton(testwindow);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));
        button_cancel->setGeometry(QRect(680, 540, 100, 40));
        button_apply = new QPushButton(testwindow);
        button_apply->setObjectName(QString::fromUtf8("button_apply"));
        button_apply->setGeometry(QRect(560, 540, 100, 40));
        TextEdit_lab_desc = new QPlainTextEdit(testwindow);
        TextEdit_lab_desc->setObjectName(QString::fromUtf8("TextEdit_lab_desc"));
        TextEdit_lab_desc->setGeometry(QRect(50, 90, 691, 191));
        lineEdit_lab_name = new QLineEdit(testwindow);
        lineEdit_lab_name->setObjectName(QString::fromUtf8("lineEdit_lab_name"));
        lineEdit_lab_name->setGeometry(QRect(50, 30, 331, 31));

        retranslateUi(testwindow);

        QMetaObject::connectSlotsByName(testwindow);
    } // setupUi

    void retranslateUi(QDialog *testwindow)
    {
        testwindow->setWindowTitle(QApplication::translate("testwindow", "Dialog", nullptr));
        button_cancel->setText(QApplication::translate("testwindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        button_apply->setText(QApplication::translate("testwindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testwindow: public Ui_testwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
