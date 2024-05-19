#ifndef MOREDETAILS_H
#define MOREDETAILS_H

#include <QDialog>
#include <QCloseEvent>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QResizeEvent>
#include <QDebug>
#include <QVector>
#include <QCloseEvent>

namespace Ui {
class moredetails;
}

class moredetails : public QDialog
{
    Q_OBJECT

public:
    explicit moredetails(QSqlDatabase& database, QWidget *parent = nullptr, int test_id = 0);
    ~moredetails();

private slots:
    void on_button_ok_clicked();

private:
    Ui::moredetails *ui;

    QSqlDatabase& m_database;

};

#endif // MOREDETAILS_H
