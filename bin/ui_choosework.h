/********************************************************************************
** Form generated from reading UI file 'choosework.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEWORK_H
#define UI_CHOOSEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_choosework
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_name;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableView *list_of_variants;
    QComboBox *comboBox_of_works;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *button_cancel_work;
    QPushButton *button_accept_work;

    void setupUi(QDialog *choosework)
    {
        if (choosework->objectName().isEmpty())
            choosework->setObjectName(QString::fromUtf8("choosework"));
        choosework->resize(500, 372);
        gridLayout = new QGridLayout(choosework);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(choosework);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_name = new QLineEdit(choosework);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setMinimumSize(QSize(0, 30));
        lineEdit_name->setFont(font);

        horizontalLayout->addWidget(lineEdit_name);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(choosework);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        list_of_variants = new QTableView(choosework);
        list_of_variants->setObjectName(QString::fromUtf8("list_of_variants"));
        list_of_variants->setFont(font);

        verticalLayout->addWidget(list_of_variants);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        comboBox_of_works = new QComboBox(choosework);
        comboBox_of_works->addItem(QString());
        comboBox_of_works->setObjectName(QString::fromUtf8("comboBox_of_works"));
        comboBox_of_works->setFont(font);

        gridLayout->addWidget(comboBox_of_works, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(30);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        button_cancel_work = new QPushButton(choosework);
        button_cancel_work->setObjectName(QString::fromUtf8("button_cancel_work"));
        button_cancel_work->setMinimumSize(QSize(100, 40));
        button_cancel_work->setFont(font);

        horizontalLayout_2->addWidget(button_cancel_work);

        button_accept_work = new QPushButton(choosework);
        button_accept_work->setObjectName(QString::fromUtf8("button_accept_work"));
        button_accept_work->setMinimumSize(QSize(100, 40));
        button_accept_work->setFont(font);

        horizontalLayout_2->addWidget(button_accept_work);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 1);


        retranslateUi(choosework);

        QMetaObject::connectSlotsByName(choosework);
    } // setupUi

    void retranslateUi(QDialog *choosework)
    {
        choosework->setWindowTitle(QApplication::translate("choosework", "Dialog", nullptr));
        label->setText(QApplication::translate("choosework", "\320\230\320\274\321\217 (\320\275\320\265 \320\276\320\261\321\217\320\267\320\260\321\202\320\265\320\273\321\214\320\275\320\276):", nullptr));
        lineEdit_name->setText(QString());
        label_2->setText(QApplication::translate("choosework", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202\321\213:", nullptr));
        comboBox_of_works->setItemText(0, QApplication::translate("choosework", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\200\320\260\320\261\320\276\321\202\321\203", nullptr));

        button_cancel_work->setText(QApplication::translate("choosework", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        button_accept_work->setText(QApplication::translate("choosework", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choosework: public Ui_choosework {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEWORK_H
