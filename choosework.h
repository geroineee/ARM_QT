#ifndef CHOOSEWORK_H
#define CHOOSEWORK_H

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
class choosework;
}

class choosework : public QDialog
{
    Q_OBJECT

public:
    explicit choosework(QSqlDatabase& database, QWidget *parent = nullptr);
    ~choosework();

private slots:
    void on_comboBox_of_works_currentIndexChanged(int index);
    void on_button_cancel_work_clicked();

    void on_button_accept_work_clicked();

private:
    Ui::choosework *ui;

    QSqlDatabase& m_database;
    QSqlTableModel* db_model_var;

    void closeEvent(QCloseEvent *evnt);

    QVector<QVariantList> labs;

signals:
    void send_id(int id_lab, int id_var);
};

#endif // CHOOSEWORK_H
