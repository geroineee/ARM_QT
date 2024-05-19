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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testwindow
{
public:
    QGridLayout *gridLayout_4;
    QStackedWidget *stackedWidget;
    QWidget *page_task;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_lab_name;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QTableView *list_variants;
    QPushButton *button_save_lab;
    QVBoxLayout *verticalLayout;
    QPushButton *button_edit_variant;
    QPushButton *button_delete_variant;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_add_variant;
    QPlainTextEdit *TextEdit_lab_desc;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *button_cancel_lab;
    QWidget *page_variant;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_number_variant;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QPushButton *button_cancel_variants;
    QPlainTextEdit *TextEdit_variant;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *button_edit_tests;
    QPushButton *button_delete_tests;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *button_add_tests;
    QPushButton *button_save_variant;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_4;
    QTableView *list_of_tests;
    QSpacerItem *horizontalSpacer_3;
    QWidget *page_tests;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_6;
    QStackedWidget *stacked_widget_modes;
    QWidget *page_code_mode;
    QGridLayout *gridLayout_7;
    QPlainTextEdit *user_code_text_edit;
    QLabel *label_insert_code;
    QPushButton *upload_user_code_button;
    QWidget *page_file_mode;
    QGridLayout *gridLayout_8;
    QListWidget *list_files;
    QPushButton *button_get_files;
    QPushButton *button_compile_file;
    QGridLayout *gridLayout_9;
    QLabel *label_input_data;
    QPlainTextEdit *to_user_output_data;
    QPlainTextEdit *user_input_data;
    QPushButton *button_switch_mode;
    QLabel *label_output_data;
    QPushButton *button_test_append;
    QPushButton *button_cancel;

    void setupUi(QDialog *testwindow)
    {
        if (testwindow->objectName().isEmpty())
            testwindow->setObjectName(QString::fromUtf8("testwindow"));
        testwindow->resize(800, 600);
        testwindow->setMinimumSize(QSize(300, 300));
        gridLayout_4 = new QGridLayout(testwindow);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        stackedWidget = new QStackedWidget(testwindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_task = new QWidget();
        page_task->setObjectName(QString::fromUtf8("page_task"));
        gridLayout_3 = new QGridLayout(page_task);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(page_task);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        lineEdit_lab_name = new QLineEdit(page_task);
        lineEdit_lab_name->setObjectName(QString::fromUtf8("lineEdit_lab_name"));
        lineEdit_lab_name->setMinimumSize(QSize(0, 30));
        lineEdit_lab_name->setFont(font);

        horizontalLayout->addWidget(lineEdit_lab_name);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        label_2 = new QLabel(page_task);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        list_variants = new QTableView(page_task);
        list_variants->setObjectName(QString::fromUtf8("list_variants"));

        gridLayout->addWidget(list_variants, 4, 0, 1, 1);

        button_save_lab = new QPushButton(page_task);
        button_save_lab->setObjectName(QString::fromUtf8("button_save_lab"));
        button_save_lab->setMinimumSize(QSize(130, 40));

        gridLayout->addWidget(button_save_lab, 9, 4, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        button_edit_variant = new QPushButton(page_task);
        button_edit_variant->setObjectName(QString::fromUtf8("button_edit_variant"));
        button_edit_variant->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(button_edit_variant);

        button_delete_variant = new QPushButton(page_task);
        button_delete_variant->setObjectName(QString::fromUtf8("button_delete_variant"));
        button_delete_variant->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(button_delete_variant);

        horizontalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(horizontalSpacer_2);

        button_add_variant = new QPushButton(page_task);
        button_add_variant->setObjectName(QString::fromUtf8("button_add_variant"));
        button_add_variant->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(button_add_variant);


        gridLayout->addLayout(verticalLayout, 4, 1, 1, 1);

        TextEdit_lab_desc = new QPlainTextEdit(page_task);
        TextEdit_lab_desc->setObjectName(QString::fromUtf8("TextEdit_lab_desc"));
        TextEdit_lab_desc->setFont(font);
        TextEdit_lab_desc->setFrameShape(QFrame::Box);

        gridLayout->addWidget(TextEdit_lab_desc, 2, 0, 1, 5);

        label_3 = new QLabel(page_task);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout->addItem(verticalSpacer, 4, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 2, 1, 1);

        button_cancel_lab = new QPushButton(page_task);
        button_cancel_lab->setObjectName(QString::fromUtf8("button_cancel_lab"));
        button_cancel_lab->setMinimumSize(QSize(130, 40));

        gridLayout->addWidget(button_cancel_lab, 9, 3, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        stackedWidget->addWidget(page_task);
        page_variant = new QWidget();
        page_variant->setObjectName(QString::fromUtf8("page_variant"));
        gridLayout_5 = new QGridLayout(page_variant);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(page_variant);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_2->addWidget(label_4);

        label_number_variant = new QLabel(page_variant);
        label_number_variant->setObjectName(QString::fromUtf8("label_number_variant"));
        label_number_variant->setFont(font);

        horizontalLayout_2->addWidget(label_number_variant);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 5);

        label_5 = new QLabel(page_variant);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        button_cancel_variants = new QPushButton(page_variant);
        button_cancel_variants->setObjectName(QString::fromUtf8("button_cancel_variants"));
        button_cancel_variants->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(button_cancel_variants, 10, 2, 1, 1);

        TextEdit_variant = new QPlainTextEdit(page_variant);
        TextEdit_variant->setObjectName(QString::fromUtf8("TextEdit_variant"));
        TextEdit_variant->setFont(font);
        TextEdit_variant->setFrameShape(QFrame::Box);

        gridLayout_2->addWidget(TextEdit_variant, 3, 0, 1, 5);

        verticalSpacer_3 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_2->addItem(verticalSpacer_3, 5, 4, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        button_edit_tests = new QPushButton(page_variant);
        button_edit_tests->setObjectName(QString::fromUtf8("button_edit_tests"));
        button_edit_tests->setMinimumSize(QSize(118, 40));

        verticalLayout_3->addWidget(button_edit_tests);

        button_delete_tests = new QPushButton(page_variant);
        button_delete_tests->setObjectName(QString::fromUtf8("button_delete_tests"));
        button_delete_tests->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(button_delete_tests);

        horizontalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(horizontalSpacer_4);

        button_add_tests = new QPushButton(page_variant);
        button_add_tests->setObjectName(QString::fromUtf8("button_add_tests"));
        button_add_tests->setMinimumSize(QSize(0, 40));

        verticalLayout_3->addWidget(button_add_tests);


        gridLayout_2->addLayout(verticalLayout_3, 5, 1, 1, 1);

        button_save_variant = new QPushButton(page_variant);
        button_save_variant->setObjectName(QString::fromUtf8("button_save_variant"));
        button_save_variant->setMinimumSize(QSize(130, 40));

        gridLayout_2->addWidget(button_save_variant, 10, 3, 1, 2);

        label_6 = new QLabel(page_variant);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 4, 1, 1, 1);

        list_of_tests = new QTableView(page_variant);
        list_of_tests->setObjectName(QString::fromUtf8("list_of_tests"));
        list_of_tests->setMinimumSize(QSize(350, 0));

        gridLayout_2->addWidget(list_of_tests, 5, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(300, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 5, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);

        stackedWidget->addWidget(page_variant);
        page_tests = new QWidget();
        page_tests->setObjectName(QString::fromUtf8("page_tests"));
        gridLayout_10 = new QGridLayout(page_tests);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, -1, -1, 0);
        stacked_widget_modes = new QStackedWidget(page_tests);
        stacked_widget_modes->setObjectName(QString::fromUtf8("stacked_widget_modes"));
        page_code_mode = new QWidget();
        page_code_mode->setObjectName(QString::fromUtf8("page_code_mode"));
        gridLayout_7 = new QGridLayout(page_code_mode);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        user_code_text_edit = new QPlainTextEdit(page_code_mode);
        user_code_text_edit->setObjectName(QString::fromUtf8("user_code_text_edit"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        user_code_text_edit->setFont(font1);
        user_code_text_edit->setFrameShape(QFrame::Box);
        user_code_text_edit->setLineWrapMode(QPlainTextEdit::NoWrap);
        user_code_text_edit->setTabStopWidth(10000);

        gridLayout_7->addWidget(user_code_text_edit, 1, 0, 1, 2);

        label_insert_code = new QLabel(page_code_mode);
        label_insert_code->setObjectName(QString::fromUtf8("label_insert_code"));
        QFont font2;
        font2.setPointSize(10);
        label_insert_code->setFont(font2);

        gridLayout_7->addWidget(label_insert_code, 0, 0, 1, 1);

        upload_user_code_button = new QPushButton(page_code_mode);
        upload_user_code_button->setObjectName(QString::fromUtf8("upload_user_code_button"));
        upload_user_code_button->setMinimumSize(QSize(0, 30));
        upload_user_code_button->setFont(font2);

        gridLayout_7->addWidget(upload_user_code_button, 2, 0, 1, 2);

        stacked_widget_modes->addWidget(page_code_mode);
        page_file_mode = new QWidget();
        page_file_mode->setObjectName(QString::fromUtf8("page_file_mode"));
        gridLayout_8 = new QGridLayout(page_file_mode);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(-1, 39, -1, -1);
        list_files = new QListWidget(page_file_mode);
        list_files->setObjectName(QString::fromUtf8("list_files"));
        QFont font3;
        font3.setPointSize(13);
        list_files->setFont(font3);

        gridLayout_8->addWidget(list_files, 0, 0, 1, 1);

        button_get_files = new QPushButton(page_file_mode);
        button_get_files->setObjectName(QString::fromUtf8("button_get_files"));
        button_get_files->setMinimumSize(QSize(0, 30));
        button_get_files->setFont(font2);

        gridLayout_8->addWidget(button_get_files, 1, 0, 1, 1);

        button_compile_file = new QPushButton(page_file_mode);
        button_compile_file->setObjectName(QString::fromUtf8("button_compile_file"));
        button_compile_file->setMinimumSize(QSize(0, 30));
        button_compile_file->setFont(font2);

        gridLayout_8->addWidget(button_compile_file, 2, 0, 1, 1);

        stacked_widget_modes->addWidget(page_file_mode);

        gridLayout_6->addWidget(stacked_widget_modes, 0, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(7);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(-1, 11, -1, 11);
        label_input_data = new QLabel(page_tests);
        label_input_data->setObjectName(QString::fromUtf8("label_input_data"));
        label_input_data->setFont(font2);

        gridLayout_9->addWidget(label_input_data, 0, 0, 1, 1);

        to_user_output_data = new QPlainTextEdit(page_tests);
        to_user_output_data->setObjectName(QString::fromUtf8("to_user_output_data"));
        to_user_output_data->setFont(font2);
        to_user_output_data->setFrameShape(QFrame::Box);
        to_user_output_data->setFrameShadow(QFrame::Sunken);
        to_user_output_data->setLineWidth(1);
        to_user_output_data->setMidLineWidth(0);

        gridLayout_9->addWidget(to_user_output_data, 3, 0, 1, 1);

        user_input_data = new QPlainTextEdit(page_tests);
        user_input_data->setObjectName(QString::fromUtf8("user_input_data"));
        user_input_data->setFont(font2);
        user_input_data->setFrameShape(QFrame::Box);
        user_input_data->setLineWrapMode(QPlainTextEdit::NoWrap);

        gridLayout_9->addWidget(user_input_data, 1, 0, 1, 1);

        button_switch_mode = new QPushButton(page_tests);
        button_switch_mode->setObjectName(QString::fromUtf8("button_switch_mode"));
        button_switch_mode->setMinimumSize(QSize(0, 30));
        button_switch_mode->setFont(font2);

        gridLayout_9->addWidget(button_switch_mode, 4, 0, 1, 1);

        label_output_data = new QLabel(page_tests);
        label_output_data->setObjectName(QString::fromUtf8("label_output_data"));
        label_output_data->setFont(font2);

        gridLayout_9->addWidget(label_output_data, 2, 0, 1, 1);

        button_test_append = new QPushButton(page_tests);
        button_test_append->setObjectName(QString::fromUtf8("button_test_append"));
        button_test_append->setMinimumSize(QSize(0, 30));
        button_test_append->setFont(font2);

        gridLayout_9->addWidget(button_test_append, 5, 0, 1, 1);

        button_cancel = new QPushButton(page_tests);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));
        button_cancel->setMinimumSize(QSize(0, 30));
        button_cancel->setFont(font2);

        gridLayout_9->addWidget(button_cancel, 6, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_9, 0, 1, 1, 1);

        gridLayout_6->setColumnStretch(0, 70);

        gridLayout_10->addLayout(gridLayout_6, 0, 0, 1, 1);

        stackedWidget->addWidget(page_tests);

        gridLayout_4->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(testwindow);

        stackedWidget->setCurrentIndex(0);
        stacked_widget_modes->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(testwindow);
    } // setupUi

    void retranslateUi(QDialog *testwindow)
    {
        testwindow->setWindowTitle(QApplication::translate("testwindow", "Dialog", nullptr));
        label->setText(QApplication::translate("testwindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\200\320\260\320\261\320\276\321\202\321\213:", nullptr));
        lineEdit_lab_name->setText(QString());
        label_2->setText(QApplication::translate("testwindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        button_save_lab->setText(QApplication::translate("testwindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        button_edit_variant->setText(QApplication::translate("testwindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        button_delete_variant->setText(QApplication::translate("testwindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        button_add_variant->setText(QApplication::translate("testwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\260\321\200\320\270\320\260\320\275\321\202", nullptr));
        label_3->setText(QApplication::translate("testwindow", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202\321\213", nullptr));
        button_cancel_lab->setText(QApplication::translate("testwindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label_4->setText(QApplication::translate("testwindow", "\320\222\320\260\321\200\320\270\320\260\320\275\321\202 \342\204\226", nullptr));
        label_number_variant->setText(QApplication::translate("testwindow", "-1", nullptr));
        label_5->setText(QApplication::translate("testwindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\262\320\260\321\200\320\270\320\260\320\275\321\202\320\260", nullptr));
        button_cancel_variants->setText(QApplication::translate("testwindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        button_edit_tests->setText(QApplication::translate("testwindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        button_delete_tests->setText(QApplication::translate("testwindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        button_add_tests->setText(QApplication::translate("testwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        button_save_variant->setText(QApplication::translate("testwindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_6->setText(QApplication::translate("testwindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        user_code_text_edit->setPlainText(QString());
        label_insert_code->setText(QApplication::translate("testwindow", "\320\222\320\260\321\210 \320\272\320\276\320\264:", nullptr));
        upload_user_code_button->setText(QApplication::translate("testwindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        button_get_files->setText(QApplication::translate("testwindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", nullptr));
        button_compile_file->setText(QApplication::translate("testwindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_input_data->setText(QApplication::translate("testwindow", "\320\222\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        button_switch_mode->setText(QApplication::translate("testwindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \321\204\320\260\320\271\320\273\320\260\320\274\320\270", nullptr));
        label_output_data->setText(QApplication::translate("testwindow", "\320\222\321\213\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        button_test_append->setText(QApplication::translate("testwindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        button_cancel->setText(QApplication::translate("testwindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testwindow: public Ui_testwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
