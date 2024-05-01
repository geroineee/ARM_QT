#include "tabwidget.h"
#include "ui_tabwidget.h"

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent), ui(new Ui::TabWidget)
{
    ui->setupUi(this);
    QTabWidget mainTabWidget;

//    mainTabWidget.addTab()
}

TabWidget::~TabWidget()
{
    delete ui;
}
