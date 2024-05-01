#include "codetab.h"
#include "ui_codetab.h"

CodeTab::CodeTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CodeTab)
{
    ui->setupUi(this);
}

CodeTab::~CodeTab()
{
    delete ui;
}
