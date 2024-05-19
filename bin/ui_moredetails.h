/********************************************************************************
** Form generated from reading UI file 'moredetails.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOREDETAILS_H
#define UI_MOREDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_moredetails
{
public:
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser_task;
    QFormLayout *formLayout;
    QLabel *label_status;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser_input_data;
    QTextBrowser *textBrowser_expected_output;
    QTextBrowser *textBrowser_output_data;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_ok;

    void setupUi(QDialog *moredetails)
    {
        if (moredetails->objectName().isEmpty())
            moredetails->setObjectName(QString::fromUtf8("moredetails"));
        moredetails->resize(672, 653);
        gridLayout_2 = new QGridLayout(moredetails);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textBrowser_task = new QTextBrowser(moredetails);
        textBrowser_task->setObjectName(QString::fromUtf8("textBrowser_task"));
        QFont font;
        font.setPointSize(10);
        textBrowser_task->setFont(font);
        textBrowser_task->setFrameShape(QFrame::Box);

        gridLayout_2->addWidget(textBrowser_task, 0, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_status = new QLabel(moredetails);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, label_status);

        label = new QLabel(moredetails);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        gridLayout_2->addLayout(formLayout, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser_input_data = new QTextBrowser(moredetails);
        textBrowser_input_data->setObjectName(QString::fromUtf8("textBrowser_input_data"));
        textBrowser_input_data->setFont(font);
        textBrowser_input_data->setFrameShape(QFrame::Box);

        gridLayout->addWidget(textBrowser_input_data, 0, 0, 1, 1);

        textBrowser_expected_output = new QTextBrowser(moredetails);
        textBrowser_expected_output->setObjectName(QString::fromUtf8("textBrowser_expected_output"));
        textBrowser_expected_output->setFont(font);
        textBrowser_expected_output->setFrameShape(QFrame::Box);

        gridLayout->addWidget(textBrowser_expected_output, 0, 2, 1, 1);

        textBrowser_output_data = new QTextBrowser(moredetails);
        textBrowser_output_data->setObjectName(QString::fromUtf8("textBrowser_output_data"));
        textBrowser_output_data->setFont(font);
        textBrowser_output_data->setFrameShape(QFrame::Box);

        gridLayout->addWidget(textBrowser_output_data, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button_ok = new QPushButton(moredetails);
        button_ok->setObjectName(QString::fromUtf8("button_ok"));
        button_ok->setMinimumSize(QSize(120, 30));
        button_ok->setFont(font);

        horizontalLayout->addWidget(button_ok);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 2, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 50);
        gridLayout_2->setRowStretch(2, 50);

        retranslateUi(moredetails);

        QMetaObject::connectSlotsByName(moredetails);
    } // setupUi

    void retranslateUi(QDialog *moredetails)
    {
        moredetails->setWindowTitle(QApplication::translate("moredetails", "Dialog", nullptr));
        label_status->setText(QApplication::translate("moredetails", "\320\260", nullptr));
        label->setText(QApplication::translate("moredetails", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        button_ok->setText(QApplication::translate("moredetails", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class moredetails: public Ui_moredetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOREDETAILS_H
