/********************************************************************************
** Form generated from reading UI file 'textwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTWINDOW_H
#define UI_TEXTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_usercodewindow
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *text_user_code;

    void setupUi(QDialog *usercodewindow)
    {
        if (usercodewindow->objectName().isEmpty())
            usercodewindow->setObjectName(QString::fromUtf8("usercodewindow"));
        usercodewindow->resize(442, 506);
        usercodewindow->setMinimumSize(QSize(300, 300));
        verticalLayout = new QVBoxLayout(usercodewindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        text_user_code = new QTextBrowser(usercodewindow);
        text_user_code->setObjectName(QString::fromUtf8("text_user_code"));
        text_user_code->setFrameShape(QFrame::Box);
        text_user_code->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout->addWidget(text_user_code);


        retranslateUi(usercodewindow);

        QMetaObject::connectSlotsByName(usercodewindow);
    } // setupUi

    void retranslateUi(QDialog *usercodewindow)
    {
        usercodewindow->setWindowTitle(QApplication::translate("usercodewindow", "Dialog", nullptr));
#ifndef QT_NO_TOOLTIP
        usercodewindow->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        usercodewindow->setWhatsThis(QApplication::translate("usercodewindow", "<html><head/><body><p>\320\237\321\200\320\270\320\262\320\265\321\202 \320\276\321\202 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\321\207\320\270\320\272\320\276\320\262</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class usercodewindow: public Ui_usercodewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTWINDOW_H
