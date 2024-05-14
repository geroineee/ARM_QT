/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_files;
    QGridLayout *gridLayout_7;
    QTextBrowser *text_input_example;
    QTableWidget *table_result_test;
    QTextBrowser *text_info_task;
    QTextBrowser *text_output_example;
    QPushButton *button_get_task;
    QListWidget *list_selected_files;
    QPushButton *button_start_test;
    QPushButton *button_get_path_files;
    QComboBox *combo_box_example;
    QWidget *tab_edit_task;
    QGridLayout *gridLayout_2;
    QPushButton *button_add_test;
    QPushButton *button_edit_test;
    QPushButton *button_delete_test;
    QSpacerItem *verticalSpacer;
    QTableView *list_tests;
    QWidget *tab_only_code;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QStackedWidget *stacked_widget_modes;
    QWidget *page_code_mode;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *user_code_text_edit;
    QLabel *label_insert_code;
    QPushButton *upload_user_code_button;
    QWidget *page_file_mode;
    QGridLayout *gridLayout_6;
    QListWidget *list_files;
    QPushButton *button_get_files;
    QPushButton *button_compile_file;
    QGridLayout *gridLayout;
    QPushButton *button_switch_mode;
    QLabel *label_output_data;
    QLabel *label_input_data;
    QTextBrowser *to_user_output_data;
    QPlainTextEdit *user_input_data;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setInputMethodHints(Qt::ImhNone);
        MainWindow->setAnimated(true);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab_files = new QWidget();
        tab_files->setObjectName(QString::fromUtf8("tab_files"));
        gridLayout_7 = new QGridLayout(tab_files);
        gridLayout_7->setSpacing(9);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        text_input_example = new QTextBrowser(tab_files);
        text_input_example->setObjectName(QString::fromUtf8("text_input_example"));
        text_input_example->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(text_input_example, 1, 1, 1, 1);

        table_result_test = new QTableWidget(tab_files);
        table_result_test->setObjectName(QString::fromUtf8("table_result_test"));
        table_result_test->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(table_result_test, 4, 0, 1, 1);

        text_info_task = new QTextBrowser(tab_files);
        text_info_task->setObjectName(QString::fromUtf8("text_info_task"));
        text_info_task->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(text_info_task, 0, 0, 3, 1);

        text_output_example = new QTextBrowser(tab_files);
        text_output_example->setObjectName(QString::fromUtf8("text_output_example"));
        text_output_example->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(text_output_example, 2, 1, 1, 1);

        button_get_task = new QPushButton(tab_files);
        button_get_task->setObjectName(QString::fromUtf8("button_get_task"));
        button_get_task->setMinimumSize(QSize(180, 40));

        gridLayout_7->addWidget(button_get_task, 0, 1, 1, 1);

        list_selected_files = new QListWidget(tab_files);
        list_selected_files->setObjectName(QString::fromUtf8("list_selected_files"));
        list_selected_files->setFrameShape(QFrame::Box);

        gridLayout_7->addWidget(list_selected_files, 4, 1, 1, 1);

        button_start_test = new QPushButton(tab_files);
        button_start_test->setObjectName(QString::fromUtf8("button_start_test"));
        button_start_test->setMinimumSize(QSize(180, 40));

        gridLayout_7->addWidget(button_start_test, 5, 0, 1, 1);

        button_get_path_files = new QPushButton(tab_files);
        button_get_path_files->setObjectName(QString::fromUtf8("button_get_path_files"));
        button_get_path_files->setMinimumSize(QSize(180, 40));

        gridLayout_7->addWidget(button_get_path_files, 5, 1, 1, 1);

        combo_box_example = new QComboBox(tab_files);
        combo_box_example->addItem(QString());
        combo_box_example->setObjectName(QString::fromUtf8("combo_box_example"));
        combo_box_example->setMinimumSize(QSize(0, 30));

        gridLayout_7->addWidget(combo_box_example, 3, 1, 1, 1);

        gridLayout_7->setColumnStretch(0, 70);
        tabWidget->addTab(tab_files, QString());
        tab_edit_task = new QWidget();
        tab_edit_task->setObjectName(QString::fromUtf8("tab_edit_task"));
        gridLayout_2 = new QGridLayout(tab_edit_task);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        button_add_test = new QPushButton(tab_edit_task);
        button_add_test->setObjectName(QString::fromUtf8("button_add_test"));
        button_add_test->setMinimumSize(QSize(180, 40));

        gridLayout_2->addWidget(button_add_test, 3, 1, 1, 1);

        button_edit_test = new QPushButton(tab_edit_task);
        button_edit_test->setObjectName(QString::fromUtf8("button_edit_test"));
        button_edit_test->setMinimumSize(QSize(180, 40));

        gridLayout_2->addWidget(button_edit_test, 0, 1, 1, 1);

        button_delete_test = new QPushButton(tab_edit_task);
        button_delete_test->setObjectName(QString::fromUtf8("button_delete_test"));
        button_delete_test->setMinimumSize(QSize(180, 40));

        gridLayout_2->addWidget(button_delete_test, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);

        list_tests = new QTableView(tab_edit_task);
        list_tests->setObjectName(QString::fromUtf8("list_tests"));
        list_tests->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        list_tests->setShowGrid(true);
        list_tests->horizontalHeader()->setCascadingSectionResizes(false);

        gridLayout_2->addWidget(list_tests, 0, 0, 4, 1);

        gridLayout_2->setColumnStretch(0, 70);
        tabWidget->addTab(tab_edit_task, QString());
        tab_only_code = new QWidget();
        tab_only_code->setObjectName(QString::fromUtf8("tab_only_code"));
        tab_only_code->setEnabled(true);
        tab_only_code->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(10);
        tab_only_code->setFont(font);
        tab_only_code->setLayoutDirection(Qt::LeftToRight);
        gridLayout_5 = new QGridLayout(tab_only_code);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, -1, -1, 0);
        stacked_widget_modes = new QStackedWidget(tab_only_code);
        stacked_widget_modes->setObjectName(QString::fromUtf8("stacked_widget_modes"));
        page_code_mode = new QWidget();
        page_code_mode->setObjectName(QString::fromUtf8("page_code_mode"));
        gridLayout_3 = new QGridLayout(page_code_mode);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
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

        gridLayout_3->addWidget(user_code_text_edit, 1, 0, 1, 2);

        label_insert_code = new QLabel(page_code_mode);
        label_insert_code->setObjectName(QString::fromUtf8("label_insert_code"));
        label_insert_code->setFont(font);

        gridLayout_3->addWidget(label_insert_code, 0, 0, 1, 1);

        upload_user_code_button = new QPushButton(page_code_mode);
        upload_user_code_button->setObjectName(QString::fromUtf8("upload_user_code_button"));
        upload_user_code_button->setFont(font);

        gridLayout_3->addWidget(upload_user_code_button, 2, 0, 1, 1);

        stacked_widget_modes->addWidget(page_code_mode);
        page_file_mode = new QWidget();
        page_file_mode->setObjectName(QString::fromUtf8("page_file_mode"));
        gridLayout_6 = new QGridLayout(page_file_mode);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, 39, -1, -1);
        list_files = new QListWidget(page_file_mode);
        list_files->setObjectName(QString::fromUtf8("list_files"));
        QFont font2;
        font2.setPointSize(13);
        list_files->setFont(font2);

        gridLayout_6->addWidget(list_files, 0, 0, 1, 1);

        button_get_files = new QPushButton(page_file_mode);
        button_get_files->setObjectName(QString::fromUtf8("button_get_files"));

        gridLayout_6->addWidget(button_get_files, 1, 0, 1, 1);

        button_compile_file = new QPushButton(page_file_mode);
        button_compile_file->setObjectName(QString::fromUtf8("button_compile_file"));

        gridLayout_6->addWidget(button_compile_file, 2, 0, 1, 1);

        stacked_widget_modes->addWidget(page_file_mode);

        gridLayout_4->addWidget(stacked_widget_modes, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(7);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 11, -1, 11);
        button_switch_mode = new QPushButton(tab_only_code);
        button_switch_mode->setObjectName(QString::fromUtf8("button_switch_mode"));

        gridLayout->addWidget(button_switch_mode, 4, 0, 1, 1);

        label_output_data = new QLabel(tab_only_code);
        label_output_data->setObjectName(QString::fromUtf8("label_output_data"));
        label_output_data->setFont(font);

        gridLayout->addWidget(label_output_data, 2, 0, 1, 1);

        label_input_data = new QLabel(tab_only_code);
        label_input_data->setObjectName(QString::fromUtf8("label_input_data"));
        label_input_data->setFont(font);

        gridLayout->addWidget(label_input_data, 0, 0, 1, 1);

        to_user_output_data = new QTextBrowser(tab_only_code);
        to_user_output_data->setObjectName(QString::fromUtf8("to_user_output_data"));
        to_user_output_data->setFrameShape(QFrame::Box);
        to_user_output_data->setFrameShadow(QFrame::Sunken);
        to_user_output_data->setLineWidth(1);
        to_user_output_data->setMidLineWidth(0);
        to_user_output_data->setLineWrapMode(QTextEdit::NoWrap);

        gridLayout->addWidget(to_user_output_data, 3, 0, 1, 1);

        user_input_data = new QPlainTextEdit(tab_only_code);
        user_input_data->setObjectName(QString::fromUtf8("user_input_data"));
        user_input_data->setFrameShape(QFrame::Box);
        user_input_data->setLineWrapMode(QPlainTextEdit::NoWrap);

        gridLayout->addWidget(user_input_data, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 1, 1, 1);

        gridLayout_4->setColumnStretch(0, 70);
        gridLayout_4->setColumnStretch(1, 30);

        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_only_code, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        stacked_widget_modes->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        button_get_task->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", nullptr));
        button_start_test->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        button_get_path_files->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", nullptr));
        combo_box_example->setItemText(0, QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\277\321\200\320\270\320\274\320\265\321\200", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_files), QApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\320\270\321\200\320\276\320\262\320\276\321\207\320\275\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        tab_edit_task->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        button_add_test->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        button_edit_test->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        button_delete_test->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_edit_task), QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274 \321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        user_code_text_edit->setPlainText(QApplication::translate("MainWindow", "#include <iostream>\n"
"\n"
"using namespace std;\n"
"\n"
"\n"
"int main()\n"
"{\n"
"    string str;\n"
"    cin >> str;\n"
"    int a, b;\n"
"    cin >> a >> b;\n"
"    cout << a + b << endl;\n"
"    cout << str;\n"
"    cout << \"\321\210\320\260\320\273\320\260\320\273\320\260 \320\270\321\206\321\203\320\272\320\260\320\272\320\270\321\202\321\215\";\n"
"    return 0;\n"
"}", nullptr));
        label_insert_code->setText(QApplication::translate("MainWindow", "\320\222\320\260\321\210 \320\272\320\276\320\264:", nullptr));
        upload_user_code_button->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        button_get_files->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\260\320\271\320\273\321\213", nullptr));
        button_compile_file->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        button_switch_mode->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \321\201 \321\204\320\260\320\271\320\273\320\260\320\274\320\270", nullptr));
        label_output_data->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        label_input_data->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_only_code), QApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\272\320\276\320\264\320\260", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
