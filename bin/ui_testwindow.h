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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testwindow
{
public:
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page_task;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPlainTextEdit *TextEdit_lab_desc;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_lab_name;
    QSpacerItem *verticalSpacer;
    QPushButton *button_cancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_add_variant;
    QWidget *page_variant;
    QPushButton *button_back_to_edie_test;

    void setupUi(QDialog *testwindow)
    {
        if (testwindow->objectName().isEmpty())
            testwindow->setObjectName(QString::fromUtf8("testwindow"));
        testwindow->resize(800, 600);
        testwindow->setMinimumSize(QSize(300, 300));
        gridLayout_2 = new QGridLayout(testwindow);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(20, 20, 20, 20);
        stackedWidget = new QStackedWidget(testwindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_task = new QWidget();
        page_task->setObjectName(QString::fromUtf8("page_task"));
        gridLayout_3 = new QGridLayout(page_task);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, -1, -1);
        label_2 = new QLabel(page_task);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(10);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        TextEdit_lab_desc = new QPlainTextEdit(page_task);
        TextEdit_lab_desc->setObjectName(QString::fromUtf8("TextEdit_lab_desc"));
        QFont font1;
        font1.setPointSize(12);
        TextEdit_lab_desc->setFont(font1);

        gridLayout->addWidget(TextEdit_lab_desc, 2, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(page_task);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_lab_name = new QLineEdit(page_task);
        lineEdit_lab_name->setObjectName(QString::fromUtf8("lineEdit_lab_name"));
        lineEdit_lab_name->setMinimumSize(QSize(0, 30));
        lineEdit_lab_name->setFont(font1);

        horizontalLayout->addWidget(lineEdit_lab_name);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer, 3, 2, 1, 1);

        button_cancel = new QPushButton(page_task);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));
        button_cancel->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(button_cancel, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(300, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 1);

        button_add_variant = new QPushButton(page_task);
        button_add_variant->setObjectName(QString::fromUtf8("button_add_variant"));
        button_add_variant->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(button_add_variant, 4, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        stackedWidget->addWidget(page_task);
        page_variant = new QWidget();
        page_variant->setObjectName(QString::fromUtf8("page_variant"));
        button_back_to_edie_test = new QPushButton(page_variant);
        button_back_to_edie_test->setObjectName(QString::fromUtf8("button_back_to_edie_test"));
        button_back_to_edie_test->setGeometry(QRect(60, 480, 80, 40));
        button_back_to_edie_test->setMinimumSize(QSize(0, 40));
        stackedWidget->addWidget(page_variant);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(testwindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(testwindow);
    } // setupUi

    void retranslateUi(QDialog *testwindow)
    {
        testwindow->setWindowTitle(QApplication::translate("testwindow", "Dialog", nullptr));
        label_2->setText(QApplication::translate("testwindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QApplication::translate("testwindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\200\320\260\320\261\320\276\321\202\321\213:", nullptr));
        lineEdit_lab_name->setText(QString());
        button_cancel->setText(QApplication::translate("testwindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        button_add_variant->setText(QApplication::translate("testwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\260\321\200\320\270\320\260\320\275\321\202", nullptr));
        button_back_to_edie_test->setText(QApplication::translate("testwindow", "\320\235\320\260\320\267\320\260\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testwindow: public Ui_testwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
